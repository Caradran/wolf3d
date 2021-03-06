/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmymath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:03:31 by esuits            #+#    #+#             */
/*   Updated: 2018/10/05 13:05:06 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_ceil(double x)
{
	if ((int)x == x)
		return ((int)x);
	return ((int)x + 1);
}

int		ft_floor(double x)
{
	return ((int)x);
}

double	ft_abs(double x)
{
	return (x >= 0 ? x : -x);
}

int		sign(double x)
{
	return (x > 0 ? 1 : -1);
}

double	part_dec(double x)
{
	return (x - ft_floor(x));
}
