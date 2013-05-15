import java.io.File;
import java.util.Scanner;

class LineAndToken {
	public static void main(String[] args) throws Exception {
		String fileName = args[0];
		Scanner s = new Scanner(new File(fileName));
		int lines = 0, tokens = 0;
		while (s.hasNextLine()) {
			String line = s.nextLine();
			lines += 1;
			Scanner t = new Scanner(line);
			while (t.hasNext()) {
				String token = t.next();
				tokens += 1;
			}
		}
		System.out.println("Lines: " + lines + ", tokens: " + tokens);
	}
}