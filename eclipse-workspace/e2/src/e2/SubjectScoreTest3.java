package e2;

public class SubjectScoreTest3 {

	public static void main(String[] args) {
		String subject [] = {"AA", "BB", "CC", "DD", "EE", "FF", "GG", "HH", "II"};
        int score [] = {90, 80, 99, 60, 99, 95, 90, 80, 93};

        SubjectScore taro = new SubjectScore(10);

        taro.setStudentName("Taro");
        for(int i = 0; i < subject.length; i++){
            taro.setSubject(i, subject[i]);
            System.out.println("Set " + taro.getSubject(i) + " to the name of the No." + (i + 1) + " subject of " + taro.getStudentName());
            taro.setScore(i, score[i]);
            System.out.println("Set " + taro.getScore(i) + " to the score of the No." + (i + 1) + " subject of " + taro.getStudentName());
        }

        System.out.println("The name of 10th subject of Taro: " + taro.getSubject(9));

	}

}
