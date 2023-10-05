# Minishell - My own little shell

## Project Description

The Minishell project aims to create a simple shell program. The shell should be capable of parsing and executing basic commands, handle redirections, pipes, and environment variables.

## Features

1. **Prompt**: The shell should display a prompt when waiting for a new command.
2. **History**: The shell should maintain a history of commands.
3. **Executable search**: The shell should search and launch the right executable based on the PATH variable or using a relative or absolute path.
4. **Quotes**: The shell should handle both single (`'`) and double (`"`) quotes, preventing the interpretation of meta-characters inside the quotes.
5. **Redirections**: The shell should support input (`<`), output (`>`), here-document (`<<`), and append output redirection (`>>`).
6. **Pipes**: The shell should support pipes (`|`), connecting the output of each command in the pipeline to the input of the next.
7. **Environment Variables**: The shell should handle environment variables (`$`), expanding them to their values.
8. **Exit Status**: The shell should handle `$?`, expanding it to the exit status of the most recently executed foreground pipeline.
9. **Interrupts**: The shell should handle `ctrl-C`, `ctrl-D` and `ctrl-\`, behaving as bash does.
10. **Builtins**: The shell should implement the following builtins: `echo` with `-n` option, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

## Compilation

A Makefile is provided to compile the source files. 

## Limitations

* The shell should not use more than one global variable.
* It should not interpret unclosed quotes or special characters such as `\` (backslash) or `;` (semicolon) which are not required by the subject.

## Usage

```bash
./minishell
```

Upon running, the shell will display a prompt and wait for the user to enter commands.
