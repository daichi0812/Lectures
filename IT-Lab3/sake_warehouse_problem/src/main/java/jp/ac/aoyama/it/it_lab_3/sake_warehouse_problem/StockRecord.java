/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

public class StockRecord {
    // フィールド
    private String brand; // 酒の銘柄
    private int numberOfBottles; // ボトルの本数

    // 銘柄とボトルを初期化するコンストラクタ
    public StockRecord(String brand, int numberOfBottles){
        this.brand = brand;
        this.numberOfBottles = numberOfBottles;
    }

    // メソッド
    // 銘柄を取得する
    public String getBrand(){
        return this.brand;
    }
    // ボトルの本数を取得する
    public int getNumberOfBottles(){
        return this.numberOfBottles;
    }
    // ボトルの本数を設定する
    public void setNumberOfBottles(int numberOfBottles){
        this.numberOfBottles = numberOfBottles;
    }

}
