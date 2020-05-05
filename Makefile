CC = gcc
CFLAGS = -Wall

#Dependencies
DEPS = coff.h

#Object Files   
OBJ = functions.o main.o

#Default goal
coff: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

#Header dependencies
$(OBJ): $(DEPS)

.PHONY: clean
clean:
	rm -f *.o *.out coff
