# Basic compilation macros
CC = gcc # GCC Compiler
CFLAGS = -ansi -Wall -pedantic # Flags
GLOBAL_DEPS = declarations.h  # Dependencies for everything
EXE_DEPS = assembler.o preAssembler.o stepOne.o utils.o directive.o code.o # Deps for exe

## Executable
assembler: $(EXE_DEPS) $(GLOBAL_DEPS)
	$(CC) -g $(EXE_DEPS) $(CFLAGS) -o $@

## Main:
assembler.o: assembler.c preAssembler.h stepOne.h $(GLOBAL_DEPS)
	$(CC) -c assembler.c $(CFLAGS) -o $@

preAssembler.o: preAssembler.c preAssembler.h $(GLOBAL_DEPS)
	$(CC) -c preAssembler.c $(CFLAGS) -o $@

## First Pass:
stepOne.o: stepOne.c stepOne.h $(GLOBAL_DEPS)
	$(CC) -c stepOne.c $(CFLAGS) -o $@ 

# Code helper functions:
code.o: code.c code.h $(GLOBAL_DEPS)
	$(CC) -c code.c $(CFLAGS) -o $@

## directives helper functions:
directive.o: directive.c directive.h $(GLOBAL_DEPS)
	$(CC) -c directive.c $(CFLAGS) -o $@
	
## Useful functions:
utils.o: utils.c utils.h directive.h $(GLOBAL_DEPS)
	$(CC) -c utils.c $(CFLAGS) -o $@



# Clean Target (remove leftovers)
clean:
	rm -rf *.o
