package score;

public class JisshuScoreTest4_5 {
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
		
		try {
			System.out.printf("  %s: %d\n", taro.getSubject(10), taro.getScore(10));				
		} catch  (Exception e) {
			System.out.println(e.getMessage());
		}
		try {
			taro.setSubject(10, "IT-Pro1");				
		} catch  (Exception e) {
			System.out.println(e.getMessage());
		}
		try {
			taro.setScore(9, 110);				
		} catch  (Exception e) {
			System.out.println(e.getMessage());
		}
	}
}
