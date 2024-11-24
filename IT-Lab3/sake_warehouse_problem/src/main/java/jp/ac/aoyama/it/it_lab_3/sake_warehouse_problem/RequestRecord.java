/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

public class RequestRecord {
    //コンテナ、注文番号、送り先名、酒の銘柄、ボトルの本数のフィールド
    private Container container;
    private String orderId;
    private String sendingCustomerName;
    private String brand;
    private int numberOfBottles;

    // 各フィールドを初期化するコンストラクタ
    public RequestRecord(Container container, String orderId, String sendingCustomerName, String brand, int numberOfBottles) {
        this.container = container;
        this.orderId = orderId;
        this.sendingCustomerName = sendingCustomerName;
        this.brand = brand;
        this.numberOfBottles = numberOfBottles;
    }

    // メソッド
    // 酒の銘柄を取得
    public String getBrand(){
        return brand;
    }
    // コンテナを取得
    public Container getContainer(){
        return container;
    }
    // ボトルの本数を取得
    public int getNumberOfBottles(){
        return numberOfBottles;
    }
    // 出庫指示書の一行分を返す
    public String toString(){
        return String.format("%s,%d,%s,%s,%d", orderId, container.getId(), sendingCustomerName, brand, numberOfBottles);
    }

}
