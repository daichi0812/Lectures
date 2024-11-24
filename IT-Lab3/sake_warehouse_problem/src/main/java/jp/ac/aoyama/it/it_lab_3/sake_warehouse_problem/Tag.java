/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Tag {
    // フィールド
    private Container container;
    private List<StockRecord> stockRecordList;
    private Date broughtDate;

    // コンテナを初期化するコンストラクタ
    public Tag(Container container){
        this.container = container;
        this.stockRecordList = new ArrayList<>();
    }

    // メソッド
    // 在庫記録を追加する
    public void addStockRecord(StockRecord stockRecord){
        this.stockRecordList.add(stockRecord);
    }

    // 酒をコンテナに搬入した年月日を取得する
    public String getBroughtDate(){
        if (broughtDate == null) {
            return "Unknown";
        }
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        return sdf.format(broughtDate);
    }

    // コンテナを取得する
    public Container getContainer(){
        return this.container;
    }

    // コンテナIDを取得する
    public int getContainerId(){
        return this.container.getId();
    }

    // 在庫記録リストを取得する
    public List<StockRecord> getStockRecordList(){
        return this.stockRecordList;
    }

    // broughtDateを設定する
    public void setBroughtDate(Date broughtDate){
        this.broughtDate = broughtDate;
    }

    // 積荷票から出庫する酒の銘柄のボトルの本数を差し引く
    public int takeLiquor(String brand, int numOfBottlesToBeShipped) {
        int remainingBottlesToShip = numOfBottlesToBeShipped;
        int shippedBottles = 0;

        // stockRecordListを更新
        for (int i = 0; i < stockRecordList.size() && remainingBottlesToShip > 0; i++) {
            StockRecord stockRecord = stockRecordList.get(i);

            if (stockRecord.getBrand().equals(brand)) {
                int availableBottles = stockRecord.getNumberOfBottles();

                if (availableBottles <= remainingBottlesToShip) {
                    shippedBottles += availableBottles;
                    remainingBottlesToShip -= availableBottles;

                    // 要素を削除
                    stockRecordList.remove(i);
                    i--; // インデックスを調整
                } else {
                    // ボトル数を減らす
                    stockRecord.setNumberOfBottles(availableBottles - remainingBottlesToShip);
                    shippedBottles += remainingBottlesToShip;
                    remainingBottlesToShip = 0;
                    break;
                }
            }
        }

        // Containerの在庫をここで減少させない

        return shippedBottles;
    }
}
