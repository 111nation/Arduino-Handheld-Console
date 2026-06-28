# Detect calling operating system
ifeq ($(OS),Windows_NT)
    # Windows Settings
    RM = del /Q /F
    FIX_PATH = $(subst /,\,$1)
    # Changed to create the full directory tree if it doesn't exist
    MKDIR = if not exist $(dir $1) mkdir $(subst /,\,$(dir $1))
else
    # Linux and macOS Settings
    RM = rm -f
    FIX_PATH = $1
    MKDIR = mkdir -p $(dir $1)
endif

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Target Binary (Inside build directory)
BIN = build/main

# Source Files (Added Lib/seriallib.cpp)
SRC = GameEngine.cpp Program.cpp Parse.cpp Lib/serialib.cpp Serial.cpp

# Object Files (Mapped to inside build directory)
OBJ = $(addprefix build/,$(SRC:.cpp=.o))

# Build and Run the Executable
all: $(BIN)
	@./$(BIN)

# Rule to compile .cpp files into .o files
# Dynamic MKDIR ensures build/Lib/ is created alongside build/
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
