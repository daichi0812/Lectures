// 15822108 情報テクノロジー学科 堀田大智
package task11_2;

import java.io.*;
import java.util.ArrayList;

public class LinearSolver {
	double[][] data;
	int rows;
	int columns;
	boolean debug = false;
	Matrix A;
	Vector b;
	static final double EPS = 1e-10;
	
	private Matrix aug_matrix;
	
	private Vector solve() {
        final Vector solution = new Vector(this.aug_matrix.data.length);
        int i, j, k, ip;
        double amax, tmp, alpha;
        
        int N = this.aug_matrix.data.length; 
        int M = this.aug_matrix.data[0].length;

        for (k = 0; k < N; k++) {
        	//ピボット選択
            amax = Math.abs(this.aug_matrix.data[k][k]);
            ip = k;
            for (i = k + 1; i < N; i++) {
                if (Math.abs(this.aug_matrix.data[i][k]) > amax) {
                    amax = Math.abs(this.aug_matrix.data[i][k]);
                    ip = i;
                }
            }
            
            //正則性の判定
            if(amax < EPS) {
	    		System.out.println("Input matrix is singular!");
	    		System.exit(1);
	    	}
            
            //行交換
            if (ip != k) {
                for (j = k; j < M; j++) {
                    tmp = this.aug_matrix.data[k][j];
                    this.aug_matrix.data[k][j] = this.aug_matrix.data[ip][j];
                    this.aug_matrix.data[ip][j] = tmp;
                }
            }
            
            //前進消去
            for (i = k + 1; i < N; i++) {
                alpha = -this.aug_matrix.data[i][k] / this.aug_matrix.data[k][k];
                for (j = k + 1; j < M; j++) {
                    this.aug_matrix.data[i][j] = this.aug_matrix.data[i][j] + alpha * this.aug_matrix.data[k][j];
                }
            }
        }
        
        //後退代入
        this.aug_matrix.data[N - 1][M - 1] = this.aug_matrix.data[N - 1][M - 1] / this.aug_matrix.data[N - 1][M - 2];
        for (k = N - 2; k >= 0; k--) {
            tmp = this.aug_matrix.data[k][M - 1];
            for (j = k + 1; j < N; j++) {
                tmp = tmp - this.aug_matrix.data[k][j] * this.aug_matrix.data[j][M - 1];
            }
            this.aug_matrix.data[k][M - 1] = tmp / this.aug_matrix.data[k][k];
        }

        for (i = 0; i < N; i++)
            solution.replace(i, this.aug_matrix.data[i][M - 1]);

        return solution;

    }
	
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
		//args[0]を読み取ってLinearSolver.javaを動かす
		LinearSolver solver = new LinearSolver(args[0]);
		//Matrix, Vectorそれぞれに渡してShow()させる
		solver.A().show("A");
		solver.b().show("b");
		solver.getAugmentedMatrix().show("Augmented Matrix");
		
		//LinearSolverのSolve()を動かす
		Vector solution = solver.solve();
		solution.show("solution");
		//引き算を行う
		Vector.sub(solver.A().dot(solution),  solver.b()).show("Ax-b");
		//ファイルに書き込む
		solution.writeToFile(args[1]);

	}

}
