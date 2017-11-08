/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:06:17 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/08 08:18:32 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static size_t	scop_obj_count_arg(char *line)
{
	size_t i;

	i = 0;
	while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
		line++;
	while (*line)
	{
		while (*line && *line != ' ' && *line != '\t' && *line != '\n')
			line++;
		i++;
		while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
			line++;
	}
	return (i);
}

static void		scop_obj_cline(t_scop *scop, char *line)
{
	size_t	i;

	if (!line || !*line)
		return ;
	if (ft_strstart(line, "v "))
		scop->obj.vcount += 1;
	if (ft_strstart(line, "vt "))
		scop->obj.vtcount += 1;
	if (ft_strstart(line, "vn "))
		scop->obj.vncount += 1;
	if (ft_strstart(line, "f "))
	{
		if ((i = scop_obj_count_arg(line + 2)) > 0)
			scop->obj.tcount += i - 2;
	}
}

static void		scop_obj_count(t_scop *scop, char *file_content)
{
	char	*line;
	size_t	i;
	size_t	size;
	size_t	len;

	size = 0;
	len = ft_strlen(file_content);
	while (size < len)
	{
		while (file_content[size] == '\n')
			size += 1;
		if ((i = ft_strchr(file_content + size, '\n')) > 0)
		{
			line = ft_strsub(file_content + size, 0, i);
			size += i + 1;
		}
		scop_obj_cline(scop, line);
		if (line)
			free(line);
		line = NULL;
	}
}

int				scop_load_obj(t_scop *scop, char *path)
{
	char	*file_content;

	scop->obj.vcount = 0;
	scop->obj.vtcount = 0;
	scop->obj.vncount = 0;
	scop->obj.tcount = 0;
	scop->obj.v = NULL;
	scop->obj.vt = NULL;
	scop->obj.vn = NULL;
	file_content = scop_file_content(path);
	scop_obj_count(scop, file_content);
	// scop->obj.v = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.vcount * 3);
	// scop->obj.vpos = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.tcount * 9);
	// scop->obj.color = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.tcount * 9);
	// scop_obj_parser(scop, file_content);
	scop_obj_log(scop);
	if (file_content)
		free(file_content);
	return (0);
}

void			scop_unload_obj(t_scop *scop)
{
	scop->obj.vcount = 0;
	scop->obj.vtcount = 0;
	scop->obj.vncount = 0;
	scop->obj.tcount = 0;
	if (scop->obj.v)
		free(scop->obj.v);
	if (scop->obj.vt)
		free(scop->obj.vt);
	if (scop->obj.vn)
		free(scop->obj.vn);
	if (scop->obj.vpos)
		free(scop->obj.vpos);
	if (scop->obj.color)
		free(scop->obj.color);
}
