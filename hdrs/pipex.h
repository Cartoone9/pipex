/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:10:08 by *******           #+#    #+#             */
/*   Updated: 2025/01/25 01:27:54 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_list
{
	char			**args;
	char			**env;
	char			*path;
	pid_t			pid;
	struct s_list	*next;
}					t_list;

typedef struct s_sizet
{
	size_t			i;
	size_t			j;
	size_t			k;
}					t_sizet;

int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_is_path(char *cmd);
int					ft_tester_cmd(t_list *cmd_list);
int					ft_new_cmd(t_list **cmd_list, char *cmd, char **envp);
int					ft_absolute_cmd(t_list *list);
int					ft_wait(t_list *cmd_list);
int					ft_temp_file(char *buffer, int *fd);
int					ft_init_buffer(char **buffer);
int					ft_main_suite(t_list *cmd_list, int *fd, char **envp,
						int output_error);
int					ft_space_spcase(t_list *cursor);
int					ft_check_cmd(t_list **cmd_list);
int					ft_execute(t_list *cmd_list, char **envp);
int					ft_pipe_n_fork(t_list *cmd_list, int prev_pipe[2],
						int *fd, char **envp);
int					ft_children(t_list *cmd_list, int *fd, char **envp);
/*int					ft_check_pid(t_list *cmd_list);*/
int					*ft_check_files(char *infile, char *outfile,
						int *output_error);
int					*ft_check_files_sp(char *delimiter, char *outfile,
						int *output_error, char **buffer);
int					*ft_check_files_sp_suite(char *delimiter, char **buffer,
						int *fd);
int					*ft_file_parsing(int ac, char **av, int *cmd_n,
						int *output_error);
char				**ft_extract_path(char **envp);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *str, int c);
char				*ft_strjoin_spe(char const *s1, char const *s2);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strrchr(const char *str, int c);
char				*ft_trunc_arg(char *str, char *stop);
char				*get_next_line(int fd);
char				*ft_strdup(const char *src);
char				*ft_strjoin_args(char **args);
char				*ft_strjoin_error(char const *s1, char const *s2,
						char const *s3);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_free_list(t_list *list);
void				ft_free_strr(char **strr);
void				ft_free_str(char *str);
void				ft_cleaning(t_list *cmd_list, int *fd);
void				ft_no_path_cmd(t_list *cursor);
void				ft_child_process(int curr_pipe[2], int prev_pipe[2],
						t_list *cmd_list, int *fd);
void				ft_parent_process(int curr_pipe[2], int prev_pipe[2],
						int has_next);
void				ft_unlink(char *buffer);
void				ft_close_pipe(int pipe[2]);
void				ft_close_fd_outfile(int *fd);
void				ft_close_fd_infile(int *fd);
void				ft_init_main(int *ret, int *output_error,
						t_list **cmd_list);
void				ft_print_error(char *source, int cmd_notfound);
void				ft_empty_args(t_list *cursor);
size_t				ft_strlen(const char *str);
size_t				ft_nextch(const char *str, char c);
size_t				ft_nextch_noquote(const char *str, char c, char d, char e);
size_t				ft_strcnt(const char *str, char c);

#endif
