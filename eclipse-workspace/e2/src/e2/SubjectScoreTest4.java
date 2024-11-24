package e2;

public class SubjectScoreTest4 {

	public static void main(String[] args) {
		String subject[] = { "AA", "BB", "CC", "DD", "EE", "FF", "GG", "HH", "II" };
		int score[] = { 90, 80, 99, 60, 99, 95, 90, 80, 93 };

		SubjectScore taro = new SubjectScore(10);

        taro.setStudentName("Taro");
        for(int i = 0; i < subject.length; i++){
            taro.setSubject(i, subject[i]);
            taro.setScore(i, score[i]);
        }

		System.out.printf("The average score of %s: %.2f\n", taro.getStudentName(), taro.calAverage());
		System.out.printf("The maximum score of %s: %d [%s]\n", taro.getStudentName(), taro.getMaxScore(),
				taro.getMaxSubject());
		System.out.printf("The minimum score of %s: %d [%s]\n", taro.getStudentName(), taro.getMinScore(),
				taro.getMinSubject());

	}

}
