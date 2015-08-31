CC = g++
CFLAGS = -std=c++11
LINKDIRS = -L/usr/lib/x86_64-linux-gnu -L/usr/lib
LINKOPTS = -lpcre -lpcre++ -lsqlite3

all: parser.o weblogdb.o reader.o reader

parser.o: parser.cpp parser.h weblog.h weblogdb.h
	$(CC) parser.cpp -c $(CFLAGS)

weblogdb.o: weblogdb.cpp weblogdb.h weblog.h
	$(CC) $(CFLAGS) -c weblogdb.cpp

reader.o: reader.cpp
	$(CC) $(CFLAGS) -c reader.cpp

reader: reader.o
	$(CC) $(CFLAGS) -o reader reader.o weblogdb.o parser.o $(LINKDIRS) $(LINKOPTS)

clean:
	rm -f *.o reader

