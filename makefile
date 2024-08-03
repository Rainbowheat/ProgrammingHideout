all: outs bins

CC = gcc
CFLAGS = -Wall -g
INCLUDES =
LINKS =
LIBS =
OUT_DIR = out
BIN_DIR = bin

.SECONDARY: $(patsubst %.c,$(OUT_DIR)/%.o,$(wildcard *.c))

$(OUT_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKS) -c $< -o $@ $(LIBS)

$(BIN_DIR)/%.out : $(OUT_DIR)/%.o
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKS) $< -o $@ $(LIBS)

outs: $(patsubst %.c,$(OUT_DIR)/%.o,$(wildcard *.c))
bins: $(patsubst %.c,$(BIN_DIR)/%.out,$(wildcard *.c))

clean:
	rm -f $(OUT_DIR)/*.o $(BIN_DIR)/*.out
