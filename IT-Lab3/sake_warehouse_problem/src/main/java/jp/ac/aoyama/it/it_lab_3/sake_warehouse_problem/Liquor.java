/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

public class Liquor {
    // 酒の銘柄を格納するフィールド
    private String brand;

    // 銘柄を初期化するコンストラクタ
    public Liquor(String brand){
       this.brand = brand;
    }

    // 酒の銘柄を取得するゲッター
    public String getBrand(){
        return this.brand;
    }
}
