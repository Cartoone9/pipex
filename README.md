<div align="center">
  <img src="https://i.ibb.co/cmF80PB/image.png" alt="Project score">
</div>

# pipex
  
This is my Pipex project, where the goal was to build a C program that simulates shell piping (`|`) and redirections (`<` with `>`, and as a bonus `<<` with `>>`). It was a deep dive into UNIX system calls for process management, including `fork()`, `pipe()`, `dup2()`, and `execve()`, providing critical insights into how the shell executes commands. 

## Table of Contents

- [About](#pipex)
- [Important functions](#important-functions)
- [Usage](#usage)
- [Examples](#examples)
- [Note on Project State](#note-on-project-state)
- [Known Issues & Fix Suggestions](#known-issues--fix-suggestions)
- [License](#license)

## Important functions

- `fork()`: creates a new child process, useful to execute multiple processes at the same time, in parallel.

- `pipe()`: creates a pipe for interprocess communication, in this project it allows one child process to communicate with the next.

- `dup2()`: redirects file descriptors, useful to change stdin and stdout for redirections.

- `execve()`: executes a new command with arguments inside a sub-shell.

## Usage

To compile the program, navigate to the project root and run:
```bash
make
# or
make bonus
```

Then you can use the program like this:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Or like this for the heredoc bonus:

```bash
./pipex here_doc eof "cmd1" "cmd2" outfile
```

You can use two or more commands in a row.
 
## Examples

Without bonus (infile and truncate):  
![Pipex example](https://i.ibb.co/chfzsdD4/image.png)  
Zsh:  
![Pipex compare](https://i.ibb.co/4nGbxBDL/image.png)  

With bonus (heredoc and append):  
![Pipex bonus example](https://i.ibb.co/TD5Y3krT/image.png)  
Zsh:  
![Pipex bonus compare](https://i.ibb.co/q30DpC72/image.png)  

## Note on Project State

All projects from my 42 cursus are preserved in their state immediately following their final evaluation. While they may contain mistakes or stylistic errors, I've chosen not to alter them. This approach provides a clear and authentic timeline of my progress and learning journey as a programmer.

## Known Issues & Fix Suggestions

The program currently accepts a command like:

```bash
./pipex here_doc "cmd1" "cmd2" outfile
```

It shouldn't work because the command is missing the `EOF`.  
You could easily fix this by modifying the function `ft_file_parsing()` like this:

```C
int	*ft_file_parsing(int ac, char **av, int *cmd_n, int *output_error)
{
	char	*buffer;
	int		*fd;

	fd = NULL;
	buffer = NULL;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
        	// EDIT BEGIN
		if (ac < 6)
		{
			write(2, "pipex: missing args\n", 20);
			return (NULL);
		}
        	// EDIT END

		if (ft_init_buffer(&buffer) == -1)
			return (NULL);
		fd = ft_check_files_sp(av[2], av[ac - 1], output_error, &buffer);
		*cmd_n = 2;
	}
	else

...
```

`ft_fill_stash()` in my get_next_line implementation contains an unprotected `malloc()` that could cause issues in edge cases.

## License

[MIT](https://choosealicense.com/licenses/mit/)  
