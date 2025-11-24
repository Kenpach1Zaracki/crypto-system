# ===========================
#   COMPILER SETTINGS
# ===========================

CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -O2

INCLUDES = -Iinclude -Iinclude/utils -Ilibs

# Source files
SRC_MAIN = src/main.cpp
SRC_FILE_IO = src/file_io.cpp

SRC_CAESAR = libs/caesar/shift_c.cpp
SRC_ATBASH = libs/atbash/atb_cipher.cpp
SRC_DTRANS = libs/double_transposition/dtrans.cpp
SRC_VINPUT = libs/validInput/vinput.cpp

# Object files
OBJ_DIR = build
OBJ_MAIN = $(OBJ_DIR)/main.o
OBJ_FILE_IO = $(OBJ_DIR)/file_io.o
OBJ_CAESAR = $(OBJ_DIR)/shift_c.o
OBJ_ATBASH = $(OBJ_DIR)/atb_cipher.o
OBJ_DTRANS = $(OBJ_DIR)/dtrans.o
OBJ_VINPUT = $(OBJ_DIR)/vinput.o

OBJS = $(OBJ_MAIN) $(OBJ_FILE_IO) $(OBJ_CAESAR) $(OBJ_ATBASH) $(OBJ_DTRANS) $(OBJ_VINPUT)

# Target app
TARGET = crypto_app

# ===========================
#           RULES
# ===========================

all: dirs $(TARGET)

dirs:
	mkdir -p $(OBJ_DIR)

# Compile object files
$(OBJ_MAIN): $(SRC_MAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_FILE_IO): $(SRC_FILE_IO)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_CAESAR): $(SRC_CAESAR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_ATBASH): $(SRC_ATBASH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DTRANS): $(SRC_DTRANS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_VINPUT): $(SRC_VINPUT)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Clean build
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
