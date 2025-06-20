/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:28:13 by *******           #+#    #+#             */
/*   Updated: 2025/01/24 21:46:09 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

int	ft_check_cmd(t_list **cmd_list)
{
	t_list	*cursor;

	if (!(*cmd_list))
		return (-1);
	cursor = *cmd_list;
	while (cursor->next)
		cursor = cursor->next;
	if (!cursor->env)
	{
		if (!cursor->args[0])
		{
			ft_empty_args(cursor);
			return (0);
		}
		if (ft_absolute_cmd(cursor) == -1)
			return (-1);
	}
	else
		ft_no_path_cmd(cursor);
	return (0);
}
// if (!cursor->env) checks if it's an absolute path cmd or not
// like /bin/ls or ls

void	ft_empty_args(t_list *cursor)
{
	ft_free_strr(cursor->args);
	cursor->args = malloc(sizeof(char *) * 2);
	cursor->args[0] = ft_strdup("error");
	cursor->args[1] = NULL;
	ft_free_str(cursor->path);
	cursor->path = ft_strdup("error");
	ft_free_strr(cursor->env);
	cursor->env = NULL;
}

void	ft_no_path_cmd(t_list *cursor)
{
	char	*temp;
	int		i;

	i = 0;
	while (cursor->env[i])
	{
		temp = ft_strjoin_spe(cursor->env[i], cursor->args[0]);
		if (!temp)
			return (perror("malloc error in ft_no_path_cmd"));
		if (access(temp, F_OK) == 0)
		{
			cursor->path = temp;
			ft_free_strr(cursor->env);
			cursor->env = NULL;
			return ;
		}
		free(temp);
		i++;
	}
	cursor->path = ft_strdup("error");
	ft_free_strr(cursor->env);
	cursor->env = NULL;
	return ;
}

int	ft_absolute_cmd(t_list *list)
{
	char	*temp_arg;
	char	*temp;

	if (ft_space_spcase(list))
		return (0);
	temp = ft_strrchr(list->args[0], '/');
	temp_arg = ft_trunc_arg(list->args[0], temp);
	if (!temp_arg)
		return (-1);
	list->path = list->args[0];
	list->args[0] = temp_arg;
	return (0);
}

char	*ft_trunc_arg(char *args, char *stop)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	start;

	i = 0;
	while (&args[i] != stop)
		i++;
	start = ++i;
	while (args[i])
		i++;
	ret = malloc(sizeof(i - start) + 1);
	if (!ret)
		return (perror("malloc error in ft_trunc_arg"), NULL);
	j = 0;
	k = start;
	while (j < i - start)
	{
		ret[j] = args[k];
		j++;
		k++;
	}
	ret[j] = '\0';
	return (ret);
}

/*char	*ft_trunc_path(t_list *list, char *stop)*/
/*{*/
/*	char	*ret;*/
/*	size_t	i;*/
/*	size_t	j;*/
/**/
/*	i = 0;*/
/*	while (&list->args[0][i] != stop)*/
/*		i++;*/
/*	ret = malloc(sizeof(i) + 1);*/
/*	if (!ret)*/
/*		return (perror("Malloc error in ft_trunc_path"), NULL);*/
/*	j = 0;*/
/*	while (j < i)*/
/*	{*/
/*		ret[j] = list->args[0][j];*/
/*		j++;*/
/*	}*/
/*	ret[j] = '\0';*/
/*	return (ret);*/
/*}*/
