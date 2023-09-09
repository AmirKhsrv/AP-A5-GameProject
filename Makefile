CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: FieldRunners.out

FieldRunners.out: main.o rsdl.o Block.o Field.o Path.o Enemy.o Wave.o Attack.o FieldRunner.o Interface.o Tower.o Defense.o Shot.o
	$(CC) main.o rsdl.o Block.o Field.o Path.o Enemy.o Wave.o Attack.o FieldRunner.o Interface.o Tower.o Defense.o Shot.o $(CCFLAGS) -o FieldRunners.out

main.o: main.cpp rsdl.hpp Block.hpp Field.hpp Path.hpp Enemy.hpp Wave.hpp Attack.hpp FieldRunner.hpp Interface.hpp Tower.hpp Defense.hpp Shot.hpp InitialData.hpp AddressData.hpp
	$(CC) -c main.cpp -o main.o

rsdl.o: rsdl.hpp rsdl.cpp InitialData.hpp AddressData.hpp
	$(CC) -c rsdl.cpp -o rsdl.o

Interface.o: Interface.hpp Interface.cpp FieldRunner.hpp Attack.hpp Wave.hpp Enemy.hpp Path.hpp Field.hpp Block.hpp Tower.hpp Defense.hpp Shot.hpp InitialData.hpp AddressData.hpp
	$(CC) -c Interface.cpp -o Interface.o

FieldRunner.o: FieldRunner.hpp FieldRunner.cpp Attack.hpp Wave.hpp Enemy.hpp Path.hpp Field.hpp Block.hpp Tower.hpp Defense.hpp Shot.hpp InitialData.hpp AddressData.hpp
	$(CC) -c FieldRunner.cpp -o FieldRunner.o

Attack.o: Attack.hpp Attack.cpp Wave.hpp Enemy.hpp Path.hpp Field.hpp Block.hpp InitialData.hpp AddressData.hpp
	$(CC) -c Attack.cpp -o Attack.o

Wave.o: Wave.hpp Wave.cpp Enemy.hpp Path.hpp Field.hpp Block.hpp InitialData.hpp AddressData.hpp
	$(CC) -c Wave.cpp -o Wave.o

Enemy.o: Enemy.hpp Enemy.cpp Path.hpp Field.hpp Block.hpp InitialData.hpp AddressData.hpp
	$(CC) -c Enemy.cpp -o Enemy.o

Shot.o: Shot.hpp Shot.cpp Enemy.hpp Path.hpp Field.hpp Block.hpp Attack.hpp InitialData.hpp AddressData.hpp
	$(CC) -c Shot.cpp -o Shot.o

Path.o: Path.hpp Path.cpp Field.hpp Block.hpp InitialData.hpp AddressData.hpp
	$(CC) -c Path.cpp -o Path.o

Defense.o: Defense.hpp Defense.cpp Tower.hpp Attack.hpp Wave.hpp Enemy.hpp Path.hpp Field.hpp Block.hpp Shot.hpp InitialData.hpp AddressData.hpp
	$(CC) -c Defense.cpp -o Defense.o

Tower.o: Tower.hpp Tower.cpp Attack.hpp Wave.hpp Enemy.hpp Path.hpp Field.hpp Block.hpp Shot.hpp InitialData.hpp AddressData.hpp
	$(CC) -c Tower.cpp -o Tower.o

Field.o: Field.hpp Field.cpp Block.hpp InitialData.hpp AddressData.hpp
	$(CC) -c Field.cpp -o Field.o

Block.o: Block.hpp Block.cpp InitialData.hpp AddressData.hpp
	$(CC) -c Block.cpp -o Block.o

clean:
	rm -r *.o
	rm -r *.out
