import java.util.Random;

class Four {
	public static void main(String[] args) {
		int number = Integer.parseInt(args[0]);
		String command = args[1];
		// initialize coords
		double x1 = 0;
		double y1 = 0;
		double x2 = 0;
		double y2 = 0;
		// initialize distance and steps
		double distance = 0;
		int steps = 0;
		// create a random humber generator
		Random a = new Random();
		
		if (command.equals("away")) {
			while (distance < number) {
				int move = a.nextInt(4); // get random number 0-3
				if (move == 0) {
					y2 += 1; // move north
					steps += 1;
				} else if (move == 1) {
					y2 -= 1; // move south
					steps += 1;
				} else if (move == 2) {
					x2 += 1; // move east
					steps += 1;
				} else {
					x2 -= 1; // move west
					steps += 1;
				}
				double xDiff = x1 - x2;
				double yDiff = y1 - y2;
				distance = (Math.sqrt(xDiff * xDiff + yDiff * yDiff)); // update distance
			}
		} else if (command.equals("steps")) {
			for (int i = 0; i < number; i++) {
				int move = a.nextInt(4); // get random number 0-3
				if (move == 0) {
					y2 += 1; // move north
					steps += 1;
				} else if (move == 1) {
					y2 -= 1; // move south
					steps += 1;
				} else if (move == 2) {
					x2 += 1; // move east
					steps += 1;
				} else {
					x2 -= 1; // move west
					steps += 1;
				}
			}
			double xDiff = x1 - x2;
			double yDiff = y1 - y2;
			distance = (Math.sqrt(xDiff * xDiff + yDiff * yDiff)); //  update distance
			
		}
		System.out.print(distance + " away after; " + steps + " steps taken"); // print results

	}
}