/*
 * ex3_4 15822108　堀田大智
 */
#include <stdio.h>

int is_leap_year(int year);
int get_days(int year, int month);
int get_start_day_of_week(int year, int month);
void print_calendar(int year, int month);

int main() {
    int year, month;
	
	while(year<2000){
		printf("西暦を入力してください（2000年以降）：");
		scanf("%d", &year);
	}
	
    printf("月を入力してください：");
	while(1){
		scanf("%d", &month);
		if(month<1||12<month){
			printf("月は1~12までの整数で入力してください :");
			month=0;
		}
		else{
			break;
		}
	}

    print_calendar(year, month);

    return 0;
}

int is_leap_year(int year) {
    if (year % 100 == 0 && year % 400 == 0) {
        return 1;
    } else if (year % 100 == 0) {
        return 0;
    } else if (year % 4 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int get_days(int year, int month) {
    if (month == 2) {
        if (is_leap_year(year)) {
            return 29;
        } else {
            return 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

int get_start_day_of_week(int year, int month) {
    int startDayOfWeek = 6;  // 2000年1月1日（土曜日）を基準として、月の初日の曜日を表す数値（0:土曜日, 1:日曜日, 2:月曜日, ..., 6:金曜日）
    int day = 1;

    for (int y = 2000; y < year; y++) {
        if (is_leap_year(y)) {
            startDayOfWeek = (startDayOfWeek + 366) % 7;
        } else {
            startDayOfWeek = (startDayOfWeek + 365) % 7;
        }
    }

    for (int m = 1; m < month; m++) {
        startDayOfWeek = (startDayOfWeek + get_days(year, m)) % 7;
    }

    return startDayOfWeek;
}

void print_calendar(int year, int month) {
    int daysInMonth = get_days(year, month);
    int startDayOfWeek = get_start_day_of_week(year, month);
    int day = 1;

    // カレンダーのヘッダーを表示
    printf("%d年%d月\n", year, month);
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    // 月の初日までの空白を表示
    for (int i = 0; i < startDayOfWeek; i++) {
        printf("    ");
    }

    // 日付を表示
    for (int i = 1; i <= daysInMonth; i++) {
        printf("%3d ", day);

        // 改行処理と曜日の更新
		if ((startDayOfWeek + i) % 7 == 0) {
            printf("\n");
        }

        day++;
    }

    // 最終行の改行
    printf("\n");
}