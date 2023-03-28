CC:=gcc
CFLAGS:= -Wall -g
LDFLAGS=


BUILD_FOLDER:= objects
LIB_FOLDER:=lib
INCLUDE_FOLDER:=include
LIB=$(LIB_FOLDER)/libeda.a
LIBSRC=$(wildcard arvore/*.c) $(wildcard fila/*.c)  $(wildcard lista/*.c)  $(wildcard ordenacao/*.c)  $(wildcard pilha/*.c) $(wildcard utils/*.c) $(wildcard vetor-dinamico/*.c)  
LIBHEAD=$(wildcard arvore/*.h)  $(wildcard fila/*.h)  $(wildcard lista/*.h)  $(wildcard ordenacao/*.h)  $(wildcard pilha/*.h) $(wildcard utils/*.h) $(wildcard vetor-dinamico/*.h) 
LIBOBJ = $(patsubst %.c,$(BUILD_FOLDER)/%.o,$(LIBSRC))

test_src = $(wildcard Testes/*.c)


BINFOLDER:= bin
SRC:=$(wildcard Exemplos/*.c)
BIN:= $(patsubst Exemplos/%.c,$(BINFOLDER)/%,$(SRC))

all: $(BUILD_FOLDER) $(LIB)

examples: $(BINFOLDER) $(BIN)

$(BIN): $(LIB)


bin/%: Exemplos/%.c
	$(CC) $(CFLAGS) $^ -I./$(INCLUDE_FOLDER)  $(LIB) -o $@

$(BINFOLDER):
	@mkdir -p bin

$(BUILD_FOLDER):
	@mkdir -p $(BUILD_FOLDER)

$(INCLUDE_FOLDER):
	@mkdir -p $(INCLUDE_FOLDER)

$(LIB): $(LIBOBJ) $(INCLUDE_FOLDER)
	@echo "Building library"
	@mkdir -p $(LIB_FOLDER)
	@ar rcs $(LIB) $(LIBOBJ)
	@echo "Done"
	@echo "Copying includes to include dir"
	@cp $(LIBHEAD) $(INCLUDE_FOLDER)

$(BUILD_FOLDER)/%.o: %.c %.h
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@



test: $(test_src) $(LIB) 
	$(CC) $(CFLAGS) $^ -I$(INCLUDE_FOLDER) -o  Testes/main  -pthread -lcheck -pthread -lrt -lm
	@echo "Running Tests"
	./Testes/main

.PHONY: clean
clean:
	@echo "Cleaning objects, include and lib"
	@rm -r $(BUILD_FOLDER)
	@rm -r $(LIB_FOLDER)
	@rm -r $(INCLUDE_FOLDER)
	@echo "Done"

