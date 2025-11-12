CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude -fPIC
LDFLAGS = -ldl

SRCDIR = src
INCDIR = include
LIBDIR = lib

TARGET = crypto_app

# Динамические библиотеки
LIBS = $(LIBDIR)/librc4.so $(LIBDIR)/libaes.so $(LIBDIR)/libbinvig.so

all: $(LIBDIR) $(LIBS) $(TARGET)

$(LIBDIR):
	mkdir -p $(LIBDIR)

# Компиляция объектных файлов с флагом -fPIC
$(SRCDIR)/rc4.o: $(SRCDIR)/rc4.cpp $(INCDIR)/rc4.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/rc4.cpp -o $(SRCDIR)/rc4.o

$(SRCDIR)/aes_cfb.o: $(SRCDIR)/aes_cfb.cpp $(INCDIR)/aes_cfb.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/aes_cfb.cpp -o $(SRCDIR)/aes_cfb.o

$(SRCDIR)/binary_vigenere.o: $(SRCDIR)/binary_vigenere.cpp $(INCDIR)/binary_vigenere.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/binary_vigenere.cpp -o $(SRCDIR)/binary_vigenere.o

$(SRCDIR)/crypto_system.o: $(SRCDIR)/crypto_system.cpp $(INCDIR)/crypto_system.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/crypto_system.cpp -o $(SRCDIR)/crypto_system.o

# Создание динамических библиотек
$(LIBDIR)/librc4.so: $(SRCDIR)/rc4.o
	$(CXX) -shared -o $@ $^

$(LIBDIR)/libaes.so: $(SRCDIR)/aes_cfb.o
	$(CXX) -shared -o $@ $^

$(LIBDIR)/libbinvig.so: $(SRCDIR)/binary_vigenere.o
	$(CXX) -shared -o $@ $^

# Основная программа
$(TARGET): $(SRCDIR)/main.cpp $(SRCDIR)/crypto_system.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(SRCDIR)/main.cpp $(SRCDIR)/crypto_system.o

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)
	rm -rf $(LIBDIR)
	rm -f *.encrypted *.decrypted

help:
	@echo "make          - собрать проект"
	@echo "make clean    - очистить объектные файлы и библиотеки"
	@echo "make help     - показать эту справку"

.PHONY: all clean help