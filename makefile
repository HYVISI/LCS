a.out: lcs.o
	gcc -o a.out lcs.o
lcs.o: lcs.c
	gcc -c -o lcs.o lcs.c
clean:
	rm a.out lcs.o
 
