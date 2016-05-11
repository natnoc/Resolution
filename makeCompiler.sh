bison -d parser.y
flex -t TokenScanner.l > scanner.c
gcc -c -o scanner.o scanner.c
gcc -c -o parser.tab.o parser.tab.c
#gcc -c -o definition.o definition.c
gcc -c -o functions.o functions.c
gcc scanner.o parser.tab.o functions.o -o scanner
