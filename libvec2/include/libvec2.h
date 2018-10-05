/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvec2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:05:16 by esuits            #+#    #+#             */
/*   Updated: 2018/10/05 13:05:18 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVEC2_H
# define LIBVEC2_H
# include <math.h>

typedef struct	s_vec2
{
	double		x;
	double		y;
}				t_vec2;

t_vec2			vec2_init(double x, double y);
t_vec2			vec2_add(t_vec2 a, t_vec2 b);
t_vec2			vec2_sub(t_vec2 a, t_vec2 b);
double			vec2_dot(t_vec2 a, t_vec2 b);
double			vec2_norme(t_vec2 a);
double			vec2_dist(t_vec2 a, t_vec2 b);
t_vec2			vec2_normalize(t_vec2 a);
t_vec2			vec2_scale(double a, t_vec2 vec);
t_vec2			vec2_rot(double a, t_vec2 vec);

#endif
