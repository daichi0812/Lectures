/*
 * 15822108 情報テクノロジー　堀田大智
 */
package task14_1;

import java.io.*;
import java.util.ArrayList;

public class Matrix {
	// Member variable to store a 2D matrix
	double[][] data;
	int rows;
	int columns;
	boolean debug = false;
	static final double EPS = 1e-10;

	// Constructor that takes filename and read its content
	Matrix(String filename) {
		readFromFile(filename);
	}

	// Added: Constructor that takes the number of rows and columns
	// and allocate memory to data
	Matrix(int rows, int cols) {
		data = new double[rows][cols];
	}

	double[][] at(int x_index, int y_index, double sub_fig) {

		data[x_index][y_index] = sub_fig;

		return data;
	}

	double at(int x_index, int y_index) {
		double result;

		result = data[x_index][y_index];

		return result;
	}

	// task14_1
	public boolean isSymmetric() {
		if (rows != columns) {
			return false;
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < i; j++) {
				if (data[i][j] != data[j][i]) {
					return false;
				}
			}
		}

		return true;
	}

	public static Matrix eye(int n) {
		Matrix identity = new Matrix(n, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					identity.data[i][j] = 1.0;
				} else {
					identity.data[i][j] = 0.0;
				}
			}
		}
		return identity;
	}

	static Matrix mul(double a, Matrix matrix) {
		int row = matrix.data.length;
		int col = matrix.data[0].length;

		Matrix mul = new Matrix(row, col);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				mul.data[i][j] = a * matrix.data[i][j];
			}
		}

		return mul;
	}

//	public Vector getColumn(int columnIndex) {
//		if(columnIndex < 0 || columnIndex >= columns) {
//			throw new IllegalArgumentException("Column index"
//					+ " out of bounds");
//		}
//		
//		Vector columnVector = new Vector(rows);
//		for(int i = 0; i < rows; i++) {
//			columnVector.set(i,  data[i][columnIndex]);
//		}
//		
//		return columnVector;
//	}

	static Vector dot(Matrix matrix, Vector vector) {
		int row = matrix.data.length;
		int col = matrix.data[0].length;

		Vector result = new Vector(row);

		for (int i = 0; i < row; i++) {
			double sum = 0.0;
			for (int j = 0; j < col; j++) {
				sum += matrix.data[i][j] * vector.get(j);
			}
			result.set(i, sum);
		}

		return result;
	}

	public Matrix inv() {
		int i, j, k, ip;
		double amax, tmp, alpha;

		if (rows != columns) {
			System.err.println("Error: Matrix is not square. Cannot calculate inverse.");
			return null;
		}

		int n = rows;
		double[][] augmentedMatrix = new double[n][n];
		double[][] identityMatrix = new double[n][n];
		Matrix ansMatrix = new Matrix(n, n);

		// Create an augmented matrix
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				augmentedMatrix[i][j] = data[i][j];
			}
		}
		// Create an identity matrix
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (i == j) {
					identityMatrix[i][j] = 1.0;
				} else {
					identityMatrix[i][j] = 0.0;
				}

			}
		}

		// ピボット選択付きガウスの消去法の実装
		for (k = 0; k < n; k++) {
			// ピボット選択
			amax = Math.abs(augmentedMatrix[k][k]);
			ip = k;
			for (i = k + 1; i < n; i++) {
				if (Math.abs(augmentedMatrix[i][k]) > amax) {
					amax = Math.abs(augmentedMatrix[i][k]);
					ip = i;
				}
			}

			// 正則性の判定
			if (amax < EPS) {
				System.out.println("Input matrix is singular!");
				System.exit(1);
			}

			// 行交換
			if (ip != k) {
				for (j = 0; j < n; j++) {
					tmp = augmentedMatrix[k][j];
					augmentedMatrix[k][j] = augmentedMatrix[ip][j];
					augmentedMatrix[ip][j] = tmp;

					tmp = identityMatrix[k][j];
					identityMatrix[k][j] = identityMatrix[ip][j];
					identityMatrix[ip][j] = tmp;
				}
			}

			// 前進消去
			for (i = 0; i < n; i++) {
				if (i != k) {
					alpha = -augmentedMatrix[i][k] / augmentedMatrix[k][k];
					for (j = 0; j < n; j++) {
						augmentedMatrix[i][j] = augmentedMatrix[i][j] + alpha * augmentedMatrix[k][j];
						identityMatrix[i][j] = identityMatrix[i][j] + alpha * identityMatrix[k][j];
					}
				}
			}
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				identityMatrix[i][j] = identityMatrix[i][j] / augmentedMatrix[i][i];
			}
		}

//	    System.out.println("確認(逆行列が出力されるはず)");
//	    for( i = 0; i < n; i++) {
//	    	for( j = 0; j < n; j++) {
//	    		System.out.print(identityMatrix.data[i][j] + " ");
//	    	}
//	    	System.out.println();
//	    }

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				ansMatrix.data[i][j] = identityMatrix[i][j];
			}
		}

		return ansMatrix;
	}

	double det() {
		Matrix d = new Matrix(rows(), cols());
		d.data = this.data;
		int n = d.data.length;
        // 行列が空か1x1の場合
        if (n == 0) return 0;
        if (n == 1) return data[0][0];

        double det = 0;
        int sign = 1;  // 符号を交互に変えるための変数

        for (int i = 0; i < n; i++) {
            // 小行列を作成
            Matrix subMatrix = new Matrix(n - 1, n - 1);
            for (int j = 1; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (k < i) {
                        subMatrix.data[j - 1][k] = data[j][k];
                    } else if (k > i) {
                        subMatrix.data[j - 1][k - 1] = data[j][k];
                    }
                }
            }

            // 再帰的に小行列の行列式を計算し、現在の要素と乗算
            det += sign * data[0][i] * subMatrix.det();
            // 符号を反転
            sign = -sign;
        }
        return det;
	}

	// Method to read a text file and store its content to data
	// Note that data is now double type
	void readFromFile(String filename) {
		try {
			FileReader fr = new FileReader(new File(filename));
			BufferedReader br = new BufferedReader(fr);
			String line;

			while ((line = br.readLine()) != null) {
				// use "[//s]+" for splitting string with multiple spaces
				String[] values = line.trim().replaceAll("\\\\n", "").split("[\\s]+", 0);
				if (rows == 0) {
					columns = values.length;
					rows++;
				} else if (columns > 0 && columns != values.length && values.length > 0) {
					try {
						if (debug) {
							System.out.println("Warning: inconsistent column size at row: " + rows + " columns: "
									+ values.length + " " + columns);
						}
						continue;
					} catch (NumberFormatException e) {
						if (debug) {
							System.out.println("Warning: data has a line without any integer number");
						}
					}
				} else {
					rows++;
				}
			}
			br.close();
			fr.close();
		} catch (IOException e) {
			System.err.println(e);
			System.exit(1);
		}

		// allocate memory for data
		data = new double[rows][columns];

		ArrayList<ArrayList<Double>> dataList = new ArrayList<>();

		try {// read in the data
			FileReader fr = new FileReader(new File(filename));
			BufferedReader br = new BufferedReader(fr);
			String line;
			while ((line = br.readLine()) != null) {
				ArrayList<Double> row = new ArrayList<>();
				String[] values = line.trim().replaceAll("\\\\n", "").split("[\\s]+", 0);

				if (values.length == columns) {
					for (String value : values) {
						row.add(Double.parseDouble(value));
					}
					dataList.add(row);
				}
			}
			br.close();
			fr.close();
		} catch (IOException e) {
			System.err.println(e);
			System.exit(1);
		}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++)
				data[i][j] = dataList.get(i).get(j);
		}
	}

	// Method to write the content of data to a text file
	void writeToFile(String filename) {
		writeToFile(filename, false);
	}

	// Overloaded method to write the content of data to a text file
	// If append is type, append the content of data to the end of the existing file
	// Otherwise, overwrite the existing file and store the content of data to the
	// new file
	void writeToFile(String filename, boolean append) {
		try {
			BufferedWriter bw = new BufferedWriter(new FileWriter(filename, append));

			for (int i = 0; i < data.length; i++) {
				for (int j = 0; j < data.length; j++) {
					bw.write(data[j][i] + " ");
				}
				bw.newLine();
			}
			bw.close();
		} catch (IOException e) {
			System.err.println(e);
			System.exit(1);
		}
	}

	// Method to print the content of data to the standard output (System.out)
	void show() {
		for (double[] row : data) {
			for (double value : row) {
				System.out.print(value + " ");
			}
			System.out.println();
		}
	}

	void show(String description) {
		System.out.println(description);
		show();
	}

	// (optional)Getter method to return the number of rows
	int rows() {
		return data.length;
	}

	// (optional)Getter method to return the number of columns
	int cols() {
		return data[0].length;
	}

	// Static method that takes Matrix a and b and returns the sum of them
	static Matrix add(Matrix a, Matrix b) {
		// Initialize a matrix storing the result
		Matrix result = new Matrix(a.rows(), a.cols());

		for (int i = 0; i < a.rows(); i++) {
			for (int j = 0; j < a.cols(); j++) {
				result.data[i][j] = a.data[i][j] + b.data[i][j];
			}
		}

		return result;
	}

	// Static method that takes Matrix a and b and returns the difference between
	// them
	static Matrix sub(Matrix a, Matrix b) {
		// Initialize a matrix storing the result
		Matrix result = new Matrix(a.rows(), a.cols());

		for (int i = 0; i < a.rows(); i++) {
			for (int j = 0; j < a.cols(); j++) {
				result.data[i][j] = a.data[i][j] - b.data[i][j];
			}
		}

		return result;
	}

	// Static method that takes Matrix a and b and returns the element-wise product
	// of them
	static Matrix mul(Matrix a, Matrix b) {
		// Initialize a matrix storing the result
		Matrix mul = new Matrix(a.rows(), a.cols());

		for (int i = 0; i < a.rows(); i++) {
			for (int j = 0; j < b.cols(); j++) {
				mul.data[i][j] = a.data[i][j] * b.data[i][j];
			}
		}

		return mul;
	}

	// Static method that takes Matrix a and b and returns the dot product of them
	static Matrix dot(Matrix a, Matrix b) {
		// Initialize a matrix storing the result

		if (a.cols() != b.rows()) {
			System.err.println("Error: size mismatch");
			System.exit(1);
		}

		Matrix dot = new Matrix(a.rows(), b.cols());

		for (int i = 0; i < a.rows(); i++) {
			for (int j = 0; j < b.cols(); j++) {
				for (int k = 0; k < a.cols(); k++) {
					dot.data[i][j] += a.data[i][k] * b.data[k][j];
				}
			}
		}

		return dot;
	}

	public static void main(String[] args) {

	}
}
