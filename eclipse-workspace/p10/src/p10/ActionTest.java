package p10;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ActionTest extends JFrame implements ActionListener {
	private JTextField textField;
	private JTextArea textArea;
	private JScrollPane scrollPane;
	private JButton addButton;
	private JButton clearButton;
	
	ActionTest(){
		textField = new JTextField();
		textArea = new JTextArea();
		scrollPane = new JScrollPane(textArea);
		addButton = new JButton("Add");
		clearButton = new JButton("Clear");
		
		//Bind addButton and clerButton with action listener
		addButton.addActionListener(this);
		clearButton.addActionListener(this);
		
		// Create a JPanel instance, then add the addButton and the clear Button to i
		// JPanel can be used as a content pane
		JPanel buttonPane = new JPanel();
		buttonPane.add(addButton);
		buttonPane.add(clearButton);
		
		// Add to the content pane of JFrame
		add(textField, BorderLayout.NORTH);
		add(scrollPane, BorderLayout.CENTER);
		add(buttonPane, BorderLayout.SOUTH);
	}
	
	public void actionPerformed(ActionEvent event) {
		//Action performed when "addButton" is pressed
		if(event.getSource() == addButton) {
			// Add text in the textField to the textArea
			textArea.append(textField.getText() + "\n");
		}
		//Action performed when "clearButton" is pressed
		if(event.getSource() == clearButton) {
			//Clear text in the textArea
			textArea.setText(null);
		}
	}

	public static void main(String[] args) {
		ActionTest frame = new ActionTest();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(600, 400);
		frame.setVisible(true);
	}
}
