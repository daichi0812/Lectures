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

public class VerbExtractorTest {
    private VerbExtractor verbExtractor;
    private static final Path TEST_INPUT_TEXT = WordExtractorUtils.getResourceFilePath(INPUT_FILES_DIR, "test_input1.txt");
    private static final Path ACTUAL_VERB_LIST = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_verb_list.txt");
    private static final Path EXPECTED_VERB_LIST = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_verb_list.txt");
    private static final Path ACTUAL_VERB_SET = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_verb_set.txt");
    private static final Path EXPECTED_VERB_SET = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_verb_set.txt");

    @BeforeEach
    public void initialize() {
        verbExtractor = new VerbExtractor();
    }

    @Test
    public void testGetVerbList() {
        List<String> actual = verbExtractor.getVerbList("ビルは１０階建とし、エレベータは４基備えられている。");
        List<String> expected = Arrays.asList("する", "備える", "られる", "いる");
        assertEquals(expected, actual);
    }

    @Test
    public void testGetVerbSet() {
        Set<String> actual = verbExtractor.getVerbSet(TEST_INPUT_TEXT.toString());
        Set<String> expected = new TreeSet<>(Arrays.asList("いる", "する", "られる", "乗る", "備える", "待つ"));
        assertEquals(expected, actual);
    }

    @Test
    public void testWriteVerbList() {
        verbExtractor.writeVerbList(TEST_INPUT_TEXT.toString(), ACTUAL_VERB_LIST.toString());
        try {
            String actual = Files.readString(ACTUAL_VERB_LIST, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_VERB_LIST, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }

    @Test
    public void testWriteVerbSet() {
        verbExtractor.writeVerbSet(TEST_INPUT_TEXT.toString(), ACTUAL_VERB_SET.toString());
        try {
            String actual = Files.readString(ACTUAL_VERB_SET, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_VERB_SET, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }
}
