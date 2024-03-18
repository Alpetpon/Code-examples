#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Функция для вывода сообщения об использовании программы
void print_usage() {
    printf("Использование: cat [ПАРАМЕТР]... [ФАЙЛ]...\n");
    printf("Конкатенирует ФАЙЛ(ы) и выводит в стандартный вывод.\n\n");
    printf("Если ФАЙЛ не указан, или указан как -, читает стандартный ввод.\n\n");
    printf("Параметры:\n");
    printf("  -b, --number-nonblank   нумеровать только непустые строки, переопределяет -n\n");
    printf("  -e                       эквивалентно -vE\n");
    printf("  -E, --show-ends          отображать $ в конце каждой строки\n");
    printf("  -n, --number             нумеровать все строки\n");
    printf("  -s, --squeeze-blank      удалять последовательные пустые строки\n");
    printf("  -t                       эквивалентно -vT\n");
    printf("  -T, --show-tabs          отображать символы TAB как ^I\n");
}

// Функция для вывода сообщения об ошибке
void print_error(const char *message) {
    fprintf(stderr, "Ошибка: %s\n", message);
}

// Функция для обработки содержимого файла с учетом заданных флагов
void process_file(FILE *file, bool number_nonblank, bool show_ends, bool number, bool squeeze_blank, bool show_tabs) {
    int line_number = 1; // Счетчик номера строки
    int prev_char = '\n'; // Предыдущий символ (для обработки пустых строк)
    int c; // Переменная для символа
    
    // Построчное чтение файла и обработка содержимого
    while ((c = fgetc(file)) != EOF) {
        // Отображение символа конца строки
        if (show_ends && c == '\n')
            putchar('$');
        
        // Отображение символа табуляции
        if (show_tabs && c == '\t') {
            putchar('^');
            putchar('I');
            continue;
        }
        
        // Нумерация строк
        if (number || (number_nonblank && (c != '\n' || prev_char != '\n')))
            printf("%6d  ", line_number++);
        
        // Вывод символа
        putchar(c);
        
        // Удаление последовательных пустых строк
        if (squeeze_blank && c == '\n') {
            while ((c = fgetc(file)) == '\n'); // Пропуск пустых строк
            ungetc(c, file); // Возвращение символа в поток
        }
        
        // Обновление предыдущего символа
        prev_char = c;
    }
}

int main(int argc, char *argv[]) {
    // Обработка аргументов командной строки
    bool number_nonblank = false; // Флаг для нумерации только непустых строк
    bool show_ends = false; // Флаг для отображения символа конца строки
    bool number = false; // Флаг для нумерации всех строк
    bool squeeze_blank = false; // Флаг для удаления последовательных пустых строк
    bool show_tabs = false; // Флаг для отображения символов табуляции
    
    // Проверка аргументов командной строки
    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        if (arg[0] == '-') {
            if (arg[1] == '-') {
                // Проверка длинных опций
                if (strcmp(arg, "--number-nonblank") == 0)
                    number_nonblank = true;
                else if (strcmp(arg, "--show-ends") == 0)
                    show_ends = true;
                else if (strcmp(arg, "--number") == 0)
                    number = true;
                else if (strcmp(arg, "--squeeze-blank") == 0)
                    squeeze_blank = true;
                else if (strcmp(arg, "--show-tabs") == 0)
                    show_tabs = true;
                else if (strcmp(arg, "--help") == 0) {
                    print_usage();
                    return 0;
                } else {
                    print_error("Неверный параметр");
                    return 1;
                }
            } else {
                // Проверка коротких опций
                for (int j = 1; arg[j] != '\0'; j++) {
                    if (arg[j] == 'b')
                        number_nonblank = true;
                    else if (arg[j] == 'e')
                        show_ends = true;
                    else if (arg[j] == 'E') {
                        show_ends = true;
                        show_tabs = false;
                    } else if (arg[j] == 'n')
                        number = true;
                    else if (arg[j] == 's')
                        squeeze_blank = true;
                    else if (arg[j] == 't')
                        show_tabs = true;
                    else if (arg[j] == 'T') {
                        show_tabs = true;
                        show_ends = false;
                    } else if (arg[j] == 'h') {
                        print_usage();
                        return 0;
                    } else {
                        print_error("Неверный параметр");
                        return 1;
                    }
                }
            }
        } else {
            // Обработка файлов
            FILE *file = fopen(arg, "r");
            if (file == NULL) {
                print_error("Не удалось открыть файл");
                return 1;
            }
            process_file(file, number_nonblank, show_ends, number, squeeze_blank, show_tabs);
            fclose(file);
        }
    }
    
    // Если аргументы не были переданы, читаем стандартный ввод
    if (argc == 1) {
        process_file(stdin, number_nonblank, show_ends, number, squeeze_blank, show_tabs);
    }
    
    return 0;
}
