# ===========================
#        SETTINGS
# ===========================

CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -O2

INCLUDES = -Iinclude -Iinclude/utils -Ilibs

SRC_MAIN = src/main.cpp
SRC_FILE_IO = src/file_io.cpp

SRC_CAESAR = libs/caesar/shift_c.cpp
SRC_ATBASH = libs/atbash/atb_cipher.cpp
SRC_DTRANS = libs/double_transposition/dtrans.cpp
SRC_VINPUT = libs/validInput/vinput.cpp

OBJS = \
    build/main.o \
    build/file_io.o \
    build/shift_c.o \
    build/atb_cipher.o \
    build/dtrans.o \
    build/vinput.o

TARGET = linux

# ===========================
#        RULES
# ===========================

all: $(TARGET)

$(TARGET): build $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

build:
	mkdir -p build

build/main.o: $(SRC_MAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

build/file_io.o: $(SRC_FILE_IO)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

build/shift_c.o: $(SRC_CAESAR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

build/atb_cipher.o: $(SRC_ATBASH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

build/dtrans.o: $(SRC_DTRANS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

build/vinput.o: $(SRC_VINPUT)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ===========================
#       CLEAN
# ===========================
clean:
	rm -rf build $(TARGET)

