/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:06:17 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 21:13:07 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		scop_obj_ignore_line(char *line)
{
	return (ft_strstart(line, "# ") || ft_strstart(line, "o ")
		|| ft_strstart(line, "s ") || ft_strstart(line, "mtllib ")
		|| ft_strstart(line, "usemtl ") || ft_strstart(line, "p ")
		|| ft_strstart(line, "l ") || ft_strstart(line, "surf ")
		|| ft_strstart(line, "g "));
}

static int		scop_obj_count_check(t_scop *scop, t_array *arr)
{
	size_t	i;
	char	*line;
	t_array	*check;

	i = -1;
	while (++i < arr->len)
	{
		line = arr->data[i];
		check = array_bystr(line, ' ', 1);
		if (ft_strstart(line, "v ") && check->len == 4)
			scop->obj.vcount += 1;
		else if (ft_strstart(line, "vt ") && check->len == 3)
			scop->obj.vtcount += 1;
		else if (ft_strstart(line, "vn ") && check->len == 4)
			scop->obj.vncount += 1;
		else if (ft_strstart(line, "f ")
			&& (check->len == 4 || check->len == 5))
			scop->obj.tcount += check->len - 3;
		else if (!scop_obj_ignore_line(line))
			return (ft_putlog("Error file format is incorrect.\nLine: ", line));
		array_free(&check);
	}
	return (1);
}

void			scop_init_obj(t_scop *scop)
{
	scop->obj.vcount = 0;
	scop->obj.vtcount = 0;
	scop->obj.vncount = 0;
	scop->obj.tcount = 0;
	scop->obj.v = NULL;
	scop->obj.vt = NULL;
	scop->obj.vn = NULL;
	scop->obj.vn = NULL;
	scop->obj.vpos = NULL;
	scop->obj.color = NULL;
	scop->obj.cx = 0.f;
	scop->obj.cy = 0.f;
	scop->obj.cz = 0.f;
	scop->obj.pos.x = 0.f;
	scop->obj.pos.y = 0.f;
	scop->obj.pos.z = 6.f;
	scop->obj.rot.x = 0.f;
	scop->obj.rot.y = 0.f;
	scop->obj.rot.z = 0.f;
	scop->obj.mesh.vao = 0;
	scop->obj.mesh.vertexbuffer = 0;
	scop->obj.mesh.colorbuffer = 0;
}

int				scop_load_obj(t_scop *scop, char *path)
{
	char	*file_content;
	t_array	*array_file;

	file_content = scop_file_content(path);
	array_file = array_bystr(file_content, '\n', 1);
	if (file_content)
		free(file_content);
	if (!scop_obj_count_check(scop, array_file))
		return (0);
	scop->obj.v = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.vcount * 3);
	scop->obj.vpos = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.tcount * 9);
	scop->obj.color = (GLfloat *)malloc(sizeof(GLfloat) * scop->obj.tcount * 9);
	if (!scop_obj_parser(scop, array_file))
		return (0);
	scop_obj_log(scop);
	if (array_file)
		array_free(&array_file);
	return (1);
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
