package score;

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
		
		/*for Practice 3-1 */
		void setSubject(int i) {
			subject[i] = "unknown";
		}
		
		void setScore(int i, int j) {
			point[i]=j;
		}
		
		//for Practice 3-1
		void setScore(int i) {
			point[i] = 60;
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
		
		//以下ex31の内容
		double calAverage(int m) {
			if(m > num) {
				return calAverage();
			}
			else {
				int i;
				double sum = 0.0;
				for( i = 0; i < m; i++) {
					if(subject[i]==null) {
						break;
					}
					sum += (double)point[i];
				}
				return sum / i;
			}
		}
		
		void setScores(int[] p) {
			if(p.length >= point.length) {
				for(int i = 0; i < point.length; i++) {
					point[i] = p[i];
				}
			}
			else {
				for(int i = 0; i < p.length; i++) {
					point[i] = p[i];
				}
			}
		}
		
		void setSubjects(String[] s) {
			if(s.length >= subject.length) {
				for(int i = 0; i< subject.length; i++) {
					subject[i] = s[i];
				}
			}
			else {
				for(int i = 0; i < s.length; i++) {
					subject[i] = s[i];
				}
			}
		}
		
		void copyScores(int[] p) {
			for(int i = 0; i < p.length; i++) {
				p[i] = point[i];
			}
		}
		
		void copySubjects(String[] s) {
			
			for(int i = 0; i < s.length; i++) {
				s[i] = subject[i];
			}
		}
		
	public static void main(String[] args) {
		
	}

}
