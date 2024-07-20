# Two-Pass Assembler for Imaginary 24-bit Computer 🖥️

## Project Overview 🚀

This project is a two-pass assembler written in ANSI C90 for an imaginary 24-bit computer. It was developed as part of a C programming course (20465) at the Open University of Israel. The assembler is designed to process a custom 15-instruction assembly language and generate machine code for a 24-bit CPU with 21 bits of memory addressing.

## Features ✨

- Processes custom assembly language with 15 instructions
- Supports a 24-bit CPU architecture
- Handles 21 bits of memory addressing
- Implements a two-pass assembly process
- Written in ANSI C90 for maximum compatibility
- Includes a pre-assembler for macro processing

## Project Structure 📁

The assembler is organized into several modules, each responsible for specific functionality:

- `assembler.c`: Main function, command-line argument processing, and file handling
- `preAssembler.c`: Macro expansion and pre-processing
- `stepOne.c`: First pass of the assembly process
- `stepTwo.c`: Second pass of the assembly process
- `code.c`: Code generation and instruction processing
- `directive.c`: Handling of assembly directives
- `utils.c`: General-purpose utility functions
- `table.c`: Symbol table management
- `declarations.h`: Type and constant definitions

## Building and Running 🛠️

To build the project, use the provided Makefile:
make
To run the assembler:
./assembler file1 file2 file3 ...
Note: Specify input files WITHOUT the file extension. The assembler does not support filenames with spaces.

## Input and Output 📥📤

The assembler processes `.as` (assembly) files and generates the following output files:

- `.am`: Expanded assembly code after macro processing
- `.ob`: Object file containing the generated machine code
- `.ent`: Entry points file
- `.ext`: External references file

## Error Handling ⚠️

The assembler performs extensive error checking during both passes. Error messages are printed to stderr, including the filename and line number where the error occurred.

## Limitations ⚖️

- Maximum line length: 80 characters
- Maximum label length: 30 characters
- Memory size: 256 words (21-bit addressing)

## Contributing 🤝

This project is primarily for educational purposes. However, if you find any bugs or have suggestions for improvements, please open an issue or submit a pull request.

## Author ✍️

This project was developed by Guy Bernstein (@GuyBernstain) as part of the Open University of Israel's C programming course.

## Acknowledgments 🙏

Special thanks to the Open University of Israel and the course staff for providing the project specifications and guidance.


