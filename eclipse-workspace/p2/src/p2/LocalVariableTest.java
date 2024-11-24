package p2;

public class LocalVariableTest {
	//member variables
	int num = 10;
	int[] score;
	int[] default_scores = {11, 13, 12, 19, 17, 15, 10, 14, 14, 13};
	
	//Constructor
	LocalVariableTest(){
		score = new int [num];
		for(int i = 0; i < num; i++)
			score[i] = default_scores[i];
	}
	
	LocalVariableTest(int n){
		score = new int[n];
		num = n;
	}
	
	double calAverage() {
		double ans = 0.0;
		
		for(int num = 0; num < this.num; num++)
			ans += score[num];
		
		return ans / num;
	}
	public static void main(String[] args) {
		LocalVariableTest seiseki = new LocalVariableTest();
		System.out.println("Average over default values: " + seiseki.calAverage());

	}

}
