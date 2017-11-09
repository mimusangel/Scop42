/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:15:50 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 21:49:39 by mgallo           ###   ########.fr       */
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

static void		scop_loop(t_scop *scop)
{
	if (!scop_shaders_build(scop))
		return ;
	if (!mesh_generate(scop))
		return ;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	while (scop->run)
	{
		if (glfwWindowShouldClose(scop->win)
			|| glfwGetKey(scop->win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			scop->run = 0;
		else
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			scop_update(scop);
			mesh_render(scop);
			glfwSwapBuffers(scop->win);
			glfwPollEvents();
		}
	}
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
		ft_putlog(av[0], " <file.obj> [image.bmp]");
		return (0);
	}
	scop_init_obj(&scop);
	scop_shaders_init(&scop);
	if (ft_strend(av[1], ".obj"))
	{
		if (scop_load_obj(&scop, av[1]))
		{
			if (scop_shaders_load(&scop))
			{
				if ((scop.run = scop_load(&scop)) > 0)
					scop_loop(&scop);
			}
		}
	}
	else
		ft_putstr("File extend isn't valid!");
	scop_unload(&scop);
	return (0);
}
