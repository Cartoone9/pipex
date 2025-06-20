/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:44:51 by *******           #+#    #+#             */
/*   Updated: 2025/01/24 23:07:31 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

int	ft_children(t_list *cmd_list, int *fd, char **envp)
{
	int		prev_pipe[2];
	t_list	*cursor;
	int		ret;

	ret = 0;
	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	cursor = cmd_list;
	while (cursor)
	{
		ret = ft_pipe_n_fork(cursor, prev_pipe, fd, envp);
		if (ret)
			return (ret);
		cursor = cursor->next;
	}
	return (0);
}

int	ft_pipe_n_fork(t_list *cmd_list, int prev_pipe[2], int *fd, char **envp)
{
	int	curr_pipe[2];
	int	ret;

	ret = 0;
	if (cmd_list->next != NULL)
	{
		if (pipe(curr_pipe) == -1)
		{
			return (1);
		}
	}
	cmd_list->pid = fork();
	if (cmd_list->pid < 0)
	{
		return (1);
	}
	else if (cmd_list->pid == 0)
	{
		ft_child_process(curr_pipe, prev_pipe, cmd_list, fd);
		ret = ft_execute(cmd_list, envp);
	}
	ft_parent_process(curr_pipe, prev_pipe, cmd_list->next != NULL);
	return (ret);
}

int	ft_execute(t_list *cmd_list, char **envp)
{
	if (cmd_list->path && cmd_list->args)
	{
		if (access(cmd_list->path, F_OK) != 0)
		{
			ft_print_error(cmd_list->args[0], 1);
			return (127);
		}
		if (access(cmd_list->path, X_OK) != 0)
		{
			ft_print_error(cmd_list->args[0], 0);
			return (126);
		}
		execve(cmd_list->path, cmd_list->args, envp);
	}
	perror("pipex : error");
	return (1);
}

void	ft_child_process(int curr_pipe[2], int prev_pipe[2], t_list *cmd_list,
		int *fd)
{
	if (prev_pipe[0] != -1)
	{
		if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
			perror("dup2 error with prev pipe");
		ft_close_pipe(prev_pipe);
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			perror("dup2 error with infile");
	}
	ft_close_fd_infile(fd);
	if (cmd_list->next)
	{
		if (dup2(curr_pipe[1], STDOUT_FILENO) == -1)
			perror("dup2 error with curr pipe");
		ft_close_pipe(curr_pipe);
	}
	else
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("dup2 error with outfile");
	}
	ft_close_fd_outfile(fd);
}

void	ft_parent_process(int curr_pipe[2], int prev_pipe[2], int has_next)
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (has_next)
	{
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
	}
}
