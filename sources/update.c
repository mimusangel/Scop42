/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:34:15 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 21:46:56 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		scop_rotate_key(t_scop *scop)
{
	if (glfwGetKey(scop->win, GLFW_KEY_KP_1) == GLFW_PRESS)
		scop->obj.rot.y = 0;
	if (glfwGetKey(scop->win, GLFW_KEY_KP_2) == GLFW_PRESS)
		scop->obj.rot.y = 90;
	if (glfwGetKey(scop->win, GLFW_KEY_KP_3) == GLFW_PRESS)
		scop->obj.rot.y = 180;
	if (glfwGetKey(scop->win, GLFW_KEY_KP_4) == GLFW_PRESS)
		scop->obj.rot.y = 270;
	if (glfwGetKey(scop->win, GLFW_KEY_KP_5) == GLFW_PRESS)
		scop->obj.rot.y = 45;
	if (glfwGetKey(scop->win, GLFW_KEY_KP_6) == GLFW_PRESS)
		scop->obj.rot.y = 135;
	if (glfwGetKey(scop->win, GLFW_KEY_KP_9) == GLFW_PRESS)
		scop->auto_rotate = 1;
	if (glfwGetKey(scop->win, GLFW_KEY_KP_7) == GLFW_PRESS)
		scop->auto_rotate = 0;
	if (glfwGetKey(scop->win, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		scop->rotate_speed += 0.1f;
	if (scop->rotate_speed > 5.f)
		scop->rotate_speed = 5.f;
	if (glfwGetKey(scop->win, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		scop->rotate_speed -= 0.1f;
	if (scop->rotate_speed < -5.f)
		scop->rotate_speed = -5.f;
}

void			scop_texture_mode(t_scop *scop)
{
	static int	mode = 0;

	if (mode == 0)
		scop->texture_mode -= 0.005f;
	if (mode == 1)
		scop->texture_mode += 0.005f;
	if (scop->texture_mode < 0.f)
		scop->texture_mode = 0.f;
	if (scop->texture_mode > 1.0f)
		scop->texture_mode = 1.0f;
	if (glfwGetKey(scop->win, GLFW_KEY_T) == GLFW_PRESS)
		mode = 1;
	if (glfwGetKey(scop->win, GLFW_KEY_U) == GLFW_PRESS)
		mode = 0;
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
	if (glfwGetKey(scop->win, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(scop->win, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	scop_rotate_key(scop);
	scop_texture_mode(scop);
}
