CC = g++
CFLAGS = -fPIC -Wall -std=c++11 -g
LDFLAGS = -shared -g
PYCFLAGS = $(shell python3.2-config --cflags)
PYLDFLAGS = $(shell python3.2-config --ldflags)
SRC = pyet/src
INCLUDE = pyet/include

TARGET_WRAPPER = qagame.mp.$(shell uname -m).so
TARGET_PYET = pyet.so

all: $(TARGET_WRAPPER) $(TARGET_PYET)

$(TARGET_WRAPPER): wrapper.o
		$(CC) -o $@ $^ $(LDFLAGS)

wrapper.o: $(SRC)/wrapper.cpp $(INCLUDE)/wrapper.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(TARGET_PYET): pyet.o gent.o tool.o
		$(CC) -o $@ $^ $(LDFLAGS) $(PYLDFLAGS) -lboost_python-py32 

pyet.o: $(SRC)/pyet.cpp $(INCLUDE)/pyet.hpp
		$(CC) -o $@ -c $< $(CFLAGS) $(PYCFLAGS)

gent.o:  $(SRC)/gent.cpp $(INCLUDE)/gent.hpp 
		$(CC) -o $@ -c $< $(CFLAGS) $(PYCFLAGS)

tool.o: $(SRC)/tools.cpp $(INCLUDE)/tools.hpp 
		$(CC) -o $@ -c $< $(CFLAGS) $(PYCFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
