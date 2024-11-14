/*
 * 15822108 情報テクノロジー　堀田大智
 */
package task9_3;
import java.io.*;

public class Matrix {
	//Member variable to store a 2D matrix
	double[][] data;
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
		data = new double[rows][cols];
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
		data = new double[rows][columns];
		
		try {//read in the data
			FileReader fr = new FileReader(new File(filename));
			BufferedReader br = new BufferedReader(fr);
			int i = 0;
			String line;
			while((line = br.readLine()) != null) {
				String[] values = line.trim().replaceAll("\\\\n", "").split("[\\s]+", 0);

				if(values.length == columns) {
					for(int j = 0; j < columns; j++) {
						data[i][j] = Double.parseDouble(values[j]);
					}
					i++;
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
			
			for(double[] row : data) {
				for(double value : row) {
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
		for(double[] row : data) {
			for(double value : row) {
				System.out.print(value + " ");
			}
			System.out.println();
		}
		
	}
	
	//(optional)Getter method to return the number of rows
	int rows() {
		return data.length;
	}
	
	//(optional)Getter method to return the number of columns
	int cols() {
		return data[0].length;
	}
	
	//Static method that takes Matrix a and b and returns the sum of them
	static Matrix add(Matrix a, Matrix b) {
		//Initialize a matrix storing the result
		Matrix result = new Matrix(a.rows(), a.cols());
		
		for(int i = 0; i < a.rows(); i++) {
			for(int j = 0; j < a.cols(); j++) {
				result.data[i][j] =  a.data[i][j] + b.data[i][j];
			}
		}
		
		return result;
	}

	//Static method that takes Matrix a and b and returns the difference between them
	static Matrix sub(Matrix a, Matrix b) {
		//Initialize a matrix storing the result
		Matrix result = new Matrix(a.rows(), a.cols());
		
		for(int i = 0; i < a.rows(); i++) {
			for(int j = 0 ; j < a.cols(); j++) {
				result.data[i][j] = a.data[i][j] - b.data[i][j];
			}
		}
		
		return result;
	}
	
	//Static method that takes Matrix a and b and returns the element-wise product of them
	static Matrix mul(Matrix a, Matrix b) {
		//Initialize a matrix storing the result		
		Matrix mul = new Matrix(a.rows(), a.cols());
		
		for(int i = 0; i < a.rows(); i++) {
			for(int j = 0; j < b.cols(); j++) {
				mul.data[i][j] = a.data[i][j] * b.data[i][j];
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
				for(int k = 0; k < a.cols(); k++) {
					dot.data[i][j] += a.data[i][k] * b.data[k][j];
				}
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
