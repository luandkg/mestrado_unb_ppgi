# Compilador e flags
CC = gcc
CFLAGS = -Wall -O2

# Diretórios
SRC_DIR = src
OBJ_DIR = build/objects
OUT_DIR = build/out

# Arquivos fonte
SOURCES = $(SRC_DIR)/bully.c
OBJECTS = $(OBJ_DIR)/bully.o

# Nome do executável
TARGET = $(OUT_DIR)/bully

# Regra principal
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJECTS)
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação do objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
