game: dependencies
	g++ -std=c++17 -Wall src/game/Game.cpp -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf Music.o Sprite.o State.o  -o game -g


dependencies: 
	g++ -std=c++17 -Wall src/game/Music.cpp -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf -c -g
	g++ -std=c++17 -Wall src/game/Sprite.cpp -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf -c -g
	g++ -std=c++17 -Wall src/game/State.cpp -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_net -lSDL2_ttf -c -g