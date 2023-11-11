# Define compiler
CC = gcc

# Define compiler flags
CFLAGS = -ansi -Wall -Wextra -pedantic

# Define global dependencies
GLOBAL_DEPS = declarations.h

# Define object file dependencies for executable
EXE_DEPS = assembler.o preAssembler.o stepOne.o utils.o directive.o table.o stepTwo.o

# Define executable target and dependencies
assembler: $(EXE_DEPS) $(GLOBAL_DEPS)
	$(CC) -g  $(CFLAGS) -o $@ $(EXE_DEPS)

# Define main source file target and dependencies
assembler.o: assembler.c preAssembler.h stepOne.h $(GLOBAL_DEPS)
	$(CC) $(CFLAGS) -c -o $@ assembler.c

# Define preassembler source file target and dependencies
preAssembler.o: preAssembler.c preAssembler.h $(GLOBAL_DEPS)
	$(CC) $(CFLAGS) -c -o $@ preAssembler.c

# Define first pass source file target and dependencies
stepOne.o: stepOne.c stepOne.h $(GLOBAL_DEPS)
	$(CC) $(CFLAGS) -c -o $@ stepOne.c

# Define second pass source file target and dependencies
stepTwo.o: stepTwo.c stepTwo.h $(GLOBAL_DEPS)
	$(CC) $(CFLAGS) -c -o $@ stepTwo.c

# Define table source file target and dependencies
table.o: table.c table.h $(GLOBAL_DEPS)
	$(CC) $(CFLAGS) -c -o $@ table.c

# Define directives helper functions source file target and dependencies
directive.o: directive.c directive.h $(GLOBAL_DEPS)
	$(CC) $(CFLAGS) -c -o $@ directive.c

# Define useful functions source file target and dependencies
utils.o: utils.c utils.h directive.h $(GLOBAL_DEPS)
	$(CC) $(CFLAGS) -c -o $@ utils.c

# Define clean target to remove object files and executable
clean:
	rm -f *.o assembler
