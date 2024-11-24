package p2;

public class SubjectScore {
	//member variables
	//"private" is Access modifier
	private String subject;
	private int point;
	
	//Constructor
	SubjectScore(){
		this("unknown", 60);
	}
	
	SubjectScore(String s){
		this(s, 60);
	}
	
	SubjectScore(String s, int i){
		subject=s;
		point=i;
	}
	
	//Member method
	void showScore() {
		System.out.println(subject+": " + point);
	}
	
	//Accessor methods
	String getSubject() {	//getter method
		return subject;
	}
	
	int getScore() {	//getter method
		return point;
	}
	
	void setSubject(String s) {	//setter method
		subject=s;
	}
	
	void setScore(int i) {	//setter method
		point=i;
	}

	public static void main(String[] args) {
		//class type variable
		SubjectScore s1=new SubjectScore();
		System.out.println("Subject: " + s1.subject + "Score: " + s1.point);
		s1.showScore();
		
		SubjectScore s2=new SubjectScore("Mathmatics");
		System.out.println("Subject: " + s2.subject + "Score: " + s2.point);
		s2.showScore();
		
		SubjectScore s3=new SubjectScore("English", 100);
		System.out.println("Subject: " + s3.subject + "Score: " + s3.point);
		s3.showScore();
	}

}
