/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:15:53 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/07 02:01:45 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

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

#endif
