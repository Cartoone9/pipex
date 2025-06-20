/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:23:56 by *******           #+#    #+#             */
/*   Updated: 2025/01/24 20:26:20 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

int	*ft_check_files(char *infile, char *outfile, int *output_error)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	if (!fd)
		return (perror("malloc error in ft_check_files"), NULL);
	fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		*output_error = 1;
		ft_print_error("output", 0);
		fd[1] = open("/dev/null", O_WRONLY);
		if (fd[1] == -1)
			return (free(fd), NULL);
	}
	fd[0] = open(infile, O_RDONLY);
	if (fd[0] == -1)
	{
		ft_print_error("input", 0);
		fd[0] = open("/dev/null", O_RDONLY);
		if (fd[0] == -1)
			return (close(fd[1]), free(fd), NULL);
	}
	return (fd);
}

int	ft_new_cmd(t_list **cmd_list, char *cmd, char **envp)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (perror("malloc error in ft_new_cmd"), -1);
	new->pid = 0;
	new->path = NULL;
	new->next = NULL;
	new->args = ft_split(cmd, ' ');
	if (!new->args[0] || new->args[0][0] == '\0' || ft_strchr(new->args[0],
			'/'))
		new->env = NULL;
	else
		new->env = ft_extract_path(envp);
	ft_lstadd_back(cmd_list, new);
	return (0);
}

char	**ft_extract_path(char **envp)
{
	char	*hardcoded;
	char	**ret;
	int		i;

	i = 0;
	hardcoded = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	if (!envp[0])
	{
		ret = ft_split(hardcoded, ':');
	}
	else
	{
		while (ft_strncmp("PATH=", envp[i], 5))
			i++;
		ret = ft_split(envp[i] + 5, ':');
	}
	return (ret);
}
