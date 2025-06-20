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
<img width="421" height="123" alt="ex-nobonus" src="https://github.com/user-attachments/assets/4c0125c8-85c7-4b88-b7a0-96fa67ebca83" />  
Zsh:  
<img width="422" height="88" alt="ex-nobonus-zsh" src="https://github.com/user-attachments/assets/8d2d63d1-d166-4ae0-a708-075f9481b995" />  
  
With bonus (heredoc and append):  
<img width="421" height="139" alt="ex-bonus" src="https://github.com/user-attachments/assets/afe2388e-6c5f-4feb-aaee-7b57443995c9" />  
Zsh:  
<img width="421" height="139" alt="ex-bonus-zsh" src="https://github.com/user-attachments/assets/c7e86e9e-10e9-4034-92ab-a734d03a5d65" />  
  
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
