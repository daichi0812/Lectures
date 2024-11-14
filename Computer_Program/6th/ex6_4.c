/*
*ex6_4.c 15822108 情報テクノロジー 堀田大智
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

void embedText(const char *inputFile, const char *outputFile, const char *text) {
    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(outputFile, "w");

    if (input == NULL || output == NULL) {
        printf("ファイルを開くことができませんでした．\n");
        exit(1);
    }

    char magicNumber[3];
    int width, height, maxBrightness;
    fscanf(input, "%s %d %d %d", magicNumber, &width, &height, &maxBrightness);

    fprintf(output, "%s\n%d %d\n%d\n", magicNumber, width, height, maxBrightness);

    // 文字列の長さを先頭画素に埋め込む
    int textLength = strlen(text);
    fprintf(output, "%d ", textLength);

    int pixelCount = 0;
    int characterIndex = 0;
    int red, green, blue;

    while (!feof(input)) {
        fscanf(input, "%d %d %d", &red, &green, &blue);

        // 埋め込む文字列の文字コードで画素値を置き換える
        if (pixelCount % 100 == 0 && characterIndex < textLength) {
            red = (int)text[characterIndex];
            characterIndex++;
        }

        fprintf(output, "%d %d %d ", red, green, blue);

        pixelCount++;
    }

    fclose(input);
    fclose(output);
}

int main() {
    char inputFile[100];
    char outputFile[100];
    char text[MAX_LENGTH];

    printf("文字列を埋め込む画像ファイルの名前を入力してください：");
    scanf("%s", inputFile);

    printf("文字列を指定してください：");
    scanf("%s", text);

    // 出力ファイル名を生成
    strcpy(outputFile, inputFile);
    char *extension = strstr(outputFile, ".ppm");
    strcpy(extension, "_embedded.ppm");

    embedText(inputFile, outputFile, text);

    printf("ファイル %s を作成しました．\n", outputFile);

    return 0;
}
