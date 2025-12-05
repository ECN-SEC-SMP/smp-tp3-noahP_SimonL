# === Variables ===
EXEC_PROGRAM1 = folder_build
EXEC_PROGRAM2 = main

# === Règles ===

all: $(EXEC_PROGRAM1) $(EXEC_PROGRAM2)  
 
# Compilation de l'exécutable

$(EXEC_PROGRAM1): 
	mkdir -p build

$(EXEC_PROGRAM2): ./build/main.o ./build/outils.o ./build/chargesauve.o
	g++ -o $(EXEC_PROGRAM2) ./build/main.o ./build/outils.o ./build/chargesauve.o


# Compilation des fichiers sources en fichiers objets
./build/main.o: ./main.cpp
	g++ -I./include -c ./main.cpp -o ./build/main.o

./build/outils.o: ./src/outils.cpp
	g++ -I./include -c ./src/outils.cpp -o ./build/outils.o

./build/chargesauve.o: ./src/chargesauve.cpp
	g++ -I./include -c ./src/chargesauve.cpp -o ./build/chargesauve.o


# Supprime les fichiers objets et l'exécutable
clean:
	rm -f build/*.o
#	rm -f ./assets/pgmMod/*
	rm -f $(EXEC_PROGRAM1) $(EXEC_PROGRAM2)

.PHONY: all cleanZ

