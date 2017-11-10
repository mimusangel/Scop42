/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:15:50 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 09:36:09 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		scop_load(t_scop *scop)
{
	if (!glfwInit())
	{
		ft_putstr("Erreur init glfw!");
		return (0);
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!(scop->win = glfwCreateWindow(1280, 720, "Scop", NULL, NULL)))
	{
		ft_putstr("Erreur creation de la fenetre!");
		return (0);
	}
	glfwMakeContextCurrent(scop->win);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		ft_putstr("Erreur init glew!");
		return (0);
	}
	return (1);
}

static int		scop_generate(t_scop *scop)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	if (!scop_shaders_build(scop))
		return (0);
	if (!mesh_begin(scop))
		return (0);
	mesh_add(&(scop->obj.mesh), VBO_POS, 3 * scop->obj.tcount, scop->obj.buff);
	texture_generate_buffer(scop);
	mesh_add(&(scop->obj.mesh), VBO_TEXTURE, 3 * scop->obj.tcount,
		scop->obj.buff);
	scop_obj_color(scop);
	mesh_add(&(scop->obj.mesh), VBO_COLOR, 3 * scop->obj.tcount,
		scop->obj.buff);
	mesh_end(scop);
	if (!texture_generate(scop) && scop->bmp_loaded)
		return (0);
	return (1);
}

static void		scop_loop(t_scop *scop)
{
	if (!scop_generate(scop))
		return ;
	while (scop->run)
	{
		if (glfwWindowShouldClose(scop->win)
			|| glfwGetKey(scop->win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			scop->run = 0;
		else
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			scop_update(scop);
			if (scop->bmp_loaded)
			{
				glActiveTexture(GL_TEXTURE0);
				texture_bind(scop);
				uniform_int(scop->program_shader, "uTexture", 0);
			}
			mesh_render(scop);
			glfwSwapBuffers(scop->win);
			glfwPollEvents();
		}
	}
	if (scop->bmp_loaded)
		texture_unload(scop);
	mesh_delete(scop);
}

static void		scop_unload(t_scop *scop)
{
	scop_unload_obj(scop);
	scop_shaders_unload(scop);
	glfwTerminate();
}

int				main(int ac, char **av)
{
	t_scop	scop;

	if (ac < 2)
	{
		ft_putstr("Usage: ");
		ft_putlog(av[0], " <file.obj> [image.bmp] [-sphere/-flat]");
		return (0);
	}
	scop_args(&scop, ac, av);
	scop_init_obj(&scop);
	scop_shaders_init(&scop);
	if (!ft_strend(av[1], ".obj"))
		ft_putstr("File extend isn't valid!");
	else if (scop_load_obj(&scop, av[1]) && scop_shaders_load(&scop))
	{
		scop.bmp_loaded = 0;
		if (ac > 2)
			scop.bmp_loaded = bmp_load(&(scop.bmp), av[2]);
		if (!scop.bmp_loaded)
			ft_putstr("No texture loaded. Texture mod is disabled\n");
		if ((scop.run = scop_load(&scop)) > 0)
			scop_loop(&scop);
	}
	scop_unload(&scop);
	return (0);
}
