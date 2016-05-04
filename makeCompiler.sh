bison -d parser.y
flex -t TokenScanner.l > TokenScanner.c
gcc -c -o TokenScanner.o TokenScanner.c
gcc -c -o parser.tab.o parser.tab.c
gcc -c -o functions.o functions.c
gcc TokenScanner.o parser.tab.o functions.o -o compiler
