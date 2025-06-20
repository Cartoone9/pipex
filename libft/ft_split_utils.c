/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:04:32 by *******           #+#    #+#             */
/*   Updated: 2025/01/24 03:58:23 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

size_t	ft_nextch(const char *str, char c)
{
	size_t	backslash;
	size_t	sum;

	sum = 0;
	backslash = 0;
	while (str[sum] && (str[sum] != c || (sum > 0 && str[sum - 1] == '\\')))
	{
		if (str[sum] == '\\' && str[sum + 1]
			&& (str[sum + 1] == '"' || str[sum + 1] == '\''))
		{
			backslash++;
		}
		sum++;
	}
	return (sum - backslash);
}

size_t	ft_nextch_noquote(const char *str, char c, char d, char e)
{
	size_t	backslash;
	size_t	sum;

	sum = 0;
	backslash = 0;
	while (str[sum] && str[sum] != c)
	{
		if (str[sum] == d && ((sum > 0 && str[sum - 1] != '\\')
				&& ft_strchr(&str[sum + 1], d)))
		{
			break ;
		}
		if (str[sum] == e && ((sum > 0 && str[sum - 1] != '\\')
				&& ft_strchr(&str[sum + 1], e)))
		{
			break ;
		}
		if (str[sum] == '\\' && str[sum + 1]
			&& (str[sum + 1] == '"' || str[sum + 1] == '\''))
		{
			backslash++;
		}
		sum++;
	}
	return (sum - backslash);
}

size_t	ft_strcnt(const char *str, char c)
{
	size_t	i;
	size_t	sum;

	i = 0;
	sum = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != c)
			sum++;
		if (str[i] == c && str[i + 1] && str[i + 1] != c)
			sum++;
		i++;
	}
	return (sum);
}
