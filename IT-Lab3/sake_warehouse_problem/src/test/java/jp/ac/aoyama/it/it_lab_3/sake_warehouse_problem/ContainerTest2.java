package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;


import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.Container;
import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.Liquor;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ContainerTest2 {
    private Container container;

    @BeforeEach
    public void initialize() {
        container = new Container(1);
        Liquor beer1 = new Liquor("BEER");
        container.putLiquor(beer1, 5);
        Liquor beer2 = new Liquor("BEER");
        container.putLiquor(beer2, 5);
        Liquor wine = new Liquor("WINE");
        container.putLiquor(wine, 5);
        Liquor whiskey = new Liquor("WHISKEY");
        container.putLiquor(whiskey, 8);
    }

    @Test
    public void testTakeLiquor1() {
        int actual = container.takeLiquor("BEER", 5);
        int expected = 5;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor2() {
        container.takeLiquor("BEER", 5);
        int actual = container.getStockList().size();
        int expected = 3;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor3() {
        container.takeLiquor("BEER", 8);
        int actual = container.getStockList().size();
        int expected = 3;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor4() {
        container.takeLiquor("BEER", 8);
        int actual = container.getStockList().get(0).getNumberOfBottles();
        int expected = 2;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor5() {
        container.takeLiquor("BEER", 3);
        int actual = container.getStockList().size();
        int expected = 4;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor6() {
        container.takeLiquor("BEER", 5);
        container.takeLiquor("BEER", 5);
        container.takeLiquor("WINE", 5);
        container.takeLiquor("WHISKEY", 8);
        int actual = container.getStockList().size();
        int expected = 0;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor7() {
        int actual = container.takeLiquor("BEER", 18);
        int expected = 10;
        assertEquals(expected, actual);
    }
}
