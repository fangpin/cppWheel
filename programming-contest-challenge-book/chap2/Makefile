CC = g++ -std=c++11
CFLAGS = -Wall -Werror -o
SRC =$(wildcard *.cpp)
OBJ =$(patsubst %.cpp, %, $(SRC))

.PHONY:all clean

all:$(OBJ)

%:%.cpp
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -rf $(OBJ) *.o *.dSYM
