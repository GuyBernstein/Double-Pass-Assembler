# GuyBernstein-OpenU-C-Project
Double-pass assembler, written in ANSI C90 for an imaginary 24-bit computer.
About
This project is an assignment in a C programming course at the open unvieristy (20465). The purpose of this project is to build an assembler for 15-instruction asssembly language, for an imaginary 24-bit CPU and 21 bits of memory size. This project was done by @GuyBernstain and @Yuval. For any issues, questions and ideas turn to the Issues tab.



Source structure (Modules)
assembler - main function definition, argv & argc processing, single file processing.
first_pass - contains functions for processing a single line in the first pass and a code line in the first pass.
second_pass - contains function for processing a single line in second pass and replacing symbol by it's address.
code - contains useful function for processing code.
instructions - contains useful function for processing instruction.
globals.h - contains type and constant definitions.
table - contains definition of table-like linked list data structure.
utils - contains general-purposed, project-wide functions.
writefiles - contains methods for writing output files: *.ob, *.ext and *.ent
Usage
./assembler file1 file2 file3 ... Will start the processing of each file (specify WITHOUT extension!). No support for double-quoting file names.
