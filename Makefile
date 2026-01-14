CC = g++
CFLAGS = -std=c++11 -Wall
SOURCES = main.cpp kernel/kernel.cpp drivers/screen.cpp shell/shell.cpp lib/string_utils.cpp
TARGET = myos

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean
