package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.Container;
import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.Liquor;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;


public class ContainerTest1 {
    private Container container;

    @BeforeEach
    public void initialize() {
        container = new Container(1);
    }

    @Test
    public void testGetTotalNumberOfBottles() {
        container = new Container(1);
        Liquor beer1 = new Liquor("BEER");
        container.putLiquor(beer1, 5);
        Liquor beer2 = new Liquor("BEER");
        container.putLiquor(beer2, 5);
        Liquor wine = new Liquor("WINE");
        container.putLiquor(wine, 5);
        int actual = container.getTotalNumberOfBottles();
        int expected = 15;
        assertEquals(expected, actual);
    }

    @Test
    public void testPutLiquor1() {
        Liquor liquor = new Liquor("BEER");
        container.putLiquor(liquor, 5);
        String actual = container.getTag().getStockRecordList().get(0).getBrand();
        String expected = "BEER";
        assertEquals(expected, actual);
    }

    @Test
    public void testPutLiquor2() {
        Liquor liquor = new Liquor("BEER");
        container.putLiquor(liquor, 5);
        int actual = container.getTag().getStockRecordList().get(0).getNumberOfBottles();
        int expected = 5;
        assertEquals(expected, actual);
    }

}
