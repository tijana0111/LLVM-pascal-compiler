CC=clang++
CPPFLAGS:=$(shell llvm-config-3.8 --cxxflags)
LDFLAGS:=$(shell llvm-config-3.8 --ldflags --system-libs --libs core native mcjit)

pascal: lex.yy.o parser.tab.o izraz.o naredba.o codegen.o
	$(CC) -g -o $@ $^ $(LDFLAGS) -rdynamic
parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) $(CPPFLAGS) -Wno-deprecated-register -Wno-sign-compare -c -o $@  $<
lex.yy.c: lexer.lex
	flex $<
izraz.o: izraz.cpp izraz.hpp codegen.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
naredba.o: naredba.cpp naredba.hpp izraz.hpp codegen.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
codegen.o: codegen.cpp codegen.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf *~ *tab* lex.yy.* *.o pseudokod *.output


