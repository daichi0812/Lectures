/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class WarehouseKeeper {
    // 出庫依頼リストを保存するファイルパス定数フィールド
    public static final String REQUEST_LIST_FILE_PATH = "request-list.csv";
    // フィールド
    private WarehouseClerk warehouseClerk;
    private List<Container> containerList = new ArrayList<>();

    // コンストラクタ(デフォルトコンストラクタ)
    public WarehouseKeeper(){}

    // メソッド
    // コンテナを倉庫に搬入し、受付係にコンテナの積荷票を渡す
    public void bringContainers(Container container) throws Exception{
        // warehouseClerkが設定されていることを確認
        if (warehouseClerk == null) {
            throw new Exception("受付係 (WarehouseClerk) が設定されていません。");
        }

        // コンテナの上限を確認
        if (containerList.size() >= Container.NUM_OF_MAX_CONTAINERS) {
            throw new Exception("倉庫にこれ以上コンテナを搬入できません");
        }

        // コンテナを倉庫に追加し、受付係に積荷票を渡す
        containerList.add(container);
        warehouseClerk.addTag(container.getTag());
    }

    // 倉庫に保管されているコンテナ数を返すメソッド
    public int getNumberOfContainers(){
        return containerList.size();
    }

    // 受付係を設定するメソッド
    public void setWarehouseClerk(WarehouseClerk warehouseClerk){
        this.warehouseClerk = warehouseClerk;
    }

    // 出庫指示に従って倉庫から酒を出庫するメソッド
    public void shipLiquors(List<RequestRecord> requestList) throws Exception {
        // warehouseClerkが設定されていることを確認
        if (warehouseClerk == null) {
            throw new Exception("受付係 (WarehouseClerk) が設定されていません。");
        }

        try(BufferedWriter writer = new BufferedWriter(new FileWriter(REQUEST_LIST_FILE_PATH, true))){
            for(RequestRecord request : requestList){
                Container container = request.getContainer();
                // コンテナが倉庫にあるか確認
                if(!containerList.contains(container)){
                    throw new Exception("指定されたコンテナは倉庫に存在しません");
                }

                // 在庫がまだ存在する場合のみ減少させる
                int availableBottlesContainer = 0;
                for (StockUnit stockUnit : container.getStockList()) {
                    if (stockUnit.getBrand().equals(request.getBrand())) {
                        availableBottlesContainer += stockUnit.getNumberOfBottles();
                    }
                }

                // 在庫を減少させる
                int shippedBottles = container.takeLiquor(request.getBrand(), request.getNumberOfBottles());
                if (shippedBottles != request.getNumberOfBottles()) {
                    throw new Exception("在庫不足が発生しました");
                }

                writer.write(request.toString());
                writer.newLine();
                // コンテナが空の場合は搬出処理
                if(container.getTotalNumberOfBottles() == 0){
                    containerList.remove(container);
                    container.carryOut();
                    // 受付係の集荷リストから削除
                    warehouseClerk.getTagList().remove(container.getTag());
                }
            }
        }catch(IOException e){
            System.out.println("ファイル書き込みエラー: " + e.getMessage());
        }
    }
}
