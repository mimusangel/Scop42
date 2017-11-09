/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:15:50 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 17:13:05 by mgallo           ###   ########.fr       */
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
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * scop->obj.tcount, scop->obj.vpos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * scop->obj.tcount, scop->obj.color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

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
			if (glfwGetKey(scop->win, GLFW_KEY_W) == GLFW_PRESS)
				scop->obj.pos.z += 0.05f;
			if (glfwGetKey(scop->win, GLFW_KEY_S) == GLFW_PRESS)
				scop->obj.pos.z -= 0.05f;
			if (glfwGetKey(scop->win, GLFW_KEY_A) == GLFW_PRESS
				|| glfwGetKey(scop->win, GLFW_KEY_LEFT) == GLFW_PRESS)
				scop->obj.pos.x -= 0.05f;
			if (glfwGetKey(scop->win, GLFW_KEY_D) == GLFW_PRESS
				|| glfwGetKey(scop->win, GLFW_KEY_RIGHT) == GLFW_PRESS)
				scop->obj.pos.x += 0.05f;
			if (glfwGetKey(scop->win, GLFW_KEY_UP) == GLFW_PRESS)
				scop->obj.pos.y += 0.05f;
			if (glfwGetKey(scop->win, GLFW_KEY_DOWN) == GLFW_PRESS)
				scop->obj.pos.y -= 0.05f;
			scop_shaders_update(scop);

			// TEST
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, scop->obj.tcount * 3);
			glBindVertexArray(0);

			glfwSwapBuffers(scop->win);
			glfwPollEvents();
		}
	}
}

static void		scop_unload(t_scop *scop)
{
	scop_unload_obj(scop);
	scop_shaders_unload(scop);
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
	scop_load_obj(&scop, av[1]);
	scop_shaders_load(&scop);
	if ((scop.run = scop_load(&scop)) > 0)
	{
		scop_shaders_build(&scop);
		scop_loop(&scop);
	}
	scop_unload(&scop);
	return (0);
}
