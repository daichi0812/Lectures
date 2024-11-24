package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

public class LiquorSalesCompany {
    // フィールド
    private WarehouseKeeper warehouseKeeper;
    private WarehouseClerk warehouseClerk;

    // コンストラクタ
    public LiquorSalesCompany(){
        this.warehouseKeeper = new WarehouseKeeper();
        this.warehouseClerk = new WarehouseClerk(warehouseKeeper);
        // 受付係 (WarehouseClerk) を倉庫係 (WarehouseKeeper) に設定
        this.warehouseKeeper.setWarehouseClerk(warehouseClerk);
    }

    // メソッド
    // 倉庫係を取得する
    public WarehouseClerk getWarehouseClerk(){
        return warehouseClerk;
    }
    // 受付係を取得する
    public WarehouseKeeper getWarehouseKeeper(){
        return warehouseKeeper;
    }

}
