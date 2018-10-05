/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvec2_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:05:32 by esuits            #+#    #+#             */
/*   Updated: 2018/10/05 13:05:35 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec2.h"

t_vec2	vec2_scale(double a, t_vec2 vec)
{
	return ((t_vec2){vec.x * a, vec.y * a});
}

t_vec2	vec2_rot(double a, t_vec2 vec)
{
	return ((t_vec2){vec.x * cos(a) - vec.y * sin(a),
	vec.x * sin(a) + vec.y * cos(a)});
}

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x - b.x, a.y - b.y});
}

double	vec2_dist(t_vec2 a, t_vec2 b)
{
	return (vec2_norme(vec2_sub(a, b)));
}
