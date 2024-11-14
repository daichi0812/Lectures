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

public class SpecifiedMorphemeExtractorTest {
    private SpecifiedMorphemeExtractor specifiedMorphemeExtractor;
    private static final Path TEST_INPUT_TEXT = WordExtractorUtils.getResourceFilePath(INPUT_FILES_DIR, "test_input1.txt");
    private static final Path ACTUAL_MORPHEME_LIST = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_morpheme_list.txt");
    private static final Path EXPECTED_MORPHEME_LIST1 = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_noun_list.txt");
    private static final Path EXPECTED_MORPHEME_LIST2 = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_verb_list.txt");
    private static final Path ACTUAL_MORPHEME_SET = WordExtractorUtils.getResourceFilePath(ACTUAL_OUTPUT_FILES_DIR, "actual_morpheme_set.txt");
    private static final Path EXPECTED_MORPHEME_SET1 = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_noun_set.txt");
    private static final Path EXPECTED_MORPHEME_SET2 = WordExtractorUtils.getResourceFilePath(EXPECTED_OUTPUT_FILES_DIR, "expected_verb_set.txt");

    @BeforeEach
    public void initialize() {
        specifiedMorphemeExtractor = new SpecifiedMorphemeExtractor();
    }

    @Test
    public void testGetSpecifiedMorphemeList1() {
        List<String> actual = specifiedMorphemeExtractor.getSpecifiedMorphemeList("ビルは１０階建とし、エレベータは４基備えられている。", "名詞");
        List<String> expected = Arrays.asList("ビル", "１", "０", "階", "建", "エレベータ", "４", "基");
        assertEquals(expected, actual);
    }

    @Test
    public void testGetSpecifiedMorphemeList2() {
        List<String> actual = specifiedMorphemeExtractor.getSpecifiedMorphemeList("ビルは１０階建とし、エレベータは４基備えられている。", "動詞");
        List<String> expected = Arrays.asList("する", "備える", "られる", "いる");
        assertEquals(expected, actual);
    }

    @Test
    public void testGetSpecifiedMorphemeSet1() {
        Set<String> actual = specifiedMorphemeExtractor.getSpecifiedMorphemeSet(TEST_INPUT_TEXT.toString(), "名詞");
        Set<String> expected = new HashSet<>(Arrays.asList("エレベータ", "ビル", "フロア", "ランダム", "人",
                "基", "建", "発生", "階", "０", "１", "４"));
        assertEquals(expected, actual);
    }

    @Test
    public void testGetSpecifiedMorphemeSet2() {
        Set<String> actual = specifiedMorphemeExtractor.getSpecifiedMorphemeSet(TEST_INPUT_TEXT.toString(), "動詞");
        Set<String> expected = new HashSet<>(Arrays.asList("いる", "する", "られる", "乗る", "備える", "待つ"));
        assertEquals(expected, actual);
    }

    @Test
    public void testWriteSpecifiedMorphemeList1() {
        specifiedMorphemeExtractor.writeSpecifiedMorphemeList(TEST_INPUT_TEXT.toString(), ACTUAL_MORPHEME_LIST.toString(), "名詞");
        try {
            String actual = Files.readString(ACTUAL_MORPHEME_LIST, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_MORPHEME_LIST1, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }

    @Test
    public void testWriteSpecifiedMorphemeList2() {
        specifiedMorphemeExtractor.writeSpecifiedMorphemeList(TEST_INPUT_TEXT.toString(), ACTUAL_MORPHEME_LIST.toString(), "動詞");
        try {
            String actual = Files.readString(ACTUAL_MORPHEME_LIST, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_MORPHEME_LIST2, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }

    @Test
    public void testWriteSpecifiedMorphemeSet1() {
        specifiedMorphemeExtractor.writeSpecifiedMorphemeSet(TEST_INPUT_TEXT.toString(), ACTUAL_MORPHEME_SET.toString(), "名詞");
        try {
            String actual = Files.readString(ACTUAL_MORPHEME_SET, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_MORPHEME_SET1, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }

    @Test
    public void testWriteSpecifiedMorphemeSet2() {
        specifiedMorphemeExtractor.writeSpecifiedMorphemeSet(TEST_INPUT_TEXT.toString(), ACTUAL_MORPHEME_SET.toString(), "動詞");
        try {
            String actual = Files.readString(ACTUAL_MORPHEME_SET, StandardCharsets.UTF_8);
            String expected = Files.readString(EXPECTED_MORPHEME_SET2, StandardCharsets.UTF_8);
            assertEquals(expected, actual);
        } catch (IOException e) {
            e.printStackTrace();
            fail();
        }
    }
}
