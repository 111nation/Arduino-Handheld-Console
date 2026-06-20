# Detect calling operating system
ifeq ($(OS),Windows_NT)
    # Windows Settings
    RM = del /Q /F
    FIX_PATH = $(subst /,\,$1)
    MKDIR = if not exist build mkdir build
else
    # Linux and macOS Settings
    RM = rm -f
    FIX_PATH = $1
    MKDIR = mkdir -p build
endif

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Target Binary (Inside build directory)
BIN = build/main

# Source Files
SRC = GameEngine.cpp

# Object Files (Mapped to inside build directory)
OBJ = $(addprefix build/,$(SRC:.cpp=.o))

# Build and Run the Executable
all: $(BIN)
	@./$(BIN)

# Rule to compile .cpp files into .o files
# Added the MKDIR step to ensure the build folder exists before writing to it
build/%.o: %.cpp
	@$(MKDIR)
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
