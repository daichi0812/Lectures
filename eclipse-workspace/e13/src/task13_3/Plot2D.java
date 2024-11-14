//15822108 情報テクノロジー　堀田大智
package task13_3;

import javax.swing.JFrame;


public class Plot2D extends JFrame {
	
	// Constructor that takes String window_title
	Plot2D(String window_title, String filename, int approximation, int numPoints, String imageName){
		
		super(window_title);
		
		//What to do when the window is closed
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				
		// Set the initial window width and height in pixel
		// change window size 600x600
		setSize(600, 600);
		
		//GraphPanel インスタンスの作成
		Matrix points = new Matrix(filename);
		GraphPanel graphPanel = new GraphPanel(points, approximation, numPoints);
		DataPanel dataPanel = new DataPanel(/*適切なコードを書く*/);
		add(graphPanel);
		pack();
		
		graphPanel.saveImage(imageName);
		setVisible(false);
	}
	
	public static void main(String[] args) {
		if(args.length != 4) {
			System.err.println("Usage: (filename) (Approximation order) (numPoints) (outputImage)");
			System.exit(1);
		}
		
		String filename = args[0];
		int approximation = Integer.parseInt(args[1]);
		int numPoints = Integer.parseInt(args[2]);
		String outputImageName = args[3];
		
		Plot2D frame = new Plot2D("Daichi Hotta", filename, approximation, numPoints, outputImageName);
		frame.pack();
		frame.setVisible(true);
	}

}
