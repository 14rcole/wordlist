OPTS= -g -c  -Wall -Werror
all: classwords

classwords: wordSearchNode.o classwords.o
	g++ classwords.o wordSearchNode.o -o classwords

classwords.o: classwords.cpp
	g++ $(OPTS) classwords.cpp -o classwords.o

wordSearchNode.o: wordSearchNode.cpp
	g++ $(OPTS) wordSearchNode.cpp -o wordSearchNode.o

clean:
	rm -f wordSearchNode.o classwords.o classwords
