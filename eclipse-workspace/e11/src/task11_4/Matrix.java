/*
 * 15822108 情報テクノロジー　堀田大智
 */
package task11_4;
import java.io.*;
import java.util.ArrayList;

public class Matrix {
	//Member variable to store a 2D matrix
	double[][] data;
	int rows;
	int columns;
	boolean debug = false;
	static final double EPS = 1e-10;
	
	//Constructor that takes filename and read its content
	Matrix(String filename){
		readFromFile(filename);
	}
	
	//Added: Constructor that takes the number of rows and columns
	//and allocate memory to data
	Matrix(int rows, int cols){
		data = new double[rows][cols];
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
	    for ( i = 0; i < n; i++) {
	        for ( j = 0; j < n; j++) {
	            augmentedMatrix[i][j] = data[i][j];
	        }
	    }
	    // Create an identity matrix
	    for( i = 0; i < n; i++) {
	    	for( j = 0; j < n; j++) {
	    		if(i == j) {
	    			identityMatrix[i][j] = 1.0;
	    		}else {
	    			identityMatrix[i][j] = 0.0;
	    		}
	    		
	    	}
	    }
	    
	    //ピボット選択付きガウスの消去法の実装
	    for( k = 0; k < n; k++) {
	    	//ピボット選択
	    	amax = Math.abs(augmentedMatrix[k][k]);
	    	ip = k;
	    	for( i = k + 1; i < n; i++) {
	    		if(Math.abs(augmentedMatrix[i][k]) > amax) {
	    			amax = Math.abs(augmentedMatrix[i][k]);
	    			ip = i;
	    		}
	    	}
	    	
	    	//正則性の判定
	    	if(amax < EPS) {
	    		System.out.println("Input matrix is singular!");
	    		System.exit(1);
	    	}
	    	
	    	//行交換
	    	if(ip != k) {
	    		for( j = 0; j < n; j++) {
	    			tmp = augmentedMatrix[k][j];
	    			augmentedMatrix[k][j] = augmentedMatrix[ip][j];
	    			augmentedMatrix[ip][j] = tmp;
	    			
	    			tmp = identityMatrix[k][j];
	    			identityMatrix[k][j] = identityMatrix[ip][j];
	    			identityMatrix[ip][j] = tmp;
	    		}
	    	}
	    	
	    	//前進消去
	    	for( i = 0; i < n; i++) {
	    		if(i != k) {
	    			alpha = - augmentedMatrix[i][k] / augmentedMatrix[k][k];
		    		for( j = 0; j < n; j++) {
		    			augmentedMatrix[i][j] = augmentedMatrix[i][j] + alpha * augmentedMatrix[k][j];
		    			identityMatrix[i][j] = identityMatrix[i][j] + alpha * identityMatrix[k][j];
		    		}
	    		}
	    	}
	    }
	    
	    for( i = 0; i < n; i++) {
	    	for( j = 0; j < n; j++) {
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
	    
	    for( i = 0; i < n; i++) {
	    	for(j = 0; j < n; j++) {
	    		ansMatrix.data[i][j] = identityMatrix[i][j];
	    	}
	    }

	    return ansMatrix;
	}
	
	double det() {
		if(rows != columns) {
			System.out.println("行列式は正方行列のみに対して行われます");
		}
		
		int n = rows;
		
		//ガウス消去法を使用して、行列を上三角形形式に変換
		double[][] upperTriangular = new double[n][n];
		for(int i = 0; i < n; i++) {
			System.arraycopy(data[i], 0, upperTriangular[i], 0, n);
		}
		
		int swaps = 0;
		for(int i = 0; i < n; i++) {
			int pivotRow = i;
			for(int j = i + 1; j < n; j++) {
				 if (Math.abs(upperTriangular[j][i]) > Math.abs(upperTriangular[pivotRow][i])) {
	                    pivotRow = j;
	                }
			}
			if (Math.abs(upperTriangular[pivotRow][i]) < EPS) {
                // Matrix is not regular (det is 0)
                return 0.0;
            }
			if(pivotRow != i) {
				//行の交換
				double[] temp = upperTriangular[i];
				upperTriangular[i] = upperTriangular[pivotRow];
                upperTriangular[pivotRow] = temp;
                swaps++;
			}
			for (int j = i + 1; j < n; j++) {
                double factor = upperTriangular[j][i] / upperTriangular[i][i];
                for (int k = i; k < n; k++) {
                    upperTriangular[j][k] -= factor * upperTriangular[i][k];
                }
			}
		}
		// 行列式を計算する
        double determinant = 1.0;
        for (int i = 0; i < n; i++) {
            determinant *= upperTriangular[i][i];
        }
        
        // 行交換の調整
        if (swaps % 2 == 1) {
            determinant = -determinant;
        }
        
        return determinant;
        
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
        final Matrix A = new Matrix(args[0]);
        A.inv().show("A^(-1)");
        
        Matrix.dot(A.inv(), A).show("A^(-1)A");
        Matrix.dot(A, A.inv()).show("AA^(-1)");
        
        try {
        	A.inv().writeToFile(args[1]);
        }catch(Exception e) {
        	e.printStackTrace();
        }
    }
}
