CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic

LIB_DIR=lib

SRC_DIR=src
SRC_SOURCES=$(wildcard $(SRC_DIR)/*.c)

OBJECTS_DIR=objects
SRC_OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SRC_SOURCES))

TESTS_DIR=tests
TESTS_SOURCES=$(wildcard $(TESTS_DIR)/*.c)

TESTS_OBJECTS=$(patsubst $(TESTS_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(TESTS_SOURCES))

BIN_DIR=bin
TESTS_BINS=$(patsubst $(TESTS_DIR)/%.c, $(BIN_DIR)/%, $(TESTS_SOURCES))

all: $(LIB_DIR) $(SRC_OBJECTS)
	ar rcs $(LIB_DIR)/libstr.a $(SRC_OBJECTS)

clean:
	rm -rf $(BIN_DIR) $(OBJECTS_DIR) $(LIB_DIR)

test: $(TESTS_BINS)

runtest: $(TESTS_BINS)
	./$(BIN_DIR)/str_test
	./$(BIN_DIR)/strbuf_test

$(SRC_OBJECTS): $(OBJECTS_DIR) $(SRC_SOURCES)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/str.c -o $(OBJECTS_DIR)/str.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/strbuf.c -o $(OBJECTS_DIR)/strbuf.o

$(TESTS_OBJECTS): $(OBJECTS_DIR) $(TESTS_SOURCES)
	$(CC) $(CFLAGS) -c $(TESTS_DIR)/str_test.c -o $(OBJECTS_DIR)/str_test.o
	$(CC) $(CFLAGS) -c $(TESTS_DIR)/strbuf_test.c -o $(OBJECTS_DIR)/strbuf_test.o

$(TESTS_BINS): $(BIN_DIR) $(SRC_OBJECTS) $(TESTS_OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/str_test  $(OBJECTS_DIR)/str_test.o $(SRC_OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/strbuf_test  $(OBJECTS_DIR)/strbuf_test.o $(SRC_OBJECTS)

$(OBJECTS_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(LIB_DIR):
	mkdir -p $@
