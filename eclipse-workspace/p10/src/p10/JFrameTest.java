package p10;

import javax.swing.*;

public class JFrameTest {

	public static void main(String[] args) {
		//Create a JFrame instance
		JFrame frame = new JFrame("Frame Title");
		
		//What to do when the window is closed
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		//Set the initial window width and height in pixel
		frame.setSize(400, 400);
		
		//Show the window
		frame.setVisible(true);

	}

}
