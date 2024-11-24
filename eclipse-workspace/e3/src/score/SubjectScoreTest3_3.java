package score;

public class SubjectScoreTest3_3 {
	public static void main(String[] args) {
		String subject [] = {"AA", "BB", "CC", "DD", "EE", "FF", "GG", "HH", "II"};
		int score [] = {90, 80, 99, 60, 99, 95, 90, 80, 93};

		SubjectScore taro = new SubjectScore("Taro", 10);

		for(int i = 0; i < subject.length; i++){
			taro.setSubject(i, subject[i]);
			taro.setScore(i, score[i]);
		}
		
		String [] xy_subjects = {"XX", "YY", "ZZ"};
		int [] xy_scores = {45, 56, 32};
		String [] empty_subjects = new String [taro.getNum()];
		int [] empty_scores = new int [taro.getNum()];
				
		taro.setSubjects(xy_subjects);
		taro.setScores(xy_scores);
		taro.copySubjects(empty_subjects);
		taro.copyScores(empty_scores);
		System.out.println("Scores copied from Taro's");
		for(int i = 0; i < empty_scores.length; i++)
			System.out.printf("  %s: %d\n", empty_subjects[i], empty_scores[i]);
	}
}
