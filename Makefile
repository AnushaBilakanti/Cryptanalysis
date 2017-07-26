hw3: main.o keygen.o crypt.o invkey.o histo.o solve.o 
	gcc -g main.o keygen.o crypt.o invkey.o histo.o solve.o -o hw3 -L/home/scf-22/csci551b/openssl/lib -lcrypto -lm

main.o: main.c functions.h
	gcc  -c -g -Wall main.c -I/home/scf-22/csci551b/openssl/include

keygen.o: keygen.c functions.h
	gcc  -c -g -Wall keygen.c -I/home/scf-22/csci551b/openssl/include

crypt.o: crypt.c functions.h
	gcc -c -g -Wall crypt.c -I/home/scf-22/csci551b/openssl/includes

invkey.o: invkey.c functions.h
	gcc -g -c -Wall invkey.c -I/home/scf-22/csci551b/openssl/include

histo.o: histo.c functions.h
	gcc -g -c -Wall histo.c -I/home/scf-22/csci551b/openssl/include

solve.o: solve.c functions.h 
	gcc -g -c -Wall solve.c -I/home/scf-22/csci551b/openssl/include

clean:
	rm *.o
	rm hw3
