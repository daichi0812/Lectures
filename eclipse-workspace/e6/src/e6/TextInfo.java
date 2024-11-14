/*　
 * 15822108
 * 情報テクノロジー学科
 * 堀田大智
 */
package e6;

import java.io.*;
import java.util.*;

public class TextInfo {
	private String source_name; //variable to store the name of the information source ( input file name)
	private int total;	//variable to store the number of words
	private HashMap<String, Integer> word_freq;	//HashMap to store the frequency of each word
	
	//Constructor that takes the name of the information source as its argument
	TextInfo(String fn){
		//ファイルの名前をセットする
		setSourceName(fn);
		//単語カウントの初期化
		total = 0;
		//新しいハッシュマップを作る
		word_freq = new HashMap<String, Integer>();
	}
	
	//Getter method to return the value of source_name
	String getSourceName() {
		//Return the source name
		return source_name;
	}
	
	//Setter method to set the name of the information source(file name)
	void setSourceName(String s) {
		//ソース名をしていされた文字列に設定(セット)する
		source_name = s;
	}
	
	//Method to increment the frequency of a word specified by its argument
	private void countFreq(String word) {
		//ハッシュマップから単語の現在の頻度を取得する
		Integer freq = word_freq.get(word);
		
		if( freq == null) {
			freq = 1;
		}
		else {
			freq++;
		}
		
		//更新された頻度をハッシュマップに戻す
		word_freq.put(word, freq);
		//This method is used in readFile()
	}
	
	//Method to read text from the information source (input file) and count the frequency of each word
	void readFile() {
		try {
			//BufferedReaderを作る
			BufferedReader br = new BufferedReader(new FileReader(getSourceName()));
			//ファイルの行を読む
			String line = br.readLine();
			while(line != null) {
				//空白文字で行を単語に分割する
				String[] words = line.split("\\s+");
				//行の中のそれぞれの単語に対して
				for(String word : words) {
					countFreq(word);
					//総単語数を1増やす
					total++;
				}
				//次のラインに進む
				line = br.readLine();
			}
			br.close();
		}
		catch(IOException e) {
			System.out.println("Error reading file: " + e.getMessage());
		}
	}
	
	//Method to return the frequency of a word specified by its argument
	int getFreq(String word) {
		//ハッシュまっぷから頻度を得る
		Integer freq = word_freq.get(word);
		//もしハッシュマップに単語がなければ
		if(freq == null) {
			return 0;
		}
		else {
			return freq.intValue();
		}
	}
	
	//Method to output of the frequency of every word
	void writeAllFreq(String outputFilePath) {
		try {
			//ファイルに書き込むため
			PrintWriter pw = new PrintWriter(new FileWriter(outputFilePath));
			//出力ファイルにヘッダー行を書き込む
			pw.println("Information source: " + source_name);
			//ハッシュマップから単語を得る
			Set<String> words = word_freq.keySet();
			//それぞれの単語に
			for(String word : words) {
				int freq = getFreq(word);
				pw.println("Frequency of \"" + word + "\": " + freq);
			}
			pw.close();
		}
		catch(IOException e) {
			System.out.println("Error writeing file: " + e.getMessage());
		}
	}
	
	//Return the self-information of the specified word
	double calSelfInfo(String word) {
		//ハッシュ関数から単語の頻度を得る
		int freq = getFreq(word);
		if(freq == 0) {
			return 0; 
		}
		//単語の頻度を単語の総数で割って、その単語の確率を計算する
		double prob = (double)freq / total;
		//log_2(x) = log_10(x)/log_10(2.0)
		double selfInfo = -Math.log(prob) / Math.log(2.0);
		return selfInfo;
	}
	
	//Method to output the self-information of every word
	void writeAllSelfInfo(String outputFilePath) {
		try {
			PrintWriter pw = new PrintWriter(new FileWriter(outputFilePath));
			pw.println("Information source: " + source_name);
			Set<String> words = word_freq.keySet();
			for(String word : words) {
				double selfInfo = calSelfInfo(word);
				pw.println("Self-Information of \"" + word + "\": " +(String.format("%.3f", selfInfo)));
			}
			pw.close();
		}
		catch(IOException e){
			System.out.println("Error writing file: " + e.getMessage());
		}
	}
	
	//Method to return the entropy of the information source
	double calInfo() {
		double entropy = 0;
		Set<String> words = word_freq.keySet();
		
		for(String word : words) {
			double prob = (double)getFreq(word) / total;
			double info = prob * calSelfInfo(word);
			entropy += info;
		}
		return entropy;
	}
	public static void main(String[] args) {
		if(args.length != 3) {
			System.out.println("java TextInfo [freq|self-info] [input file path] [output file path]");
			System.exit(-1);
		}
		String type = args[0];
		String inputFilePath = args[1];
		String outputFilePath = args[2];
		TextInfo source = new TextInfo(inputFilePath);
		source.readFile();
		switch(type) {
		case"freq":
			source.writeAllFreq(outputFilePath);
			break;
		case"self-info":
			source.writeAllSelfInfo(outputFilePath);
			break;
		default:
			System.err.println("java TextInfo [freq|self-info] [input file path] [output file path]");
		}
	}

}
