/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:04 by *******           #+#    #+#             */
/*   Updated: 2025/01/24 21:44:14 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

char	*ft_strjoin_spe(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i++] = '/';
	j = 0;
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin_args(char **args)
{
	char	*ret;
	size_t	malloc_size;
	size_t	i;
	size_t	j;
	size_t	k;

	i = -1;
	malloc_size = 0;
	while (args[++i])
		malloc_size += ft_strlen(args[i]) + 1;
	ret = malloc(sizeof(char) * (malloc_size));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (args[++j])
	{
		k = 0;
		while (args[j][k])
			ret[i++] = args[j][k++];
		if (args[j + 1])
			ret[i++] = ' ';
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin_error(char const *s1, char const *s2, char const *s3)
{
	char	*ret;
	size_t	i;
	size_t	j;

	ret = malloc(sizeof(char) * (ft_strlen(s1)+ft_strlen(s2)+ft_strlen(s3)+4));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		ret[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i++] = ':';
	ret[i++] = ' ';
	j = 0;
	while (s3[j])
		ret[i++] = s3[j++];
	ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}
