CXX = g++
CXXFLAGS = -Wall -std=c++11 
LIBS = -lSDL2 -lstdc++ -lSDL2_image

sdl_chess: main.o Game.o Move.o Piece.o Board.o
	$(CXX) $(CXXFLAGS) $(LIBS) main.o Game.o Move.o Piece.o Board.o -o sdl_chess

main.o: Game.h main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp 

Game.o: Game.h Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

Move.o: Move.h Move.cpp
	$(CXX) $(CXXFLAGS) -c Move.cpp

Piece.o: Piece.h Piece.cpp
	$(CXX) $(CXXFLAGS) -c Piece.cpp

Board.o: Board.h Board.cpp
	$(CXX) $(CXXFLAGS) -c Board.cpp

clean:
	rm -f *.o sdl_chess
