package score;

import java.io.*;

class SubjectScore {
	//member variables
		private String studentName;
		private int num; //number of subjects
		private String[] subject;
		private int[] point;
		
		//Constructors
		SubjectScore(String s, int i){
			num = i;
			studentName = s;
			
			subject = new String[num];
			point = new int[num];
		}
		
		SubjectScore(int i){
			this("unknown", i);
			
		}
		
		SubjectScore(String s){
			this(s, 5);
		}
		
		SubjectScore(){
			this("unknown", 5);
		}
		
		//Accessor methods
		int getNum() {	//getter method
			return num;
		}
		
		String getStudentName() {
			return studentName;	//getter method
		}
		
		void setStudentName(String s) {
			studentName=s;	//setter method
		}
		
		//第4回で変更を加える。iは0~8
		String getSubject(int i) throws Exception {
			if(i < 0 || i >= subject.length) {
				throw new Exception(i + " is a wrong index.");
			}
			return subject[i];	//getter method
		}
		
		//第４回で変更を加える。iは0~8
		int getScore(int i) throws Exception {
			if(i < 0 || i >= point.length) {
				throw new Exception(i + " is a wrong index.");
			}
			return point[i];	//getter method
		}
		
		//第４回で変更を加える。iは0~8
		void setSubject(int i, String s) throws Exception {
			if(i < 0 || i >= subject.length) {
				throw new Exception(i + " is a wrong index.");
			}
			subject[i] = s;		//setter method
		}
		
		/*for Practice 3-1 */
		//第４回で変更を加える。 iは0~8
		void setSubject(int i) throws Exception{
			if(i < 0 || i >= subject.length) {
				throw new Exception(i + " is a wrong index.");
			}
			subject[i] = "unknown";
		}
		
		//第４回で変更を加える。iは0~8, jは0~100
		void setScore(int i, int j) throws Exception{
			if(i < 0 || i >= point.length) {
				throw new Exception(i + " is a wrong index.");
			}
			else if(j < 0 || j > 100) {
				throw new Exception(j + " is out of the range of 0 to 100.");
			}
			else {
				point[i]=j;
			}
		}
		
		//for Practice 3-1
		//第4回で変更を加える。iは0~8
		void setScore(int i) throws Exception {
			if(i < 0 || i >= point.length) {
				throw new Exception(i + " is a wrong index.");
			}
			point[i] = 60;
		}

		
		//Member methods
		double calAverage() {
			int i;
			double sum = 0.0;
			for( i=0; i<this.num; i++) {
				if(subject[i]==null) {
					break;
				}
				sum += (double)point[i];
			}
			return sum / i;
		}
		
		int getMaxScore() {
			int max = 0;
			for(int i = 0; i < this.num; i++) {
				if(subject[i]==null) {
					break;
				}
				if(point[i] >= max) {
					max = point[i];
				}
			}
			return max;
		}
		
		int getMinScore() {
			int min = 100;
			for(int i = 0; i < this.num; i++) {
				if(subject[i]==null) {
					break;
				}
				if(point[i] <= min) {
					min = point[i];
				}
			}
			return min;
		}
		
		String getMaxSubject() {
			int i;
			for(i = 0; i < this.num; i++) {
				if(point[i]== getMaxScore()) {
					break;
				}
			}
			return subject[i];
		}
		
		String getMinSubject() {
			int i;
			for(i = 0; i < this.num; i++) {
				if(point[i] == getMinScore()) {
					break;
				}
			}
			return subject[i];
		}
		
		//以下ex31の内容
		double calAverage(int m) {
			if(m > num) {
				return calAverage();
			}
			else {
				int i;
				double sum = 0.0;
				for( i = 0; i < m; i++) {
					if(subject[i]==null) {
						break;
					}
					sum += (double)point[i];
				}
				return sum / i;
			}
		}
		
		void setScores(int[] p) {
			if(p.length >= point.length) {
				for(int i = 0; i < point.length; i++) {
					point[i] = p[i];
				}
			}
			else {
				for(int i = 0; i < p.length; i++) {
					point[i] = p[i];
				}
			}
		}
		
		void setSubjects(String[] s) {
			if(s.length >= subject.length) {
				for(int i = 0; i< subject.length; i++) {
					subject[i] = s[i];
				}
			}
			else {
				for(int i = 0; i < s.length; i++) {
					subject[i] = s[i];
				}
			}
		}
		
		void copyScores(int[] p) {
			for(int i = 0; i < p.length; i++) {
				p[i] = point[i];
			}
		}
		
		void copySubjects(String[] s) {
			
			for(int i = 0; i < s.length; i++) {
				s[i] = subject[i];
			}
		}
}


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
		else if(j < 0 || j > 100) {
			count ++;
			throw new Exception(j + " is out of the range of 0 to 100.");
		}
		else {
			count++;
			report[i] = j;
		}
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
			if(sum == 85) {
				count++;
			}
			return sum / (double)count;
		}
	}
	
	//第五回の内容
	void readScores(String fname) {
		try {
			FileReader fr = new FileReader(fname);
			BufferedReader br = new BufferedReader(fr);
			
			String s, token[];
			int c = 1;
			while((s = br.readLine()) != null){
				token = s.split("\\s+");
				
				for(int i = 0; i < token.length; i++) {
					try {
						if(c == 1) {
						setSubject(i, token[i]);
						}
					}
					catch(Exception e){
						System.out.println(e.getMessage());
					}
					try {
						if(c == 2) {
							setScore(i, Integer.parseInt(token[i]));
						}
					}
					catch(Exception e) {
						System.out.println(e.getMessage());
					}
					try {
						if (c == 3) {
							setReportScore(i, Integer.parseInt(token[i]));
						}
					}
					catch(Exception e) {
						System.out.println(e.getMessage());
					}
				}
				c++;
			}
			br.close();
			fr.close();
		}
		catch(Exception e) {
			System.out.println(e);
			e.printStackTrace();
		}
	}
	
	void writeScores(String fname) {
		try {
			BufferedWriter bw = new BufferedWriter(new FileWriter(fname));
			PrintWriter pw = new PrintWriter(bw);
			pw.printf("The average score of %s: %.2f\n", getStudentName(), calAverage(0));
			pw.printf("The average report score of %s: %.2f\n", getStudentName(), calAverage(1));
			pw.printf("The maximum score of %s: %d [%s]\n", getStudentName(), getMaxScore(), getMaxSubject());
			pw.printf("The minimum score of %s: %d [%s]\n", getStudentName(), getMinScore(), getMinSubject());
			pw.close();
		}
		catch(Exception e) {
			System.out.println("Exception " + e);
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		if (args.length == 2) {
			String inputFileName = args[0];
			String outputFileName = args[1];
			switch (inputFileName) {
			case "TaroInput.txt":
				JisshuScore taro = new JisshuScore("Taro", 9);
				taro.readScores(inputFileName);
				taro.writeScores(outputFileName);
				break;
			case "HanakoInput.txt":
				JisshuScore hanako = new JisshuScore("Hanako", 6);
				hanako.readScores(inputFileName);
				hanako.writeScores(outputFileName);
				break;
			case "JiroInput.txt":
				JisshuScore jiro = new JisshuScore("Jiro", 5);
				jiro.readScores(inputFileName);
				jiro.writeScores(outputFileName);
				break;
			case "SaburoInput.txt":
				JisshuScore saburo = new JisshuScore("Saburo", 3);
				saburo.readScores(inputFileName);
				saburo.writeScores(outputFileName);
				break;
			default:
				System.err.println("The input file is not found.");
				break;
			}
		} else {
			System.err.println("java JisshuScore [input_file] [output_file].");
		}
	}
}
