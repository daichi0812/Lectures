package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.Container;
import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.Liquor;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TagTest {

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
        int actual = container.getTag().takeLiquor("BEER", 5);
        int expected = 5;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor2() {
        container.getTag().takeLiquor("BEER", 5);
        int actual = container.getTag().getStockRecordList().size();
        int expected = 3;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor3() {
        container.getTag().takeLiquor("BEER", 8);
        int actual = container.getTag().getStockRecordList().size();
        int expected = 3;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor4() {
        container.getTag().takeLiquor("BEER", 8);
        int actual = container.getTag().getStockRecordList().get(0).getNumberOfBottles();
        int expected = 2;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor5() {
        container.getTag().takeLiquor("BEER", 3);
        int actual = container.getTag().getStockRecordList().size();
        int expected = 4;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor6() {
        container.getTag().takeLiquor("BEER", 5);
        container.getTag().takeLiquor("BEER", 5);
        container.getTag().takeLiquor("WINE", 5);
        container.getTag().takeLiquor("WHISKEY", 8);
        int actual = container.getTag().getStockRecordList().size();
        int expected = 0;
        assertEquals(expected, actual);
    }

    @Test
    public void testTakeLiquor7() {
        int actual = container.getTag().takeLiquor("BEER", 18);
        int expected = 10;
        assertEquals(expected, actual);
    }
}
