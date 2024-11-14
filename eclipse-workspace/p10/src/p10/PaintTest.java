package p10;

import java.awt.*;
import javax.swing.*;

public class PaintTest extends JPanel {
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		// Set color to red
		g.setColor(Color.red);
		
		// Fill the specified rectangle
		g.fillRect(50, 100, 100, 100);
		
		// Draw the outline of the specified rectangle
		g.drawRect(200, 100, 100, 100);
		
		// Set color to black
		g.setColor(Color.black);
		
		//Draw a line between the points (350, 100) and (450, 200)
		g.drawLine(350,  100,  450,  200);
		
		// Set color to gray
		g.setColor(Color.gray);
		
		// Fill an oval bounded by the specified rectangle
		g.fillOval(50,  240,  100,  100);
		
		// Draw the outline of an oval
		g.drawOval(200, 240, 100, 100);
		
		// Set color to green
		g.setColor(Color.green);
		
		// Fill an elliptical arc covering the specified rectangle
		g.fillArc(350, 240, 100, 100, 30, 300);
		
		// Set color to black
		g.setColor(Color.black);
		
		//Draw text
		g.drawString("Welcome to Java graphics.", 10, 20);
	}

	public static void main(String[] args) {
		JFrame frame = new JFrame();
		frame.setTitle("Basic Shapes");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(640, 480);
		
		// Create a PaintTest instance
		PaintTest panel = new PaintTest();
		
		// Add the panel to the content pane
		frame.add(panel);
		
		frame.setVisible(true);

	}

}
