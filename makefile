#'make' crea el archivo ejecutable
# 'make clean'Borra el archivo ejecutable
CXX = g++
CXXFLAGS = -std=c++11 -pthread
TARGET = carrera

all: $(TARGET)

$(TARGET): carreraDeAutos.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) carreraDeAutos.cpp

clean:
	rm -f $(TARGET)
