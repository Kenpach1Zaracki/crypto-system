CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -fPIC
LDFLAGS = -shared

# Цели
all: build/libCaesar.so build/libAtbash.so build/libDoubleTransposition.so build/libValidInput.so build/cryptoTool

# Библиотеки
build/libCaesar.so: libs/caesar/caesar.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

build/libAtbash.so: libs/atbash/atbash.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

build/libDoubleTransposition.so: libs/double_transposition/double_transposition.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

build/libValidInput.so: libs/validInput/validInput.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

# Основная программа
build/cryptoTool: src/main.cpp src/file_io.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -fPIC $^ -o $@ -Lbuild -lCaesar -lAtbash -lDoubleTransposition -lValidInput

# Linux версия
linux: all
	@mkdir -p linux
	cp build/cryptoTool build/*.so linux/

clean:
	rm -rf build linux

.PHONY: all clean linux
