/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******* <*******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:54:04 by *******           #+#    #+#             */
/*   Updated: 2025/01/19 17:52:37 by *******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/pipex.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	c_uc;
	size_t			strlen;

	if (c == -1)
		return (NULL);
	c_uc = (unsigned char)c;
	strlen = ft_strlen(str);
	if (c_uc == '\0')
		return ((char *)&str[strlen]);
	while (strlen > 0)
	{
		strlen--;
		if (str[strlen] == c_uc)
			return ((char *)&str[strlen]);
	}
	return (NULL);
}
