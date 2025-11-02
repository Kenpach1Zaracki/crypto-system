CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

SRCDIR = src
INCDIR = include
OBJDIR = src

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

TARGET = crypto_app

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f *.encrypted *.decrypted

help:
	@echo "make          - собрать проект"
	@echo "make clean    - очистить объектные файлы и бинарник"
	@echo "make help     - показать эту справку"

.PHONY: all clean help