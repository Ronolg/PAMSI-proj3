APP = checkers

_start__: obj ./${APP}

obj:
	mkdir obj


./${APP}: obj/main.o obj/Position.o obj/Piece.o obj/GameTree.o obj/Player.o obj/AIplayer.o obj/Board.o 
	g++ -o ./${APP} obj/main.o obj/Position.o obj/Piece.o obj/GameTree.o obj/Player.o obj/AIplayer.o obj/Board.o 

obj/main.o: src/main.cpp inc/Position.h inc/Piece.h inc/Player.h inc/AIplayer.h inc/GameTree.h inc/Board.h 
	g++  -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

obj/Position.o: src/Position.cpp inc/Position.h
	g++ -Iinc -W -Wall -pedantic -c -o obj/Position.o src/Position.cpp

obj/Piece.o: src/Piece.cpp inc/Piece.h
	g++ -Iinc -W -Wall -pedantic -c -o obj/Piece.o src/Piece.cpp

obj/GameTree.o: src/GameTree.cpp inc/GameTree.h
	g++ -Iinc -W -Wall -pedantic -c -o obj/GameTree.o src/GameTree.cpp

obj/Player.o: src/Player.cpp inc/Player.h
	g++ -Iinc -W -Wall -pedantic -c -o obj/Player.o src/Player.cpp

obj/AIplayer.o: src/AIplayer.cpp inc/AIplayer.h
	g++ -Iinc -W -Wall -pedantic -c -o obj/AIplayer.o src/AIplayer.cpp

obj/Board.o: src/Board.cpp inc/Board.h
	g++ -Iinc -W -Wall -pedantic -c -o obj/Board.o src/Board.cpp


clean:
	rm -f obj/* ./${APP}

