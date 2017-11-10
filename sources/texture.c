/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 01:50:13 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 09:25:45 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			texture_generate(t_scop *scop)
{
	int	format;

	scop->texture = 0;
	if (!scop->bmp_loaded)
		return (0);
	glGenTextures(1, &(scop->texture));
	if (!scop->texture)
		return (scop->bmp_loaded = ft_putlog("Error generate Texture", ""));
	texture_bind(scop);
	format = (scop->bmp.info.bits == 24) ? GL_BGR : GL_BGRA;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scop->bmp.info.width,
		scop->bmp.info.height, 0, format, GL_UNSIGNED_BYTE,
		scop->bmp.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return (1);
}

void		texture_bind(t_scop *scop)
{
	glBindTexture(GL_TEXTURE_2D, scop->texture);
}

void		texture_unbind(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void		texture_unload(t_scop *scop)
{
	if (scop->texture)
		glDeleteTextures(1, &(scop->texture));
}

void		texture_generate_buffer(t_scop *scop)
{
	t_vec3	normal;
	float	len;
	size_t	i;
	size_t	j;
	float	color;

	i = -1;
	while (++i < scop->obj.tcount * 3)
	{
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
}
