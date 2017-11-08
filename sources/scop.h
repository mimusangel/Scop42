/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:15:53 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/08 00:52:58 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <unistd.h>
# include <stdlib.h>
# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <math.h>

# define SCOP_PI 3.14159265359f
# define SCOP_TORADIANS(x)	(x * 0.0174533f)

# ifndef BUFF_SIZE
#  define BUFF_SIZE 2048
# endif

typedef struct	s_scop
{
	GLFWwindow	*win;
	int			run;
	char		*shader_frag;
	char		*shader_vert;
	GLuint		program_shader;
	GLfloat		*projection;
	GLfloat		*view;
	GLfloat		*model;
}				t_scop;

// log.c
size_t		ft_strlen(const char *str);
void		ft_putstr(const char *str);
void		ft_putlog(const char *str, const char *strlog);
// str.c
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strchr(const char *str, const char c);
void		ft_strcpy(char *dest, char *src, size_t size);
char		*ft_strsub(char *src, size_t begin, size_t end);
// file.c
char		*scop_file_content(const char *path);
size_t		get_str_line(char *str, char **line);
// obj.c
int			scop_load_obj(t_scop *scop, char *path);
// Shader.c
void		uniform_mat4(GLuint program, GLchar *name, GLfloat *mat);
GLuint		load_shaders(const GLchar *v_src, const GLchar *f_src);
// mat4.c
GLfloat		*mat4_create(void);
GLfloat		*mat4_identity(void);
GLfloat		*mat4_perspective(float fov, float asp, float near, float far);
GLfloat		*mat4_translate(float x, float y, float z);
GLfloat		*mat4_multiplie(float *m0, float *m1);
// scop_shaders.c
void		scop_shaders_load(t_scop *scop);
void		scop_shaders_build(t_scop *scop);
void		scop_shaders_unload(t_scop *scop);
#endif
