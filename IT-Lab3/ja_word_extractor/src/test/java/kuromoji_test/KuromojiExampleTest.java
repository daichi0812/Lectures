/* 15822108 堀田大智 */
package kuromoji_test;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.List;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class KuromojiExampleTest {

    private KuromojiExample kuromojiExample;

    @BeforeEach
    public void initialize() {
        kuromojiExample = new KuromojiExample();
    }

    @Test
    public void testGetBaseFormList() {
        List<String> actual = kuromojiExample.getBaseFormList("吾輩は猫である");
        List<String> expected = Arrays.asList("吾輩", "は", "猫", "だ", "ある");
        assertEquals(expected, actual);
    }

    @Test
    public void testGetBaseFormReadingMap() {
        Map<String, String> baseFormReadingMap = kuromojiExample.getBaseFormReadingMap("吾輩は猫である");
        String[] actual = new String[] {baseFormReadingMap.get("吾輩"), baseFormReadingMap.get("猫")};
        String[] expected = {"ワガハイ", "ネコ"};
        assertArrayEquals(expected, actual);
    }
}
