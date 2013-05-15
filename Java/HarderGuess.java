import java.util.*;

class HarderGuess extends NumberGuess {
	void start() {
		int count = 0;
		System.out.println(this.secret);
		System.out.println("-----------");
		Scanner s = new Scanner(System.in);
		System.out.print("Enter guess: ");
		while (count <= 6) {
			this.guess = Integer.parseInt(s.nextLine());
			if (this.guess < this.secret) {
				count++;
				System.out.println(count + " Try higher.");
			} else if (this.guess > this.secret) {
				count++;
				System.out.println(count + " Try lower.");
			} else {
				System.out.println("You guessed it.");
				break;
			}
		}
		System.out.println("You lost.");
	}
	public static void main(String[] args) {
		HarderGuess n = new HarderGuess();
		n.start();
	}
}