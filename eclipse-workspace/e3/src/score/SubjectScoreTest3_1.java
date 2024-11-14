package score;

// for Practice 3-1
public class SubjectScoreTest3_1 {
	public static void main(String[] args) {
		SubjectScore saburo = new SubjectScore("Saburo", 3);

		System.out.println(
				"The name and score of the 1st subject of Saburo: " + saburo.getSubject(1) + ", " + saburo.getScore(1));
		saburo.setScore(1);
		saburo.setSubject(1);
		System.out.println(
				"The name and score of the 1st subject of Saburo: " + saburo.getSubject(1) + ", " + saburo.getScore(1));
	}
}
