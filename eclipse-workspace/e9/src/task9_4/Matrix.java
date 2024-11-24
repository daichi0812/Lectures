/*15822108 情報テクノロジー 堀田大智*/
package task9_4;

import java.io.*;
import java.util.ArrayList;

public class Matrix {
	//Member variable to store a 2D matrix
	ArrayList<ArrayList<Double>> data;
	int rows;
	int columns;
	boolean debug = false;
	
	//Constructor that takes filename and read its content
	Matrix(String filename){
		readFromFile(filename);
	}
	
	//Added: Constructor that takes the number of rows and columns
	//and allocate memory to data
	Matrix(int rows, int cols){
		data = new ArrayList<>();
		for(int i = 0; i < rows; i++) {
			ArrayList<Double> row = new ArrayList<>();
			for(int j = 0; j < cols; j++) {
				row.add(0.0);
			}
			data.add(row);
		}
	}

	//Method to read a text file and store its content to data
	//Note that data is now double type
	void readFromFile(String filename) {
		try {
			FileReader fr = new FileReader(new File(filename));
			BufferedReader br = new BufferedReader(fr);
			String line;
			
			while((line = br.readLine()) != null) {				
				// use "[//s]+" for splitting string with multiple spaces
				String[] values = line.trim().replaceAll("\\\\n", "").split("[\\s]+", 0);
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
			br.close();
			fr.close();
		}catch(IOException e) {
			System.err.println(e);
			System.exit(1);
		}

		//allocate memory for data
		data = new ArrayList<ArrayList<Double>>();
		
		try {//read in the data
			FileReader fr = new FileReader(new File(filename));
			BufferedReader br = new BufferedReader(fr);
			String line;
			while((line = br.readLine()) != null) {
				ArrayList<Double> row = new ArrayList<>();
				String[] values = line.trim().replaceAll("\\\\n", "").split("[\\s]+", 0);
				
				if(values.length == columns) {
					for(String value : values) {
						row.add(Double.parseDouble(value));
					}
					data.add(row);
				}
			}
			br.close();
			fr.close();
		}catch(IOException e) {
			System.err.println(e);
			System.exit(1);
		}
	}
	
	//Method to write the content of data to a text file
	void writeToFile(String filename) {
		writeToFile(filename, false);
	}
	//Overloaded method to write the content of data to a text file
	//If append is type, append the content of data to the end of the existing file
	//Otherwise, overwrite the existing file and store the content of data to the new file
	void writeToFile(String filename, boolean append) {
		try {
			BufferedWriter bw = new BufferedWriter(new FileWriter(filename, append));
			
			for(ArrayList<Double> row : data) {
				for(Double value : row) {
					bw.write(value + " ");
				}
				bw.newLine();
			}
			bw.close();
		}catch(IOException e){
			System.err.println(e);
			System.exit(1);
		}
		
	}
	
	//Method to print the content of data to the standard output (System.out)
	void show() {
		for(ArrayList<Double> row : data) {
			for(Double value : row) {
				System.out.print(value + " ");
			}
			System.out.println();
		}
		
	}
	
	//(optional)Getter method to return the number of rows
	int rows() {
		return data.size();
	}
	
	//(optional)Getter method to return the number of columns
	int cols() {
		return data.get(0).size();
	}
	
	//Static method that takes Matrix a and b and returns the sum of them
	static Matrix add(Matrix a, Matrix b) {
		if(a.rows != b.rows || a.columns != b.columns){
            System.err.println("Error: size mismatch");
            System.exit(1);
        }
        // Initialize a matrix storing the result
        Matrix result = new Matrix(a.rows(), a.cols());
        
        //Compute the sum of two matrices
        for(int i = 0; i < a.rows(); i++){
            for(int j = 0; j < a.cols(); j++){
            	double sum = a.data.get(i).get(j) + b.data.get(i).get(j);
                result.data.get(i).set(j, sum);
            }
        }

		return result;
	}

	//Static method that takes Matrix a and b and returns the difference between them
	static Matrix sub(Matrix a, Matrix b) {
		if(a.rows != b.rows || a.columns != b.columns){
            System.err.println("Error: size mismatch");
            System.exit(1);
        }
		//Initialize a matrix storing the result
		Matrix result = new Matrix(a.rows(), a.cols());
		
		for(int i = 0; i < a.rows(); i++) {
			for(int j = 0 ; j < a.cols(); j++) {
				double diff = a.data.get(i).get(j) - b.data.get(i).get(j);
				result.data.get(i).set(j, diff);
			}
		}
		return result;
	}
	
	//Static method that takes Matrix a and b and returns the element-wise product of them
	static Matrix mul(Matrix a, Matrix b) {
		if(a.rows != b.rows || a.columns != b.columns){
            System.err.println("Error: size mismatch");
            System.exit(1);
        }
		//Initialize a matrix storing the result		
		Matrix mul = new Matrix(a.rows(), a.cols());
		
		for(int i = 0; i < a.rows(); i++) {
			for(int j = 0; j < b.cols(); j++) {
				double product = a.data.get(i).get(j) * b.data.get(i).get(j);
				mul.data.get(i).set(j, product);
			}
		}
		
		return mul;
	}
	
	//Static method that takes Matrix a and b and returns the dot product of them
	static Matrix dot(Matrix a, Matrix b) {
		//Initialize a matrix storing the result
		
		if(a.cols() != b.rows()) {
			System.err.println("Error: size mismatch");
			System.exit(1);
		}
		
		Matrix dot = new Matrix(a.rows(), b.cols());
		
		for(int i = 0; i < a.rows(); i++) {
			for(int j = 0; j < b.cols(); j++) {
				double sum = 0;
				for(int k = 0; k < a.cols(); k++) {
					sum += a.data.get(i).get(k) * b.data.get(k).get(j);
				}
				dot.data.get(i).set(j, sum);
			}
		}
		
		return dot;
	}
	
	public static void main(String[] args) {
		Matrix a = new Matrix(args[0]);
		Matrix b = new Matrix(args[1]);
		String output = args[2];
		
		Matrix sum = Matrix.add(a, b);
		System.out.println("a+b");
		sum.show();
		sum.writeToFile(output);
		
		Matrix sub = Matrix.sub(a,  b);
		System.out.println("a-b");
		sub.show();
		sub.writeToFile(output, true);
		
		Matrix mul = Matrix.mul(a,  b);
		System.out.println("a*b");
		mul.show();
		mul.writeToFile(output, true);
		
		Matrix dot = Matrix.dot(a, b);
		System.out.println("a・b");
		dot.show();
		dot.writeToFile(output, true);

	}

}
