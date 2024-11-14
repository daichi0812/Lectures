/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class WarehouseClerk {
    // 定数フィールド
    public static String STOCK_LIST_FILE_PATH = "stock-list.csv";
    public static String NEW_STOCK_LIST_FILE_PATH = "new-stock-list.csv";
    public static String  OUT_OF_STOCK_LIST_FILE_PATH = "out-of-stock-list.csv";
    // フィールド
    private WarehouseKeeper warehouseKeeper;
    private List<Tag> tagList = new ArrayList<>();

    // 倉庫係を受け取って初期化するコンストラクタ
    public WarehouseClerk(WarehouseKeeper warehouseKeeper){
        this.warehouseKeeper = warehouseKeeper;
    }

    // メソッド
    // 積荷票を受け取り、積荷票リストに加える
    public void addTag(Tag tag) throws Exception {
        tagList.add(tag);
    }

    // 積荷票リストを返す
    public List<Tag> getTagList() {
        return tagList;
    }

    // 出庫依頼を受け、在庫確認と出庫指示を行う
    public boolean makeRequest(Order order) {
        int remainingBottles = order.getNumberOfBottles();
        List<RequestRecord> requestList = new ArrayList<>();

        // 在庫確認と出庫指示リスト作成
        for (Tag tag : tagList) {
            if (remainingBottles <= 0) break; // 残り本数が0になったら終了

            int shippedBottles = tag.takeLiquor(order.getBrand(), remainingBottles);
            if (shippedBottles > 0) {
                requestList.add(new RequestRecord(tag.getContainer(), order.getOrderId(),
                        order.getSendingCustomerName(), order.getBrand(), shippedBottles));
                remainingBottles -= shippedBottles;
            }
        }

        // 出庫指示の送信（在庫不足があっても出庫可能な分だけ出庫する）
        if (!requestList.isEmpty()) {
            try {
                warehouseKeeper.shipLiquors(requestList);
            } catch (Exception e) {
                System.out.println("出庫指示エラー: " + e.getMessage());
                return false;
            }
        }

        // 在庫不足がある場合、不足リストに記録
        if (remainingBottles > 0) {
            reportOufOfStockBottles(order, remainingBottles);
            return false;
        } else {
            return true;
        }
    }

    // 在庫不足リストをファイルに出力するメソッド
    public void reportOufOfStockBottles(Order order, int numOfOutOfStockBottles) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(OUT_OF_STOCK_LIST_FILE_PATH, true))) {
            writer.write(String.format("%s,%s,%s,%d",
                    order.getOrderId(),
                    order.getSendingCustomerName(),
                    order.getBrand(),
                    numOfOutOfStockBottles));
            writer.newLine();
        } catch (IOException e) {
            System.out.println("在庫不足リストのファイル書き込みエラー: " + e.getMessage());
        }
    }

    // 在庫リストをファイルに出力するメソッド
    public void writeStockList(String stockListFilePath) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(stockListFilePath))) {
            for (Tag tag : tagList) {
                String broughtDate = tag.getBroughtDate();
                if (broughtDate == null) {
                    broughtDate = "Unknown";
                }
                int containerId = tag.getContainerId();
                for (StockRecord record : tag.getStockRecordList()) {
                    writer.write(String.format("%d,%s,%s,%d",
                            containerId,
                            broughtDate,
                            record.getBrand(),
                            record.getNumberOfBottles()));
                    writer.newLine();
                }
            }
        } catch (IOException e) {
            System.out.println("在庫リストのファイル書き込みエラー: " + e.getMessage());
        }
    }
}
