# Gets the Operating system name
OS := $(shell uname -s)

# Default shell
SHELL := /bin/bash

# Color prefix for Linux distributions
COLOR_PREFIX := e

ifeq ($(OS),Darwin)
	COLOR_PREFIX := 033
endif

# Color definition for print purpose
export BROWN=\$(COLOR_PREFIX)[0;33m
export BLUE=\$(COLOR_PREFIX)[1;34m
export END_COLOR=\$(COLOR_PREFIX)[0m



# Source code directory structure
ACTUAL_PATH := $(shell pwd)
SRCDIR := .
BINDIR := .
export OBJDIR := .


# Source code file extension
export SRCEXT := c
SRCEXEC := $(shell find $(SRCDIR) -type f -name Makefile)
OBJEXEC := $(shell echo "$(SRCEXEC)"|sed 's/\/Makefile/\/$(OBJDIR)\/*.o/g')
SRCEXEC := $(shell echo "$(SRCEXEC)"|sed 's/\/Makefile//g')
# NUMEXEC := 0


# Defines the C Compiler
export CC := gcc


# Defines the language standards for GCC
STD := -std=gnu99 # See man gcc for more options

# Protection for stack-smashing attack
STACK := -fstack-protector-all -Wstack-protector

# Specifies to GCC the required warnings
WARNS := -Wall -Wextra -pedantic # -pedantic warns on language standards

# Flags for compiling
export CFLAGS := -O3 $(STD) $(STACK) $(WARNS)

# Debug options
export DEBUG := -g3 -DDEBUG=0

# Dependency libraries
export LIBS := # -lm  -I some/path/to/library

# Test libraries
TEST_LIBS := -l cmocka -L /usr/lib

# Searce code
FILE_NAME := selection_sort_run.c selection_sort.c

# Binary
BINARY := out



# Tests binary file
TEST_BINARY := $(BINARY)_test_runner


MFILEDIR := resources/makefile/sample
D_FILE := vimspector.json


default: all

# Help message
help:
	@echo "C Project Template"
	@echo
	@echo "Target rules:"
	@echo "    all       - Compiles and generates binary file"
	@echo "    install   - Same as all argument"
	@echo "    dir       - Create a new diretory into src folder with all dependencies already fullfilled"
	@echo "    srcfolder - Transform an existent directory int a source directory"
	@echo "    run       - execute the binary file"
	@echo "    tests     - Compiles with cmocka and run tests binary file"
	@echo "    valgrind  - Runs binary file using valgrind tool"
	@echo "    clean     - Clean the project by removing binaries"
	@echo "    help      - Prints a help message with target rules"


# Rule for link and generate the binary file
all:
	@echo ""
	@echo -e "$(BROWN)[ Processing objects ]$(END_COLOR)";
	@echo "-"
	@echo -en "$(BROWN)LD $(END_COLOR)";
	$(CC) -o $(BINDIR)/$(BINARY) $(DEBUG) $(CFLAGS) $(LIBS) $(FILE_NAME)
	@echo -en "\n--\nBinary file placed at" \
			  "$(BROWN)$(BINDIR)/$(BINARY)$(END_COLOR)\n";


install: all


run:
	@[[ ! -f $(BINDIR)/$(BINARY) ]] && echo -e "$(BROWN)[ERROR]$(END_COLOR) Binary file does not exists. Compile the project first" && exit 1 || $(BINDIR)/$(BINARY)


# Rule for run valgrind tool
valgrind:
	valgrind \
		--track-origins=yes \
		--leak-check=full \
		--leak-resolution=high \
		--log-file=$(LOGDIR)/$@.log \
		$(BINDIR)/$(BINARY)
	@echo -en "\nCheck the log file: $(LOGDIR)/$@.log\n"


# Compile tests and run the test binary
tests:
	@echo -en "$(BROWN)CC $(END_COLOR)";
	$(CC) $(TESTDIR)/main.c -o $(BINDIR)/$(TEST_BINARY) $(DEBUG) $(CFLAGS) $(LIBS) $(TEST_LIBS)
	@which ldconfig && ldconfig -C /tmp/ld.so.cache || true # caching the library linking
	@echo -en "$(BROWN) Running tests: $(END_COLOR)";
	./$(BINDIR)/$(TEST_BINARY)


dir:
	@read -p "Directory name: " DIR; \
	[[ -z $$DIR ]] && echo -e "$(BROWN)[ERROR]$(END_COLOR) You need to specify a name for the new directory!" && exit; \
	[[ -d "$(SRCDIR)/$$DIR" ]] && echo -e "$(BROWN)[ERROR]$(END_COLOR) $$DIR already created in $(SRCDIR)" && exit; \
	echo "-" && echo "Creating $$DIR" && mkdir -pv "$(SRCDIR)/$$DIR/$(OBJDIR)" && touch "$(SRCDIR)/$$DIR/$(OBJDIR)/.gitkeep" && echo "$$DIR created in $(SRCDIR)" || exit; \
	echo "-" && echo "Transferring Makefile for $(SRCDIR)/$$DIR" && cp -vf "$(MFILEDIR)/Makefile" "$(SRCDIR)/$$DIR" && echo "Makefile transferred for $(SRCDIR)/$$DIR" && echo "-" || exit;


srcfolder:
	@read -p "Directory name: " DIR; \
	[[ -z $$DIR ]] && echo -e "$(BROWN)[ERROR]$(END_COLOR) You need to specify a name for a existent directory!" && exit; \
	[[ ! -d "$(SRCDIR)/$$DIR" ]] && echo -e "$(BROWN)[ERROR]$(END_COLOR) $$DIR must exist!" && exit; \
	[[ -d "$(SRCDIR)/$$DIR/$(OBJDIR)" ]] && [[ -f "$(SRCDIR)/$$DIR/Makefile" ]] && echo -e "$(BROWN)[ERROR]$(END_COLOR) $$DIR is already a source folder!" && exit; \
	echo "-" && echo "Creating object folder $(OBJDIR)" && mkdir -pv "$(SRCDIR)/$$DIR/$(OBJDIR)" && touch "$(SRCDIR)/$$DIR/$(OBJDIR)/.gitkeep" && echo "Object directory $(OBJDIR) created!" || exit; \
	echo "-" && echo "Transferring Makefile for $(SRCDIR)/$$DIR" && cp -vf "$(MFILEDIR)/Makefile" "$(SRCDIR)/$$DIR" && echo "Makefile transferred for $(SRCDIR)/$$DIR" && echo "-" || exit;


# Rule for cleaning the project
clean:
	@rm -rvf *o $(BINARY);
