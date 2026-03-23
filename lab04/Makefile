CC = gcc
CFLAGS = -Wall -O2
TARGET = lab1
SRC = src/main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lm

run: $(TARGET)
	./$(TARGET)
	python3 scripts/plot.py

clean:
	rm -f $(TARGET)
	rm -rf data/*
	rm -rf graphs/*

.PHONY: all run clean