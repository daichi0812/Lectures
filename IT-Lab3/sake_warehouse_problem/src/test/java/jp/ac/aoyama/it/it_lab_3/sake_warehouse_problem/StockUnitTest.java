package jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem;

import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.Liquor;
import jp.ac.aoyama.it.it_lab_3.sake_warehouse_problem.StockUnit;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class StockUnitTest {
    @Test
    public void testStockUnitConstructor() {
        Assertions.assertThrows(Exception.class, () -> {
            Liquor liquor = new Liquor("BEER");
            StockUnit stockUnit = new StockUnit(liquor, 30);
        });
    }
}
