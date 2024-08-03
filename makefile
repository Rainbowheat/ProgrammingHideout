all: outs bins

CC = gcc
CFLAGS = -Wall -g
INCLUDES =
LINKS =
LIBS =
OUT_DIR = out
BIN_DIR = bin

SRC_FILES = $(wildcard *.c)
OUT_FILES = $(patsubst %.c,$(OUT_DIR)/%.o,$(SRC_FILES))
BIN_FILES = $(patsubst %.c,$(OUT_DIR)/%.out,$(SRC_FILES))

.SECONDARY: $(OUT_FILES)

$(OUT_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKS) -c $< -o $@ $(LIBS)

$(BIN_DIR)/%.out : $(OUT_DIR)/%.o
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKS) $< -o $@ $(LIBS)

outs: $(OUT_FILES)
bins: $(BIN_FILES)

clean:
	rm -f $(OUT_DIR)/*.o $(BIN_DIR)/*.out
