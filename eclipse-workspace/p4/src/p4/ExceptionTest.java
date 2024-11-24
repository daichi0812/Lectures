package p4;

public class ExceptionTest {
	private int [] score;
	
	ExceptionTest(){
		score = new int [9];
	}
	
	void setScore(int i, int v) throws Exception {
		if(i < 0 || i >= score.length) {
			throw new Exception(i + " is a wrong index.");
		}
		score[i] = v;
	}
	
	int getScore(int i) throws Exception {
		if(i < 0 || i >= score.length) {
			throw new Exception(i + " is a wrong index.");
		}
		return score[i];
	}

	public static void main(String[] args) {
		ExceptionTest a = new ExceptionTest();
		
		for(int i = 0; i < 10; i++) {
			try {
				a.setScore(i,  i * 5);
				System.out.printf("Value of score[%d]: %d\n", i, a.getScore(i));
			}
			catch(Exception e) {
				System.out.println(e.getMessage());
			}
		}

	}

}
