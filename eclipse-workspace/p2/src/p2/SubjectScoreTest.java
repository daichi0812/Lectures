package p2;

public class SubjectScoreTest {

	public static void main(String[] args) {
		SubjectScore s1=new SubjectScore();
		System.out.println(s1.getSubject() + ": " + s1.getScore());
		s1.setSubject("English");
		System.out.println(s1.getSubject() + ": " + s1.getScore());
		s1.setSubject("Mathmatics");
		s1.setScore(55);
		System.out.println(s1.getSubject() + ": " + s1.getScore());

	}

}
