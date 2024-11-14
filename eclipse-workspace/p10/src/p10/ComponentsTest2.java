package p10;

import java.awt.*;
import javax.swing.*;

public class ComponentsTest2 {

	public static void main(String[] args) {
		JFrame frame = new JFrame("Text Area and Field");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(400, 200);
		
		// Create a text field instance
		JTextField textField = new JTextField();
		
		// Create a text area instance
		JTextArea textArea = new JTextArea();
		
		// Add text area on scroll pain
		JScrollPane scrollPane = new JScrollPane(textArea);
		
		// Create a button instance
		JButton button = new JButton("Button");
		
		// Put textField, scrollPane and button on contentPane
		// We can use frame.add() as the shortened form of frame.getContentPane().add()
		// to add components to contentPane
		frame.add(textField, BorderLayout.NORTH);
		frame.add(scrollPane, BorderLayout.CENTER);
		frame.add(button, BorderLayout.SOUTH);
		
		frame.setVisible(true);

	}

}
