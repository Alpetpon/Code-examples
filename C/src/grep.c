#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h> 

#define MAX_LINE_LENGTH 1024 // Максимальная длина строки

// Функция для вывода сообщения об ошибке
void print_error(const char *message) {
    fprintf(stderr, "Ошибка: %s\n", message);
}

// Функция для поиска совпадений в строке
void grep(const char *pattern, const char *filename, bool ignore_case, bool invert_match, bool print_count, bool print_filenames, bool print_line_numbers, bool print_matched_lines, bool suppress_errors, bool print_only_matched_parts) {
    FILE *file = fopen(filename, "r"); // Открытие файла для чтения
    if (file == NULL) { // Проверка на успешное открытие файла
        if (!suppress_errors)
            print_error("Не удалось открыть файл");
        return;
    }

    regex_t regex; // Структура для представления скомпилированного регулярного выражения
    int compile_flags = REG_EXTENDED | REG_NOSUB; // Флаги компиляции регулярного выражения
    if (ignore_case)
        compile_flags |= REG_ICASE; // Флаг для игнорирования регистра символов
    
    int ret = regcomp(&regex, pattern, compile_flags); // Компиляция регулярного выражения
    if (ret != 0) { // Проверка на успешность компиляции
        if (!suppress_errors) {
            char error_message[MAX_LINE_LENGTH];
            regerror(ret, &regex, error_message, MAX_LINE_LENGTH); // Получение сообщения об ошибке
            print_error(error_message); // Вывод сообщения об ошибке
        }
        fclose(file); // Закрытие файла
        return;
    }

    char line[MAX_LINE_LENGTH]; // Буфер для строки
    int line_number = 0; // Счетчик номера строки
    int match_count = 0; // Счетчик совпадений
    bool matched = false; // Флаг, указывающий на то, были ли найдены совпадения

    while (fgets(line, sizeof(line), file) != NULL) { // Построчное чтение файла
        line_number++; // Увеличение номера строки

        if (regexec(&regex, line, 0, NULL, 0) == 0) { // Проверка на совпадение строки с регулярным выражением
            matched = true; // Установка флага наличия совпадений
            match_count++; // Увеличение счетчика совпадений
            if (!invert_match) { // Если не нужно инвертировать смысл поиска
                if (print_filenames && print_count) { // Вывод только имен файлов и количества совпадений
                    printf("%s: %d\n", filename, match_count);
                    fclose(file);
                    return;
                } else if (print_filenames && !print_count) { // Вывод только имен файлов
                    if (print_only_matched_parts) { // Если нужно выводить только совпадающие части
                        printf("%s\n", filename);
                        fclose(file);
                        return;
                    } else {
                        if (print_line_numbers) printf("%d:", line_number); // Вывод номера строки
                        printf("%s", line); // Вывод строки
                    }
                } else if (!print_filenames && print_count) { // Вывод только количества совпадений
                    printf("%d\n", match_count);
                    fclose(file);
                    return;
                } else {
                    if (print_line_numbers) printf("%d:", line_number); // Вывод номера строки
                    printf("%s", line); // Вывод строки
                }
            }
        } else { // Если совпадений нет
            if (invert_match) { // Если нужно инвертировать смысл поиска
                matched = true; // Установка флага наличия совпадений
                if (print_filenames && print_count) { // Вывод только имен файлов и количества совпадений
                    printf("%s: %d\n", filename, match_count);
                    fclose(file);
                    return;
                } else if (print_filenames && !print_count) { // Вывод только имен файлов
                    if (print_only_matched_parts) { // Если нужно выводить только совпадающие части
                        printf("%s\n", filename);
                        fclose(file);
                        return;
                    } else {
                        if (print_line_numbers) printf("%d:", line_number); // Вывод номера строки
                        printf("%s", line); // Вывод строки
                    }
                } else if (!print_filenames && print_count) { // Вывод только количества совпадений
                    printf("%d\n", match_count);
                    fclose(file);
                    return;
                } else {
                    if (print_line_numbers) printf("%d:", line_number); // Вывод номера строки
                    printf("%s", line); // Вывод строки
                }
            }
        }
    }

    if (!matched && invert_match) { // Если не было совпадений и был инвертирован смысл поиска
        if (print_filenames && print_count) { // Вывод только имен файлов и количества совпадений
            printf("%s: %d\n", filename, 0);
        } else if (print_filenames && !print_count) { // Вывод только имен файлов
            printf("%s\n", filename);
        } else if (!print_filenames && print_count) { // Вывод только количества совпадений
            printf("0\n");
        }
    }

    regfree(&regex); // Освобождение ресурсов, занятых для регулярного выражения
    fclose(file); // Закрытие файла
}

int main(int argc, char *argv[]) {
    // Проверка наличия необходимых аргументов
    if (argc < 3) {
        print_error("Недостаточно аргументов");
        return 1;
    }

    // Инициализация переменных для аргументов командной строки
    char *pattern = NULL;
    bool ignore_case = false;
    bool invert_match = false;
    bool print_count = false;
    bool print_filenames = false;
    bool print_line_numbers = false;
    bool print_matched_lines = true;
    bool suppress_errors = false;
    bool print_only_matched_parts = false;
    char *filename = NULL;

    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) { // Опция для указания шаблона
            if (i + 1 < argc) {
                pattern = argv[++i];
            } else {
                print_error("Отсутствует аргумент для опции -e");
                return 1;
            }
        } else if (strcmp(argv[i], "-i") == 0) { // Опция для игнорирования регистра
            ignore_case = true;
        } else if (strcmp(argv[i], "-v") == 0) { // Опция для инвертирования смысла поиска
            invert_match = true;
        } else if (strcmp(argv[i], "-c") == 0) { // Опция для вывода только количества совпадений
            print_count = true;
        } else if (strcmp(argv[i], "-l") == 0) { // Опция для вывода только имен файлов
            print_filenames = true;
        } else if (strcmp(argv[i], "-n") == 0) { // Опция для вывода номеров строк
            print_line_numbers = true;
        } else if (strcmp(argv[i], "-h") == 0) { // Опция для подавления сообщений об ошибках
            print_matched_lines = false;
        } else if (strcmp(argv[i], "-s") == 0) { // Опция для подавления сообщений об ошибках о несуществующих или нечитаемых файлах
            suppress_errors = true;
        } else if (strcmp(argv[i], "-f") == 0) { // Опция для получения регулярных выражений из файла
            if (i + 1 < argc) {
                FILE *pattern_file = fopen(argv[++i], "r");
                if (pattern_file == NULL) {
                    print_error("Не удалось открыть файл с регулярными выражениями");
                    return 1;
                }
                fseek(pattern_file, 0, SEEK_END);
                long pattern_file_size = ftell(pattern_file);
                fseek(pattern_file, 0, SEEK_SET);
                pattern = (char *)malloc(pattern_file_size + 1);
                fread(pattern, 1, pattern_file_size, pattern_file);
                pattern[pattern_file_size] = '\0';
                fclose(pattern_file);
            } else {
                print_error("Отсутствует аргумент для опции -f");
                return 1;
            }
        } else if (strcmp(argv[i], "-o") == 0) { // Опция для вывода только совпадающих (непустых) частей совпавших строк
            print_only_matched_parts = true;
        } else {
            filename = argv[i]; // Установка имени файла
        }
    }

    // Проверка наличия шаблона и имени файла
    if (pattern == NULL || filename == NULL) {
        print_error("Отсутствует обязательный аргумент");
        return 1;
    }

    // Запуск функции поиска совпадений
    grep(pattern, filename, ignore_case, invert_match, print_count, print_filenames, print_line_numbers, print_matched_lines, suppress_errors, print_only_matched_parts);

    return 0;
}
