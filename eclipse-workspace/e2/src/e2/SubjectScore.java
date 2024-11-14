//15822108 堀田大智
package e2;

public class SubjectScore {
	//member variables
	private String studentName;
	private int num; //number of subjects
	private String[] subject;
	private int[] point;
	
	//Constructors
	SubjectScore(String s, int i){
		num = i;
		studentName = s;
		
		subject = new String[num];
		point = new int[num];
	}
	
	SubjectScore(int i){
		this("unknown", i);
		
	}
	
	SubjectScore(String s){
		this(s, 5);
	}
	
	SubjectScore(){
		this("unknown", 5);
	}
	
	//Accessor methods
	int getNum() {	//getter method
		return num;
	}
	
	String getStudentName() {
		return studentName;	//getter method
	}
	
	void setStudentName(String s) {
		studentName=s;	//setter method
	}
	
	String getSubject(int i) {
		return subject[i];	//getter method
	}
	
	int getScore(int i) {
		return point[i];	//getter method
	}
	
	void setSubject(int i, String s) {
		subject[i] = s;		//setter method
	}
	
	void setScore(int i, int j) {
		point[i]=j;
	}
	
	//Member methods
	double calAverage() {
		int i;
		double sum = 0.0;
		for( i=0; i<this.num; i++) {
			if(subject[i]==null) {
				break;
			}
			sum += (double)point[i];
		}
		return sum / i;
	}
	
	int getMaxScore() {
		int max = 0;
		for(int i = 0; i < this.num; i++) {
			if(subject[i]==null) {
				break;
			}
			if(point[i] >= max) {
				max = point[i];
			}
		}
		return max;
	}
	
	int getMinScore() {
		int min = 100;
		for(int i = 0; i < this.num; i++) {
			if(subject[i]==null) {
				break;
			}
			if(point[i] <= min) {
				min = point[i];
			}
		}
		return min;
	}
	
	String getMaxSubject() {
		int i;
		for(i = 0; i < this.num; i++) {
			if(point[i]== getMaxScore()) {
				break;
			}
		}
		return subject[i];
	}
	
	String getMinSubject() {
		int i;
		for(i = 0; i < this.num; i++) {
			if(point[i] == getMinScore()) {
				break;
			}
		}
		return subject[i];
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
