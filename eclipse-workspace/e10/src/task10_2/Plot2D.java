//15822108 情報テクノロジー　堀田大智
package task10_2;

import javax.swing.JFrame;


public class Plot2D extends JFrame {
	
	// Constructor that takes String window_title
	Plot2D(String window_title){
		
		super(window_title);
		
		//What to do when the window is closed
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				
		// Set the initial window width and height in pixel
		setSize(800, 400);
		
	}
	
	public static void main(String[] args) {
		Matrix points = new Matrix(args[0]);
		
		GraphPanel graphPanel = new GraphPanel(points);
		
		Plot2D frame = new Plot2D("Daichi Hotta");

		frame.add(graphPanel);
		frame.setVisible(true);

	}

}
