/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:49:03 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 19:55:33 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int				mesh_generate(t_scop *scop)
{
	glGenVertexArrays(1, &(scop->obj.mesh.vao));
	if (!scop->obj.mesh.vao)
		return (ft_putlog("Error generate VAO ID!", ""));
	glBindVertexArray(scop->obj.mesh.vao);
	glGenBuffers(1, &(scop->obj.mesh.vertexbuffer));
	if (!scop->obj.mesh.vertexbuffer)
		return (ft_putlog("Error generate Position Buffer ID!", ""));
	glBindBuffer(GL_ARRAY_BUFFER, scop->obj.mesh.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * scop->obj.tcount,
		scop->obj.vpos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &(scop->obj.mesh.colorbuffer));
	if (!scop->obj.mesh.colorbuffer)
		return (ft_putlog("Error generate Color Buffer ID!", ""));
	glBindBuffer(GL_ARRAY_BUFFER, scop->obj.mesh.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * scop->obj.tcount,
		scop->obj.color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return (1);
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
	glDeleteBuffers(1, &(scop->obj.mesh.vertexbuffer));
	glDeleteBuffers(1, &(scop->obj.mesh.colorbuffer));
	glDeleteVertexArrays(1, &(scop->obj.mesh.vao));
}
