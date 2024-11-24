package extractor;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import static extractor.WordExtractorUtils.*;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

public class AdvancedNounExtractorTest {
    private NounExtractor nounExtractor;
    private static final Path TEST_INPUT_TEXT = WordExtractorUtils.getResourceFilePath(INPUT_FILES_DIR, "test_input2.txt");
    private static final Path ACTUAL_NOUN_COUNT_MAP = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_noun_count_map.txt");
    private static final Path EXPECTED_NOUN_COUNT_MAP = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_noun_count_map.txt");
    private static final Path ACTUAL_COMPOUND_NOUN_LIST = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_compound_noun_list.txt");
    private static final Path EXPECTED_COMPOUND_NOUN_LIST = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_compound_noun_list.txt");
    private static final Path ACTUAL_COMPOUND_NOUN_SET = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_compound_noun_set.txt");
    private static final Path EXPECTED_COMPOUND_NOUN_SET = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_compound_noun_set.txt");

    @BeforeEach
    public void initialize() {
        nounExtractor = new NounExtractor();
    }

    @Test
    public void testWriteNounCountMap() {
        nounExtractor.writeNounCountMap(TEST_INPUT_TEXT.toString(), ACTUAL_NOUN_COUNT_MAP.toString());
        try {
            String actual = Files.readString(ACTUAL_NOUN_COUNT_MAP, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_NOUN_COUNT_MAP, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }

    @Test
    public void testGetCompoundNounList() {
        List<String> actual = nounExtractor.getCompoundNounList("ビルは１０階建とし、エレベータは４基備えられている。");
        List<String> expected = Arrays.asList("１０階建", "４基");
        assertEquals(expected, actual);
    }

    @Test
    public void testGetCompoundNounSet() {
        Set<String> actual = nounExtractor.getCompoundNounSet(TEST_INPUT_TEXT.toString());
        Set<String> expected = new HashSet<>(Arrays.asList("指定階", "搭乗者", "要求階"));
        assertEquals(expected, actual);
    }

    @Test
    public void testWriteCompoundNounList() {
        nounExtractor.writeCompoundNounList(TEST_INPUT_TEXT.toString(), ACTUAL_COMPOUND_NOUN_LIST.toString());
        try {
            String actual = Files.readString(ACTUAL_COMPOUND_NOUN_LIST, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_COMPOUND_NOUN_LIST, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }

    @Test
    public void testWriteCompoundNounSet() {
        nounExtractor.writeCompoundNounSet(TEST_INPUT_TEXT.toString(), ACTUAL_COMPOUND_NOUN_SET.toString());
        try {
            String actual = Files.readString(ACTUAL_COMPOUND_NOUN_SET, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_COMPOUND_NOUN_SET, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }
}
