/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 03:39:32 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/07 05:02:45 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
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

char		*scop_file_content(const char *path)
{
	char	buf[2049];
	int		fd;
	char	*str;
	char	*tmp;
	int		i;

	if ((fd = open(path, O_RDONLY))> 2)
	{
		str = NULL;
		while ((i = read(fd, buf, 2048)) > 0)
		{
			buf[i] = '\0';
			tmp = str;
			str = ft_strjoin(str, buf);
			if (tmp)
				free(tmp);
		}
		close(fd);
		return (str);
	}
	return (NULL);
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
