package score;

public class SubjectScoreTest3_5 {
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
				
		taro.setSubjects(xy_subjects);
		taro.setScores(xy_scores);

		System.out.printf("Average over Taro's first 5 scores: %.2f\n", taro.calAverage(5));
		System.out.printf("Average over Taro's first 15 scores: %.2f\n", taro.calAverage(15));
	}
}
