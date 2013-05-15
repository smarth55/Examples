import java.util.*;

class MeanAndSd {
	public static void main(String[] args) {
		// create variables for the mean and sd
		Double mean, sd;
		// recieve the list of numbers and put them in an array(list)
		System.out.println("Enter values one at a time. Type 'end' to stop.");
		ArrayList<Double> values = new ArrayList<Double>();
		String value;
		Scanner m = new Scanner(System.in);
		while (true) {
			System.out.println("Enter value: ");
			value = m.nextLine();
			if (value.equals("end")) {
				break;
			} else {
				values.add(Double.parseDouble(value));
			}
		}
		// get the mean and sd and print them out
		System.out.println(values.toString());
		System.out.println("There are " + values.size() + " values.");
		mean = MeanAndSd.mean(values);
		System.out.println("The mean is " + mean);
		sd = MeanAndSd.standardDeviation(values, mean);
		System.out.println("The standard deviation is " + sd);
		
	}
	public static Double mean(ArrayList<Double> values) {
		// create a variable for the total
		Double total = 0.0;
		// iterate through the values and add to the total
		for (int i = 0; i < values.size(); i++) {
			total += values.get(i);
		}
		// return the total devided by the number of values
		return total / values.size();
	}
	public static Double standardDeviation(ArrayList<Double> values, Double mean) {
		// create a variable for the difference
		Double diff = 0.0;
		// iterate though the values and add to the difference the (index minus the mean)^2
		for (int i = 0; i < values.size(); i++) {
			diff += Math.pow((values.get(i) - mean),2);
		}
		// return the sqrt of the difference devided by the length of values minus 1
		return Math.sqrt(diff / values.size() - 1);
	}
}