/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:08:28 by *******           #+#    #+#             */
/*   Updated: 2025/01/24 23:04:40 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_list	*cmd_list;
	int		*fd;
	int		output_error;
	int		cmd_n;
	int		ret;

	ft_init_main(&ret, &output_error, &cmd_list);
	if (ac >= 5)
	{
		fd = ft_file_parsing(ac, av, &cmd_n, &output_error);
		if (!fd)
			return (1);
		while (++cmd_n < ac - 1)
		{
			if (ft_new_cmd(&cmd_list, av[cmd_n], envp) == -1)
				return (ft_cleaning(cmd_list, fd), 1);
			if (ft_check_cmd(&cmd_list) == -1)
				return (ft_cleaning(cmd_list, fd), 1);
		}
		ret = ft_main_suite(cmd_list, fd, envp, output_error);
		ft_cleaning(cmd_list, fd);
	}
	return (ret);
}

void	ft_init_main(int *ret, int *output_error, t_list **cmd_list)
{
	*ret = 0;
	*output_error = 0;
	*cmd_list = NULL;
}

int	*ft_file_parsing(int ac, char **av, int *cmd_n, int *output_error)
{
	char	*buffer;
	int		*fd;

	fd = NULL;
	buffer = NULL;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ft_init_buffer(&buffer) == -1)
			return (NULL);
		fd = ft_check_files_sp(av[2], av[ac - 1], output_error, &buffer);
		*cmd_n = 2;
	}
	else
	{
		fd = ft_check_files(av[1], av[ac - 1], output_error);
		*cmd_n = 1;
	}
	if (!fd)
		return (NULL);
	return (fd);
}

int	ft_main_suite(t_list *cmd_list, int *fd, char **envp, int output_error)
{
	int	ret;

	ret = 0;
	ret = ft_children(cmd_list, fd, envp);
	if (!ret)
		ret = ft_wait(cmd_list);
	if (output_error)
		ret = 1;
	return (ret);
}

// bash error code 127 : command not found
// bash error code 1 : general error
