/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:45:27 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 09:21:28 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		scop_shaders_init(t_scop *scop)
{
	scop->program_shader = 0;
	scop->shader_frag = NULL;
	scop->shader_vert = NULL;
	scop->projection = NULL;
	scop->view = NULL;
	scop->model = NULL;
	scop->rotate_speed = 0.5f;
	scop->auto_rotate = 1;
	scop->texture_mode = 0.f;
}

int			scop_shaders_load(t_scop *scop)
{
	scop->shader_frag = scop_file_content("scop.frag");
	if (scop->shader_frag == NULL)
		return (ft_putlog("File not found! ", "scop.frag"));
	scop->shader_vert = scop_file_content("scop.vert");
	if (scop->shader_vert == NULL)
		return (ft_putlog("File not found! ", "scop.vert"));
	scop->projection = mat4_perspective(70.0f, 1280.f / 720.f, 0.1f, 1000.0f);
	scop->view = mat4_identity();
	scop->model = mat4_identity();
	return (1);
}

void		scop_shaders_update(t_scop *scop)
{
	GLfloat			*tmp[4];

	free(scop->model);
	tmp[0] = mat4_translate(scop->obj.pos.x, scop->obj.pos.y, scop->obj.pos.z);
	tmp[1] = mat4_rotate(scop->obj.rot.x, scop->obj.rot.y, scop->obj.rot.z);
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
	uniform_float(scop->program_shader, "tMode", scop->texture_mode);
	uniform_int(scop->program_shader, "disableTexture", !scop->bmp_loaded);
	if (scop->auto_rotate)
		scop->obj.rot.y += scop->rotate_speed;
	if (scop->obj.rot.y > 360.f)
		scop->obj.rot.y = scop->obj.rot.y - 360.f;
	if (scop->obj.rot.y < -360.f)
		scop->obj.rot.y = scop->obj.rot.y + 360.f;
}

int			scop_shaders_build(t_scop *scop)
{
	scop->program_shader = load_shaders(scop->shader_vert, scop->shader_frag);
	if (scop->program_shader <= 0)
		return (ft_putlog("Shader not Loaded! ", ""));
	return (1);
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
