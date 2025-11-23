CXX = g++
CXXFLAGS = -fPIC -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = -shared
MAIN_LDFLAGS = -L. -lCaesar -lAtbash -lDoubleTransposition -lValidInput -Wl,-rpath,.

# Цели
LIB_TARGETS = libCaesar.so libAtbash.so libDoubleTransposition.so libValidInput.so
MAIN_TARGET = cryptoTool

all: $(LIB_TARGETS) $(MAIN_TARGET)

# Библиотеки
libCaesar.so: libs/caesar/caesar.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

libAtbash.so: libs/atbash/atbash.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

libDoubleTransposition.so: libs/double_transposition/double_transposition.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

libValidInput.so: libs/validInput/validInput.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

# Основная программа
$(MAIN_TARGET): src/main.cpp src/utils/file_io.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(MAIN_LDFLAGS)

# Для linux папки
linux: all
	mkdir -p linux
	cp $(MAIN_TARGET) $(LIB_TARGETS) linux/

clean:
	rm -f $(LIB_TARGETS) $(MAIN_TARGET)
	rm -rf linux

.PHONY: all clean linux
