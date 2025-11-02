bin/Parcial2: src/Parcial2.cpp
	c++ -IFTXUI/include -LFTXUI/build src/Parcial2.cpp -o bin/Parcial2 -lftxui-screen -lftxui-dom -lftxui-component

runParcial2: bin/Parcial2
	./bin/Parcial2

