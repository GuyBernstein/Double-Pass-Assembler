# GuyBernstein-OpenU-C-Project
Double-pass assembler, written in ANSI C90 for an imaginary 24-bit computer.
About
This project is an assignment in a C programming course at the open unvieristy (20465). The purpose of this project is to build an assembler for 15-instruction asssembly language, for an imaginary 24-bit CPU and 21 bits of memory size. This project was done by @GuyBernstain . For any issues, questions and ideas turn to the Issues tab.



Source structure (Modules)
assembler - main function definition, argv & argc processing, single file processing.
preAssembler - remove macros and invocations of macros defenitions in the file and creating a file to be proccessed.
first_pass - contains functions for processing a single line in the first pass and a code line in the first pass.
code - contains useful function for processing code.
directive - contains useful function for processing directives.
declerations.h - contains type and constant definitions.
utils - contains general-purposed, project-wide functions.
./assembler file1 file2 file3 ... Will start the processing of each file (specify WITHOUT extension!). No support for double-quoting file names.
