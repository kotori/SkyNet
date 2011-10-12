CC:=cc
CFLAGS:=-g -Wall -W -O2 -Wno-write-strings
LDFLAGS:=-lpthread -ldl -lboost_system
INSTALL_PATH=skynet
OBJDIR=obj
SRCDIR=src
EXEC=skynet
OBJECTS:= $(OBJDIR)/sqlite3.o $(OBJDIR)/database.o $(OBJDIR)/main.o

all: $(EXEC)

# Link command:
$(EXEC): $(OBJECTS)
	mkdir -p $(INSTALL_PATH)/bin
	$(CC) $(OBJECTS) -o $(INSTALL_PATH)/bin/$(EXEC) $(LDFLAGS)

# Compilation commands:
$(OBJDIR)/sqlite3.o: $(SRCDIR)/sqlite3/sqlite3.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(SRCDIR)/sqlite3/sqlite3.c -o $(OBJDIR)/sqlite3.o -lpthread -ldl

$(OBJDIR)/database.o: $(SRCDIR)/database.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(SRCDIR)/database.cpp -o $(OBJDIR)/database.o

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

.PHONY: clean

clean:
	rm -rf $(OBJDIR)

uninstall:
	echo "WARNING THIS WILL REMOVE THE ENTIRE $(INSTALL_PATH) DIRECTORY!"
	rm -rf $(INSTALL_PATH)
