package p10;

import java.awt.*;

import javax.swing.*;

public class ComponentsTest1 {

	public static void main(String[] args) {
		JFrame frame = new JFrame("Label and Button");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(400, 200);
		
		// Get the content pane of the frame
		Container contentPane = frame.getContentPane();
		
		// Create a Label instance
		JLabel label = new JLabel("Label");
		
		// Create a Button instance
		JButton button = new JButton("Button");
		
		// Put label on contentPane
		contentPane.add(label, BorderLayout.CENTER);
		
		// Put button on contentPane
		contentPane.add(button, BorderLayout.SOUTH);
		
		frame.setVisible(true);

	}

}
