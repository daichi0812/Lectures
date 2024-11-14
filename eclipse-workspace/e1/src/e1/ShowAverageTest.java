package e1;

public class ShowAverageTest {

	public static void main(String[] args) {
		String[] subjects =  { "English", "Mathematics", "Science" };
		double[][] scores = { { 53, 68, 88 }, { 73, 81, 70 }, { 91, 90, 62 } };
		
		if (args.length == 1) {
			if (args[0].equals("test1")) {
				scores = new double[][] { { 53, 68, 88 }, { 73, 81, 70 }, { 91, 90, 62 } };
			} else if (args[0].equals("test2")) {
				scores = new double[][] { { 80, 65, 90 }, { 70, 50, 75 }, { 100, 90, 80 } };
			} else if (args[0].equals("test3")) {
				scores = new double[][] { { 92, 85, 70 }, { 63, 61, 74 }, { 60, 75, 93 } };
			} else if (args[0].equals("test4")) {
				scores = new double[][] { { 100, 95, 87 }, { 90, 100, 63 }, { 85, 70, 65 } };
			} else if (args[0].equals("test5")) {
				scores = new double[][] { { 70, 60, 80 }, { 90, 85, 75 }, { 95, 85, 70 } };
			}
		}
		
		// Complete the code.
double sum1=0.0, sum2=0.0, average1=0.0, average2=0.0;
		
		for(int i=0; i<scores.length; i++) {
			for(int j=0; j<3; j++) {
				sum1+=scores[i][j];
			}
			average1=(sum1/3.0);
			System.out.printf("Average score over the three subjects for student %d: %.1f\n", i+1, average1);
			average1=0.0;
			sum1=0.0;
		}
		
		System.out.println();
		
		for(int k=0; k<scores.length; k++) {
			for(int l=0; l<subjects.length; l++) {
				sum2+=scores[l][k];
			}
			average2=(sum2/3.0);
			System.out.printf("Average score over the 3 students for %s: %.1f\n", subjects[k], average2);
			average2=0.0;
			sum2=0.0;
		}
	}
}
