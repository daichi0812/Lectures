package e7;

import java.io.*;
import java.util.*;

//for 7th week
public class WordCount {

	private File sourceFile;
	private int totalNumOfWords;
	private Map<String, Integer> wordFreqMap;
	private Map<String, Double> tfidfMap;
	private static Map<String, Integer> docFreqMap = new HashMap<>();
	private static Map<String, WordCount> sourceWordCountMap = new HashMap<>();

	// for 7th week: Exercise 7-1
	// Initialize totalNumOfWords, wordFreqMap, and tfidfMap fields.
	WordCount() {
		totalNumOfWords = 0;
		wordFreqMap = new HashMap<>();
		tfidfMap = new HashMap<>();

	}

	// for 7th week: Exercise 7-1
	// Initialize totalNumOfWords, wordFreqMap, and tfidfMap fields using default
	// constructor.
	// Initialize sourceFile field.
	// Call readFile() method.
	WordCount(File sourceFile) {
		this();		//デフォルトコンストラクタを呼び出す。
		this.sourceFile = sourceFile;
		readFile();
	}

	// for 7th week: Exercise 7-1
	String getSourceName() {
		//return the name of the source file
		if(sourceFile != null) {
			return sourceFile.getName();	//ソースファイルの名前を取得
		}
		else {
			return null;	//ソースファイルが設定さ入れていない → null
		}
	}

	// for 7th week: Exercise 7-1
	void setSourceFile(File sourceFile) {
		this.sourceFile = sourceFile;	//ソースファイルを設定
	}

	// for 6th week
	// Copy the code from TextInfo.java
	void countFreq(String word) {
			//ハッシュマップから単語の現在の頻度を取得する
			Integer freq = wordFreqMap.get(word);
			
			if( freq == null) {
				freq = 1;
			}
			else {
				freq++;
			}
			
			//更新された頻度をハッシュマップに戻す
			wordFreqMap.put(word, freq);
			//This method is used in readFile()
	}

	// for 7th week: Exercise 7-1
	// Count the number of occurrences of each word in the sourceFile.
	// Count the total number of words in the sourceFile.
	void readFile() {
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(sourceFile), "Shift-JIS"));
			String line;
			
			//ファイルを行ごとに読み込む
			while((line = br.readLine()) != null) {
				
				if(line.isEmpty()) {
					continue;
				}
				
				//行を空白で単語に分割
				String[] words = line.split("\\s+");
				
				//各単語をの出現数をカウント
				for(String word : words) {
					countFreq(word);
					
					//総単語数を更新
					totalNumOfWords ++;
				}
			}
			br.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	// for 6th week
	// Copy the code from TextInfo.java
	int getWordFreq(String word) {
		//ハッシュマップから頻度を得る
		Integer freq = wordFreqMap.get(word);
		
		//もしハッシュマップに単語がなければ
		if(freq == null) {
			return 0;
		}
		else {
			return freq;	//ハッシュマップに単語があれば、その頻度をそのまま返す
		}
	}

	// for 7th week: Exercise 7-1
	// Set sourceWordCountMap that stores the pairs of a sourceName (key) and
	// the instance of WordCount (value).
	static void setSourceWordCountMap(String inputDirPath) {
		File dir = new File(inputDirPath);
		File[] files = dir.listFiles();
		if(files != null) {
			for(File file : files) {
				if(file.isFile()) {
					//ファイルが存在する場合、新しいWordCountインスタンスを作成。
					WordCount wordCount = new WordCount(file);
					//ファイル名をキーとして、soruceWordCountMapに追加。
					sourceWordCountMap.put(file.getName(), wordCount);
				}
			}
		}
	}

	// for 7th week: Exercise 7-1
	static WordCount getWordCountObj(String sourceName) {
		//sourceNameをキーとして、sourceWordCountMapからWordCountインスタンスを取得
		return sourceWordCountMap.get(sourceName);
	}

	// for 7th week: Exercise 7-2
	// Writes the top n words in frequency (together with their frequency).
	void writeTopNFrequentWords(int n, File outputFile) {

		try {
			BufferedWriter bw = new BufferedWriter(
					new OutputStreamWriter(new FileOutputStream(outputFile), "Shift-JIS"));
			PrintWriter pw = new PrintWriter(bw);
			
			pw.printf("Top 5 words in frequency\n");
			List<Map.Entry<String, Integer>> wordList = new ArrayList<>(wordFreqMap.entrySet());
			wordList.sort((entry1, entry2) -> entry2.getValue().compareTo(entry1.getValue()));
			
			int count = 1;
			for(Map.Entry<String, Integer> entry : wordList) {
				pw.printf("%d: %s (%d)\n", count, entry.getKey(), entry.getValue());
				if(count == n) {
					break;
				}
				count++;
			}
			pw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	// for 7th week: Exercise 7-3
	// Returns the set of words stored in its instance.
	Set<String> getWordSet() {
		Set<String> set = new HashSet<>();
		
		for(String key : wordFreqMap.keySet()) {
			set.add(key);
		}
		
		return set;
	}

	// for 7th week: Exercise 7-3
	// Set docFreqMap that stores the pairs of a word (key) and the number of
	// documents in which the word appears (value).
	static void setDocFreqMap() {
		docFreqMap.clear();
		for(WordCount wordCount : sourceWordCountMap.values()) {
			Set<String> wordSet = wordCount.getWordSet();
			for(String word : wordSet) {
				if(docFreqMap.containsKey(word)) {
					docFreqMap.put(word, docFreqMap.get(word) + 1);
				}
				else {
					docFreqMap.put(word, 1);
				}
			}
		}
	}

	// for 7th week: Exercise 7-3
	// Get the number of documents in which the input word appears.
	static int getDocFreq(String word) {
		return docFreqMap.get(word);
	}

	// for 7th week: Exercise 7-3
	// Calculates the TF-IDF weight of each word stored in its instance.
	// See the slide p.16 for the definition of TF-IDF.
	double calTFIDF(int wf, int df, int totalNumOfWords, int totalNumOfDocs) {
		double idf = Math.log((double)totalNumOfDocs / df);
		double tf = (double) wf / totalNumOfWords;
		return tf * idf;
	}

	// for 7th week: Exercise 7-3
	void setTFIDFMap() {
		// 単語数を取得
	    int totalNumOfWordsInDoc = totalNumOfWords;

	    // すべての文書の数を取得
	    int totalNumOfDocs = sourceWordCountMap.size();

	    // 各単語に対してTF-IDF重みを計算し、tfidfMapにセット
	    for (String word : wordFreqMap.keySet()) {
	        // この文書内の単語の出現回数 (wf) を取得
	        int wf = getWordFreq(word);

	        // この単語が出現する文書の数 (df) を取得
	        int df = getDocFreq(word);

	        // TF-IDF重みを計算
	        double tfidf = calTFIDF(wf, df, totalNumOfWordsInDoc, totalNumOfDocs);

	        // tfidfMapにセット
	        tfidfMap.put(word, tfidf);
	    }
	}

	// for 7th week: Exercise 7-3
	double getTFIDFWeight(String word) {
		return tfidfMap.getOrDefault(word, 0.0);
	}

	// for 7th week: Exercise 7-4
	// Writes the top n words in TF-IDF weight (together with their TF-IDF weight).
	void writeTopNTfIdfWords(int n, File outputFile) {

		try {
			BufferedWriter bw = new BufferedWriter(
					new OutputStreamWriter(new FileOutputStream(outputFile), "Shift-JIS"));
			PrintWriter pw = new PrintWriter(bw);
			pw.printf("Top 5 words in TF-IDF weight\n");
			
			List<Map.Entry<String, Double>> wordList = new ArrayList<>(tfidfMap.entrySet());
			wordList.sort((entry1, entry2) -> Double.compare(entry2.getValue(), entry1.getValue()));
			
			int count = 1;
			for(Map.Entry<String, Double> entry : wordList) {
				
			pw.printf("%d: %s (%.3f)\n", count, entry.getKey(), entry.getValue());
			if(count == n) {
				break;
			}
			count++;
			}
			
			pw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
