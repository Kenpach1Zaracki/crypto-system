# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

# Директории
SRCDIR = src
INCDIR = include
OBJDIR = src

# Исходные файлы
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Цель
TARGET = crypto_app

# Основная цель
all: $(TARGET)

# Компиляция исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Компиляция объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f *.encrypted *.decrypted
	rm -rf encrypted/ decrypted/ files/
	find . -maxdepth 1 -name "test_*.txt" -delete 2>/dev/null || true
	find . -maxdepth 1 -name "test_*.dat" -delete 2>/dev/null || true
	find . -maxdepth 1 -name "test_*.png" -delete 2>/dev/null || true
	find . -maxdepth 1 -name "test_*.wav" -delete 2>/dev/null || true
	find . -maxdepth 1 -name "test_*.avi" -delete 2>/dev/null || true

# Полная очистка (включая test_files/)
cleanall: clean
	rm -rf test_files/

# Создание директорий
dirs:
	mkdir -p test_files files encrypted decrypted

# Установка (создание необходимых директорий)
install: dirs

# Помощь
help:
	@echo "Доступные команды:"
	@echo "  make          - собрать проект"
	@echo "  make clean    - очистить объектные файлы и временные файлы"
	@echo "  make cleanall - полная очистка (включая test_files/)"
	@echo "  make dirs     - создать необходимые директории"
	@echo "  make install  - создать директории"
	@echo "  make help     - показать эту справку"

.PHONY: all clean cleanall dirs install help