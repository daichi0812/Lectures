/*
    情報テクノロジー学科
    15822108
    堀田大智
 */
package extractor;

import java.io.File;
import java.net.URL;
import java.nio.file.Path;

public class WordExtractorUtils {
    public static final URL INPUT_FILES_DIR = WordExtractorUtils.class.getResource("/input_files/");
    public static final URL EXPECTED_OUTPUT_FILES_DIR = WordExtractorUtils.class.getResource("/expected_output_files/");
    public static final URL ACTUAL_OUTPUT_FILES_DIR = WordExtractorUtils.class.getResource("/actual_output_files/");

    public static Path getResourceFilePath(URL dirURL, String fileName) {
        return new File(dirURL.getFile() + fileName).toPath();
    }
}
