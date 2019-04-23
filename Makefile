#all: cipher #mydes myaes

cipher:	cipher.o DES.o AES.o
	g++ cipher.o DES.o AES.o -o cipher -lcrypto


cipher.o: cipher.cpp
	g++ -g -c -std=c++11 cipher.cpp


mydes: mydes.cpp
	g++ mydes.cpp -o mydes -lcrypto
	
myaes: myaes.cpp
	g++ myaes.cpp -o myaes -lcrypto

DES.o: DES.cpp DES.h
	g++ -g -c -std=c++11 DES.cpp

AES.o: AES.cpp AES.h
	g++ -g -c -std=c++11 AES.cpp

RSA.o: RSA.cpp RSA.h
	g++ -g -c RSA.cpp


clean:
	rm -rf *.o cipher myaes mydes
