CC:=cc
CFLAGS:=-g -Wall -W -O2 -Wno-write-strings
LDFLAGS:=-lpthread -ldl -lboost_system
OBJECTS:= sqlite3.o database.o main.o
INSTALL_PATH=bin
SRCDIR=src
EXEC=skynet

all: $(EXEC) clean

# Link command:
$(EXEC): $(OBJECTS)
	mkdir -p $(INSTALL_PATH)
	$(CC) $(OBJECTS) -o $(INSTALL_PATH)/$(EXEC) $(LDFLAGS)

# Compilation commands:
sqlite3.o: $(SRCDIR)/sqlite3/sqlite3.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/sqlite3/sqlite3.c -o sqlite3.o -lpthread -ldl

database.o: $(SRCDIR)/database.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)/database.cpp -o database.o

main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.cpp -o main.o

.PHONY: clean cleanest

clean:
	rm *.o

uninstall:
	echo "WARNING THIS WILL REMOVE THE ENTIRE $(INSTALL_PATH) DIRECTORY!"
	rm -rf $(INSTALL_PATH)
