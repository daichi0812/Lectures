package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.Customer;
import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.LiquorSalesCompany;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class CustomerTest {
    private Customer customer;

    @BeforeEach
    public void initialize() {
        LiquorSalesCompany supplier = new LiquorSalesCompany();
        customer = new Customer("A-sake-shop", supplier);
    }

    @Test
    public void testCreateOrder() {
        customer.createOrder("AA-0001-01", "WHISKEY", 18);
        customer.createOrder("AA-0001-02", "BEER", 2);
        int actual = customer.getNumberOfOrders();
        int expected = 2;
        assertEquals(expected, actual);
    }

}
