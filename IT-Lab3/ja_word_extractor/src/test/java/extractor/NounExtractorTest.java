/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package extractor;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import static extractor.WordExtractorUtils.*;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

public class NounExtractorTest {
    private NounExtractor nounExtractor;
    private static final Path TEST_INPUT_TEXT = WordExtractorUtils.getResourceFilePath(INPUT_FILES_DIR, "test_input1.txt");
    private static final Path ACTUAL_NOUN_LIST = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_noun_list.txt");
    private static final Path EXPECTED_NOUN_LIST = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_noun_list.txt");
    private static final Path ACTUAL_NOUN_SET = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_noun_set.txt");
    private static final Path EXPECTED_NOUN_SET = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_noun_set.txt");

    @BeforeEach
    public void initialize() {
        nounExtractor = new NounExtractor();
    }

    @Test
    public void testGetNounList() {
        List<String> actual = nounExtractor.getNounList("ビルは１０階建とし、エレベータは４基備えられている。");
        List<String> expected = Arrays.asList("ビル", "１", "０", "階", "建", "エレベータ", "４", "基");
        assertEquals(expected, actual);
    }

    @Test
    public void testGetNounSet() {
        Set<String> actual = nounExtractor.getNounSet(TEST_INPUT_TEXT.toString());
        Set<String> expected = new TreeSet<>(Arrays.asList("エレベータ", "ビル", "フロア", "ランダム", "人",
                "基", "建", "発生", "階", "０", "１", "４"));
        assertEquals(expected, actual);
    }

    @Test
    public void testWriteNounList() {
        nounExtractor.writeNounList(TEST_INPUT_TEXT.toString(), ACTUAL_NOUN_LIST.toString());
        try {
            String actual = Files.readString(ACTUAL_NOUN_LIST, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_NOUN_LIST, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }

    @Test
    public void testWriteNounSet() {
        nounExtractor.writeNounSet(TEST_INPUT_TEXT.toString(), ACTUAL_NOUN_SET.toString());
        try {
            String actual = Files.readString(ACTUAL_NOUN_SET, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_NOUN_SET, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }
}
