/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

public class StockUnit {
    // コンテナ内の最大ボトル数を格納する定数フィールド
    public int NUM_OF_MAX_BOTTLES = 20;

    // 酒とボトルの本数を格納するフィールド
    private Liquor liquor;
    private int numberOfBottles;

    // liquorとボトルの本数を初期化するコンストラクタ
    public StockUnit(Liquor liquor, int numberOfBottles) throws Exception {
        if(numberOfBottles > NUM_OF_MAX_BOTTLES){
            throw new Exception("最大ボトル数を超えています。");
        }
        this.liquor = liquor;
        this.numberOfBottles = numberOfBottles;
    }

    // メソッド
    // 酒の銘柄を取得する
    public String getBrand(){
        return this.liquor.getBrand();
    }
    // ボトルの本数を取得する
    public int getNumberOfBottles(){
        return this.numberOfBottles;
    }
    // ボトルの本数を設定する
    public void setNumberOfBottles(int numberOfBottles) throws Exception {
        if(numberOfBottles > NUM_OF_MAX_BOTTLES){
            throw new Exception("最大ボトル数を超えています。");
        }
        this.numberOfBottles = numberOfBottles;
    }
}
