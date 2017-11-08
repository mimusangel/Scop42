/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:45:27 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/08 07:01:01 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		scop_shaders_load(t_scop *scop)
{
	GLfloat		*tmp1;
	GLfloat		*tmp2;

	scop->program_shader = 0;
	scop->shader_frag = scop_file_content("sample.frag");
	scop->shader_vert = scop_file_content("sample.vert");
	scop->projection = mat4_perspective(70.0f, 1280.f / 720.f, 0.1f, 1000.0f);
	scop->view = mat4_identity();
	tmp1 = mat4_translate(0, 0, 2);
	tmp2 = mat4_rotate(0, -45, 0);
	scop->model = mat4_multiplie(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
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
