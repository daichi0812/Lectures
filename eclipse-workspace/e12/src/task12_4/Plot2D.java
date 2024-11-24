//15822108 情報テクノロジー　堀田大智
package task12_4;

import javax.swing.JFrame;


public class Plot2D extends JFrame {
	
	// Constructor that takes String window_title
	Plot2D(String window_title, double x1, double x2, int division){
		
		super(window_title);
		
		//What to do when the window is closed
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				
		// Set the initial window width and height in pixel
		// change window size 600x600
		setSize(600, 600);
		
		//GraphPanel インスタンスの作成
		GraphPanel graphPanel = new GraphPanel(x1, x2, division);
		add(graphPanel);
	}
	
	public static void main(String[] args) {
		if(args.length != 3) {
			System.err.println("Usage: (x_min) (x_max) (division_d)");
			System.exit(1);
		}
		
		double x1 = Double.parseDouble(args[0]);
		double x2 = Double.parseDouble(args[1]);
		int division = Integer.parseInt(args[2]);
		
		if(x1 >= x2) {
			System.err.println("Error: please x1 < x2");
			System.exit(1);
		}
		
		Plot2D frame = new Plot2D("Daichi Hotta", x1, x2, division);
		frame.pack();
		frame.setVisible(true);
	}

}
