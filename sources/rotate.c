/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:34:34 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/08 06:17:24 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLfloat		*mat4_axisangle(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat		*m;
	GLfloat		c;
	GLfloat		s;
	GLfloat		t;
	GLfloat		tmp[2];

	if (!(m = mat4_identity()))
		return (NULL);
	c = (GLfloat)cosf(SCOP_TORADIANS(angle));
	s = (GLfloat)sinf(SCOP_TORADIANS(angle));
	t = 1.0f - c;
	m[0] = c + x * x * t;
	m[5] = c + y * y * t;
	m[10] = c + z * z * t;
	tmp[0] = x * y * t;
	tmp[1] = z * s;
	m[1] = tmp[0] - tmp[1];
	m[4] = tmp[0] + tmp[1];
	tmp[0] = x * z * t;
	tmp[1] = y * s;
	m[2] = tmp[0] + tmp[1];
	m[8] = tmp[0] - tmp[1];
	tmp[0] = y * z * t;
	tmp[1] = x * s;
	m[6] = tmp[0] - tmp[1];
	m[9] = tmp[0] + tmp[1];
	return (m);
}

GLfloat		*mat4_rotate(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat	*rx;
	GLfloat	*ry;
	GLfloat	*rz;
	GLfloat	*tmp;
	GLfloat	*res;

	rx = mat4_axisangle(x, 1.f, 0.f, 0.f);
	ry = mat4_axisangle(y, 0.f, 1.f, 0.f);
	rz = mat4_axisangle(z, 0.f, 0.f, 1.f);
	tmp = mat4_multiplie(rz, ry);
	res = mat4_multiplie(tmp, rx);
	free(tmp);
	free(rz);
	free(ry);
	free(rx);
	return (res);
}
