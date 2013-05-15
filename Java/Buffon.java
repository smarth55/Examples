import java.util.*;

class Buffon {
	public static void main(String[] args) {
	Random generator = new Random();
	double trials = Integer.parseInt(args[0]);
	double hits = 0;
	
	for (int i = 0; i < trials; i++) {
		double low = generator.nextDouble() * 2;
		double angle = Math.sin(generator.nextInt(180));
		if (low + angle >= 2) {
			hits += 1;
		}
	}
	//hits = Integer.doubleValue(hits);
	//trials = Integer.doubleValue(trials);
		
	System.out.println((int)hits);
	System.out.println(trials/hits);
	}
}