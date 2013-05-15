import java.util.*;

class Hangman {
	public static void main(String[] args) {
		String secret = args[0];
		String mask = "";
		for (int i = 0; i < secret.length(); i++) {
			mask += "-";
		}
		Scanner s = new Scanner(System.in);
		while (!mask.equals(secret)) {
			System.out.print(mask + ": ");
			String letter = s.nextLine().substring(0,1);
			String result = "";
			for (int i = 0; i < secret.length(); i++) {
				if (secret.substring(i,i+1).equals(letter)) {
					result += letter;
				} else {
					result += mask.substring(i,i+1);
				}
			}
			mask = result;
		}
	}
}