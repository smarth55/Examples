<!DOCTYPE html>
<html>
<head>
	<title>PHP Test</title>
	<style>
		.red { color:red; }
		.blue {	color:blue; }
		.green { color:green; }
		.black { color:black; }
		.folder	{
			position:relative;
			z-index:5;
			list-style:none;
			max-height:0px;
			opacity:0;
			transition: max-height 0.5s, opacity 0.5s;
			-webkit-transition: max-height 0.5s, opacity 0.5s;
		}
	</style>
	<script>
		function togglefolder(elm) {
			var folder = document.getElementById(elm);
			if (folder.style.maxHeight == "0px" || folder.style.maxHeight == "") {
				folder.style.maxHeight="2000px"; //some large number
				folder.style.opacity="1";
			} else {
				folder.style.maxHeight="0px";
				folder.style.opacity="0";
			}
		}
	</script>
</head>
<body>
	<?php
	function printdata($file) {
		$color = "";
		$current_level = 0;
		while(!feof($file)) {
			list($code, $filename) = preg_split("/ /", fgets($file), -1, PREG_SPLIT_NO_EMPTY);
			$code = trim($code);
			$filename = trim($filename);
			
			// get color
			if ($code[0] === "*") $color = "red";         // deleting
			else if ($code[0] === "c") $color = "blue";   // changed
			else if ($code[0] === "<") $color = "green";  // added
			else $color = "black";
			
			// file or directory
			if ($code[1] === "f" || ($code[0] === "*" && $code[1] === "d")) echo "<li class=\"" . $color . "\">" .basename($filename). "</li>"; // file
			if ($code[1] === "d" && $code[0] !== "*") {
				
				$dir_level = substr_count($filename,"/");
				if ($filename === "./") $dir_level = 0;
				if ($current_level < $dir_level) { 
					printDir($filename,$color);
				} else if ($current_level > $dir_level) {
					echo str_repeat("</ul>",($current_level-$dir_level)+1);
					printDir($filename,$color);
				} else {
					echo "</ul>";
					printDir($filename,$color);
				}
				$current_level = $dir_level;
			}
		}
	}
	function printDir($filename,$color){
		if ($filename !== "./")	$filename = basename($filename);
		echo "<li class=\"".$color."\" style=\"cursor:pointer;position:relative;z-index:100;\" onclick=\"togglefolder('".$filename."')\"> [+]".$filename."</li><ul class=\"folder\" id=\"".$filename."\">";
	}
	?>
	
	<ul>
	updated to use basename()
	<?php
	$file = fopen("rsync_output.txt", "r") or exit("Unable to open file!");
	fgets($file);
	printdata($file);
	fclose($file);
	?>
	</ul>
</body>
</html>
