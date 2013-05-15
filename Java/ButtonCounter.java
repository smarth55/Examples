import java.awt.event.*;
import javax.swing.*;

public class ButtonCounter extends JFrame implements ActionListener {
	JButton button;
	int count;
	ButtonCounter() {
		this.button = new JButton("Hi there!");
		this.setSize(300,300);
		this.add(this.button);
		this.setVisible(true);
		this.button.addActionListener(this);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	public void actionPerformed(ActionEvent e) {
		this.count += 1;
		((JButton)e.getSource()).setText("You have clicked " + this.count + " times.");
	}
	public static void main(String[] args) {
		ButtonCounter a = new ButtonCounter();
	}
}