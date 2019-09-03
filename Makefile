BIN    := stoneup
OBJS   := main.o getch.o

CC     := gcc
CFLAGS := -Wall
INC    := -I .
RM     := rm

.SUFFIXES: .c .o

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(BIN)

