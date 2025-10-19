# Project Overview

This is a simple C++20 Hello World application. The program demonstrates basic C++ syntax and outputs "Hello World" to the console.

## User Preferences

Preferred communication style: Simple, everyday language.

## System Architecture

**Language**: C++20  
**Compiler**: Clang 14  
**Build System**: Direct compilation via command line

### Project Structure
- `main.cpp` - Main source file containing the Hello World program
- `.gitignore` - Excludes C++ build artifacts from version control

### Compilation
The program is compiled with:
```bash
clang++ -std=c++20 main.cpp -o main
```

This ensures C++20 standard compliance as requested.

## External Dependencies

**Compiler**: Clang 14 (cpp-clang14 module)
- Includes C++ compiler, GDB debugger, and ccls language server
- Supports C++20 standard features

**No external libraries** - This is a minimal Hello World program using only the C++ standard library (`<iostream>`).

---

**Last Updated**: October 19, 2025  
**Status**: Complete - Application runs successfully and outputs "Hello World"
