/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:05:25 by esuits            #+#    #+#             */
/*   Updated: 2018/10/05 13:05:27 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec2.h"

t_vec2	vec2_init(double x, double y)
{
	return ((t_vec2){x, y});
}

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x + b.x, a.y + b.y});
}

double	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

double	vec2_norme(t_vec2 a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_vec2	vec2_normalize(t_vec2 a)
{
	double norm;

	norm = vec2_norme(a);
	return ((t_vec2){a.x / norm, a.y / norm});
}
