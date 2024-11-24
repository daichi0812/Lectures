package score;

public class SubjectScoreTest3_2 {
	public static void main(String[] args) {
		String subject[] = { "AA", "BB", "CC", "DD", "EE", "FF", "GG", "HH", "II" };
		int score[] = { 90, 80, 99, 60, 99, 95, 90, 80, 93 };
		SubjectScore taro = new SubjectScore("Taro", 10);

		for (int i = 0; i < subject.length; i++) {
			taro.setSubject(i, subject[i]);
			taro.setScore(i, score[i]);
		}

		String[] xy_subjects = { "XX", "YY", "ZZ" };
		int[] xy_scores = { 45, 56, 32 };

		taro.setSubjects(xy_subjects);
		taro.setScores(xy_scores);
		System.out.println("Taro's updated scores");
		for (int i = 0; i < taro.getNum(); i++) {
			System.out.printf("  %s: %d\n", taro.getSubject(i), taro.getScore(i));
		}
	}
}
