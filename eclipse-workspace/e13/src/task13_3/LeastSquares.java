package task13_3;

public class LeastSquares {
	
	static Vector minimize(Matrix points, int n) {
		int i, j, k, m;
		m = points.data.length;
		
		// Define augmented matrix as a (n+1 * n+2)-sized matrix
		Matrix augMatrix = new Matrix(n + 1, n + 2);
		
		//係数行列
		Matrix p = new Matrix(n + 1, n + 1);
		//右辺ベクトル
		Matrix a = new Matrix(n + 1, 1);
		
		// Construct the augmented matrix (eq. 6.5)
		//右辺ベクトルの作成
		for(i = 0; i < n + 1; i++) {
			a.data[i][0] =0.0;
			for(j = 0; j < m; j++) {
				a.data[i][0] += points.data[j][1]
						* Math.pow(points.data[j][0], (double)(i));
			}
		}
		
		System.out.println("右ベクトルの確認");
		for(i = 0; i < n + 1; i++) {
			System.out.println(a.data[i][0]);
		}
		System.out.println();
		
		//係数行列の作成
		for(i = 0; i < n + 1; i ++) {
			for(j = 0; j <= i; j++) {
				p.data[i][j] = 0.0;
				for(k = 0; k < m; k++) {
					p.data[i][j] += Math.pow(points.data[k][0]
							, (double)(i + j));
				}
				p.data[j][i] = p.data[i][j];
			}
		}
		
		System.out.println("係数行列の確認");
		for(i = 0; i < n + 1; i++) {
			for(j = 0; j < n + 1; j++) {
				System.out.print(p.data[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
		
		//上記二つをまとめる
		for(i = 0; i < n + 1; i++) {
			for(j = 0; j < n + 1; j++) {
				augMatrix.data[i][j] = p.data[i][j];
			}
		}
		for(i = 0; i < n + 1; i++) {
			augMatrix.data[i][n + 1] = a.data[i][0];
		}
		
		System.out.println("まとめた行列の確認");
		for(i = 0; i < n + 1; i++) {
			for( j = 0; j < n + 2; j++) {
				System.out.print(augMatrix.data[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
		
		// Solve the simultaneous linear equation
		// You may need to add a constructor that takes augMatrix
		LinearSolver solver = new LinearSolver(augMatrix);
		Vector coeffs = solver.solve();
		
		System.out.println("Coeffsの中身(インデックス0から)");
		for(i = 0; i < n + 1; i++) {
			System.out.println(coeffs.get(i));
		}
		
		return coeffs;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
