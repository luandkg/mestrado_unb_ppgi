# Compilador e flags
CC = gcc
CFLAGS = -Wall -O2

# Diretórios
SRC_DIR = algoritmos
OBJ_DIR = build/objects
OUT_DIR = build/out

# Lista de fontes (declare aqui apenas os nomes .c)
SRC_FILES = bully.c chang_roberts.c

# Geração automática de caminhos
SOURCES = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
TARGETS = $(patsubst %.c,$(OUT_DIR)/%,$(SRC_FILES))

# Regra principal
all: $(TARGETS)

# Linkagem genérica: cada executável depende do objeto correspondente
$(OUT_DIR)/%: $(OBJ_DIR)/%.o
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação genérica dos objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGETS)

.PHONY: all clean
