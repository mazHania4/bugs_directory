CPP = g++
CFLAGS = -wall -g
OF = compiled/
TARGET = $(OF)bugs_contacts

# all
all: .all-post

.all-post: Tree.o List.o FileManager.o Controller.o Field.o Pair.o HashTable.o main.o
	$(CPP) $(OF)Tree.o $(OF)List.o $(OF)FileManager.o $(OF)Controller.o $(OF)Field.o $(OF)Pair.o $(OF)HashTable.o $(OF)main.o -o $(TARGET)

Tree.o: Tree.cpp
	$(CPP) -c Tree.cpp -o $(OF)Tree.o

List.o: List.cpp
	$(CPP) -c List.cpp -o $(OF)List.o

FileManager.o: FileManager.cpp
	$(CPP) -c FileManager.cpp -o $(OF)FileManager.o

Controller.o: Controller.cpp Controller.h
	$(CPP) -c Controller.cpp -o $(OF)Controller.o

Field.o: model/Field.cpp model/Field.h
	$(CPP) -c model/Field.cpp -o $(OF)Field.o

Pair.o: hash_table/Pair.cpp hash_table/Pair.h
	$(CPP) -c hash_table/Pair.cpp -o $(OF)Pair.o

HashTable.o: hash_table/HashTable.cpp
	$(CPP) -c hash_table/HashTable.cpp -o $(OF)HashTable.o

main.o:
	$(CPP) -c main.cpp -o $(OF)main.o

# clean
clean:
	rm -f *.o $(TARGET)
