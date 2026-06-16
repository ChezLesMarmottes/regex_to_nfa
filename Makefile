CC ?= cc
CPPFLAGS := -Iinclude
CFLAGS ?= -Wall -Wextra -std=c11 -O2
TARGET := build/app
SRC := $(shell find src -type f -name '*.c' | sort)
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))
DEP := $(OBJ:.o=.d)
LDLIBS :=

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJ) -o $@ $(LDLIBS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build

-include $(DEP)

.PHONY: all run clean
