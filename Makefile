###
### Makefile for Gerp Project
### Gerp is a search function for words in a file
###
### Josh Blum (jblum02) Nate Perry (nperry02)

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

gerp: main.o Gerp.o hashTable.o bucket.o DirNode.o FSTree.o
	${CXX} ${LDFLAGS} -O2 -o gerp $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -O2 -c main.cpp

Gerp.o: Gerp.cpp Gerp.h
	$(CXX) $(CXXFLAGS) -O2 -c Gerp.cpp

treeTraversal: FSTreeTraversal.cpp DirNode.o FSTree.o
	${CXX} ${LDFLAGS} -O2 -o treeTraversal $^

stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -O2 -c stringProcessing.cpp

bucket.o: bucket.cpp bucket.h
	$(CXX) $(CXXFLAGS) -O2 -c bucket.cpp

hashTable.o: hashTable.cpp hashTable.h
	$(CXX) $(CXXFLAGS) -O2 -c hashTable.cpp

unit_test: unit_test_driver.o stringProcessing.o bucket.o hashTable.o
	$(CXX) $(CXXFLAGS) $^
