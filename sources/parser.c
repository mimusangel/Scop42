/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:56:36 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/08 08:12:49 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	scop_obj_line(t_scop *scop, char *line)
{
	static size_t	iv = 0;
	GLfloat			val[3];

	if (!line || !*line)
		return ;
	if (ft_strstart(line, "v "))
	{
		iv += 1;
	}
}

void		scop_obj_parser(t_scop *scop, char *file_content)
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
		scop_obj_line(scop, line);
		if (line)
			free(line);
	}
}
