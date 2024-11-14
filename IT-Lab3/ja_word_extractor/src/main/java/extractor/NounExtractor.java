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

public class NounExtractor {
    private Tokenizer tokenizer;

    /**
     * tokenizerを初期化
     */
    public NounExtractor() {
        tokenizer = new Tokenizer();
    }

    /**
     * 実習課題 5-1：
     * 日本語文から名詞のリストを取得するメソッド．
     *
     * @param line 日本語文
     * @return 品詞細分類が名詞である形態素の基本形のリスト
     */
    public List<String> getNounList(String line) {
        List<String> nounList = new ArrayList<>();
        List<Token> tokens = tokenizer.tokenize(line);
        for (Token token : tokens) {
            if (token.getPartOfSpeechLevel1().equals("名詞")) {
                nounList.add(token.getBaseForm());
            }
        }
        return nounList;
    }

    /**
     * 実習課題 5-1：
     * 日本語テキストファイルから辞書順にソートした名詞のセットを取得するメソッド．
     *
     * @param inputFilePath 日本語テキストファイルのパス
     * @return 辞書順にソートした品詞細分類が名詞の形態素の基本形のセット
     */
    public Set<String> getNounSet(String inputFilePath) {
        Set<String> nounSet = new TreeSet<>();
        try{
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath), Charset.forName("UTF-8"));
            for(String line : lines) {
                nounSet.addAll(getNounList(line));
            }
        } catch(IOException e){
            e.printStackTrace();
        }
        return nounSet;
    }

    /**
     * 実習課題 5-1：
     * 日本語テキストファイルから各文ごとの名詞のリストを抽出し，
     * outputFilePathで指定したファイルに「文番号,名詞1,名詞2,名詞3...,名詞N」の形式で出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 名詞のリストを出力するファイルのパス
     */
    public void writeNounList(String inputFilePath, String outputFilePath) {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))){
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath));
            int sentenceNumber = 1;
            for(String line : lines){
                List<String> nounList = getNounList(line);
                if(!nounList.isEmpty()){
                    writer.write(sentenceNumber + "," + String.join(",", nounList) + "\n");
                }
                sentenceNumber ++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 実習課題 5-1：
     * 日本語テキストファイルから辞書順にソートした名詞のセットを，outputFilePathで指定したファイルに改行区切りで出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 名詞のセットを出力するファイルのパス
     */
    public void writeNounSet(String inputFilePath, String outputFilePath) {
        try(BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))) {
            Set<String> nounSet = getNounSet(inputFilePath);
            int count = 1;
            for (String noun : nounSet) {
                if(count == nounSet.size()){
                    writer.write(noun);
                }else{
                    writer.write(noun + "\n");
                }
                count ++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 実習課題 5-A2（発展課題）：
     * outputFilePathで指定したファイルに，「名詞,出現回数」の形式でinputFilePathにある日本語テキストファイル中の名詞とその出現回数を，
     * 名詞の辞書順にソートして改行区切りで出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 名詞とその出現回数を出力するファイルのパス
     */
    public void writeNounCountMap(String inputFilePath, String outputFilePath) {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))) {
            Map<String, Integer> nounCountMap = new TreeMap<>();
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath), Charset.forName("UTF-8"));

            for (String line : lines) {
                for (String noun : getNounList(line)) {
                    nounCountMap.put(noun, nounCountMap.getOrDefault(noun, 0) + 1);
                }
            }
            for (Map.Entry<String, Integer> entry : nounCountMap.entrySet()) {
                writer.write(entry.getKey() + "," + entry.getValue() + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 実習課題 5-A3（発展課題）
     * 日本語文を入力として，名詞が連続する場合に，それらを一つにまとめて複合名詞として抽出する．
     *
     * @param line 日本語文
     * @return 複合名詞のリスト
     */
    public List<String> getCompoundNounList(String line) {
        List<String> compoundNounList = new ArrayList<>();
        List<Token> tokens = tokenizer.tokenize(line);
        StringBuilder compoundNoun = new StringBuilder();
        int nounCount = 0;

        for (Token token : tokens) {
            if (token.getPartOfSpeechLevel1().equals("名詞")) {
                if (nounCount == 0) {
                    compoundNoun.setLength(0);
                    compoundNoun.append(token.getSurface());
                } else {
                    compoundNoun.append(token.getSurface());
                }
                nounCount++;
            } else {
                if (nounCount > 1) {
                    compoundNounList.add(compoundNoun.toString());
                }
                nounCount = 0;
                compoundNoun.setLength(0);
            }
        }

        if (nounCount > 1) {
            compoundNounList.add(compoundNoun.toString());
        }

        return compoundNounList;
    }

    /**
     * 実習課題 5-A3（発展課題）：
     * inputFilePathにある日本語テキストファイルから抽出した複合名詞のセットを返すメソッド．
     *
     * @param inputFilePath 日本語テキストファイルのパス
     * @return 日本語テキストファイルにある複合名詞のセット
     */
    public Set<String> getCompoundNounSet(String inputFilePath) {
        Set<String> compoundNounSet = new TreeSet<>();
        try {
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath), Charset.forName("UTF-8"));
            for (String line : lines) {
                compoundNounSet.addAll(getCompoundNounList(line));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return compoundNounSet;
    }

    /**
     * 実習課題 5-A3（発展課題）：
     * inputFilePathにある日本語テキストファイルから，各文ごとに複合名詞のリストを抽出し，outputFilePathに出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 各文ごとの複合名詞のリスト
     */
    public void writeCompoundNounList(String inputFilePath, String outputFilePath) {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))) {
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath), Charset.forName("UTF-8"));
            int sentenceNumber = 1;
            for (String line : lines) {
                List<String> compoundNounList = getCompoundNounList(line);
                writer.write(sentenceNumber + "," + String.join(",", compoundNounList) + "\n");
                sentenceNumber++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 実習課題 5-A3（発展課題）：
     * inputFilePathにある日本語テキストファイルから複合名詞のセットを抽出し，outputFilePathに改行区切りで出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 複合名詞のセットを出力するファイルのパス
     */
    public void writeCompoundNounSet(String inputFilePath, String outputFilePath) {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))) {
            Set<String> compoundNounSet = getCompoundNounSet(inputFilePath);
            int count = 1;
            for (String compoundNoun : compoundNounSet) {
                if(count == compoundNounSet.size()){
                    writer.write(compoundNoun);
                }else{
                    writer.write(compoundNoun + "\n");
                }
                count ++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
