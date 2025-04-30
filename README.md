# 112201026-CS3140

Compiler Design Course (CS3140)

- **Name**: Gajjala Bhavani Shankar  
- **Roll Number**: 112201026

## Assignment 4 Instructions

### To Run:

0. To install prerequisites, run the `qemu.sh` script in the `compiler/` folder.
1. Go to the compiler directory:
   ```bash
   cd compiler/
   ```
2. Build the executable:
   ```bash
   make
   ```
3. Compile an input file (`a.sil`):
   ```bash
   ./bin/compiler a.sil
   ```
   The output `.s` file will be placed in `compiler/`.
4. Compile the generated `.s` to a MIPS executable:
   ```bash
   mips-linux-gnu-gcc-10 a.s -o a.o
   ```
5. Run the object file in QEMU:
   ```bash
   qemu-mips -L /usr/mips-linux-gnu/ a.o
   ```

## Implementation Details

- **Compiler executable**: `compiler/bin/compiler`
- **MIPS assembly output**: Generated `.s` files appear in `compiler/`

## Note

- If any error occurs during testing, check the `.s` files saved in the `outputs/` folder.

## Screenshots

- **AST:**  
  ![AST representation](static/b_AST.png)

- **MIPS Assembly:**  
  ![MIPS code](static/b_mips_code.png)

