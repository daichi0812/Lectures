// 15822108 情報テクノロジー学科 堀田大智
package task12_1;

public class NonLinearSolver {
	private int maxIter;
	static final double EPS = 1e-10;
	
	public NonLinearSolver(int maxIter) {
		this.maxIter = maxIter;
	}
	
	public NonLinearSolver() {
		maxIter = 30;
	}
	
	double solveNewton(double init_x) {
		int n = 0;
		double d;
		
		do {
			d = -f(init_x) / df(init_x);
			init_x = init_x + d;
			n++;
		}while(Math.abs(d) > EPS && n < maxIter);
		
		if(n == maxIter) {
			return Double.NaN;
		}else {
			return init_x;
		}

	}
	
	double f(double x) {
		return x - Math.exp(-x);
	}
	
	double df(double x) {
		return 1 + Math.exp(-x);
	}

	public static void main(String[] args) {
		boolean j = false;
		
		if(args.length == 0) {
			System.err.println("Usage: (init_x1) (init_x2) ...");
			System.exit(1);
		}
		
		for(int i = 0; i < args.length; i++) {
			String s = args[i];
			try {
				double init_x = Double.parseDouble(s);
				NonLinearSolver solver = new NonLinearSolver();
				double root = solver.solveNewton(init_x);
				if(Double.isNaN(root)) {
					System.out.printf("searching x from %.1f failed.\n", init_x);
				}else {
					j = true;
					System.out.printf("searching x from %.1f, solution is %f.\n", init_x, root);
				}
				
			}catch(ArithmeticException e) {
				System.err.println(e);
				System.exit(1);	
			}
			if(j) {
				System.exit(0);
			}else {
				System.exit(1);
			}
		}
	}

}
