#itamarbabai98@gmail.com
C = g++
CPP_DIR=CPP/
HPP_DIR=HPP/
OBJ_DIR=OBJ/
HEADERS =$(HPP_DIR)Game.hpp $(HPP_DIR)Governor.hpp $(HPP_DIR)Player.hpp $(HPP_DIR)Spy.hpp $(HPP_DIR)Baron.hpp $(HPP_DIR)General.hpp $(HPP_DIR)Judge.hpp $(HPP_DIR)Merchant.hpp $(HPP_DIR)main.hpp
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
Target_demo =demo
Target =main
TEST_TARGET = test
FLAGS = -c -g -Wall -std=c++17 -I$(HPP_DIR)
OBJECTD = $(OBJ_DIR)Demo.o $(OBJ_DIR)Game.o $(OBJ_DIR)Governor.o $(OBJ_DIR)Player.o $(OBJ_DIR)Spy.o $(OBJ_DIR)Baron.o $(OBJ_DIR)General.o $(OBJ_DIR)Judge.o $(OBJ_DIR)Merchant.o
OBJECT = $(OBJ_DIR)Game.o $(OBJ_DIR)Governor.o $(OBJ_DIR)Player.o $(OBJ_DIR)Spy.o $(OBJ_DIR)main.o $(OBJ_DIR)Baron.o $(OBJ_DIR)General.o $(OBJ_DIR)Judge.o $(OBJ_DIR)Merchant.o
TEST_OBJ = $(OBJ_DIR)test.o $(OBJ_DIR)Game.o $(OBJ_DIR)Governor.o $(OBJ_DIR)Player.o $(OBJ_DIR)Spy.o $(OBJ_DIR)Baron.o $(OBJ_DIR)General.o $(OBJ_DIR)Judge.o $(OBJ_DIR)Merchant.o

$(Target): $(OBJECT)
	$(C) -Wall -o $(Target) $(OBJECT) $(SFML_LIBS)

$(Target_demo): $(OBJECTD)
	$(C) -Wall -o $(Target_demo) $(OBJECTD) $(SFML_LIBS)

$(TEST_TARGET): $(TEST_OBJ)
	$(C) -Wall -o $(TEST_TARGET) $(TEST_OBJ) $(SFML_LIBS)

$(OBJ_DIR)Demo.o: Demo.cpp $(HEADERS)
	$(C) $(FLAGS) Demo.cpp -o $(OBJ_DIR)Demo.o

$(OBJ_DIR)main.o: main.cpp $(HEADERS)
	$(C) $(FLAGS) main.cpp -o $(OBJ_DIR)main.o

$(OBJ_DIR)Game.o: $(CPP_DIR)Game.cpp $(HEADERS)
	$(C) $(FLAGS) $(CPP_DIR)Game.cpp -o $(OBJ_DIR)Game.o

$(OBJ_DIR)Player.o: $(CPP_DIR)Player.cpp $(HEADERS)
	$(C) $(FLAGS) $(CPP_DIR)Player.cpp -o $(OBJ_DIR)Player.o

$(OBJ_DIR)Governor.o: $(CPP_DIR)Governor.cpp $(HEADERS)
	$(C) $(FLAGS) $(CPP_DIR)Governor.cpp -o $(OBJ_DIR)Governor.o

$(OBJ_DIR)Spy.o: $(CPP_DIR)Spy.cpp $(HEADERS)
	$(C) $(FLAGS) $(CPP_DIR)Spy.cpp -o $(OBJ_DIR)Spy.o

$(OBJ_DIR)Baron.o: $(CPP_DIR)Baron.cpp $(HEADERS)
	$(C) $(FLAGS) $(CPP_DIR)Baron.cpp -o $(OBJ_DIR)Baron.o

$(OBJ_DIR)General.o: $(CPP_DIR)General.cpp $(HEADERS)
	$(C) $(FLAGS) $(CPP_DIR)General.cpp -o $(OBJ_DIR)General.o

$(OBJ_DIR)Judge.o: $(CPP_DIR)Judge.cpp $(HEADERS)
	$(C) $(FLAGS) $(CPP_DIR)Judge.cpp -o $(OBJ_DIR)Judge.o

$(OBJ_DIR)Merchant.o: $(CPP_DIR)Merchant.cpp $(HEADERS)
	$(C) $(FLAGS) $(CPP_DIR)Merchant.cpp -o $(OBJ_DIR)Merchant.o

$(OBJ_DIR)test.o:test.cpp $(HEADERS)
	$(C) $(FLAGS) test.cpp -o $(OBJ_DIR)test.o

Test: $(TEST_TARGET)
	./$(TEST_TARGET)

Main: $(Target)
	./$(Target)

Demo: $(Target_demo)
	./$(Target_demo)

valgrind: $(Target_demo)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(Target_demo)

.PHONY: $(Target) clean $(Target_demo) $(TEST_TARGET) valgrind Test Main Demo

clean:
	rm -f $(OBJ_DIR)*.o $(Target) $(Target_demo) $(TEST_TARGET)