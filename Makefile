all: EuclideanVectorTester EuclideanVectorTester2

EuclideanVectorTester: EuclideanVectorTester.o EuclideanVector.o
	g++ -fsanitize=address EuclideanVectorTester.o EuclideanVector.o -o EuclideanVectorTester

EuclideanVectorTester2: EuclideanVectorTester2.o EuclideanVector.o
	g++ -fsanitize=address EuclideanVectorTester2.o EuclideanVector.o -o EuclideanVectorTester2

EuclideanVectorTester.o: EuclideanVectorTester.cpp EuclideanVector.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c EuclideanVectorTester.cpp
EuclideanVectorTester2.o: EuclideanVectorTester2.cpp EuclideanVector.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c EuclideanVectorTester2.cpp
EuclideanVector.o: EuclideanVector.cpp EuclideanVector.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c EuclideanVector.cpp

clean:
	rm *o EuclideanVectorTester EuclideanVectorTester2

win:
	make -f Makefile.win
