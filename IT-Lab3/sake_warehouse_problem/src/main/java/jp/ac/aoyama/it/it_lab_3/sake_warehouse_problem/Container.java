/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.StockUnit;

public class Container {
    // 定数フィールド
    public static final int NUM_OF_MAX_CONTAINERS = 6;

    // コンテナ番号、集荷票、在庫リストのフィールド
    private int id;
    private Tag tag;
    private List<StockUnit> stockList;

    // コンテナ番号を初期化するコンストラクタ
    public Container(int id){
        this.id = id;
        this.tag = new Tag(this);
        this.stockList = new ArrayList<>();
    }

    // メソッド
    // コンテナを搬出する
    public void carryOut(){
        System.out.println("コンテナ番号: " + id + "のコンテナは空になったため、搬出されました。");
    }
    // コンテナ番号を取得する
    public int getId(){
        return id;
    }
    // 在庫リストを取得する
    public List<StockUnit> getStockList(){
        return stockList;
    }
    // 集荷票を取得する
    public Tag getTag(){
        return tag;
    }
    // コンテナに積み込まれたボトルの本数を返す
    public int getTotalNumberOfBottles(){
        int totalBottles = 0;
        for(StockUnit stockUnit : stockList){
            totalBottles += stockUnit.getNumberOfBottles();
        }
        return totalBottles;
    }
    // コンテナに酒を積み込み、その分を集荷票に加える
    public void putLiquor(Liquor liquor, int numberOfBottles){
        StockRecord stockRecord = new StockRecord(liquor.getBrand(), numberOfBottles);
        tag.addStockRecord(stockRecord);
        try {
            stockList.add(new StockUnit(liquor, numberOfBottles));
        } catch (Exception e) {
            System.out.println("エラー: " + e.getMessage());
        }
    }
    // コンテナから酒を出庫する
    public int takeLiquor(String brand, int numberOfBottlesToBeShipped) {
        int remainingBottlesToShip = numberOfBottlesToBeShipped;
        int shippedBottles = 0;

        for (int i = 0; i < stockList.size() && remainingBottlesToShip > 0; i++) {
            StockUnit stockUnit = stockList.get(i);

            if (stockUnit.getBrand().equals(brand)) {
                int availableBottles = stockUnit.getNumberOfBottles();

                if (availableBottles <= remainingBottlesToShip) {
                    shippedBottles += availableBottles;
                    remainingBottlesToShip -= availableBottles;

                    // 要素を削除
                    stockList.remove(i);
                    i--; // インデックスを調整
                } else {
                    try {
                        // ボトル数を減らす
                        stockUnit.setNumberOfBottles(availableBottles - remainingBottlesToShip);
                    } catch (Exception e) {
                        System.out.println("エラー: " + e.getMessage());
                    }
                    shippedBottles += remainingBottlesToShip;
                    remainingBottlesToShip = 0;
                    break;
                }
            }
        }

        return shippedBottles;
    }
}
