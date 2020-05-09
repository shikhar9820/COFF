CC = gcc
CFLAGS = -Wall

#Dependencies
DEPS = coff.h

#Object Files   
OBJ_COFF = functions.o read_config.o main.o
OBJ_QUEST = functions.o read_config.o write_question.o

#Default goal
coff: $(OBJ_COFF)
	$(CC) $(CFLAGS) -o $@ $^
	./initconfig

#Writing Questions
coff-quest: $(OBJ_QUEST)
	$(CC) $(CFLAGS) -o $@ $^
	./initconfig

#Header dependencies
$(OBJ_COFF): $(DEPS)

$(OBJ_QUEST): $(DEPS)

.PHONY: clean
clean:
	@rm -f *.o *.out *.bin *.txt *.dat *.quest *.ans coff coff-quest
