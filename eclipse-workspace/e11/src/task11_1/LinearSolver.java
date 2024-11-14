// 15822108 情報テクノジ-学科 堀田大智

package task11_1;

import java.io.*;
import java.util.ArrayList;

public class LinearSolver {
	double[][] data;
	int rows;
	int columns;
	boolean debug = false;
	Matrix A;
	Vector b;
	
	private Matrix aug_matrix;
	
	LinearSolver(String filename) {
		readFromFile(filename);
	}
	
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
		aug_matrix = new Matrix(rows - 1, columns + 1);
		A = new Matrix(rows - 1, columns);
		b = new Vector(columns);
		
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
		
		for(int i = 0; i < rows - 1; i++) {
			for(int j = 0; j < columns; j++)
			aug_matrix.data[i][j] = dataList.get(i).get(j);
		}
		
		for(int i = 0; i < rows - 1; i++) {
			aug_matrix.data[i][columns] = dataList.get(rows - 1).get(i);
		}
		
		for(int i = 0; i < rows - 1; i++) {
			for(int j = 0; j < columns; j++) {
				A.data[i][j] = dataList.get(i).get(j);
			}
		}
		for(int i = 0; i < columns; i++) {
			b.set(i, dataList.get(rows-1).get(i));
		}
	}
	
	Matrix A() {
		return A;
	}
	
	Vector b() {
		return b;
	}
	
	Matrix getAugmentedMatrix() {
		return aug_matrix;
	}

	public static void main(String[] args) {
		LinearSolver solver = new LinearSolver(args[0]);
		solver.A().show("A");
		solver.b().show("b");
		solver.getAugmentedMatrix().show("Augmented Matrix");
		
		solver.A().writeToFile(args[1]);
		solver.b().writeToFile(args[1], true);

	}

}
