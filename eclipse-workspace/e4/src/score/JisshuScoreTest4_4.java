package score;

public class JisshuScoreTest4_4 {
	public static void main(String[] args) {
		String subject [] = {"AA", "BB", "CC", "DD", "EE", "FF", "GG", "HH", "II"};
		int score [] = {90, 80, 99, 60, 99, 95, 90, 80, 93};
		int report [] = {50, 60, 80, 70, 90, 110, 80, 76, 24};

		JisshuScore taro = new JisshuScore(10);
		taro.setStudentName("Taro");
		for(int i = 0; i < subject.length; i++){
			try {
				taro.setSubject(i, subject[i]);
				taro.setScore(i, score[i]);
				taro.setReportScore(i, report[i]);			
			} catch (Exception e) {
				System.out.println(e.getMessage());
			}
		}
		
		System.out.printf("The maximum score of %s: %d [%s]\n", taro.getStudentName(), taro.getMaxScore(), taro.getMaxSubject());		
		System.out.printf("The minimum score of %s: %d [%s]\n", taro.getStudentName(), taro.getMinScore(), taro.getMinSubject());
	}
}
