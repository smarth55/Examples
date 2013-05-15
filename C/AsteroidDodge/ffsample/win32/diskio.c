/*-----------------------------------------------------------------------*/
/* Low level disk control module for Win32              (C)ChaN, 2012    */
/*-----------------------------------------------------------------------*/

#include <windows.h>
#include <tchar.h>
#include <winioctl.h>
#include <stdio.h>
#include "diskio.h"
#include "ff.h"


#define MAX_DRIVES	10	/* Max number of physical drives to be used */

#define SZ_RAMDISK	64	/* Size of RAM disk [MB] */
#define SS_RAMDISK	512	/* Sector size of RAM disk [byte] */


/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

#define	BUFSIZE 65536UL	/* Size of data transfer buffer */

typedef struct {
	DSTATUS	status;
	WORD sz_sector;
	DWORD n_sectors;
	HANDLE h_drive;
} STAT;

static HANDLE hMutex, hTmrThread;
static int Drives;

static volatile STAT Stat[MAX_DRIVES];


static DWORD TmrThreadID;

static BYTE *Buffer, *RamDisk;	/* Poiter to the data transfer buffer and ramdisk */


/*-----------------------------------------------------------------------*/
/* Timer Functions                                                       */
/*-----------------------------------------------------------------------*/


DWORD WINAPI tmr_thread (LPVOID parms)
{
	DWORD dw;
	int drv;


	for (;;) {
		Sleep(100);
		for (drv = 1; drv < Drives; drv++) {
			Sleep(1);
			if (Stat[drv].h_drive == INVALID_HANDLE_VALUE || Stat[drv].status & STA_NOINIT || WaitForSingleObject(hMutex, 100) != WAIT_OBJECT_0) continue;

			if (!DeviceIoControl(Stat[drv].h_drive, IOCTL_STORAGE_CHECK_VERIFY, 0, 0, 0, 0, &dw, 0))
				Stat[drv].status |= STA_NOINIT;
			ReleaseMutex(hMutex);
			Sleep(100);
		}
	}
}



int get_status (
	BYTE drv
)
{
	volatile STAT *stat = &Stat[drv];
	HANDLE h = stat->h_drive;
	DISK_GEOMETRY parms;
	DWORD dw;


	if (drv == 0) {	/* RAMDISK */
		stat->sz_sector = SS_RAMDISK;
		stat->n_sectors = SZ_RAMDISK * 0x100000 / SS_RAMDISK;
		stat->status = 0;
		return 1;
	}

	/* Get physical drive parameters */
	if (   !DeviceIoControl(h, IOCTL_STORAGE_CHECK_VERIFY, 0, 0, 0, 0, &dw, 0)
		|| !DeviceIoControl(h, IOCTL_DISK_GET_DRIVE_GEOMETRY, 0, 0, &parms, sizeof parms, &dw, 0)) {
		stat->status = STA_NOINIT;
		return 0;
	}

	stat->sz_sector = (WORD)parms.BytesPerSector;
	if (_MAX_SS == 512 && stat->sz_sector != 512) return 0;
	stat->n_sectors = parms.SectorsPerTrack * parms.TracksPerCylinder * (DWORD)parms.Cylinders.QuadPart; //(DWORD)(part.PartitionLength.QuadPart / parms.BytesPerSector);
	stat->status = DeviceIoControl(h, IOCTL_DISK_IS_WRITABLE, 0, 0, 0, 0, &dw, 0) ? 0 : STA_PROTECT;

	return 1;
}




/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize Windows disk accesss layer                                 */
/*-----------------------------------------------------------------------*/

int assign_drives (void)
{
	BYTE drv;
	TCHAR str[30];
	HANDLE h;
	OSVERSIONINFO vinfo = { sizeof(OSVERSIONINFO) };


	hMutex = CreateMutex(0, 0, 0);
	if (hMutex == INVALID_HANDLE_VALUE) return 0;

	Buffer = VirtualAlloc(0, BUFSIZE, MEM_COMMIT, PAGE_READWRITE);
	if (!Buffer) return 0;

	RamDisk = VirtualAlloc(0, SZ_RAMDISK * 0x100000, MEM_COMMIT, PAGE_READWRITE);
	if (!RamDisk) return 0;

	for (drv = 0; drv < MAX_DRIVES; drv++) {
		if (drv) {
			_stprintf(str, _T("\\\\.\\PhysicalDrive%u"), drv);
			h = CreateFile(str, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, 0);
			if (h == INVALID_HANDLE_VALUE) break;
			Stat[drv].h_drive = h;
		} else {
			_stprintf(str, _T("RAM Disk"));
		}
		_tprintf(_T("Disk# %u <== %s"), drv, str);
		if (get_status(drv))
			_tprintf(_T(" (%uMB, %u bytes * %u sectors)\n"), (UINT)((LONGLONG)Stat[drv].sz_sector * Stat[drv].n_sectors / 1024 / 1024), Stat[drv].sz_sector, Stat[drv].n_sectors);
		else
			_tprintf(_T(" (Not Ready)\n"));
	}

	hTmrThread = CreateThread(0, 0, tmr_thread, 0, 0, &TmrThreadID);
	if (hTmrThread == INVALID_HANDLE_VALUE) drv = 0;

	if (drv > 1) {
		if (GetVersionEx(&vinfo) == FALSE) {
			drv = 0;
		} else {
			if (vinfo.dwMajorVersion > 5) {
				printf( "\nOn the Windows Vista/7, you must unmount all volumes on the physical drive\n"
						"to be accessed prior to start program, or write access to the drive will fail.\n");
			}
		}
	}

	Drives = drv;
	return drv;
}





/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE drv		/* Physical drive nmuber */
)
{
	DSTATUS sta;


	if (WaitForSingleObject(hMutex, 5000) != WAIT_OBJECT_0)
		return STA_NOINIT;

	if (drv >= Drives) {
		sta = STA_NOINIT;
	} else {
		get_status(drv);
		sta = Stat[drv].status;
	}

	ReleaseMutex(hMutex);
	return sta;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0) */
)
{
	DSTATUS sta;


	if (drv >= Drives) {
		sta = STA_NOINIT;
	} else {
		sta = Stat[drv].status;
	}

	return sta;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,			/* Physical drive nmuber (0) */
	BYTE *buff,			/* Pointer to the data buffer to store read data */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
)
{
	DWORD nc, rnc;
	LARGE_INTEGER ofs;
	DSTATUS res;


	if (drv >= Drives || Stat[drv].status & STA_NOINIT || WaitForSingleObject(hMutex, 3000) != WAIT_OBJECT_0)
		return RES_NOTRDY;

//	_tprintf(_T("[R:%d:%d]"), sector, count);
	nc = (DWORD)count * Stat[drv].sz_sector;
	ofs.QuadPart = (LONGLONG)sector * Stat[drv].sz_sector;
	if (drv) {
		if (nc > BUFSIZE) {
			res = RES_PARERR;
		} else {
			if (SetFilePointer(Stat[drv].h_drive, ofs.LowPart, &ofs.HighPart, FILE_BEGIN) != ofs.LowPart) {
				res = RES_ERROR;
			} else {
				if (!ReadFile(Stat[drv].h_drive, Buffer, nc, &rnc, 0) || nc != rnc) {
					res = RES_ERROR;
				} else {
					memcpy(buff, Buffer, nc);
					res = RES_OK;
				}
			}
		}
	} else {
		memcpy(buff, RamDisk + ofs.LowPart, nc);
		res = RES_OK;		
	}

	ReleaseMutex(hMutex);
	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0) */
	const BYTE *buff,	/* Pointer to the data to be written */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
)
{
	DWORD nc, rnc;
	LARGE_INTEGER ofs;
	DRESULT res;


	if (drv >= Drives || Stat[drv].status & STA_NOINIT || WaitForSingleObject(hMutex, 3000) != WAIT_OBJECT_0)
		return RES_NOTRDY;

//	_tprintf(_T("[W:%d:%d]"), sector, count);
	res = RES_OK;
	if (Stat[drv].status & STA_PROTECT) {
		res = RES_WRPRT;
	} else {
		nc = (DWORD)count * Stat[drv].sz_sector;
		if (nc > BUFSIZE)
			res = RES_PARERR;
	}

	ofs.QuadPart = (LONGLONG)sector * Stat[drv].sz_sector;
	if (drv) {
		if (res == RES_OK) {
			if (SetFilePointer(Stat[drv].h_drive, ofs.LowPart, &ofs.HighPart, FILE_BEGIN) != ofs.LowPart) {
				res = RES_ERROR;
			} else {
				memcpy(Buffer, buff, nc);
				if (!WriteFile(Stat[drv].h_drive, Buffer, nc, &rnc, 0) || nc != rnc)
					res = RES_ERROR;
			}
		}
	} else {
		memcpy(RamDisk + ofs.LowPart, buff, nc);
		res = RES_OK;		
	}

	ReleaseMutex(hMutex);
	return res;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive data block */
)
{
	DRESULT res = RES_PARERR;


	if (drv >= Drives || (Stat[drv].status & STA_NOINIT))
		return RES_NOTRDY;

	switch (ctrl) {
	case CTRL_SYNC:
		res = RES_OK;
		break;

	case GET_SECTOR_COUNT:
		*(DWORD*)buff = Stat[drv].n_sectors;
		res = RES_OK;
		break;

	case GET_SECTOR_SIZE:
		*(WORD*)buff = Stat[drv].sz_sector;
		res = RES_OK;
		break;

	case GET_BLOCK_SIZE:
		*(DWORD*)buff = 128;
		res = RES_OK;
		break;

	}

	return res;
}



