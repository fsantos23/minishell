# 🐚 Minishell

A simplified shell implementation inspired by bash.

## 🎯 Features

### Built-in Commands
- `echo` with -n option
- `cd` with relative/absolute path
- `pwd` without options
- `export` without options
- `unset` without options
- `env` without options
- `exit` without options

### Shell Operations
- Command history
- Single and double quotes
- Redirections (`<`, `>`, `>>`)
- Pipes (`|`)
- Environment variables (`$`)
- Exit status (`$?`)
- Ctrl-C, Ctrl-D, Ctrl-\

## 🚀 Installation

```bash
git clone https://github.com/fsantos23/minishell.git
cd minishell
make
```

## 📋 Usage

```bash
./minishell
```

## ⚙️ Implementation Details

### Signal Handling
- Ctrl-C: Display new prompt
- Ctrl-D: Exit shell
- Ctrl-\: Do nothing

### Environment
- Working history
- Environment variable expansion
- Path handling
- Error management

### Input Processing
- Command parsing
- Quote handling
- Token separation
- Redirection setup
- Pipe management

## 🧪 Testing

```bash
# Built-ins
echo "Hello World"
cd ..
pwd
export USER=john
env | grep USER
unset USER
exit

# Redirections
echo "hello" > file.txt
cat < file.txt

# Pipes
ls | grep .c | wc -l

# Environment Variables
echo $PATH
echo $?
```

## ⚠️ Error Handling

- Command not found
- Permission denied
- Syntax errors
- Memory allocation failures
- Fork errors
- Pipe errors

## ⭐ Show your support

Give a ⭐️ if this project helped you!
