import java.util.*;

class NumberGuess {
	Integer secret;
	Integer guess;
	NumberGuess() {
		this.secret = this.generate();
	}
	Integer generate() {
		return (int)((Math.random() * 1000) + 1);
	}
	void start() {
		System.out.println(this.secret);
		System.out.println("-----------");
		Scanner s = new Scanner(System.in);
		System.out.print("Enter guess: ");
		while (true) {
			this.guess = Integer.parseInt(s.nextLine());
			if (this.guess < this.secret) {
				System.out.println("Try higher.");
			} else if (this.guess > this.secret) {
				System.out.println("Try lower.");
			} else {
				System.out.println("You guessed it.");
				break;
			}
		}
	}
	public static void main(String[] args) {
		NumberGuess n = new NumberGuess();
		n.start();
	}
}