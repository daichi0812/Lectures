package e7;

public class Exercise7_3_Tests {

	public static void main(String[] args) {
		if (args.length != 3) {
			System.err.println("java WordCount [test ID] [input dir path] [source name]");
			System.exit(-1);
		}
		String testNum = args[0];
		String inputDirPath = args[1];
		String sourceName = args[2];

		WordCount.setSourceWordCountMap(inputDirPath);
		WordCount.setDocFreqMap();
		WordCount wc = WordCount.getWordCountObj(sourceName);
		switch (testNum) {
		case "ex7-3-1":
			System.out.println(wc.getWordSet().size());
			break;
		case "ex7-3-2":
			int docFreq = WordCount.getDocFreq("the");
			System.out.println(docFreq);
			break;
		case "ex7-3-3":
			double tfidf = wc.calTFIDF(9, 2, 1499, 5);
			System.out.printf("%.3f\n", tfidf);
			break;
		case "ex7-3-4":
			wc.setTFIDFMap();
			tfidf = wc.getTFIDFWeight("auto");
			System.out.printf("%.3f\n", tfidf);
			break;
		case "ex7-3-5":
			wc.setTFIDFMap();
			tfidf = wc.getTFIDFWeight("Hyundai");
			System.out.printf("%.3f\n", tfidf);
			break;
		default:
			System.err.println("java WordCount [test ID] [input dir path] [source name]");
		}

	}

}
