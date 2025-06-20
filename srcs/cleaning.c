/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:57:26 by *******           #+#    #+#             */
/*   Updated: 2025/01/24 19:16:38 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

void	ft_cleaning(t_list *cmd_list, int *fd)
{
	char	*filename;

	filename = ".temporary_file_pipex";
	if (access(filename, F_OK) == 0)
		unlink(filename);
	if (fd)
	{
		if (fd[0] != -1)
			close(fd[0]);
		if (fd[1] != -1)
			close(fd[1]);
		free(fd);
		fd = NULL;
	}
	if (cmd_list)
		ft_free_list(cmd_list);
}

void	ft_close_fd_infile(int *fd)
{
	close(fd[0]);
	fd[0] = -1;
}

void	ft_close_fd_outfile(int *fd)
{
	close(fd[1]);
	fd[1] = -1;
}

void	ft_print_error(char *source, int cmd_notfound)
{
	char	*error_msg;

	if (cmd_notfound)
		error_msg = ft_strjoin_error("pipex: ", source, "command not found");
	else
		error_msg = ft_strjoin_error("pipex: ", source, strerror(errno));
	write(2, error_msg, ft_strlen(error_msg));
	free(error_msg);
}
