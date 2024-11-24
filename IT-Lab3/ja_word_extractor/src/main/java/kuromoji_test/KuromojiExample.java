/* 15822108 堀田大智 */
package kuromoji_test;

import com.atilika.kuromoji.ipadic.Token;
import com.atilika.kuromoji.ipadic.Tokenizer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class KuromojiExample {
    private Tokenizer tokenizer;

    // private Tokenizer tokenizeフィールドを初期化
    public KuromojiExample(){
        tokenizer = new Tokenizer();
    }

    // 文字列を入力といsて、文字列中の基本形のリストを返すメソッド
    public List<String> getBaseFormList(String sentence){
        List<String> baseFormList = new ArrayList<>();
        List<Token> tokens = tokenizer.tokenize(sentence);

        for(int i = 0; i < tokens.size(); i++){
            String baseForm = tokens.get(i).getBaseForm();
            if(baseForm.isEmpty()){
                baseForm = tokens.get(i).getSurface();
            }
            baseFormList.add(baseForm);
        }
        return baseFormList;
    }

    // 文字列を入力として、文字列中の基本形をキー、基本形の読みを値とするHashMapのオブジェクトを返すメソッド
    public Map<String, String> getBaseFormReadingMap(String sentence){
        Map<String, String> baseFormReadingMap = new HashMap<>();
        List<Token> tokens = tokenizer.tokenize(sentence);
        for(int i = 0; i < tokens.size(); i++){
            String baseForm = getBaseFormList(sentence).get(i);
            String reading = tokens.get(i).getReading();
            if(reading.isEmpty()){
                reading = tokens.get(i).getSurface();
            }
            baseFormReadingMap.put(baseForm, reading);
        }
        return baseFormReadingMap;
    }

    public static void main(String[] args){
        Tokenizer tokenizer = new Tokenizer();
        List<Token> tokens = tokenizer.tokenize("ビルは10階建とし、エレベータは４基備えられている。");
        for(Token token : tokens){
            System.out.println("基本形: " + token.getBaseForm());
            System.out.println("活用形: " + token.getConjugationForm());
            System.out.println("活用型: " + token.getConjugationType());
            System.out.println("品詞細分類1: " + token.getPartOfSpeechLevel1());
            System.out.println("品詞細分類2: " + token.getPartOfSpeechLevel2());
            System.out.println("品詞細分類3: " + token.getPartOfSpeechLevel3());
            System.out.println("品詞細分類4: " + token.getPartOfSpeechLevel4());
            System.out.println("発音: " + token.getPronunciation());
            System.out.println("読み: " + token.getReading());
            System.out.println();
        }
    }


}
