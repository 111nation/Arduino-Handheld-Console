# Detect calling operating system
ifeq ($(OS),Windows_NT)
    # Windows Settings
    RM = del /Q /F
    FIX_PATH = $(subst /,\,$1)
    MKDIR = if not exist $(dir $1) mkdir $(subst /,\,$(dir $1))
else
    # Linux and macOS Settings
    RM = rm -rf
    FIX_PATH = $1
    MKDIR = mkdir -p $(dir $1)
endif

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Target Binary (Inside build directory)
BIN = build/main

# All .cpp files in the root and Lib/ directory
SRC = $(wildcard *.cpp) $(wildcard Lib/*.cpp)

# Map source paths to the build directory safely
OBJ = $(patsubst %.cpp, build/%.o, $(SRC))

# Build and Run the Executable
all: $(BIN)
	@./$(BIN)

# Rule to compile .cpp files into .o files
build/%.o: %.cpp
	@$(call MKDIR,$@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link object files to target executable
$(BIN): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

# Rule to run executable 
run: $(BIN)
	@./$(BIN)

# Rule to remove generated files
clean:
	@$(RM) $(call FIX_PATH,$(BIN) $(OBJ))
