/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:44:51 by *******           #+#    #+#             */
/*   Updated: 2025/01/24 21:46:42 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

void	ft_close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

int	ft_wait(t_list *cmd_list)
{
	t_list	*cursor;
	int		status;
	int		ret;

	ret = 0;
	cursor = cmd_list;
	while (cursor)
	{
		if (waitpid(cursor->pid, &status, 0) == -1)
		{
			perror("error during waitpid");
			return (1);
		}
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ret = WTERMSIG(status);
		cursor = cursor->next;
	}
	return (ret);
}

int	ft_space_spcase(t_list *cursor)
{
	char	*temp_marker;
	char	*temp;

	if (!cursor || !cursor->args[0] || !cursor->args[1])
		return (0);
	temp = ft_strjoin_args(cursor->args);
	if (!temp)
		return (0);
	if (access(temp, F_OK) == 0)
	{
		cursor->path = temp;
		ft_free_strr(cursor->args);
		cursor->args = malloc(sizeof(char *) * 2);
		if (!cursor->args)
			return (free(temp), 0);
		temp_marker = ft_strrchr(cursor->path, '/');
		cursor->args[0] = ft_trunc_arg(cursor->path, temp_marker);
		if (!cursor->args[0])
			return (free(temp), 0);
		cursor->args[1] = NULL;
		ft_free_strr(cursor->env);
		cursor->env = NULL;
		return (1);
	}
	return (free(temp), 0);
}

/*int	ft_check_pid(t_list *cmd_list)*/
/*{*/
/*	t_list	*cursor;*/
/**/
/*	cursor = cmd_list;*/
/*	while (cursor)*/
/*	{*/
/*		if (!cursor->pid)*/
/*			return (0);*/
/*		cursor = cursor->next;*/
/*	}*/
/*	return (1);*/
/*}*/
