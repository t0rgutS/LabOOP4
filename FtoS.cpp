#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "FtoS.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

#define MAX_STR 35

FloatString::FloatString() {
    floatStr = "";
    count = 0;
    point = 0;
    minus = false;
}

FloatString::FloatString(const FloatString &fs) {
    count = fs.count;
    for (int i = 0; i < count; i++)
        floatStr[i] = fs.floatStr[i];
    point = fs.point;
    minus = fs.minus;
}

void FloatString::operator++(int) {
    int i = 0;
    if (count) {
        try {
            if (point)
                i = point - 1;
            else
                i = count - 2;
            if (!minus) {
                if (floatStr[i] != '9') {
                    (int) floatStr[i]++;
                } else {
                    while (floatStr[i] == '9' && i > 0) {
                        floatStr[i] = '0';
                        if (i != 0)
                            i--;
                    }
                    if (floatStr[i] >= '0' && floatStr[i] <= '9')
                        (int) floatStr[i]++;
                }
            } else {
                if (floatStr[i] != '0') {
                    (int) floatStr[i]--;
                } else {
                    if (floatStr[i + 1] == '.')
                        floatStr = to_string(1 + stof(floatStr));
                    else {
                        while (floatStr[i] == '0' && i > 0) {
                            floatStr[i] = '9';
                            if (floatStr[i - 1] != '0') {
                                (int) floatStr[i - 1]--;
                            } else
                                i--;
                        }
                    }
                }
            }
            if (i == 0 && floatStr[i] == ':') {
                for (i = count - 1; i > 0; i--) {
                    floatStr[i + 1] = floatStr[i];
                }
                floatStr[0] = '1';
                if (count == 2 || floatStr[2] == '.')
                    floatStr[1] = '0';
                floatStr[count] = '\0';
                count++;
                if (count > MAX_STR)
                    throw 1;
            } else {
                if (minus)
                    i = 1;
                else
                    i = 0;
                if (floatStr[i] == '0' && floatStr[i + 1] != '.') {
                    if ((floatStr[i + 1] >= '0' && floatStr[i + 1] <= '9')) {
                        while (i < count) {
                            floatStr[i] = floatStr[i + 1];
                            i++;
                        }
                        floatStr[count] = '\0';
                        count--;
                    } else {
                        floatStr[0] = '0';
                        floatStr[1] = '\0';
                        count--;
                    }
                }
            }
            printf("Единица успешно прибавлена.\n");
        } catch (int) {
            printf("Строка слишком большая - не удалось прибавить 1.\n");
        }
    } else
        printf("Число еще не введено!\n");
}

void FloatString::operator+(const FloatString &fs1) {
    double d1, d2, d3;
    if (count && fs1.count) {
        try {
            d1 = stod(floatStr);
            d2 = stod(fs1.floatStr);
            d3 = d1 + d2;
            floatStr = to_string(d3);
            printf("Сложение успешно выполнено.\n");
        } catch (...) {
            printf("Ошибка! Возможно, хотя бы одно из чисел - слишком большое.\n");
        }
    } else
        printf("Числа еще не введены!\n");
}

FloatString operator+=(FloatString &fs1, const FloatString &fs2) {
    double d1, d2;
    if (fs1.count && fs2.count) {
        try {
            d1 = stod(fs1.floatStr);
            d2 = stod(fs2.floatStr);
            d1 += d2;
            fs1.floatStr = to_string(d1);
            printf("Сложение успешно выполнено.\n");
        } catch (...) {
            printf("Ошибка! Возможно, хотя бы одно из ваших чисел - слишком большое.\n");
        }
    } else
        printf("Числа еще не введены!\n");
}

istream &operator>>(istream &input, FloatString &f) {
    char key;
    f.count = 0;
    f.point = 0;
    f.minus = false;
    printf("Введите ваше число:");
    try {
        do {
            key = getch();
            if (f.count == 0 && (key == '-' || (key >= '0' && key <= '9'))) {
                f.floatStr[f.count] = key;
                f.count++;
                putch(key);
                if (key == '-')
                    f.minus = true;
            } else if (f.point == 0 && key == '.' && f.count != 0 &&
                       (f.floatStr[f.count - 1] >= '0' && f.floatStr[f.count - 1] <= '9')) {
                f.floatStr[f.count] = key;
                f.point = f.count;
                f.count++;
                putch(key);
            } else if (key >= '0' && key <= '9') {
                f.floatStr[f.count] = key;
                f.count++;
                putch(key);
            }
            if (f.count > MAX_STR)
                throw 8;
        } while (f.count == 0 || key != 13);
        if (f.count == 1 && f.floatStr[0] == '-') {
            f.count = 0;
            f.floatStr = "";
        } else {
            f.floatStr[f.count] = '\0';
            f.count++;
        }
    } catch (int) {
        while (getchar() != '\n');
        printf("\nВы ввели слишком много символов! Строка будет обнулена.\n");
        f.count = 0;
        f.floatStr = "";
    }
    printf("\n");
    return input;
}

ostream &operator<<(ostream &output, FloatString &f) {
    int i = 0;
    if (f.count) {
        printf("Ваше число: ");
        while (i < f.count) {
            putchar(f.floatStr[i]);
            i++;
        }
        printf("\n");
    } else
        printf("Число еще не введено!\n");
    return output;
}

int FloatString::GetCount() {
    return count;
}



