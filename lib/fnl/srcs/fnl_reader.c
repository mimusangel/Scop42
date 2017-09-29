/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnl_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 11:34:16 by mgallo            #+#    #+#             */
/*   Updated: 2017/09/29 11:34:18 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "fnl.h"

static void		fnl_read(t_fnl *file)
{
	char	buffer[READ_SIZE + 1];
	char	*tmp;
	ssize_t	size;

	while ((size = read(file->fd, buffer, READ_SIZE)) > 0)
	{
		buffer[size] = '\0';
		if (file->buf == NULL)
			file->buf = fnl_strcpy(buffer);
		else
		{
			tmp = file->buf;
			file->buf = fnl_strcat(file->buf, buffer);
			free(tmp);
		}
	}
}

int				file_next_line(t_fnl *file, char **str)
{
	ssize_t	i;

	if (!file || *str != NULL)
		return (-1);
	if (file->buf == NULL)
		fnl_read(file);
	if (file->read >= fnl_strlen(file->buf) || !file->buf[file->read])
		return (-1);
	i = fnl_getchar(file->buf, '\n', file->read);
	*str = fnl_strsub(file->buf, file->read, i);
	file->read = i;
	if (file->buf[i] == '\n')
	{
		file->read += 1;
		return (1);
	}
	return (0);
}
