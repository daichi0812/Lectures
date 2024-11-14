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

public class AdvancedVerbExtractorTest {
    private VerbExtractor verbExtractor;
    private static final Path TEST_INPUT_TEXT = WordExtractorUtils.getResourceFilePath(INPUT_FILES_DIR, "test_input3.txt");
    private static final Path ACTUAL_VERB_COUNT_MAP = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_verb_count_map.txt");
    private static final Path EXPECTED_VERB_COUNT_MAP = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_verb_count_map.txt");
    private static final Path ACTUAL_VERB_PHRASE_LIST = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_verb_phrase_list.txt");
    private static final Path EXPECTED_VERB_PHRASE_LIST = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_verb_phrase_list.txt");
    private static final Path ACTUAL_VERB_PHRASE_SET = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_verb_phrase_set.txt");
    private static final Path EXPECTED_VERB_PHRASE_SET = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_verb_phrase_set.txt");

    @BeforeEach
    public void initialize() {
        verbExtractor = new VerbExtractor();
    }

    @Test
    public void testWriteVerbCountMap() {
        verbExtractor.writeVerbCountMap(TEST_INPUT_TEXT.toString(), ACTUAL_VERB_COUNT_MAP.toString());
        try {
            String actual = Files.readString(ACTUAL_VERB_COUNT_MAP, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_VERB_COUNT_MAP, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }

    @Test
    public void testGetVerbPhraseList() {
        List<String> actual = verbExtractor.getVerbPhraseList("人は各フロアでランダムに発生する。");
        List<String> expected = Arrays.asList("発生する");
        assertEquals(expected, actual);
    }

    @Test
    public void testGetVerbPhraseSet() {
        Set<String> actual = verbExtractor.getVerbPhraseSet(TEST_INPUT_TEXT.toString());
        Set<String> expected = new HashSet<>(Arrays.asList("停止する", "到着する", "消灯する", "点灯する", "要求する"));
        assertEquals(expected, actual);
    }

    @Test
    public void testWriteVerbPhraseList() {
        verbExtractor.writeVerbPhraseList(TEST_INPUT_TEXT.toString(), ACTUAL_VERB_PHRASE_LIST.toString());
        try {
            String actual = Files.readString(ACTUAL_VERB_PHRASE_LIST, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_VERB_PHRASE_LIST, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }

    @Test
    public void testWriteVerbPhraseSet() {
        verbExtractor.writeVerbPhraseSet(TEST_INPUT_TEXT.toString(), ACTUAL_VERB_PHRASE_SET.toString());
        try {
            String actual = Files.readString(ACTUAL_VERB_PHRASE_SET, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_VERB_PHRASE_SET, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }
}
