/*
    15822108
    情報テクノロジー学科
    堀田大智
* */

package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Calendar;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class WarehouseClerkTest {

    private WarehouseKeeper warehouseKeeper;
    private WarehouseClerk warehouseClerk;

    private static final Path EXPECTED_STOCK_LIST_1_PATH = getResourcePath("/expected_output_files/expected-stock-list-1.csv");
    private static final Path EXPECTED_STOCK_LIST_2_PATH = getResourcePath("/expected_output_files/expected-stock-list-2.csv");
    private static final Path EXPECTED_OUT_OF_STOCK_LIST_1_PATH = getResourcePath("/expected_output_files/expected-out-of-stock-list-1.csv");
    private static final Path EXPECTED_OUT_OF_STOCK_LIST_2_PATH = getResourcePath("/expected_output_files/expected-out-of-stock-list-2.csv");

    private static Path getResourcePath(String resourcePath) {
        return new File(WarehouseClerkTest.class.getResource(resourcePath).getFile()).toPath();
    }

    @BeforeEach
    public void initialize() {
        warehouseKeeper = new WarehouseKeeper();
        warehouseClerk = new WarehouseClerk(warehouseKeeper);
        warehouseKeeper.setWarehouseClerk(warehouseClerk);

        try {
            if (Files.exists(Paths.get(WarehouseClerk.OUT_OF_STOCK_LIST_FILE_PATH))) {
                Files.delete(Paths.get(WarehouseClerk.OUT_OF_STOCK_LIST_FILE_PATH));
            }

            if (Files.exists(Paths.get(WarehouseClerk.STOCK_LIST_FILE_PATH))) {
                Files.delete(Paths.get(WarehouseClerk.STOCK_LIST_FILE_PATH));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void bringContainer1() {
        Container container = new Container(1);
        Liquor beer1 = new Liquor("BEER");
        container.putLiquor(beer1, 5);
        Liquor wine = new Liquor("WINE");
        container.putLiquor(wine, 5);
        Liquor beer2 = new Liquor("BEER");
        container.putLiquor(beer2, 5);
        Liquor whiskey = new Liquor("WHISKEY");
        container.putLiquor(whiskey, 8);
        Calendar broughtDate = Calendar.getInstance();
        broughtDate.set(2021, Calendar.NOVEMBER, 1);
        container.getTag().setBroughtDate(broughtDate.getTime());
        try {
            warehouseKeeper.bringContainers(container);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void bringContainer2() {
        Container container = new Container(2);
        Liquor beer = new Liquor("BEER");
        container.putLiquor(beer, 10);
        Liquor whiskey = new Liquor("WHISKEY");
        container.putLiquor(whiskey, 18);
        Calendar broughtDate = Calendar.getInstance();
        broughtDate.set(2021, Calendar.NOVEMBER, 1);
        container.getTag().setBroughtDate(broughtDate.getTime());
        try {
            warehouseKeeper.bringContainers(container);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testReportOufOfStockBottles1() {
        Order order = new Order("AA-0001-01", "WHISKEY", 18, "A-sake-shop");
        warehouseClerk.reportOufOfStockBottles(order, 10);
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.OUT_OF_STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_OUT_OF_STOCK_LIST_1_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testReportOufOfStockBottles2() {
        Order order1 = new Order("AA-0001-01", "WHISKEY", 18, "A-sake-shop");
        Order order2 = new Order("AA-0001-02", "BEER", 13, "B-sake-shop");
        warehouseClerk.reportOufOfStockBottles(order1, 10);
        warehouseClerk.reportOufOfStockBottles(order2, 5);
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.OUT_OF_STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_OUT_OF_STOCK_LIST_2_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testWriteStockList1() {
        bringContainer1();
        warehouseClerk.writeStockList(WarehouseClerk.STOCK_LIST_FILE_PATH);
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_STOCK_LIST_1_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testWriteStockList2() {
        bringContainer1();
        bringContainer2();
        warehouseClerk.writeStockList(WarehouseClerk.STOCK_LIST_FILE_PATH);
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_STOCK_LIST_2_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    /**
     * A-sake-shopがビール5本を注文．
     * bringContainer1メソッドにより，コンテナ1には，ビール5本，ワイン5本，ビール5本，ウイスキー8本が格納されているため，
     * ビール5本は出庫可能で，在庫不足はないことを確認．
     * makeRequestメソッドの戻り値がtrueであることを確認．
     */
    @Test
    public void testMakeRequest1() {
        bringContainer1();
        Order order = new Order("AA-0001-01", "BEER", 5, "A-sake-shop");
        boolean actual = warehouseClerk.makeRequest(order);
        boolean expected = true;
        assertEquals(expected, actual);
    }

    /**
     * A-sake-shopがビール5本を注文．
     * bringContainer1メソッドにより，コンテナ1には，ビール5本，ワイン5本，ビール5本，ウイスキー8本が格納されているため，
     * ビール5本を出庫するとコンテナ1のストックは3つとなることを確認．
     */
    @Test
    public void testMakeRequest2() {
        bringContainer1();
        Order order = new Order("AA-0001-01", "BEER", 5, "A-sake-shop");
        warehouseClerk.makeRequest(order);
        int actual = warehouseClerk.getTagList().get(0).getContainer().getStockList().size();
        int expected = 3;
        assertEquals(expected, actual);
    }

    /**
     * A-sake-shopがビール5本を注文．
     * bringContainer1メソッドにより，コンテナ1には，ビール5本，ワイン5本，ビール5本，ウイスキー8本が格納されているため，
     * ビール5本を出庫するとコンテナ1に対応する積荷票の在庫記録リストの要素数が3になることを確認．
     */
    @Test
    public void testMakeRequest3() {
        bringContainer1();
        Order order = new Order("AA-0001-01", "BEER", 5, "A-sake-shop");
        warehouseClerk.makeRequest(order);
        int actual = warehouseClerk.getTagList().get(0).getStockRecordList().size();
        int expected = 3;
        assertEquals(expected, actual);
    }

    /**
     * A-sake-shopがウィスキー18本を注文．
     * bringContainer1メソッドにより，コンテナ1には，ビール5本，ワイン5本，ビール5本，ウイスキー8本が格納されている．
     * コンテナにはウィスキー8本しか在庫がないため，ウィスキー18本の注文には対応できず，在庫不足となることを確認．
     * makeRequestメソッドの戻り値がfalseであることを確認．
     */
    @Test
    public void testMakeRequest4() {
        bringContainer1();
        Order order = new Order("AA-0001-01", "WHISKEY", 18, "A-sake-shop");
        boolean actual = warehouseClerk.makeRequest(order);
        boolean expected = false;
        assertEquals(expected, actual);
    }

    /**
     * A-sake-shopがウィスキー18本を注文．
     * bringContainer1メソッドにより，コンテナ1には，ビール5本，ワイン5本，ビール5本，ウイスキー8本が格納されている．
     * コンテナにはウィスキー8本しか在庫がないため，18本の注文には対応できず，ウィスキー10本が不足し，
     * 下記の在庫不足リストが出力されることを確認．
     * AA-0001-01,A-sake-shop,WHISKEY,10
     */
    @Test
    public void testMakeRequest5() {
        bringContainer1();
        Order order = new Order("AA-0001-01", "WHISKEY", 18, "A-sake-shop");
        warehouseClerk.makeRequest(order);
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.OUT_OF_STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_OUT_OF_STOCK_LIST_1_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * A-sake-shopがウィスキー18本を注文．
     * bringContainer1メソッドにより，コンテナ1には，ビール5本，ワイン5本，ビール5本，ウイスキー8本が格納されている．
     * ウィスキー8本は出庫できるため，コンテナ1のストックが3つとなることを確認．
     */
    @Test
    public void testMakeRequest6() {
        bringContainer1();
        Order order = new Order("AA-0001-01", "WHISKEY", 18, "A-sake-shop");
        warehouseClerk.makeRequest(order);
        int actual = warehouseClerk.getTagList().get(0).getContainer().getStockList().size();
        int expected = 3;
        assertEquals(expected, actual);
    }

    /**
     * A-sake-shopがウィスキー18本を注文．
     * bringContainer1メソッドにより，コンテナ1には，ビール5本，ワイン5本，ビール5本，ウイスキー8本が格納されている．
     * ウィスキー8本は出庫できるため，コンテナ1に対応する積荷票の在庫記録リストの要素数が3になることを確認．
     */
    @Test
    public void testMakeRequest7() {
        bringContainer1();
        Order order = new Order("AA-0001-01", "WHISKEY", 18, "A-sake-shop");
        warehouseClerk.makeRequest(order);
        int actual = warehouseClerk.getTagList().get(0).getStockRecordList().size();
        int expected = 3;
        assertEquals(expected, actual);
    }
}
