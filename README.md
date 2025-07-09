# 🐚 Minishell

Minishell is a simplified Unix shell implemented in C as part of the 42 school curriculum. The goal of the project is to recreate core features of a typical shell like `bash`, focusing on system calls, process control, environment management, and command execution, all from scratch.

---

## 🚀 Project Overview

This project was built without using any external parsing libraries or system shell functions like `system()`. Instead, it mimics the behavior of `bash` for:

- Command execution
- Redirections
- Pipes
- Built-in shell functions
- Signal handling
- Environment variable manipulation

The shell provides a user interface for executing both built-in and external commands in a Unix-like environment.

---

## ✨ Features

### ✅ **Command Execution**
- Supports execution of binaries found in `$PATH`
- Handles absolute and relative paths

### 🔄 **Redirections**
- `>` : Redirect output (overwrite)
- `>>` : Redirect output (append)
- `<` : Redirect input
- `<<` : Heredoc (with delimiter and signal support)

### 🔗 **Pipes**
- Supports multiple commands in a single pipeline (e.g., `ls | grep minishell | wc -l`)

### 🧠 **Built-in Commands**
- `cd`  
- `echo`  
- `pwd`  
- `export`  
- `unset`  
- `env`  
- `exit`

### 🧩 **Environment Variables**
- Dynamically update and display environment variables
- Handles `VAR=value` and `VAR+=append` syntax
- Implements the special variable `$_` (last argument of previous command)

### ⚠️ **Signal Handling**
- `Ctrl-C` → interrupt current input
- `Ctrl-D` → exit shell cleanly
- `Ctrl-\` → ignored in interactive mode

### 📦 **Exit Status Handling**
- Follows POSIX rules for exit status propagation
- Accurately returns exit codes from built-ins and external commands

---

## 📚 Bonus Features

- Built-ins executed inside pipes
- Proper parent-child separation for built-ins and redirections
- Support for deleting the current working directory during execution (`cd`, `pwd` edge case)
- Clear memory management with valgrind — no leaks or invalid reads

---

## 🛠️ How to Use

```bash
make           # Compile the shell
./minishell    # Launch it
```
## Now you can run:

```bash
export NAME=Mouad
echo Hello $NAME
cd src && pwd
ls -l | grep .c > list.txt
and some other shell commands...
```
 ## 📖 What I Learned
# Low-level programming using system calls like fork(), execve(), pipe(), dup2(), waitpid()

# Parsing and managing tokens from the command line manually

# Understanding shell grammar (quotes, redirections, expansions)

# Managing file descriptors and memory in a Unix process

# Signal management in both parent and child processes

# Structuring a complex program with modularity and responsibility separation
## 🧼 Memory Management
Tested with:
```bash
valgrind --leak-check=full --track-fds=yes ./minishell
```
## 📂 Project Structure
```bash
minishell/
├── src/
│   ├── execution/     # Execution logic, built-ins, redirections
│   ├── parsing/       # Input parsing, tokenization
│   ├── utils/         # Helper functions, memory management
│   └── main.c         # Entry point
├── includes/          # Header files
├── libft/             # Custom C standard library implementation
├── Makefile
└── README.md
```
## 🧠 Credits
Built by Mouad Najjar
42 School – BG (1337)
