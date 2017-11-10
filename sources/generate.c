/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 09:56:49 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 09:59:59 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	texture_generate_sphere(t_scop *scop, int i)
{
	t_vec3	normal;
	float	len;

	normal.x = scop->obj.buff[i * 3] - scop->obj.cx;
	normal.y = scop->obj.buff[i * 3 + 1] - scop->obj.cy;
	normal.z = scop->obj.buff[i * 3 + 2] - scop->obj.cz;
	len = sqrtf(normal.x * normal.x + normal.y * normal.y
		+ normal.z * normal.z);
	normal.x /= len;
	normal.y /= len;
	normal.z /= len;
	scop->obj.buff[i * 2] = 0.5f + (atan2(normal.z, normal.x))
		/ (2.0f * SCOP_PI);
	scop->obj.buff[i * 2 + 1] = 0.5f + (asin(normal.y)) / SCOP_PI;
}

void		texture_generate_buffer(t_scop *scop)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < scop->obj.tcount * 3)
	{
		if (scop->calc_normal_type)
		{
			scop->obj.buff[i * 2] = (scop->obj.buff[i * 3 + 2]
				- scop->obj.min.z) / (scop->obj.max.z - scop->obj.min.z);
			scop->obj.buff[i * 2 + 1] = (scop->obj.buff[i * 3 + 1]
				- scop->obj.min.y) / (scop->obj.max.y - scop->obj.min.y);
		}
		else
			texture_generate_sphere(scop, i);
	}
}
