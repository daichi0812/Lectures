package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

/**
 * 酒倉庫問題のメインクラス
 */
public class Main {

    /**
     * 搬入年月日
     */
    private static Date broughtDate;

    /**
     * 指定したファイルを削除する．
     *
     * @param filePath ファイルのパス
     */
    private static void removeFile(String filePath) {
        if (Files.exists(Paths.get(filePath))) {
            try {
                Files.delete(Paths.get(filePath));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 出力されたファイル（在庫リスト，出庫後の在庫リスト，在庫不足リスト，出庫依頼リスト）を削除する．
     */
    public static void removeOutputFiles() {
        removeFile(WarehouseClerk.STOCK_LIST_FILE_PATH);
        removeFile(WarehouseClerk.NEW_STOCK_LIST_FILE_PATH);
        removeFile(WarehouseClerk.OUT_OF_STOCK_LIST_FILE_PATH);
        removeFile(WarehouseKeeper.REQUEST_LIST_FILE_PATH);
    }

    /**
     * コンテナリストファイルを元に，酒類販売会社の倉庫にコンテナを搬入する．
     *
     * @param liquorSalesCompany    酒類販売会社
     * @param containerListFilePath コンテナリストファイルパス
     */
    public static void bringContainersFromFile(LiquorSalesCompany liquorSalesCompany, String containerListFilePath) {
        Map<Integer, Container> idContainerMap = new HashMap<>();

        try {
            List<String> lines = Files.readAllLines(Paths.get(containerListFilePath));

            for (String line : lines) {
                String[] parts = line.split(",");
                if (parts.length != 3) continue;

                int containerId = Integer.parseInt(parts[0].trim());
                String brand = parts[1].trim();
                int numberOfBottles = Integer.parseInt(parts[2].trim());

                // 既存のコンテナがあれば取得し、新しいコンテナが必要な場合は作成
                Container container = idContainerMap.get(containerId);
                if (container == null) {
                    container = new Container(containerId);
                    // TagのbroughtDateを設定
                    container.getTag().setBroughtDate(broughtDate);
                    idContainerMap.put(containerId, container);
                }
                // 新しい酒をコンテナに積み込む
                container.putLiquor(new Liquor(brand), numberOfBottles);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 全てのコンテナを倉庫に搬入
        for (Container c : idContainerMap.values()) {
            try {
                liquorSalesCompany.getWarehouseKeeper().bringContainers(c);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 出庫依頼ファイルから顧客リストを作成する．
     *
     * @param liquorSalesCompany      酒類販売会社
     * @param shippingRequestFilePath 出庫依頼ファイルパス
     * @return 顧客リスト
     */
    public static Collection<Customer> createCustomers(LiquorSalesCompany liquorSalesCompany, String shippingRequestFilePath) {
        Map<String, Customer> customerNameMap = new HashMap<>();
        List<String> customerNameList = Arrays.asList(Customer.CUSTOMER_NAME_LIST);

        try {
            List<String> lines = Files.readAllLines(Paths.get(shippingRequestFilePath));

            for (String line : lines) {
                String[] parts = line.split(",");
                if (parts.length != 4) continue;

                String orderId = parts[0].trim();
                String customerName = parts[1].trim();
                String brand = parts[2].trim();
                int numberOfBottles = Integer.parseInt(parts[3].trim());

                if (customerNameList.contains(customerName)) {
                    // 顧客が存在しなければ新しい顧客インスタンスを作成
                    Customer customer = customerNameMap.computeIfAbsent(customerName, name ->
                            new Customer(name, liquorSalesCompany)
                    );

                    // 顧客に注文を追加
                    customer.createOrder(orderId, brand, numberOfBottles);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return customerNameMap.values();
    }

    private static void printUsage() {
        System.err.println("Usage: \njava jp.ac.aoyama.it.sake_warehouse_problem.Main yyyy-MM-dd 出庫依頼ファイルパス コンテナリストファイルパス");
    }

    /**
     * メインメソッド
     * Usage: java jp.ac.aoyama.it.sake_warehouse_problem.Main yyyy-MM-dd 出庫依頼ファイルパス コンテナリストファイルパス
     *
     * @param args args[0]: yyyy-MM-dd, args[1]: 出庫依頼ファイルパス, args[2]: コンテナリストファイルパス
     */
    public static void main(String[] args) {
        if (args.length != 3) {
            printUsage();
            System.exit(-1);
        }

        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        try {
            broughtDate = sdf.parse(args[0]);
        } catch (ParseException e) {
            printUsage();
            e.printStackTrace();
            System.exit(-1);
        }

        String shippingRequestFilePath = args[1];
        if (!Files.exists(Paths.get(shippingRequestFilePath))) {
            System.err.printf("ERROR: Cannot open file '%s'.", shippingRequestFilePath);
            printUsage();
            System.exit(-1);
        }

        String containerListFilePath = args[2];
        if (!Files.exists(Paths.get(containerListFilePath))) {
            System.err.printf("ERROR: Cannot open file '%s'.", containerListFilePath);
            printUsage();
            System.exit(-1);
        }

        // 出力ファイルを削除する
        removeOutputFiles();

        // 酒類販売会社インスタンスの生成
        LiquorSalesCompany liquorSalesCompany = new LiquorSalesCompany();

        // ファイルから在庫搬入
        bringContainersFromFile(liquorSalesCompany, containerListFilePath);

        // 出庫前の在庫リストを出力
        liquorSalesCompany.getWarehouseClerk().writeStockList(WarehouseClerk.STOCK_LIST_FILE_PATH);

        // 顧客リストの作成
        Collection<Customer> customerList = createCustomers(liquorSalesCompany, shippingRequestFilePath);

        // 出庫依頼する
        for (Customer c : customerList) {
            c.order();
        }
        // 出庫後の在庫リストを出力
        liquorSalesCompany.getWarehouseClerk().writeStockList(WarehouseClerk.NEW_STOCK_LIST_FILE_PATH);
    }
}

