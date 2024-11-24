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
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class SpecifiedMorphemeExtractor {

    private Tokenizer tokenizer;

    /**
     * tokenizerを初期化
     */
    public SpecifiedMorphemeExtractor() {
        tokenizer = new Tokenizer();
    }

    /**
     * 実習課題 5-A1（発展課題）：
     * 日本語文から指定した品詞の形態素のリストを取得するメソッド．
     *
     * @param line 日本語文
     * @param pos  品詞細分類（名詞，動詞など）
     * @return 指定した品詞細分類の形態素の基本形のリスト
     */
    public List<String> getSpecifiedMorphemeList(String line, String pos) {
        List<String> morphemeList = new ArrayList<>();
        List<Token> tokens = tokenizer.tokenize(line);
        for(Token token : tokens){
            if(token.getPartOfSpeechLevel1().equals(pos)){
                morphemeList.add(token.getBaseForm());
            }
        }
        return morphemeList;
    }

    /**
     * 実習課題 5-A1（発展課題）：
     * 日本語テキストファイルから辞書順にソートした指定した品詞の形態素のセットを取得するメソッド．
     *
     * @param inputFilePath 日本語テキストファイルのパス
     * @param pos           品詞細分類（名詞，動詞など）
     * @return 辞書順にソートした指定した品詞細分類の形態素の基本形のセット
     */
    public Set<String> getSpecifiedMorphemeSet(String inputFilePath, String pos) {
        Set<String> morphemeSet = new TreeSet<>();
        try {
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath));
            for (String line : lines) {
                for (Token token : tokenizer.tokenize(line)) {
                    if (token.getPartOfSpeechLevel1().equals(pos)) {
                        morphemeSet.add(token.getBaseForm());
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return morphemeSet;
    }

    /**
     * 実習課題 5-A1（発展課題）
     * 日本語テキストファイルから各文ごとの指定の品詞の形態素の基本形のリストを抽出し，
     * outputFilePathで指定したファイルに「文番号,形態素1,形態素2,...,N」の形式で出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 指定した形態素の基本形のリストを出力するファイルのパス
     * @param pos            品詞細分類（名詞，動詞など）
     */
    public void writeSpecifiedMorphemeList(String inputFilePath, String outputFilePath, String pos) {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))) {
            List<String> lines = Files.readAllLines(Paths.get(inputFilePath));
            int sentenceNumber = 1;
            for (String line : lines) {
                List<String> morphemes = getSpecifiedMorphemeList(line, pos);
                writer.write(sentenceNumber + "," + String.join(",", morphemes) + "\n");
                sentenceNumber++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 実習課題 5-A1（発展課題）:
     * outputFilePathで指定したファイルに，辞書順にソートした指定した品詞の形態素の基本形のセットを改行区切りで出力するメソッド．
     *
     * @param inputFilePath  日本語テキストファイルのパス
     * @param outputFilePath 指定した品詞の形態素の基本形のセットを出力するファイルのパス
     * @param pos            品詞細分類（名詞，動詞など）
     */
    public void writeSpecifiedMorphemeSet(String inputFilePath, String outputFilePath, String pos) {
        try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), Charset.forName("UTF-8"))) {
            Set<String> morphemeSet = getSpecifiedMorphemeSet(inputFilePath, pos);
            int count = 1;
            for (String morpheme : morphemeSet) {
                if(count == morphemeSet.size()){
                    writer.write(morpheme);
                }else{
                    writer.write(morpheme + "\n");
                }
                count++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
