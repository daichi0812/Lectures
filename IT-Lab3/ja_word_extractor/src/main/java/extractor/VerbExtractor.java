/*
    情報テクノロジー学科
    15822108
    堀田大智
 */

package extractor;

import com.atilika.kuromoji.ipadic.Token;
import com.atilika.kuromoji.ipadic.Tokenizer;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;

public class VerbExtractor {
    private Tokenizer tokenizer;

    /**
     * tokenizerを初期化
     */
    public VerbExtractor() {
        tokenizer = new Tokenizer();
    }

    /**
     * 実習課題 5-2：
     * 日本語文から動詞のリストを取得するメソッド．
     *
     * @param line 日本語文
     * @return 品詞細分類が動詞である形態素の基本形のリスト
     */
    public List<String> getVerbList(String line) {
        List<String> verbList = new ArrayList<>();
        List<Token> tokens = tokenizer.tokenize(line);
        for(Token token : tokens){
            if(token.getPartOfSpeechLevel1().equals("動詞")){
                verbList.add(token.getBaseForm());
            }
        }
        return verbList;
    }

    /**
     * 実習課題 5-2：
     * 日本語テキストファイルから辞書順にソートした動詞のセットを取得するメソッド．
     *
     * @param inputFilePath 日本語テキストファイルのパス
     * @return 辞書順にソートした品詞細分類が動詞の形態素の基本形のセット
     */
    public Set<String> getVerbSet(String inputFilePath) {
        Set<String> verbSet = new TreeSet<>();
        try{
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath), Charset.forName("UTF-8"));
            for(String line : lines){
                verbSet.addAll(getVerbList(line));
            }
        }catch(IOException e){
            e.printStackTrace();
        }
        return verbSet;
    }

    /**
     * 実習課題 5-2：
     * 日本語テキストファイルから各文ごとの動詞のリストを抽出し，outputFilePathで指定したファイルに「文番号,動詞1,動詞2,動詞3...,動詞N」の形式で出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 動詞のリストを出力するファイルのパス
     */
    public void writeVerbList(String inputFilePath, String outputFilePath) {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))){
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath));
            int sentenceNumber = 1;
            for(String line : lines){
                List<String> verbList = getVerbList(line);
                if(!verbList.isEmpty()){
                    writer.write(sentenceNumber + "," + String.join(",", verbList) + "\n");
                }
                sentenceNumber ++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 実習課題 5-2：
     * outputFilePathで指定したファイルに，inputFilePathにある日本語テキストファイルから抽出した動詞のセットを，辞書順にソートして改行区切りで出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 動詞のセットを出力するファイルのパス
     */
    public void writeVerbSet(String inputFilePath, String outputFilePath) {
        try(BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))){
            Set<String> verbSet = getVerbSet(inputFilePath);
            int count = 1;
            for(String verb : verbSet) {
                if (count == verbSet.size()) {
                    writer.write(verb);
                } else {
                    writer.write(verb + "\n");
                }
                count++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 実習課題 5-A2（発展課題）：
     * outputFilePathで指定したファイルに，「動詞,出現回数」の形式でinputFilePathにある日本語テキストファイル中の動詞とその出現回数を，
     * 動詞の辞書順にソートして改行区切りで出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 動詞とその出現回数を出力するファイルのパス
     */
    public void writeVerbCountMap(String inputFilePath, String outputFilePath) {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))) {
            Map<String, Integer> verbCountMap = new TreeMap<>();
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath), Charset.forName("UTF-8"));

            for (String line : lines) {
                for (String verb : getVerbList(line)) {
                    verbCountMap.put(verb, verbCountMap.getOrDefault(verb, 0) + 1);
                }
            }
            for (Map.Entry<String, Integer> entry : verbCountMap.entrySet()) {
                writer.write(entry.getKey() + "," + entry.getValue() + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 実習課題 5-A4（発展課題）：
     * 日本語文を入力として，名詞-サ変接続と動詞-自立が連続する場合に，それらを一つにまとめて動詞句リストとして抽出するメソッド．
     *
     * @param line 日本語文
     * @return 動詞句のリスト
     */
    public List<String> getVerbPhraseList(String line) {
        List<String> verbPhraseList = new ArrayList<>();
        List<Token> tokens = tokenizer.tokenize(line);
        for (int i = 0; i < tokens.size() - 1; i++) {
            Token token1 = tokens.get(i);
            Token token2 = tokens.get(i + 1);

            if (token1.getPartOfSpeechLevel1().equals("名詞") && token1.getPartOfSpeechLevel2().equals("サ変接続")) {
                if (token2.getPartOfSpeechLevel1().equals("動詞")) {
                    String verbPhrase = token1.getSurface() + token2.getBaseForm();
                    verbPhraseList.add(verbPhrase);
                }
            }
        }
        return verbPhraseList;
    }

    /**
     * 実習課題 5-A4（発展課題）：
     * inputFilePathにある日本語テキストファイルから動詞句のセットを抽出するメソッド．
     *
     * @param inputFilePath 日本語テキストファイルのパス
     * @return 動詞句のセット
     */
    public Set<String> getVerbPhraseSet(String inputFilePath) {
        Set<String> verbPhraseSet = new TreeSet<>();
        try {
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath), Charset.forName("UTF-8"));
            for (String line : lines) {
                verbPhraseSet.addAll(getVerbPhraseList(line));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return verbPhraseSet;
    }

    /**
     * 実習課題 5-A4（発展課題）：
     * inputFilePathにある日本語テキストファイルから，各文ごとに動詞句のリストをoutputFilePathにあるファイルに出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 各文ごとに動詞句のリストを出力するファイルのパス
     */
    public void writeVerbPhraseList(String inputFilePath, String outputFilePath) {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))) {
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath), Charset.forName("UTF-8"));
            int sentenceNumber = 1;
            for (String line : lines) {
                List<String> verbPhraseList = getVerbPhraseList(line);
                writer.write(sentenceNumber + "," + String.join(",", verbPhraseList) + "\n");
                sentenceNumber++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 実習課題 5-A4（発展課題）：
     * inputFilePathにある日本語テキストファイルから動詞句のセットを改行区切りでoutputFilePathにあるファイルに出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 動詞句のセットを改行区切りで出力するファイルのパス
     */
    public void writeVerbPhraseSet(String inputFilePath, String outputFilePath) {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))) {
            Set<String> verbPhraseSet = getVerbPhraseSet(inputFilePath);
            List<String> verbPhraseList = new ArrayList<>(verbPhraseSet);
            for (int i = 0; i < verbPhraseList.size(); i++) {
                writer.write(verbPhraseList.get(i));
                if (i < verbPhraseList.size() - 1) {
                    writer.write("\n");
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
