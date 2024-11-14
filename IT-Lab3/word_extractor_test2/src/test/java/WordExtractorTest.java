import org.junit.jupiter.api.Test;
import word_extractor.WordExtractor;

import java.util.*;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class WordExtractorTest {
    @Test
    public void testGetWordList() {
        List<String> actual = WordExtractor.getWordList("As of 2019, Java was one of the most popular programming languages in use according to GitHub.");
        List<String> expected = Arrays.asList("as", "of", "2019", "java", "was", "one", "of", "the", "most", "popular", "programming", "languages", "in", "use", "according", "to", "github");
        assertEquals(expected, actual);
    }

    @Test
    public void testGetWordSet() {
        Set<String> actual = WordExtractor.getWordSet("As of 2019, Java was one of the most popular programming languages in use according to GitHub.");
        List<String> wordList = Arrays.asList("as", "of", "2019", "java", "was", "one", "of", "the", "most", "popular", "programming", "languages", "in", "use", "according", "to", "github");
        Set<String> expected = new TreeSet<>(wordList);
        assertEquals(expected, actual);
    }

    @Test
    public void testGetWordCountMap() {
        List<String> wordList = Arrays.asList("as", "of", "2019", "java", "was", "one", "of", "the", "most", "popular", "programming", "languages", "in", "use", "according", "to", "github");
        Map<String, Integer> actual = WordExtractor.getWordCountMap(wordList);
        Map<String, Integer> expected = new TreeMap<>();
        expected.put("2019", 1);
        expected.put("according", 1);
        expected.put("as", 1);
        expected.put("github", 1);
        expected.put("in", 1);
        expected.put("java", 1);
        expected.put("languages", 1);
        expected.put("most", 1);
        expected.put("of", 2);
        expected.put("one", 1);
        expected.put("popular", 1);
        expected.put("programming", 1);
        expected.put("the", 1);
        expected.put("to", 1);
        expected.put("use", 1);
        expected.put("was", 1);

        assertEquals(expected, actual);
    }
}
