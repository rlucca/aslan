demo: main.o lex.Aslan_.o aslan.tab.o
	g++ -g -o demo main.o lex.Aslan_.o aslan.tab.o -lfl

main.o: main.cpp
	g++ -g -c -o main.o main.cpp

lex.Aslan_.o: lex.Aslan_.c aslan.tab.h
	g++ -g -c -o lex.Aslan_.o lex.Aslan_.c

lex.Aslan_.c: aslan.l
	flex aslan.l

aslan.tab.o: aslan.tab.c
	g++ -g -c -o aslan.tab.o aslan.tab.c

aslan.tab.c aslan.tab.h: aslan.y
	bison aslan.y

.PHONY: clean
clean:
	rm -f demo *.o
	rm -f aslan.tab.c aslan.tab.h
	rm -f lex.Aslan_.c lex.Aslan_.o
