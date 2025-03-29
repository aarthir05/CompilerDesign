# Matrix Multiplication to Custom ISA & Binary Code

## Overview
This project converts a **C++ matrix multiplication program (`matmul.cpp`)** into a **custom 24-bit Instruction Set Architecture (ISA)** and then further translates it into **binary encoding**.

### **Pipeline**
1. **Compile C++ to LLVM IR** → Convert `matmul.cpp` into `matmul.ll` using Clang.
2. **Extract relevant instructions** → Parse LLVM IR (`matmul.ll`) and generate ISA (`output.isa`).
3. **Convert ISA to binary encoding** → Transform ISA instructions into a structured 24-bit binary format (`output_bin.txt`).


## **Installation & Setup**
### **1. Install Clang (if not installed)**
Run the following command:
```sh
clang -S -emit-llvm matmul.cpp -o matmul.ll
g++ ir_to_isa.cpp -o ir_to_isa.exe
g++ isa_to_bin.cpp -o isa_to_bin.exe

