IDIR  = ./include
ODIR  = ./obj
SDIR  = ./src
SRC   = $(wildcard $(SDIR)/*.cpp)
OBJS  = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SRC))
DEPS  = $(wildcard $(IDIR)/*.h) include/util.h include/parser.tab.h
FLAGS = -Wall -I$(IDIR)/ -std=c++11
CC    = g++

all: main

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -g -c -o $@ $(FLAGS) $<

src/parser.tab.c include/parser.tab.h: src/parser.y
	bison -d src/parser.y		
	mv parser.tab.c src/parser.tab.c
	mv parser.tab.h include/parser.tab.h

src/lex.yy.c: src/scanner.l src/parser.tab.c
	flex src/scanner.l
	mv lex.yy.c src/lex.yy.c

obj/parser.tab.o: src/parser.tab.c
	$(CC) -g -c -o $@ $(FLAGS) $<

obj/lex.yy.o: src/lex.yy.c
	$(CC) -g -c -o $@ $(FLAGS) $<

main: obj/parser.tab.o obj/lex.yy.o $(OBJS)
	$(CC) -o $@ $^ -Wall $(FLAGS)

.PHONY: clean
clean:
	rm -rf $(ODIR)/* main include/parser.tab.h src/parser.tab.c src/lex.yy.c
