/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:15:50 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/07 04:14:19 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		scop_info()
{
	ft_putlog("Vendor: ", (char *)glGetString(GL_VENDOR));
	ft_putlog("Renderer: ", (char *)glGetString(GL_RENDERER));
	ft_putlog("GL Version: ", (char *)glGetString(GL_VERSION));
	ft_putlog("GLSL Version: ", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

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
	scop_info();
	return (1);
}

static void		scop_loop(t_scop *scop)
{
	while (scop->run)
	{
		if (glfwWindowShouldClose(scop->win))
			scop->run = 0;
		else
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwSwapBuffers(scop->win);
			glfwPollEvents();
		}
	}
}

static void		scop_unload(t_scop *scop)
{
	glfwTerminate();
}

int		main(int ac, char **av)
{
	t_scop	scop;

	if (ac < 2)
	{
		ft_putstr("Usage: ");
		ft_putstr(av[0]);
		ft_putstr(" <file.obj>\n");
		return (0);
	}
	scop.run = scop_load(&scop);
	scop_loop(&scop);
	scop_unload(&scop);
	return (0);
}
