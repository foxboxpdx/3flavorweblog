CC = g++
CFLAGS = -std=c++11
LINKDIRS = -L/usr/lib/x86_64-linux-gnu -L/usr/lib
LINKOPTS = -lpcre -lpcre++ -lsqlite3

all: parser.o weblogdb.o tester.o

parser.o: parser.cpp parser.h weblog.h weblogdb.h
	$(CC) parser.cpp -c $(CFLAGS)

weblogdb.o: weblogdb.cpp weblogdb.h weblog.h
	$(CC) $(CFLAGS) -c weblogdb.cpp

tester.o: tester.cpp
	$(CC) $(CFLAGS) -c tester.cpp

tester:
	$(CC) $(CFLAGS) -o tester tester.o weblogdb.o parser.o $(LINKDIRS) $(LINKOPTS)

clean:
	rm *.o tester

