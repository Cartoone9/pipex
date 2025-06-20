/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:01:42 by *******           #+#    #+#             */
/*   Updated: 2025/01/24 20:14:58 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

void	ft_free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	ft_free_strr(char **strr)
{
	size_t	i;

	i = 0;
	if (!strr)
		return ;
	while (strr[i])
	{
		free(strr[i]);
		strr[i] = NULL;
		i++;
	}
	if (strr)
	{
		free(strr);
		strr = NULL;
	}
}

void	ft_free_list(t_list *list)
{
	t_list	*temp;

	if (!list)
		return ;
	while (list->next)
	{
		temp = list->next;
		ft_free_strr(list->args);
		ft_free_strr(list->env);
		ft_free_str(list->path);
		free(list);
		list = temp;
	}
	ft_free_strr(list->args);
	ft_free_strr(list->env);
	ft_free_str(list->path);
	free(list);
	list = NULL;
}
