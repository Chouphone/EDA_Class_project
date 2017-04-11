CC = g++
MAIN_OBJS = EDA.o

all: EDA

EDA: ./EDA.cc
	$(CC) -o EDA EDA.cc
clean:
	@rm -f EDA
