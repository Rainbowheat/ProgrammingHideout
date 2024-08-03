CC = gcc
CFLAGS = -Wall -g
INCLUDES =
LINKS =
LIBS =
OUT_DIR = out
BIN_DIR = bin

$(OUT_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKS) -c $< -o $@ $(LIBS)

$(BIN_DIR)/%.out : $(OUT_DIR)/%.o
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKS) $< -o $@ $(LIBS)

all: $(patsubst %.c,$(BIN_DIR)/%.out,$(wildcard *.c))
	echo ""
