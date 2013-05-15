import java.util.*;

class Student {
	Map<String, ArrayList<Integer>> scores;
	String name;
	Student(String name) {
		this.name = name;
		this.scores = new HashMap<String, ArrayList<Integer>>();
	}
	void addQuiz(String course, int score) {
		if (! this.scores.containsKey(course)) {
			this.scores.put(course, new ArrayList<Integer>());
		}
		this.scores.get(course).add(score);
	}
	void report(String course) {
		System.out.println(this.name + ": (" + course + ": " + this.scores.get(course) + ")");
	}
	void report() {
		for (String course : this.scores.keySet()) {
			this.report(course);
		}
	}
	public static void main(String[] args) {
		Student a = new Student("Larry");
		a.addQuiz("Chemistry", 91);
		a.addQuiz("History", 78);
		a.addQuiz("Math", 89);
		a.addQuiz("Chemistry", 91);
		a.addQuiz("Chemistry", 91);
		a.report();
	}
}