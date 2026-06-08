CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Iinclude
TARGET = study_room_system.exe
SRC = src/main.c src/linkedlist.c src/hashtable.c src/student.c src/seat.c src/utils.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	del /Q $(TARGET) 2>NUL || rm -f $(TARGET)
