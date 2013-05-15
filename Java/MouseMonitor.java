import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

class MouseMonitor implements MouseMotionListener{
	JFrame screen;
	MouseMonitor() {
		this.screen = new JFrame();
		screen.setSize(400,400);
		screen.setVisible(true);
		screen.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		screen.addMouseMotionListener(this);
	}
	
	public void mouseDragged(MouseEvent e) {
		
	}
	public void mouseMoved(MouseEvent e) {
		System.out.println(e.getX() + ", " + e.getY());
	}
	public static void main(String[] args) {
		MouseMonitor m = new MouseMonitor();
	}
}