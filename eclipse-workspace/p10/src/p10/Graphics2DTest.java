package p10;

import java.awt.*; 
import java.awt.geom.*;
import javax.swing.*;

public class Graphics2DTest extends JPanel {
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		// Cast g to Graphics2D
		Graphics2D g2d = (Graphics2D)g;
		
		// Get width and height of the component
		int width = this.getWidth();
		int height = this.getHeight();
		
		//Draw 10 shapes
		int num_shapes = 10;
		double shape_width = (double)width / num_shapes;
		double shape_height = (double)height / num_shapes;
		
		for(int i = 0; i < num_shapes; ++i) {
			// Left upper corner of the shape
			double x = i * shape_width;
			double y = i * shape_height;
			
			// Draw rectangle in red color
			Rectangle2D shape = new Rectangle2D.Double(x, y, shape_width, shape_height);
			g2d.setPaint(Color.red);
			g2d.fill(shape);
		}	
	}

	public static void main(String[] args) {
		JFrame frame = new JFrame();
		frame.setTitle("Basic Shapes");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(640, 480);
		
		// Create a PaintTest instance
		Graphics2DTest panel = new Graphics2DTest();
		
		//Add the panel to the content pane
		frame.add(panel);
		
		frame.setVisible(true);
	}

}
