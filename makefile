VMTranslator: *.cpp
	g++  -c -g -Wall  -o bin/codeWriter.o sources/codeWriter.cpp -std=c++17 -lstdc++fs
	g++  -c -g -Wall  -o bin/parser.o sources/parser.cpp -std=c++17 -lstdc++fs
	g++  -c -g -Wall  -o bin/commands.o sources/commands.cpp -std=c++17 -lstdc++fs
	g++  -c -g -Wall  -o bin/main.o main.cpp -std=c++17 -lstdc++fs
	g++  bin/main.o  bin/codeWriter.o bin/parser.o bin/commands.o -o VMTranslator -std=c++17 -lstdc++fs