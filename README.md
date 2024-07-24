# RISCV_assembler-

This project is an assembler coded in C that converts assembly language instructions into machine code. It not only translates the instructions but also ensures code accuracy by checking for syntactic and semantic errors, providing detailed debugging information. The assembler updates the program counter and generates machine code in various instruction formats such as R, I, S, SB, U, UJ.

Features
Error Checking: Identifies and reports syntactic and semantic errors, specifying the line number for easy debugging.
Instruction Parsing: Parses each line of the assembly code to identify operation and operands.
Machine Code Generation: Converts parsed instructions into machine code according to the instruction type format.
Program Counter Update: Keeps track of the program counter throughout the assembly process.
