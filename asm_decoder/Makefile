# Directories
SRC = src
BUILD = build
INCLUDE = include

ALL_INCLUDES = -I./$(INCLUDE) 
# Compiler and flags
CC = gcc
CXX = g++
CFLAGS = -Wall -O2 -g $(ALL_INCLUDES)
# CFLAGS = -Wall -ggdb -O3 $(INCLUDES)
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -pedantic -g -O2 $(ALL_INCLUDES)
# CXXFLAGS = -Wall -ggdb -O3 $(INCLUDES)
LDFLAGS = -lX11 -lpthread -lXrandr -lXi -ldl 
# SHARED OBJECTS AND TARGETS  (Targets are executables)

# Shared objects by multiple executables
CPP_FILES := Decoder.cpp UserInterface.cpp Application.cpp
OBJECTS := $(CPP_FILES:.cpp=.o)
OBJECTS := $(addprefix $(BUILD)/, $(OBJECTS))

# Targets
CPP_EXEC := asm_decoder.cpp
TARGETS_OBJ := $(CPP_EXEC:%.cpp=$(BUILD)/%.o)
TARGETS := $(TARGETS_OBJ:%.o=%)

# RECIPES
all: $(TARGETS)

# executables depend on shared objects
$(TARGETS): $(OBJECTS) 

# Link
# Secondary expansions allow to use the automatic variable $@ in the prerequisites list.
# https://www.gnu.org/software/make/manual/html_node/Secondary-Expansion.html
.SECONDEXPANSION:
$(TARGETS): $(OBJECTS) $$@.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile objects
# Order of recipes matter. Recipe 2 has to be before recipe 3 to take into account .h prerrequisites. 

# recipe 2: compile objects - cpp files with header files
$(BUILD)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

# recipe 3: compile executables - cpp files without header files
$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@    

# PHONY
.PHONY: all clean run

clean:
	rm -rf $(BUILD)

run: $(TARGETS)
	./$(BUILD)/asm_decoder

$(BUILD):
	mkdir -p $(BUILD)