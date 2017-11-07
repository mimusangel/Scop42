/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 05:56:36 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/07 05:57:01 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = NULL;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if ((str = (char *)malloc(sizeof(char) * (i + j + 1))) == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

size_t		ft_strchr(const char *str, const char c)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void		ft_strcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	if (!src || !dest)
		return ;
	i = -1;
	while (++i < size)
		dest[i] = src[i];
}
