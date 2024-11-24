package e2;

public class SubjectScoreTest2 {

	public static void main(String[] args) {
		SubjectScore hanako = new SubjectScore();
        SubjectScore jiro = new SubjectScore("Jiro");
        SubjectScore saburo = new SubjectScore("Saburo", 3);

        System.out.println("Student name of Hanako: " + hanako.getStudentName());
        System.out.println("Number of subjects for Hanako: " + hanako.getNum());
        hanako.setStudentName("Hanako");
        System.out.println("Student name of Hanako: " + hanako.getStudentName());

        System.out.println("Student name of Jiro: " + jiro.getStudentName());
        System.out.println("Number of subjects for Jiro: " + jiro.getNum());

        System.out.println("Student name of Saburo: " + saburo.getStudentName());
        System.out.println("Number of subjects for Saburo: " + saburo.getNum());
	}

}
