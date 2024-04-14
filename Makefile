INPUT_FILE=./recursion-riscv64-nemu.elf
TARGET=elfread
default:all
SRCS=elfread.c main.c

all:$(SRCS)
	gcc $(SRCS) -o $(TARGET) -Og -Wall

run:$(TARGET)
	./$(TARGET) $(INPUT_FILE)

clean:
	rm $(TARGET)
