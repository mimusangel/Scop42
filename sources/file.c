/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 03:39:32 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/07 06:02:14 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "scop.h"

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

size_t		get_str_line(char *str, char **line)
{
	size_t	i;

	i = ft_strchr(str, '\n');
	*line = NULL;
	if (!((*line) = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	ft_strcpy(*line, str, i);
	(*line)[i] = '\0';
	return (i);
}

int			get_file_line(int fd, char **line)
{
	static char *files[256] = {NULL};

	
	return (0);
}
