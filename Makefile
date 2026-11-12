CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic
TARGET := bank-account
SOURCES := main.cpp sources/stuff.cpp sources/transactions.cpp sources/accounts.cpp sources/bank.cpp
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
