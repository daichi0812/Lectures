package task13_1;

public class Interpolation {
	
	static double lagrange(Matrix points, double x) {
		int i, k;
		double pn = 0.0, li;
		
		for(i = 0; i < points.data.length; i++) {
			li = 1.0;
			for(k = 0; k < points.data.length; k++) {
				if(k != i) {
					li *= (x - points.data[k][0]) / (points.data[i][0] - points.data[k][0]);
				}
			}
			pn += li * points.data[i][1];
		}
		
		return pn;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
