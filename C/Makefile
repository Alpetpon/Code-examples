# Имя компилятора
CC=gcc
# Флаги компиляции
CFLAGS=-Wall -Wextra -Werror -std=c11

# Директория для объектных файлов
BUILD_DIR=build
# Директория для исполняемых файлов
BIN_DIR=bin

# Исходные файлы утилиты cat
CAT_SRC=cat.c
# Исходные файлы утилиты grep
GREP_SRC=grep.c

# Объектные файлы
CAT_OBJ=$(patsubst %.c,$(BUILD_DIR)/%.o,$(CAT_SRC))
GREP_OBJ=$(patsubst %.c,$(BUILD_DIR)/%.o,$(GREP_SRC))

# Имя исполняемых файлов
CAT_EXE=$(BIN_DIR)/cat
GREP_EXE=$(BIN_DIR)/grep

# Цель по умолчанию
all: $(CAT_EXE) $(GREP_EXE)

# Компиляция утилиты cat
$(CAT_EXE): $(CAT_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Компиляция утилиты grep
$(GREP_EXE): $(GREP_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Создание директории для объектных файлов
$(BUILD_DIR):
	mkdir -p $@

# Создание директории для исполняемых файлов
$(BIN_DIR):
	mkdir -p $@

# Компиляция исходных файлов
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
