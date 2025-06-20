/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:36:33 by *******           #+#    #+#             */
/*   Updated: 2025/01/23 20:27:35 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

int	*ft_check_files_sp(char *delimiter, char *outfile, int *output_error,
		char **buffer)
{
	int		*fd;

	fd = malloc(sizeof(int) * 2);
	if (!fd)
		return (perror("malloc error in ft_check_files"), NULL);
	fd[1] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[1] == -1)
	{
		*output_error = 1;
		perror("no such file or directory");
		fd[1] = open("/dev/null", O_WRONLY);
		if (fd[1] == -1)
			return (free(fd), NULL);
	}
	fd = ft_check_files_sp_suite(delimiter, buffer, fd);
	if (!fd)
		return (NULL);
	return (fd);
}

int	*ft_check_files_sp_suite(char *delimiter, char **buffer, int *fd)
{
	char	*temp;
	char	*temp_join;

	delimiter = ft_strjoin(delimiter, "\n");
	while (1)
	{
		temp = get_next_line(0);
		if (!ft_strncmp(temp, delimiter, ft_strlen(delimiter)))
		{
			free(temp);
			break ;
		}
		temp_join = ft_strjoin(*buffer, temp);
		free(temp);
		free(*buffer);
		*buffer = temp_join;
	}
	if (ft_temp_file(*buffer, fd) == -1)
		return (close(fd[1]), free(fd), free(*buffer), free(delimiter), NULL);
	return (free(*buffer), free(delimiter), fd);
}

int	ft_temp_file(char *buffer, int *fd)
{
	char	*filename;

	filename = ".temporary_file_pipex";
	fd[0] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[0] == -1)
		return (-1);
	write(fd[0], buffer, ft_strlen(buffer));
	close(fd[0]);
	fd[0] = open(filename, O_RDONLY, 0644);
	if (fd[0] == -1)
		return (-1);
	return (0);
}

int	ft_init_buffer(char **buffer)
{
	*buffer = malloc(1);
	if (!(*buffer))
		return (-1);
	(*buffer)[0] = 0;
	return (0);
}
