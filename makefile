CC = g++
OPENCV = `pkg-config opencv4 --cflags --libs`
EXE = app

all: main clean

main: *.o
	$(CC) -o ${EXE} *.o ${OPENCV}
 
*.o: *.cpp
	$(CC) -c *.cpp ${OPENCV}

clean:
	rm -Rf *.o
 