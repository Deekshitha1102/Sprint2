CC = g++
CFLAGS = -g -Wall -c
INCLUDEPATH = ./../include
SRCPATH = ./../src
OBJPATH = ./../obj
BINPATH = ./../bin



$(BINPATH)/main: $(OBJPATH)/mainapp.o $(OBJPATH)/LString.o
	$(CC) -Wall -g -o main $(OBJPATH)/mainapp.o $(OBJPATH)/LString.o
	mv main $(BINPATH)

$(OBJPATH)/mainapp.o: $(SRCPATH)/mainapp.cpp $(INCLUDEPATH)/LString.h
	$(CC) $(CFLAGS) $(SRCPATH)/mainapp.cpp -I $(INCLUDEPATH)/
	mv mainapp.o $(OBJPATH)/

$(OBJPATH)/LString.o: $(SRCPATH)/LString.cpp $(INCLUDEPATH)/LString.h
	$(CC) $(CFLAGS) $(SRCPATH)/LString.cpp -I $(INCLUDEPATH)/
	mv LString.o $(OBJPATH)/

clear:
	rm $(BINPATH)/main $(OBJPATH)/mainapp.o $(OBJPATH)/LString.o

