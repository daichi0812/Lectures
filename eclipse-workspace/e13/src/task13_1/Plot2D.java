//15822108 情報テクノロジー　堀田大智
package task13_1;

import javax.swing.JFrame;


public class Plot2D extends JFrame {
	
	// Constructor that takes String window_title
	Plot2D(String window_title, String filename, int numPoints, String imageName){
		
		super(window_title);
		
		//What to do when the window is closed
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				
		// Set the initial window width and height in pixel
		// change window size 600x600
		setSize(600, 600);
		
		//GraphPanel インスタンスの作成
		Matrix points = new Matrix(filename);
		GraphPanel graphPanel = new GraphPanel(points, numPoints);
		add(graphPanel);
		pack();
		
		graphPanel.saveImage(imageName);
		setVisible(false);
		
	}
	
	public static void main(String[] args) {
		if(args.length != 3) {
			System.err.println("Usage: (filename) (numPoints) (outputImage)");
			System.exit(1);
		}
		
		String filename = args[0];
		int numPoints = Integer.parseInt(args[1]);
		String outputImageName = args[2];
		
		Plot2D frame = new Plot2D("Daichi Hotta", filename, numPoints, outputImageName);
		frame.pack();
		frame.setVisible(true);
	}

}
