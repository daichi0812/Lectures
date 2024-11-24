package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class WarehouseKeeperTest {
    private Container container;
    private WarehouseKeeper warehouseKeeper;
    private WarehouseClerk warehouseClerk;

    private static final Path EXPECTED_REQUEST_LIST_1_PATH = getResourcePath("/expected_output_files/expected-request-list-1.csv");

    private static Path getResourcePath(String resourcePath) {
        return new File(WarehouseKeeperTest.class.getResource(resourcePath).getFile()).toPath();
    }

    @BeforeEach
    public void initialize() {
        warehouseKeeper = new WarehouseKeeper();
        warehouseClerk = new WarehouseClerk(warehouseKeeper);
        warehouseKeeper.setWarehouseClerk(warehouseClerk);
        try {
            if (Files.exists(Paths.get(WarehouseKeeper.REQUEST_LIST_FILE_PATH))) {
                Files.delete(Paths.get(WarehouseKeeper.REQUEST_LIST_FILE_PATH));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void bringContainer1() {
        container = new Container(1);
        Liquor beer1 = new Liquor("BEER");
        container.putLiquor(beer1, 5);
        Liquor wine = new Liquor("WINE");
        container.putLiquor(wine, 5);
        Liquor beer2 = new Liquor("BEER");
        container.putLiquor(beer2, 5);
        Liquor whiskey = new Liquor("WHISKEY");
        container.putLiquor(whiskey, 8);
        Calendar broughtDate = Calendar.getInstance();
        broughtDate.set(2000, Calendar.JANUARY, 1);
        container.getTag().setBroughtDate(broughtDate.getTime());
        try {
            warehouseKeeper.bringContainers(container);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void bringContainer2() {
        container = new Container(2);
        Liquor beer1 = new Liquor("BEER");
        container.putLiquor(beer1, 5);
        Calendar broughtDate = Calendar.getInstance();
        broughtDate.set(2000, Calendar.JANUARY, 1);
        container.getTag().setBroughtDate(broughtDate.getTime());
        try {
            warehouseKeeper.bringContainers(container);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    @Test
    public void testBringContainers1() throws Exception {
        Container container = new Container(1);
        Liquor beer1 = new Liquor("BEER");
        container.putLiquor(beer1, 5);
        warehouseKeeper.bringContainers(container);
        int actual = warehouseKeeper.getNumberOfContainers();
        int expected = 1;
        assertEquals(expected, actual);
    }

    @Test
    public void testBringContainers2() throws Exception {
        Container container = new Container(1);
        Liquor beer1 = new Liquor("BEER");
        container.putLiquor(beer1, 5);
        warehouseKeeper.bringContainers(container);
        int actual = warehouseClerk.getTagList().size();
        int expected = 1;
        assertEquals(expected, actual);
    }

    @Test
    public void testBringContainers3() {
        Assertions.assertThrows(Exception.class, () -> {
            for (int i = 1; i < 8; i++) {
                warehouseKeeper.bringContainers(new Container(i));
            }
        });
    }

    @Test
    public void testShipLiquors1() throws Exception {
        bringContainer1();
        List<RequestRecord> requestList = new ArrayList<>();
        RequestRecord r1 = new RequestRecord(container, "AA-0001-01", "A-sake-shop", "BEER", 3);
        requestList.add(r1);
        warehouseKeeper.shipLiquors(requestList);
        List<String> actual = Files.readAllLines(Paths.get(WarehouseKeeper.REQUEST_LIST_FILE_PATH));
        List<String> expected = Files.readAllLines(WarehouseKeeperTest.EXPECTED_REQUEST_LIST_1_PATH);
        assertEquals(expected, actual);
    }

    @Test
    public void testShipLiquors2() throws Exception {
        bringContainer1();
        List<RequestRecord> requestList = new ArrayList<>();
        RequestRecord r1 = new RequestRecord(container, "AA-0001-01", "A-sake-shop", "BEER", 3);
        requestList.add(r1);
        warehouseKeeper.shipLiquors(requestList);
        int actual = container.getStockList().get(0).getNumberOfBottles();
        int expected = 2;
        assertEquals(expected, actual);
    }

    @Test
    public void testShipLiquors3() throws Exception {
        bringContainer2();
        List<RequestRecord> requestList = new ArrayList<>();
        RequestRecord r1 = new RequestRecord(container, "AA-0001-01", "A-sake-shop", "BEER", 5);
        requestList.add(r1);
        warehouseKeeper.shipLiquors(requestList);
        int actual = warehouseKeeper.getNumberOfContainers();
        int expected = 0;
        assertEquals(expected, actual);
    }

    @Test
    public void testShipLiquors4() throws Exception {
        bringContainer2();
        List<RequestRecord> requestList = new ArrayList<>();
        RequestRecord r1 = new RequestRecord(container, "AA-0001-01", "A-sake-shop", "BEER", 5);
        requestList.add(r1);
        warehouseKeeper.shipLiquors(requestList);
        int actual = warehouseClerk.getTagList().size();
        int expected = 0;
        assertEquals(expected, actual);
    }

    @Test
    public void testShipLiquors5() {
        bringContainer2();
        List<RequestRecord> requestList = new ArrayList<>();
        Assertions.assertThrows(Exception.class, () -> {
            // 倉庫に搬入していないコンテナ
            Container container3 = new Container(3);
            RequestRecord r1 = new RequestRecord(container3, "AA-0001-01", "A-sake-shop", "BEER", 5);
            requestList.add(r1);
            warehouseKeeper.shipLiquors(requestList);
        });
    }
}
