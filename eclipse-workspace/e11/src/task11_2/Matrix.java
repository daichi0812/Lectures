/*
 * 15822108 情報テクノロジー　堀田大智
 */
package task11_2;
import java.io.*;
import java.util.ArrayList;

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
		
		ArrayList<ArrayList<Double>> dataList = new ArrayList<>();
		
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
					dataList.add(row);
				}
			}
			br.close();
			fr.close();
		}catch(IOException e) {
			System.err.println(e);
			System.exit(1);
		}
		
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < columns; j++)
			data[i][j] = dataList.get(i).get(j);
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
	
	void show(String description) {
		System.out.println(description);
		show();
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
	
	public Vector dot(Vector v) {
//        if (data[0].length != v.length) {
//            // エラー処理（例: サイズが一致しない場合）
//            throw new IllegalArgumentException("Matrix and Vector sizes do not match");
//        }

        double[] resultData = new double[data.length];

        for (int i = 0; i < data.length; i++) {
            double dotProduct = 0.0;
            for (int j = 0; j < data[i].length; j++) {
                dotProduct += data[i][j] * v.get(j);
            }
            resultData[i] = dotProduct;
        }
        
        Vector resultVector = new Vector(resultData.length);
        for (int i = 0; i < resultData.length; i++) {
            resultVector.set(i, resultData[i]);
        }
        return resultVector;
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

	}

}
