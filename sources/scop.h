/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:15:53 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/07 05:02:54 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <unistd.h>
# include <stdlib.h>
# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>

typedef struct	s_scop
{
	GLFWwindow	*win;
	int			run;
}				t_scop;

size_t		ft_strlen(const char *str);
void		ft_putstr(const char *str);
void		ft_putlog(const char *str, const char *strlog);
char		*ft_strjoin(char const *s1, char const *s2);
char		*scop_file_content(const char *path);
size_t		ft_strchr(const char *str, const char c);

#endif
