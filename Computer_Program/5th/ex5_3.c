#include <stdio.h>

int is_leap_year(int year);
int get_days(int year, int month);
int calculate_day_number(int year, int month, int day);
int calculate_day_of_week(int year, int month, int day);

int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char dayofweek[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int main() {
    int year, month, day;

    while (year < 2000) {
        printf("西暦を入力してください（2000年以降）：");
        scanf("%d", &year);
    }

    printf("月を入力してください：");
    while (1) {
        scanf("%d", &month);
        if (month < 1 || month > 12) {
            printf("月は1～12までの整数で入力してください：");
        } else {
            break;
        }
    }

    printf("日を入力してください：");
    while (1) {
        scanf("%d", &day);
        int maxDay = get_days(year, month);
        if (day < 1 || day > maxDay) {
            printf("日は1～%dまでの整数で入力してください：", maxDay);
        } else {
            break;
        }
    }

    int dayNumber = calculate_day_number(year, month, day);
    int dayOfWeek = calculate_day_of_week(year, month, day);

    printf("%d年での%d月%d日はその年の%d日目で曜日は%sです．\n", year, month, day, dayNumber, dayofweek[dayOfWeek]);

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
    if (month == 2 && is_leap_year(year)) {
        return 29;
    } else {
        return days[month - 1];
    }
}

int calculate_day_number(int year, int month, int day) {
    int dayNumber = 0;

    for (int m = 1; m < month; m++) {
        dayNumber += get_days(year, m);
    }

    dayNumber += day;

    return dayNumber;
}

int calculate_day_of_week(int year, int month, int day) {
    int startDayOfWeek = 6; // Saturday: 0, Sunday: 1, ..., Friday: 6
    int dayNumber = calculate_day_number(year, month, day);

    for (int y = 2000; y < year; y++) {
        startDayOfWeek += is_leap_year(y) ? 366 : 365;
    }

    startDayOfWeek = (startDayOfWeek + dayNumber - 1) % 7;

    return startDayOfWeek;
}
