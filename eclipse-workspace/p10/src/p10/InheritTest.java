package p10;

import java.awt.*;
import javax.swing.*;

//Inherit JFrame
public class InheritTest extends JFrame {
	//Member variables
	private JTextField textField;
	private JTextArea textArea;
	private JScrollPane scrollPane;
	private JButton button;
			
	// Constructor
	InheritTest(){
		// Initialize member variables
		textField = new JTextField();
		textArea = new JTextArea();
		scrollPane = new JScrollPane(textArea);
		button = new JButton("Button");
				
		//We can use the method of the superclass JFrame
		//(frame.add in SwingSample3)
		add(textField, BorderLayout.NORTH);
		add(scrollPane, BorderLayout.CENTER);
		add(button, BorderLayout.SOUTH);
	}

	public static void main(String[] args) {
		// Create an instance of SwingSample4
		InheritTest frame = new InheritTest();
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(400, 200);
		
		frame.setVisible(true);

	}

}
