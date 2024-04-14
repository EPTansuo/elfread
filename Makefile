INPUT_FILE=./recursion-riscv64-nemu.elf
TARGET=elfread
default:all

all:elfread.c main.c
	gcc $^ -o $(TARGET) -Og -Wall

run:$(TARGET)
	./$(TARGET) $(INPUT_FILE)

clean:
	rm $(TARGET)
