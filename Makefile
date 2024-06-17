# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = `pkg-config --cflags gtk+-3.0`
# Linker flags
LDFLAGS = `pkg-config --libs gtk+-3.0`

# Target executable
TARGET = simple_notepad

# Source files
SRC = main.cpp NotepadWindow.cpp NotepadController.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Build target
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ) $(TARGET)
