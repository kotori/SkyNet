CC:=cc
CFLAGS:=-g -Wall -W -O2 -Wno-write-strings
LDFLAGS:=-lpthread -ldl -lboost_system
INSTALL_PATH:=skynet
COMPRESS:= /usr/bin/upx -9
OBJDIR:=obj
SRCDIR:=src
EXEC:=skynet
OBJECTS:= $(OBJDIR)/sqlite3.o $(OBJDIR)/database.o $(OBJDIR)/server.o $(OBJDIR)/manager.o  $(OBJDIR)/main.o

all: $(EXEC)

# Link command:
$(EXEC): $(OBJECTS)
	@echo "Beginning Linking Process..."
	mkdir -p $(INSTALL_PATH)/bin
	$(CC) $(OBJECTS) -o $(INSTALL_PATH)/bin/$(EXEC) $(LDFLAGS)
	@echo "Linking Process Complete!..."
	# After compilation, compress the executable to save some space.
	$(COMPRESS) $(INSTALL_PATH)/bin/$(EXEC)
	@echo "Compilation is Complete!"

# Compilation commands:
$(OBJDIR)/sqlite3.o: $(SRCDIR)/sqlite3/sqlite3.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(SRCDIR)/sqlite3/sqlite3.c -o $(OBJDIR)/sqlite3.o -lpthread -ldl

$(OBJDIR)/database.o: $(SRCDIR)/database.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(SRCDIR)/database.cpp -o $(OBJDIR)/database.o

$(OBJDIR)/server.o: $(SRCDIR)/server.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(SRCDIR)/server.cpp -o $(OBJDIR)/server.o

$(OBJDIR)/manager.o: $(SRCDIR)/manager.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(SRCDIR)/manager.cpp -o $(OBJDIR)/manager.o

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

.PHONY: all clean

clean:
	rm -rf $(OBJDIR)

uninstall:
	@echo "WARNING THIS WILL REMOVE THE ENTIRE $(INSTALL_PATH) DIRECTORY!"
	rm -rf $(INSTALL_PATH)
