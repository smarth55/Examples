import java.util.*;

class Player implements Comparable<Player>{
	String name;
	int score;
	Player(String name, int score) {
		this.name = name;
		this.score = score;
	}
	public int compareTo(Player other) {
		if (this.score <= 21 && other.score <= 21) {
			return -this.score + other.score;
		} else if (this.score > 21 && other.score > 21) {
			return -other.score + this.score;
		} else if (this.score > 21){
			return 1;
		} else {
			return -1;
		}
	}
	public String toString() {
		return name + " : " + score;
	}
	public static void main(String[] args) {
		ArrayList<Player> players = new ArrayList<Player>();
		for (int i = 0; i < 20; i++) {
			players.add(new Player("Player" + i, 10 + i));
		}
		Collections.sort(players);
		System.out.println(players);
	}
}