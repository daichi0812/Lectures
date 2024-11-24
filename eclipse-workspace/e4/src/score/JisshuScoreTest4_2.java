package score;

public class JisshuScoreTest4_2 {
	public static void main(String[] args) {
		String subject [] = {"AA", "BB", "CC", "DD", "EE", "FF", "GG", "HH", "II"};
		int score [] = {90, 80, 99, 60, 99, 95, 90, 80, 93};
		int report [] = {50, 60, 80, 70, 90, 110, 80, 76, 24};

		JisshuScore taro = new JisshuScore(10);
		taro.setStudentName("Taro");
		for(int i = 0; i < subject.length; i++){
			try {
				taro.setSubject(i, subject[i]);
				System.out.println("Set " + taro.getSubject(i) + " to the name of the No." + (i + 1) + " subject of " + taro.getStudentName());
				taro.setScore(i, score[i]);
				taro.setReportScore(i, report[i]);
				System.out.println("Set " + taro.getScore(i) + " to the score of the No." + (i + 1) + " subject of " + taro.getStudentName());				
				System.out.println("Set " + taro.getReportScore(i) + " to the report score of the No." + (i + 1) + " subject of " + taro.getStudentName());				
			} catch (Exception e) {
				System.out.println(e.getMessage());
			}
		}
		
		try {
			System.out.println("The name of 10th subject of Taro: " + taro.getSubject(9));			
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}
}
