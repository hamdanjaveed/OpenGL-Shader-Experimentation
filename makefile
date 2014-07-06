CC = g++
CFLAGS = -Wall -g
LDFLAGS = -framework OpenGL -L/usr/local/Cellar -lglew -lglfw3

myprogram: main.o util.o
	${CC} ${CFLAGS} util.o main.o ${LDFLAGS} -o myprogram

util.o: util.cpp util.h
	${CC} ${CFLAGS} -c util.cpp

main.o: main.cpp util.o
	${CC} ${CFLAGS} -c main.cpp

clean:
	rm -f *.o

