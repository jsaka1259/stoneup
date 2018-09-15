SRC = main.c getch.c
TARGET = stoneup
all:
	gcc -o $(TARGET) $(SRC)
clean:
	rm $(TARGET)

