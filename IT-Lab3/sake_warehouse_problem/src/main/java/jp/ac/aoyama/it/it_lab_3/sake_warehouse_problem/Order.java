/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

public class Order {
    // フィールド
    private String orderId;
    private String brand;
    private int numberOfBottles;
    private String sendingCustomerName;

    // 各フィールドを初期化するコンストラクタ
    public Order(String orderId, String brand, int numberOfBottles, String sendingCustomerName) {
        this.orderId = orderId;
        this.brand = brand;
        this.numberOfBottles = numberOfBottles;
        this.sendingCustomerName = sendingCustomerName;
    }

    // メソッド
    // 酒の銘柄を取得する
    public String getBrand(){
        return brand;
    }
    // ボトル数を取得する
    public int getNumberOfBottles(){
        return numberOfBottles;
    }
    // 注文番号を取得する
    public String getOrderId(){
        return orderId;
    }
    // 送り先名を取得する
    public String getSendingCustomerName(){
        return sendingCustomerName;
    }
    // 注文情報を文字列で返す
    public String toString(){
        return String.format("%s,%s,%d,%s", orderId, brand, numberOfBottles, sendingCustomerName);
    }
}
