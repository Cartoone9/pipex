/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:03 by *******           #+#    #+#             */
/*   Updated: 2025/01/24 03:59:05 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

static int	ft_split_suite(char **strr, const char *s, char c, t_sizet *szt);
static int	ft_split_no_quotes(char **strr, const char *s, char c,
				t_sizet *szt);
static int	ft_single_quotes(char **strr, const char *s, size_t *i, size_t *j);
static int	ft_double_quotes(char **strr, const char *s, size_t *i, size_t *j);

char	**ft_split(char const *s, char c)
{
	char	**strr;
	t_sizet	szt;
	int		j;

	szt.i = 0;
	szt.j = 0;
	szt.k = 0;
	strr = malloc(sizeof(char *) * (ft_strcnt(s, c) + 1));
	if (strr == NULL)
		return (NULL);
	j = ft_split_suite(strr, s, c, &szt);
	if (j == -1)
		return (NULL);
	strr[j] = NULL;
	return (strr);
}

static int	ft_split_suite(char **strr, const char *s, char c, t_sizet *szt)
{
	while (s[szt->i])
	{
		while (s[szt->i] == c)
			szt->i++;
		while (s[szt->i] && s[szt->i] != c)
		{
			if (s[szt->i] == '\'' && s[(szt->i) + 1]
				&& ft_strchr(&(s[(szt->i) + 1]), '\''))
			{
				if (ft_single_quotes(strr, s, &szt->i, &szt->j) == -1)
					return (ft_free_strr(strr), -1);
			}
			else if (s[szt->i] == '"' && s[(szt->i) + 1]
				&& ft_strchr(&(s[(szt->i) + 1]), '"'))
			{
				if (ft_double_quotes(strr, s, &szt->i, &szt->j) == -1)
					return (ft_free_strr(strr), -1);
			}
			else if (ft_split_no_quotes(strr, s, c, szt) == -1)
				return (ft_free_strr(strr), -1);
		}
	}
	return ((int)szt->j);
}

static int	ft_split_no_quotes(char **strr, const char *s, char c, t_sizet *szt)
{
	size_t	malloc_size;

	malloc_size = ft_nextch_noquote(&s[(szt->i) + 1], c, '"', '\'') + 1;
	strr[szt->j] = malloc(sizeof(char) * (malloc_size + 1));
	if (!strr[szt->j])
		return (-1);
	szt->k = 0;
	while (szt->k < malloc_size)
	{
		if (s[szt->i] == '\\' && s[(szt->i) + 1] && (s[(szt->i) + 1] == '"'
				|| s[(szt->i) + 1] == '\''))
			(szt->i)++;
		strr[szt->j][szt->k] = s[szt->i];
		(szt->i)++;
		(szt->k)++;
	}
	strr[szt->j][szt->k] = '\0';
	(szt->j)++;
	return (0);
}

static int	ft_single_quotes(char **strr, const char *s, size_t *i, size_t *j)
{
	size_t	k;

	k = 0;
	(*i)++;
	strr[*j] = malloc(sizeof(char) * (ft_nextch(&s[*i], '\'') + 1));
	if (!strr[*j])
		return (-1);
	while (s[*i] && (s[*i] != '\'' || (*i > 0 && s[(*i) - 1] == '\\')))
	{
		if (s[*i] == '\\' && s[(*i) + 1]
			&& (s[(*i) + 1] == '\'' || s[(*i) + 1] == '"'))
			(*i)++;
		strr[*j][k] = s[*i];
		k++;
		(*i)++;
	}
	strr[*j][k] = '\0';
	(*i)++;
	(*j)++;
	return (0);
}

static int	ft_double_quotes(char **strr, const char *s, size_t *i, size_t *j)
{
	size_t	k;

	k = 0;
	(*i)++;
	strr[*j] = malloc(sizeof(char) * (ft_nextch(&s[*i], '"') + 1));
	if (!strr[*j])
		return (-1);
	while (s[*i] && (s[*i] != '"' || (*i > 0 && s[(*i) - 1] == '\\')))
	{
		if (s[*i] == '\\' && s[(*i) + 1]
			&& (s[(*i) + 1] == '\'' || s[(*i) + 1] == '"'))
			(*i)++;
		strr[*j][k] = s[*i];
		k++;
		(*i)++;
	}
	strr[*j][k] = '\0';
	(*i)++;
	(*j)++;
	return (0);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	const char	*str = "      ";
	char		c;
	char		**strr;

	c = ' ';
	strr = ft_split(str, c);
	//	for (size_t i = 0; strr[i] != NULL; i++)
	//	{
	//		printf("'%s'\n", strr[i]);
	//	}
	(void)strr;
	return (0);
}
*/
