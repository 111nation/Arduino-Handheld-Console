# Detect calling operating system
ifeq ($(OS),Windows_NT)
    # Windows Settings
    RM = del /Q /F
    FIX_PATH = $(subst /,\,$1)
else
    # Linux and macOS Settings
    RM = rm -f
    FIX_PATH = $1
endif

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = 

# Target Binary
BIN = main

# Source Files
SRC = GameEngine.cpp

# Object Files
OBJ = $(SRC:.cpp=.o)

# Build and Run the Executable
all: $(BIN)
	@./$(BIN)

# Rule to compile .cpp files into .o files
%.o: %.cpp
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
