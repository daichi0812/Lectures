package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import java.util.ArrayList;
import java.util.List;

public class Customer {
    // 定数フィールド
    public static String[] CUSTOMER_NAME_LIST = {
            "A-sake-shop", "B-sake-shop", "C-sake-shop",
            "D-sake-shop", "E-sake-shop", "F-sake-shop",
            "G-sake-shop", "H-sake-shop", "I-sake-shop",
            "J-sake-shop", "K-sake-shop"
    };

    // 顧客名と取引先の酒類販売会社のフィールド
    private String name;
    private LiquorSalesCompany liquorSalesCompany;
    private List<Order> orderList;

    // 顧客名と酒類販売会社を初期化するコンストラクタ
    public Customer(String name, LiquorSalesCompany liquorSalesCompany) {
        this.name = name;
        this.liquorSalesCompany = liquorSalesCompany;
        this.orderList = new ArrayList<>();
    }

    // メソッド
    // 顧客名を取得する
    public String getName() {
        return name;
    }
    // 注文を作成する
    public void createOrder(String orderId, String brand, int numOfBottles) {
        Order newOrder = new Order(orderId, brand, numOfBottles, this.name);
        orderList.add(newOrder);
    }
    // 酒を注文する
    public void order() {
        WarehouseClerk clerk = liquorSalesCompany.getWarehouseClerk();
        for (Order order : orderList) {
            clerk.makeRequest(order);
        }
    }
    // 顧客が行った注文の数を取得する
    public int getNumberOfOrders() {
        return orderList.size();
    }
}
