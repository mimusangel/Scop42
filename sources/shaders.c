/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 23:13:05 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/09 22:53:47 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	test_shaders(GLuint id)
{
	GLint	log_lenght;
	GLchar	*log_info;
	GLint	shader_type;

	glGetShaderiv(id, GL_SHADER_TYPE, &shader_type);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_lenght);
	if (log_lenght > 0)
	{
		if (shader_type == GL_VERTEX_SHADER)
			ft_putstr("Error Vertex Shader:\n\t");
		else
			ft_putstr("Error Fragment Shader:\n\t");
		log_info = (GLchar *)malloc(sizeof(GLchar) * log_lenght);
		glGetShaderInfoLog(id, log_lenght, &log_lenght, log_info);
		ft_putstr(log_info);
		free(log_info);
		return (0);
	}
	return (1);
}

static int	test_program(GLuint program)
{
	GLint	log_lenght;
	GLchar	*log_info;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_lenght);
	if (log_lenght > 0)
	{
		ft_putstr("Error Program: ");
		log_info = (GLchar *)malloc(sizeof(GLchar) * log_lenght);
		glGetProgramInfoLog(program, log_lenght, &log_lenght, log_info);
		ft_putstr(log_info);
		free(log_info);
		return (0);
	}
	return (1);
}

void		uniform_mat4(GLuint program, GLchar *name, GLfloat *mat)
{
	GLint id;

	id = glGetUniformLocation(program, name);
	glUniformMatrix4fv(id, 1, GL_FALSE, mat);
}

void		uniform_float(GLuint program, GLchar *name, GLfloat value)
{
	GLint id;

	id = glGetUniformLocation(program, name);
	glUniform1f(id, value);
}

GLuint		load_shaders(const GLchar *v_src, const GLchar *f_src)
{
	GLuint	vertex_id;
	GLuint	fragment_id;
	GLuint	program_id;

	vertex_id = glCreateShader(GL_VERTEX_SHADER);
	fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertex_id, 1, &v_src, NULL);
	glCompileShader(vertex_id);
	if (!test_shaders(vertex_id))
		return (0);
	glShaderSource(fragment_id, 1, &f_src, NULL);
	glCompileShader(fragment_id);
	if (!test_shaders(fragment_id))
		return (0);
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, fragment_id);
	glLinkProgram(program_id);
	if (!test_program(program_id))
		return (0);
	glDetachShader(program_id, vertex_id);
	glDetachShader(program_id, fragment_id);
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);
	return (program_id);
}
