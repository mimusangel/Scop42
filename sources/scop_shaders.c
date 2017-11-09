/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:45:27 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 17:17:39 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		scop_shaders_load(t_scop *scop)
{
	scop->program_shader = 0;
	scop->shader_frag = scop_file_content("sample.frag");
	scop->shader_vert = scop_file_content("sample.vert");
	scop->projection = mat4_perspective(70.0f, 1280.f / 720.f, 0.1f, 1000.0f);
	scop->view = mat4_identity();
	scop->model = mat4_identity();
}

void		scop_shaders_update(t_scop *scop)
{
	static float	rotate = 0;
	GLfloat			*tmp[4];

	free(scop->model);
	tmp[0] = mat4_translate(scop->obj.pos.x, scop->obj.pos.y, scop->obj.pos.z);
	tmp[1] = mat4_rotate(0, rotate, 0);
	tmp[2] = mat4_translate(-scop->obj.cx, -scop->obj.cy, -scop->obj.cz);
	tmp[3] = mat4_multiplie(tmp[1], tmp[2]);
	scop->model = mat4_multiplie(tmp[0], tmp[3]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp[3]);
	glUseProgram(scop->program_shader);
	uniform_mat4(scop->program_shader, "projection", scop->projection);
	uniform_mat4(scop->program_shader, "model", scop->model);
	uniform_mat4(scop->program_shader, "view", scop->view);
	rotate += 0.5f;
}

void		scop_shaders_build(t_scop *scop)
{
	scop->program_shader = load_shaders(scop->shader_vert, scop->shader_frag);
	uniform_mat4(scop->program_shader, "projection", scop->projection);
	uniform_mat4(scop->program_shader, "model", scop->model);
	uniform_mat4(scop->program_shader, "view", scop->view);
}

void		scop_shaders_unload(t_scop *scop)
{
	if (scop->program_shader > 0)
		glDeleteProgram(scop->program_shader);
	if (scop->shader_frag)
		free(scop->shader_frag);
	if (scop->shader_vert)
		free(scop->shader_vert);
	if (scop->projection)
		free(scop->projection);
	if (scop->view)
		free(scop->view);
	if (scop->model)
		free(scop->model);
}
