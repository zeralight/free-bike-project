# Particular paths
#==================================

BIN_DIR = ./bin
BUILD_DIR = ./build
DOC_DIR = ./doc
INCLUDE_DIR = ./include
LIB_DIR = ./lib
SRC_DIR = ./src
TST_DIR = ./tst
TST_FILES_DIR = $(TST_DIR)/files
TST_OUT_DIR = $(TST_DIR)/out

EMACS_CLEAN_DIR = . $(SRC_DIR) $(TST_DIR) $(INCLUDE_DIR) $(TST_FILES_DIR) $(DOC_DIR)


# Compilation flags
#==================================

CC = g++

FLAGS = -std=c++14 -g -Wall -fPIC -DNDEBUG
FLAGS_LIB = -shared -fPIC
LIBS =

TLP_LIBS = `tulip-config --libs`
TLP_FLAGS = `tulip-config --cxxflags`

TST_FLAGS = -DTST_FILES_PATH=\"$(TST_FILES_DIR)\" -DTST_OUT_PATH=\"$(TST_OUT_DIR)\" #relative to the BIN_DIR

INCLUDE = -I$(INCLUDE_DIR)


# Files lists
#==================================

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.cpp=.o)))
TST_BIN = $(wildcard $(BIN_DIR)/test*)


# Rules
#==================================

all: lib

$(BUILD_DIR)/test%.o: $(TST_DIR)/test%.cpp
	$(CC) $(FLAGS) $(INCLUDE) $(TLP_FLAGS) $(TST_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CC) $(FLAGS) $(INCLUDE) $(TLP_FLAGS) -c $< -o $@

$(BIN_DIR)/test%: $(BUILD_DIR)/test%.o $(OBJ)
	$(CC) $(LIBS) $(TLP_LIBS) $(FLAGS) $^ -o $@

lib: $(OBJ)
	$(CC) $(FLAGS_LIB) $^ -o $(LIB_DIR)/libgraphdb.so 

test%: $(BIN_DIR)/test%
	@echo -e "\033[1;37m$<:\033[0m"
	@$<
	@echo ""

test: testEntRel testDatabase testPattern testMatch

doc-user:
	doxygen $(DOC_DIR)/doc_user.doxyfile

doc-dev:
	doxygen $(DOC_DIR)/doc_dev.doxyfile

clean: clean-emacs
	rm -r -f $(BUILD_DIR)/*.o $(TST_OUT_DIR)/*	

clean-bin:
	rm -f $(BIN_DIR)/*

clean-doc:
	rm -r -f $(DOC_DIR)/user/* $(DOC_DIR)/dev/*

clean-emacs:
	rm -r -f $(addsuffix /*~, $(EMACS_CLEAN_DIR)) \#*\#

.PHONY: clean clean-bin	clean-doc clean-emacs lib

.SECONDARY:
