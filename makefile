# change application name here (executable output name)
TARGET=ClashOfMinds
 
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
 
PTHREAD=-pthread
 
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe
 
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
Mysqllib = `mysql_config --libs`
Mysqlconfig = `mysql_config -- cflags`
 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic
 
OBJS=    main.o
 
all: $(OBJS)
	$(LD) -o $(TARGET)   $(OBJS) $(Mysqllib) $(LDFLAGS)
    
main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB)  -o main.o

# game.o: src/game.c
#  	$(CC) -c $(CCFLAGS) src/game.c $(GTKLIB) -o game.o
clean:
	rm -f *.o $(TARGET)