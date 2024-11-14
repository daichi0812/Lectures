package e7;

import java.io.File;

public class Exercise7_1_Tests {

	public static void main(String[] args) {
		if (args.length != 3) {
			System.err.println("java WordCount [test ID] [input dir path] [source name]");
			System.exit(-1);
		}
		String testNum = args[0];
		String inputDirPath = args[1];
		String sourceName = args[2];

		switch (testNum) {
		case "ex7-1-1":
			WordCount wc = new WordCount();
			int freq = wc.getWordFreq("test");
			System.out.println(freq);
			break;
		case "ex7-1-2":
			wc = new WordCount();
			wc.countFreq("test");
			wc.countFreq("test");
			freq = wc.getWordFreq("test");
			System.out.println(freq);
			break;
		case "ex7-1-3":
			wc = new WordCount(new File(inputDirPath, sourceName));
			System.out.println(wc.getSourceName());
			break;
		case "ex7-1-4":
			wc = new WordCount(new File(inputDirPath, sourceName));
			freq = wc.getWordFreq("the");
			System.out.println(freq);
			break;
		case "ex7-1-5":
			WordCount.setSourceWordCountMap(inputDirPath);
			wc = WordCount.getWordCountObj(sourceName);
			freq = wc.getWordFreq("to");
			System.out.println(freq);
			break;
		default:
			System.err.println("java WordCount [test ID] [input dir path] [source name]");
		}
	}
}
