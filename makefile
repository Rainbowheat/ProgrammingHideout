all: $(APP)
CC = gcc
CFLAGS = -Wall -g
INCLUDES =
LINKS =
LIBS =
APP = app

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKS) -c $< -o $@ $(LIBS)

$(APP) : $(patsubst %.c, %.o, $(wildcard *.c))
	$(CC) $(CFLAGS) $(INCLUDES) $(LINKS) $^ -o $@ $(LIBS)

all: $(APP)
	./$<

clean:
	rm *.o $(APP)
