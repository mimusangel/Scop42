/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:34:15 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 18:35:23 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
}
