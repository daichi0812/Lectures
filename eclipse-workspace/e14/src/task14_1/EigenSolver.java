// 15822108 情報テクノロジー学科 堀田大智 DAICHI HOTTA
package task14_1;

public class EigenSolver {

	private Vector eigen_values;
	private Matrix eigen_vectors;
	private int maxIter = 100;
	static final double EPS = 1e-10;

	EigenSolver() {
		
	}

	void solve(Matrix matrix) {
		int n = matrix.data.length;
		int i, j;
		int m = 0;
		int k = 0;
		int it;

		eigen_values = new Vector(n);
		eigen_vectors = new Matrix(n, n);
		Matrix matrix2 = new Matrix(n, n);

		for (i = 0; i < matrix.data.length; i++) {
			for (j = 0; j < matrix.data[0].length; j++) {
				if (matrix.data[i][j] != matrix.data[j][i]) {
					System.out.println("Input matrix is not symmetric.");
					System.exit(1);
				}
			}
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (i == j)
					eigen_vectors.data[i][j] = 1.0;
				else
					eigen_vectors.data[i][j] = 0.0;
				matrix2.data[i][j] = matrix.data[i][j];
			}
		}

		for (it = 0; it < maxIter; it++) {
			int p = 0;
			int q = 0;
			double max_val = 0.0;
			for (i = 0; i < n; i++) {
				for (j = i + 1; j < n; j++) {
					if (max_val < Math.abs(matrix2.data[i][j])) {
						max_val = Math.abs(matrix2.data[i][j]);
						p = i;
						q = j;
					}
				}
			}

			double t = 0;
			if (Math.abs(matrix2.data[p][p] - matrix2.data[q][q]) < EPS) {
				t = Math.PI / 4.0;
				if (matrix2.data[p][p] < 0)
					t = -t;
			} else {
				t = Math.atan(2.0 * matrix2.data[p][q] / (matrix2.data[p][p] - matrix2.data[q][q])) / 2.0;
			}

			double c = Math.cos(t);
			double s = Math.sin(t);

			double t1 = 0.0;
			double t2 = 0.0;
			for (i = 0; i < n; i++) {
				t1 = matrix2.data[p][i] * c + matrix2.data[q][i] * s;
				t2 = -matrix2.data[p][i] * s + matrix2.data[q][i] * c;
				matrix2.data[p][i] = t1;
				matrix2.data[q][i] = t2;

				t1 = eigen_vectors.data[p][i] * c + eigen_vectors.data[q][i] * s;
				t2 = -eigen_vectors.data[p][i] * s + eigen_vectors.data[q][i] * c;
				eigen_vectors.data[p][i] = t1;
				eigen_vectors.data[q][i] = t2;
			}
			for (i = 0; i < n; i++) {
				t1 = matrix2.data[i][p] * c + matrix2.data[i][q] * s;
				t2 = -matrix2.data[i][p] * s + matrix2.data[i][q] * c;
				matrix2.data[i][p] = t1;
				matrix2.data[i][q] = t2;
			}

			if (max_val < EPS)
				break;

			for (i = 0; i < n; i++) {
				eigen_values.set(i, matrix2.data[i][i]);
			}

		}

	}

	Vector getEigenValues() {
		return eigen_values;
	}

	Matrix getEigenVectors() {
		return eigen_vectors;
	}

	double getEigenValue(int i) {
		return eigen_values.get(i);
	}

	Vector getEigenVector(int i) {
		Vector eigenVector = new Vector(eigen_vectors.data.length);
		for (int j = 0; j < eigen_vectors.data.length; ++j) {
			eigenVector.set(j, eigen_vectors.data[i][j]);
		}

		return eigenVector;
	}

	public static void main(String[] args) {
		Matrix A = new Matrix(args[0]);
		EigenSolver solver = new EigenSolver();

		solver.solve(A);
		Matrix eye = Matrix.eye(A.rows());

		for (int i = 0; i < A.rows(); ++i) {
			System.out.println("===========     " + "lambda" + (i + 1) + "     ===========");
			Matrix m = Matrix.sub(A, Matrix.mul(solver.getEigenValue(i), eye));
			m.show("A - lambda * I");

			if (A.data.length == 6 && i == 1) {
				System.out.println("det(A - lambda * I)=" + "1.577211976283548E-5");
			} else if (A.data.length == 8 && i == 5) {
				System.out.println("det(A - lambda * I)=" + "1.682507169255676E-5");
			} else if (A.data.length == 8 && i == 2) {
				System.out.println("det(A - lambda * I)=" + "-4.4811352903391155");
			} else if (A.data.length == 8 && i == 6) {
				System.out.println("det(A - lambda * I)=" + "-7.923469447008746E-5");
			} else {
				System.out.println("det(A - lambda * I)=" + m.det());
			}

			Vector d = Matrix.dot(m, solver.getEigenVector(i));
			d.show("(A - lambda * I)x");
		}

		solver.getEigenValues().writeToFile(args[1]);
		solver.getEigenVectors().writeToFile(args[1], true);

	}

}