CC:=gcc
CFLAGS:=-Wall -Wextra -Wpedantic -std=c11 -g -Iinclude
LDFLAGS:=-lm

SRC:=$(wildcard src/*.c)
OBJ:=$(SRC:.c=.o)

TARGET:=Simulator

.PHONY: all run clean rebuild

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC)$(OBJ)-o$@$(LDFLAGS)

src/%.o:src/%.c
	$(CC)$(CFLAGS)-c$<-o$@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f src/*.o $(TARGET)

rebuild: clean all