import java.util.*;

class NewStudent extends HashMap<String, ArrayList<Integer>> {
	String name;
	NewStudent(String name) {
		this.name = name;
	}
	void addQuiz(String course, int score) {
		if (!this.containsKey(course)) {
			this.put(course, new ArrayList<Integer>());
		}
		this.get(course).add(score);
	}
	void report(String course) {
		System.out.println(this.name + ": (" + course + ": " + this.get(course) + ")");
	}
	void report() {
		for (String course : this.keySet()) {
			this.report(course);
		}
	}
	public static void main(String[] args) {
		NewStudent a = new NewStudent("Larry");
		a.addQuiz("Spanish", 91);
		a.addQuiz("Math", 91);
		a.addQuiz("Chemistry", 91);
		a.report();
	}
}