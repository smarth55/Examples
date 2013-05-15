import java.util.*;

class Squares {
	public static void main(String[] args) {
		int n = Integer.parseInt(args[0]);
		int[][] square = new int[n][n];
		int row = n-1;
		int column = n/2;
		for (int k = 1; k <= n*n ; k++) {
			square[row][column] = k;
			row += 1;
			column += 1;
			if (row == n) row = 0;
			if (column == n) column = 0;
			if (square[row][column] > 0) {
				row -= 2;
				if (row < 0) row += n;
				column -= 1;
				if (column< 0) column += n;
			}
		}
		for (int i = 0; i < n; i++) {
			System.out.println(Arrays.toString(square[i]));
		}
	}
}