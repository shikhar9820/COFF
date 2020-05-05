CC = gcc
CFLAGS = -Wall

#Dependencies
DEPS = coff.h

#Object Files   
OBJ = functions.o read_config.o main.o

#Default goal
coff: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	@echo ""
	@echo "Re-writing config file with default values: ~/.coff_config"
	@echo ""
	@echo "PATH TO QUESTION"> ~/.coff_config
	@echo "~/coff/quest"    >> ~/.coff_config
	@echo "PATH TO ANSWER"  >> ~/.coff_config
	@echo "~/coff/ans"      >> ~/.coff_config
	mkdir -p ~/coff/quest ~/coff/ans

#Header dependencies
$(OBJ): $(DEPS)

.PHONY: clean
clean:
	rm -f *.o *.out coff
