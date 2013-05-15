import java.util.*;

class Profile extends Hashtable<String, Integer>{
	String word;
	Profile(String word) {
		this.word = word;
		for (int i = 0; i < word.length(); i++) {
			String letter = word.substring(i,i+1);
			if (this.containsKey(letter)) {
				this.put(letter, this.get(letter)+1);
			} else {
				this.put(letter, 1);
			}
		}
		Enumeration<String> e = this.keys();
		while (e.hasMoreElements()) {
			String letter = e.nextElement();
			System.out.println("There are " + this.get(letter) + " " + letter + "'s");
		}
	}
	public static void main(String[] args) {
		String word = args[0];
		Profile p = new Profile(word);
		System.out.println(p);
	}
}