class Point {
	int x, y;
	Point(int x, int y) {
		this.x = x;
		this.y = y;
	}
	double distanceTo(Point other) {
		return Math.sqrt(Math.pow(this.x - other.x, 2) + Math.pow(this.y - other.y, 2));
	}
}
abstract class Shape {
	Point location;
	Shape(Point where) {
		this.location = where;
	}
	abstract boolean contains(Point spot);
	abstract double area();
	void move(Point to) {
		this.location = to;
	}
}
class Circle extends Shape {
	int radius;
	Circle(Point center, int radius) {
		super(center);
		this.radius = radius;
	}
	double area() {
		return Math.PI * Math.pow(this.radius, 2);
	}
	boolean contains(Point spot) {
		return spot.distanceTo(this.location) <= this.radius;
	}
}
class Rectangle extends Shape {
	int width, height;
	Rectangle(Point where, int w, int h) {
		super(where);
		this.width = w;
		this.height = h;
	}
	double area() {
		return this.width * this.height;
	}
	boolean contains(Point spot) {
		return this.location.x <= spot.x && spot.x <= this.location.x + this.width &&
		       this.location.y <= spot.y && spot.y <= this.location.y + this.height;
	}
}