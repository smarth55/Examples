import java.awt.event.*;
import javax.swing.*;

class Input extends JFrame implements KeyListener {
	Input() {
		this.setSize(300,300);
		this.setVisible(true);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.addKeyListener(this);
	}
	public void keyPressed(KeyEvent e) { System.out.println(e); }
	public void keyReleased(KeyEvent e) {}
	public void keyTyped(KeyEvent e) {}
	public static void main(String[] args) {
		Input c = new Input();
	}
}