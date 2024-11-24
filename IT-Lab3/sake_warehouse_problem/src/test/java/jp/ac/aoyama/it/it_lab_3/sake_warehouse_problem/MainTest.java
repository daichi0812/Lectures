package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class MainTest {
    private LiquorSalesCompany liquorSalesCompany;
    private static final String BROUGHT_DATE = "2021-11-01";
    private static final Path CONTAINER_LIST_1_PATH = getResourcePath("/input_files/container-list-1.csv");
    private static final Path CONTAINER_LIST_2_PATH = getResourcePath("/input_files/container-list-2.csv");
    private static final Path CONTAINER_LIST_3_PATH = getResourcePath("/input_files/container-list-3.csv");
    private static final Path SHIPPING_REQUEST_1_PATH = getResourcePath("/input_files/shipping-request-1.csv");
    private static final Path SHIPPING_REQUEST_2_PATH = getResourcePath("/input_files/shipping-request-2.csv");
    private static final Path SHIPPING_REQUEST_3_PATH = getResourcePath("/input_files/shipping-request-3.csv");
    private static final Path SHIPPING_REQUEST_4_PATH = getResourcePath("/input_files/shipping-request-4.csv");
    private static final Path EXPECTED_STOCK_LIST_3_PATH = getResourcePath("/expected_output_files/expected-stock-list-3.csv");
    private static final Path EXPECTED_REQUEST_LIST_2_PATH = getResourcePath("/expected_output_files/expected-request-list-2.csv");
    private static final Path EXPECTED_OUT_OF_STOCK_LIST_3_PATH = getResourcePath("/expected_output_files/expected-out-of-stock-list-3.csv");
    private static final Path EXPECTED_OUT_OF_STOCK_LIST_4_PATH = getResourcePath("/expected_output_files/expected-out-of-stock-list-4.csv");
    private static final Path EXPECTED_OUT_OF_STOCK_LIST_5_PATH = getResourcePath("/expected_output_files/expected-out-of-stock-list-5.csv");
    private static final Path EXPECTED_NEW_STOCK_LIST_1_PATH = getResourcePath("/expected_output_files/expected-new-stock-list-1.csv");
    private static final Path EXPECTED_NEW_STOCK_LIST_2_PATH = getResourcePath("/expected_output_files/expected-new-stock-list-2.csv");
    private static final Path EXPECTED_NEW_STOCK_LIST_3_PATH = getResourcePath("/expected_output_files/expected-new-stock-list-3.csv");
    private static final Path EXPECTED_NEW_STOCK_LIST_4_PATH = getResourcePath("/expected_output_files/expected-new-stock-list-4.csv");

    private static Path getResourcePath(String resourcePath) {
        return new File(MainTest.class.getResource(resourcePath).getFile()).toPath();
    }

    @BeforeEach
    public void initialize() {
        liquorSalesCompany = new LiquorSalesCompany();
    }

    @Test
    public void testBringContainersFromFile1() {
        Main.bringContainersFromFile(liquorSalesCompany, CONTAINER_LIST_1_PATH.toString());
        int actual = liquorSalesCompany.getWarehouseKeeper().getNumberOfContainers();
        int expected = 1;
        assertEquals(expected, actual);
    }

    @Test
    public void testBringContainersFromFile2() {
        Main.bringContainersFromFile(liquorSalesCompany, CONTAINER_LIST_1_PATH.toString());
        int actual = liquorSalesCompany.getWarehouseClerk().getTagList().size();
        int expected = 1;
        assertEquals(expected, actual);
    }

    @Test
    public void testBringContainersFromFile3() {
        Main.bringContainersFromFile(liquorSalesCompany, CONTAINER_LIST_1_PATH.toString());
        int actual = liquorSalesCompany.getWarehouseClerk().getTagList().get(0).getContainer().getStockList().size();
        int expected = 3;
        assertEquals(expected, actual);
    }

    @Test
    public void testBringContainersFromFile4() {
        Main.bringContainersFromFile(liquorSalesCompany, CONTAINER_LIST_1_PATH.toString());
        int actual = liquorSalesCompany.getWarehouseClerk().getTagList().get(0).getContainer().getStockList().get(0).getNumberOfBottles();
        int expected = 15;
        assertEquals(expected, actual);
    }

    @Test
    public void testCreateCustomers1() {
        Collection<Customer> customers = Main.createCustomers(liquorSalesCompany, SHIPPING_REQUEST_1_PATH.toString());
        int actual = customers.size();
        int expected = 2;
        assertEquals(expected, actual);
    }

    @Test
    public void testCreateCustomers2() {
        Collection<Customer> customers = Main.createCustomers(liquorSalesCompany, SHIPPING_REQUEST_1_PATH.toString());
        List<Customer> customerList = new ArrayList<>(customers);
        String actual = customerList.get(0).getName();
        String expected = "A-sake-shop";
        assertEquals(expected, actual);
    }

    @Test
    public void testCreateCustomers3() {
        Collection<Customer> customers = Main.createCustomers(liquorSalesCompany, SHIPPING_REQUEST_1_PATH.toString());
        List<Customer> customerList = new ArrayList<>(customers);
        int actual = customerList.get(0).getNumberOfOrders();
        int expected = 2;
        assertEquals(expected, actual);
    }

    @Test
    public void testMain1() {
        Main.main(new String[]{BROUGHT_DATE, SHIPPING_REQUEST_1_PATH.toString(), CONTAINER_LIST_1_PATH.toString()});
        try {
            System.out.println(WarehouseClerk.STOCK_LIST_FILE_PATH);
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_STOCK_LIST_3_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testMain2() {
        Main.main(new String[]{BROUGHT_DATE, SHIPPING_REQUEST_1_PATH.toString(), CONTAINER_LIST_1_PATH.toString()});
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseKeeper.REQUEST_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_REQUEST_LIST_2_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testMain3() {
        Main.main(new String[]{BROUGHT_DATE, SHIPPING_REQUEST_1_PATH.toString(), CONTAINER_LIST_1_PATH.toString()});
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.NEW_STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_NEW_STOCK_LIST_1_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testMain4() {
        Main.main(new String[]{BROUGHT_DATE, SHIPPING_REQUEST_2_PATH.toString(), CONTAINER_LIST_1_PATH.toString()});
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.NEW_STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_NEW_STOCK_LIST_2_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testMain5() {
        Main.main(new String[]{BROUGHT_DATE, SHIPPING_REQUEST_2_PATH.toString(), CONTAINER_LIST_1_PATH.toString()});
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.OUT_OF_STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_OUT_OF_STOCK_LIST_3_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testMain6() {
        Main.main(new String[]{BROUGHT_DATE, SHIPPING_REQUEST_3_PATH.toString(), CONTAINER_LIST_2_PATH.toString()});
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.NEW_STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_NEW_STOCK_LIST_3_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testMain7() {
        Main.main(new String[]{BROUGHT_DATE, SHIPPING_REQUEST_3_PATH.toString(), CONTAINER_LIST_2_PATH.toString()});
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.OUT_OF_STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_OUT_OF_STOCK_LIST_4_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testMain8() {
        Main.main(new String[]{BROUGHT_DATE, SHIPPING_REQUEST_4_PATH.toString(), CONTAINER_LIST_3_PATH.toString()});
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.NEW_STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_NEW_STOCK_LIST_4_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testMain9() {
        Main.main(new String[]{BROUGHT_DATE, SHIPPING_REQUEST_4_PATH.toString(), CONTAINER_LIST_3_PATH.toString()});
        try {
            List<String> actual = Files.readAllLines(Paths.get(WarehouseClerk.OUT_OF_STOCK_LIST_FILE_PATH));
            List<String> expected = Files.readAllLines(EXPECTED_OUT_OF_STOCK_LIST_5_PATH);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
