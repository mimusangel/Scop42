/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:34:15 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/11 18:30:07 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		scop_rotate_key(t_scop *scop)
{
	if (glfwGetKey(scop->win, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		scop->rotate_speed += 0.1f;
	if (scop->rotate_speed > 5.f)
		scop->rotate_speed = 5.f;
	if (glfwGetKey(scop->win, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		scop->rotate_speed -= 0.1f;
	if (scop->rotate_speed < -5.f)
		scop->rotate_speed = -5.f;
	scop->obj.rot.y += (scop->auto_rotate) ? scop->rotate_speed : 0;
	if (scop->obj.rot.y > 360.f)
		scop->obj.rot.y = scop->obj.rot.y - 360.f;
	if (scop->obj.rot.y < -360.f)
		scop->obj.rot.y = scop->obj.rot.y + 360.f;
}

void			scop_cullface_mode(t_scop *scop)
{
	if (glfwGetKey(scop->win, GLFW_KEY_1) == GLFW_PRESS)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
	}
	if (glfwGetKey(scop->win, GLFW_KEY_2) == GLFW_PRESS)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	if (glfwGetKey(scop->win, GLFW_KEY_3) == GLFW_PRESS)
		glDisable(GL_CULL_FACE);
}

void			scop_update(t_scop *scop)
{
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
	scop_rotate_key(scop);
	scop_cullface_mode(scop);
	if (scop->mode == 0)
		scop->texture_mode -= 0.005f;
	if (scop->mode == 1)
		scop->texture_mode += 0.005f;
	if (scop->texture_mode < 0.f)
		scop->texture_mode = 0.f;
	if (scop->texture_mode > 1.0f)
		scop->texture_mode = 1.0f;
}

void			key_callback(GLFWwindow *w, int k, int sc, int a, int m)
{
	t_scop	*scop;

	scop = (t_scop *)glfwGetWindowUserPointer(w);
	if (k == GLFW_KEY_T && a == GLFW_PRESS)
		scop->mode = !scop->mode;
	if (k == GLFW_KEY_R && a == GLFW_PRESS)
		scop->auto_rotate = !scop->auto_rotate;
	if (k == GLFW_KEY_F && a == GLFW_PRESS)
		scop->wireframe = !scop->wireframe;
	if (!scop->wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (scop->wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (k == GLFW_KEY_0 && a == GLFW_PRESS)
		scop->obj.rot.y = 0;
	if (k == GLFW_KEY_9 && a == GLFW_PRESS)
		scop->obj.rot.y += 22.5f;
	if (k == GLFW_KEY_8 && a == GLFW_PRESS)
		scop->obj.rot.y -= 22.5f;
}
