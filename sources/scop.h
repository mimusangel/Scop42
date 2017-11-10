/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:15:53 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/10 09:57:41 by mgallo           ###   ########.fr       */
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
# include "bmp.h"

# define SCOP_PI 3.14159265359f
# define SCOP_TORADIANS(x)	(x * 0.0174533f)

# ifndef BUFF_SIZE
#  define BUFF_SIZE 2048
# endif

# ifndef MAX
#  define MAX(a,b)	((a) > (b) ? a : b)
# endif
# ifndef MIN
#  define MIN(a,b)	((a) < (b) ? a : b)
# endif

# define VBO_POS 0
# define VBO_COLOR 1
# define VBO_TEXTURE 2
# define VBO_NORMAL 3

# define SCOP_MAX_VBO 3

typedef	struct	s_vec3
{
	GLfloat		x;
	GLfloat		y;
	GLfloat		z;
}				t_vec3;

typedef struct	s_array
{
	char		**data;
	size_t		len;
}				t_array;

typedef struct	s_mesh
{
	GLuint		vao;
	GLuint		vbo[SCOP_MAX_VBO];
	size_t		size;
}				t_mesh;

typedef struct	s_obj
{
	size_t		vcount;
	GLfloat		*v;
	size_t		tcount;
	GLfloat		*buff;
	GLfloat		cx;
	GLfloat		cy;
	GLfloat		cz;
	t_vec3		pos;
	t_vec3		rot;
	t_vec3		min;
	t_vec3		max;
	t_mesh		mesh;
}				t_obj;

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
	t_obj		obj;
	int			auto_rotate;
	float		rotate_speed;
	float		texture_mode;
	int			bmp_loaded;
	t_bmp		bmp;
	GLuint		texture;
	int			calc_normal_type;
}				t_scop;

/*
** log.c
*/
size_t			ft_strlen(const char *str);
void			ft_putstr(const char *str);
int				ft_putlog(const char *str, const char *strlog);
void			scop_putmat4(GLfloat *mat);
void			scop_obj_log(t_scop *scop);
/*
** str.c
*/
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strchr(const char *str, const char c);
void			ft_strcpy(char *dest, char *src, size_t size);
char			*ft_strsub(char *src, size_t begin, size_t end);
size_t			ft_strstr_count(char *src, char *str);
/*
** str2.c
*/
int				ft_strstart(char *str, char *start);
int				ft_strend(char *str, char *end);
/*
** file.c
*/
char			*scop_file_content(const char *path);
size_t			get_str_line(char *str, char **line);
/*
** obj.c
*/
void			scop_init_obj(t_scop *scop);
int				scop_load_obj(t_scop *scop, char *path);
void			scop_unload_obj(t_scop *scop);
void			scop_obj_color(t_scop *scop);
/*
** parser.c
*/
int				scop_obj_parser(t_scop *scop, t_array *arr);
/*
** mesh.c
*/
int				mesh_begin(t_scop *scop);
void			mesh_add(t_mesh *mesh, int type, size_t size, GLfloat *data);
void			mesh_end(t_scop *scop);
void			mesh_render(t_scop *scop);
void			mesh_delete(t_scop *scop);
/*
** shader.c
*/
GLuint			load_shaders(const GLchar *v_src, const GLchar *f_src);
void			scop_shaders_update(t_scop *scop);
/*
** uniform.c
*/
void			uniform_int(GLuint program, GLchar *name, GLint value);
void			uniform_float(GLuint program, GLchar *name, GLfloat value);
void			uniform_mat4(GLuint program, GLchar *name, GLfloat *mat);
/*
** mat4.c
*/
GLfloat			*mat4_create(void);
GLfloat			*mat4_identity(void);
GLfloat			*mat4_perspective(float fov, float asp, float near, float far);
GLfloat			*mat4_translate(float x, float y, float z);
GLfloat			*mat4_multiplie(float *m0, float *m1);
/*
** rotate.c
*/
GLfloat			*mat4_axisangle(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
GLfloat			*mat4_rotate(GLfloat x, GLfloat y, GLfloat z);
/*
** scop_shaders.c
*/
void			scop_shaders_init(t_scop *scop);
int				scop_shaders_load(t_scop *scop);
int				scop_shaders_build(t_scop *scop);
void			scop_shaders_unload(t_scop *scop);
/*
** number.c
*/
int				ft_atoi(const char *s);
double			ft_atof(const char *s);
void			ft_putnbr(int n);
void			ft_putfloat(float n);
void			ft_putfloat_nb(float n, int size);
/*
** array.c
*/
t_array			*array_bystr(char *str, char sep, int trim);
void			array_free(t_array **arr);
/*
** update.c
*/
void			scop_update(t_scop *scop);
/*
** texture.c
*/
int				texture_generate(t_scop	*scop);
void			texture_bind(t_scop *scop);
void			texture_unbind(void);
void			texture_unload(t_scop *scop);
/*
** args.c
*/
void			scop_args(t_scop *scop, int ac, char **av);
/*
** generate.c
*/
void			texture_generate_buffer(t_scop *scop);

#endif
