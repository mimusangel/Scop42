/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 06:56:36 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/11 16:25:18 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	scop_obj_tri2(t_scop *scop, int it, int *vali, int offset)
{
	int				i;
	int				index;

	i = -1;
	while (++i < 9)
	{
		index = (i / 3 + offset) % 4;
		if ((vali[index] * 3 + i % 3) >= scop->obj.vcount * 3)
			return (ft_putlog("Vertex index not found!", ""));
		if ((it * 9 + i) >= (scop->obj.tcount * 9))
			return (ft_putlog("Buffer index not found!", ""));
		scop->obj.buff[it * 9 + i] = scop->obj.v[vali[index] * 3 + i % 3];
	}
	return (1);
}

static int	scop_obj_tri(t_scop *scop, char *line)
{
	static size_t	it = 0;
	int				vali[4];
	t_array			*arr;

	arr = array_bystr(line, ' ', 1);
	if (arr && (arr->len == 4 || arr->len == 5))
	{
		vali[0] = ft_atoi(arr->data[1]) - 1;
		vali[1] = ft_atoi(arr->data[2]) - 1;
		vali[2] = ft_atoi(arr->data[3]) - 1;
		if (!scop_obj_tri2(scop, it, vali, 0))
			return (ft_putlog("Line: ", line));
		it++;
		if (arr->len == 5)
		{
			vali[3] = ft_atoi(arr->data[4]) - 1;
			if (!scop_obj_tri2(scop, it, vali, 2))
				return (ft_putlog("Vertex index not found! Line: ", line));
			it++;
		}
		array_free(&arr);
	}
	return (1);
}

static void	scop_obj_pos(t_scop *scop, size_t i, t_vec3 pos)
{
	scop->obj.v[i] = (GLfloat)pos.x;
	scop->obj.v[i + 1] = (GLfloat)pos.y;
	scop->obj.v[i + 2] = (GLfloat)pos.z;
	if (i == 0)
	{
		scop->obj.min = (t_vec3){pos.x, pos.y, pos.z};
		scop->obj.max = (t_vec3){pos.x, pos.y, pos.z};
	}
	else
	{
		scop->obj.min.x = MIN(scop->obj.min.x, pos.x);
		scop->obj.min.y = MIN(scop->obj.min.y, pos.y);
		scop->obj.min.z = MIN(scop->obj.min.z, pos.z);
		scop->obj.max.x = MAX(scop->obj.max.x, pos.x);
		scop->obj.max.y = MAX(scop->obj.max.y, pos.y);
		scop->obj.max.z = MAX(scop->obj.max.z, pos.z);
	}
}

static int	scop_obj_line(t_scop *scop, char *line)
{
	static size_t	iv = 0;
	t_array			*arr;

	arr = NULL;
	if (ft_strstart(line, "v "))
	{
		arr = array_bystr(line, ' ', 1);
		if (arr)
		{
			if (arr->len <= 4)
				scop_obj_pos(scop, iv * 3, (t_vec3){ft_atof(arr->data[1]),
					ft_atof(arr->data[2]), ft_atof(arr->data[3])});
			iv++;
			array_free(&arr);
		}
	}
	if (ft_strstart(line, "f "))
	{
		if (!scop_obj_tri(scop, line))
			return (0);
	}
	return (1);
}

int			scop_obj_parser(t_scop *scop, t_array *arr)
{
	size_t	i;
	char	*line;

	i = -1;
	while (++i < arr->len)
	{
		line = arr->data[i];
		if (!scop_obj_line(scop, line))
			return (0);
		free(arr->data[i]);
		arr->data[i] = NULL;
	}
	free(arr->data);
	scop->obj.center.x = (scop->obj.max.x + scop->obj.min.x) / 2.0f;
	scop->obj.center.y = (scop->obj.max.y + scop->obj.min.y) / 2.0f;
	scop->obj.center.z = (scop->obj.max.z + scop->obj.min.z) / 2.0f;
	return (1);
}
