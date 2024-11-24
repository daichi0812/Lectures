// 15822108 情報テクノロジー 堀田大智
package task9_2;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.io.File;

public class Matrix {
	
	//Member variable to store a 2D matrix
	int columns;
	int rows;
	ArrayList<ArrayList<Integer>> data;
	boolean debug = true;
	
	//Constructor that takes filename and read its content
	Matrix(String filename){
		readFromFile(filename);
	}
	
	//Method to read a text file and store its content to data
	void readFromFile(String filename) {
		
		try { //pre-read in the number of row/columns
			FileReader fileReader = new FileReader(new File(filename));
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			String line;
			
			while((line = bufferedReader.readLine()) != null) {
				// use "[//s]+" for splitting string with multiple spaces
				String[] values = line.trim().split("[\\s]+", 0);
				
				if (rows == 0) {
					columns = values.length;
					rows++;
				}else if (columns > 0 && columns != values.length && values.length > 0) {
					try {
						if(debug) {
							System.out.println("Warning: inconsistent column size at row: " + rows + " columns: "
									+ values.length + " "+ columns);
						}
						continue;
					} catch (NumberFormatException e) {
						if(debug) {
							System.out.println("Warning: data has a line without any integer number");
						}
					}
				}else {
					rows++;
				}
			}
			bufferedReader.close();
			fileReader.close();
		}catch(IOException e) {
			System.err.println(e);
			System.exit(1);
		}
		
		//allocate memory for data
		data = new ArrayList<ArrayList<Integer>>();
		
		try {//read in the data
			FileReader fileReader = new FileReader(new File(filename));
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			String line;;
			ArrayList<Integer> col;
			while((line = bufferedReader.readLine()) != null) {
				col = new ArrayList <Integer>();
				String[] values = line.trim().split("[\\s+]", 0);
				if(values.length == columns) {
					for(int j = 0; j < columns; j++) {
						col.add(Integer.parseInt(values[j]));
					}
					data.add(col);
				}
			}
			bufferedReader.close();
			fileReader.close();
		}catch(IOException e) {
			System.err.println(e);
			System.exit(1);
		}
	}
	
	//Method to write the content of data to text file
	//write matrix data to file
	void writeToFile(String filename) {
		try {
			StringBuilder builder = new StringBuilder();
			for(int i = 0; i < rows; i++) {//for each row
				for(int j = 0; j < columns; j++) {//for each column
					builder.append(data.get(i).get(j) + ""); //append to the output string
					if(j < columns - 1) { //if this is not the last row element
						builder.append(" "); //then add comma(if you don't like commas you can spaces)
					}else {
						builder.append("\r\n");//append new line at the end of the row
					}
				}
			}
			BufferedWriter writer = new BufferedWriter(new FileWriter(filename));
			writer.write(builder.toString()); // save the string representation of the board
			writer.close();
		}catch(IOException e) {
			System.out.println(e);
		}
	}
	
	//Method to print the content of data to the standard output (System.out)
	void show() {
		 // 行列の内容を標準出力に表示するメソッドを実装する必要
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                System.out.print(data.get(i).get(j) + " ");
            }
            System.out.println();
        }
	}
	
	//(optional) Getter method to return the number of rows
	int rows() {
		return rows;
	}
	
	//(optional)Getter method to return the number of columns
	int cols() {
		return columns;
	}

	public static void main(String[] args) {
		//Initialize a Matrix instance with the first command line argument
		Matrix matrix = new Matrix(args[0]);
		
		//Print the content of the Matrix instance to the standard output
		matrix.show();
		
		//Output the content of the Matrix instance to
		//a text file specified by the second command line argument
		matrix.writeToFile(args[1]);

	}

}
