/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:49:03 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 05:20:41 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int				mesh_begin(t_scop *scop)
{
	size_t	i;

	glGenVertexArrays(1, &(scop->obj.mesh.vao));
	if (!scop->obj.mesh.vao)
		return (ft_putlog("Error generate VAO ID!", ""));
	glBindVertexArray(scop->obj.mesh.vao);
	glGenBuffers(SCOP_MAX_VBO, scop->obj.mesh.vbo);
	i = -1;
	while (++i < SCOP_MAX_VBO)
		if (!scop->obj.mesh.vbo[i])
			return (ft_putlog("Error generate VBO ID!", ""));
	return (1);
}

void			mesh_add(t_mesh *mesh, int type, size_t size, GLfloat *data)
{
	int		s;

	mesh->size = size;
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[type]);
	s = (type == VBO_TEXTURE) ? 2 : 3;
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * s * size, data,
		GL_STATIC_DRAW);
	glVertexAttribPointer(type, s, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(type);
}

void			mesh_end(t_scop *scop)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void			mesh_render(t_scop *scop)
{
	scop_shaders_update(scop);
	glBindVertexArray(scop->obj.mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, scop->obj.tcount * 3);
	glBindVertexArray(0);
}

void			mesh_delete(t_scop *scop)
{
	glDeleteBuffers(2, scop->obj.mesh.vbo);
	glDeleteVertexArrays(1, &(scop->obj.mesh.vao));
}
