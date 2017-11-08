/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:06:17 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/07 23:11:33 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	scop_obj_line(t_scop *scop, char *line)
{

}

static void	scop_obj_parser(t_scop *scop, char *file_content)
{
	char	*line;
	size_t	i;
	size_t	size;
	size_t	len;

	size = 0;
	len = ft_strlen(file_content);
	while (size < len)
	{
		if ((i = ft_strchr(file_content + size, '\n')) > 0)
		{
			line = ft_strsub(file_content + size, 0, i);
			size += i + 1;
		}
		else
		{
			line = ft_strsub(file_content + size, 0, len - size);
			size = len;
		}
		scop_obj_line(scop, line);
		if (line)
			free(line);
	}
}

int			scop_load_obj(t_scop *scop, char *path)
{
	char	*file_content;

	file_content = scop_file_content(path);
	scop_obj_parser(scop, file_content);
	if (file_content)
		free(file_content);
	return (0);
}
