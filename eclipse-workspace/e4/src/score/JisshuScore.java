package score;

public class JisshuScore extends SubjectScore {
	private int report[];
	private int count = 0;
	
	//Constructors
	JisshuScore(String s, int i){
		super(s, i);
		report = new int [i];
	}
			
	JisshuScore(int i){
		this("unknown", i);
	}
			
	JisshuScore(String s){
		this(s, 5);
	}
			
	JisshuScore(){
		this("unknown", 5);
	}
	
	//Accessory methods
	void setReportScore(int i, int j) throws Exception{
		if(i < 0 || i >= report.length) {
			throw new Exception(i + " is a wrong index.");
		}
		if(j < 0 || j > 100) {
			count ++;
			throw new Exception(j + " is out of the range of 0 to 100.");
		}
		
		count++;
		report[i] = j;
	}
	
	int getReportScore(int i) throws Exception{
		if(i < 0 || i >= report.length) {
			throw new Exception(i + " is a wrong index.");
		}
		return report[i];
	}
	
	//Member methods
	double calAverage(int i) {
		if(i == 0) {
			return super.calAverage();
		}
		else {
			int n;
			double sum = 0.0;
			for( n = 0; n < report.length; n++) {  
				if(report[n] >= 0 && report[n] <= 100) {
					sum += (double)report[n];
				}
			}
			return sum / count;
		}
	}
		

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
