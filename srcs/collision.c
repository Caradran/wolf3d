/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:28:04 by esuits            #+#    #+#             */
/*   Updated: 2018/10/07 18:28:08 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		detect_collision(t_env env, int dir)
{
	double	x;
	double	y;
	int		supp;

	x = env.player.pos.x + 0.05 * dir * env.player.dir.x;
	y = env.player.pos.y + 0.05 * dir * env.player.dir.y;
	supp = 0;
	if (fabs(env.player.dir.x) > fabs(env.player.dir.y))
		supp = 1;
	if (x < 0 || x > 64 || y < 0 || y > 64 || env.map[(int)x][(int)y])
		return (1);
	else if (((int)x != (int)env.player.pos.x && (int)y !=
		(int)env.player.pos.y) &&
		supp && env.map[(int)x][(int)y - sign(dir * env.player.dir.y)])
		return (1);
	else if (((int)x != (int)env.player.pos.x && (int)y !=
		(int)env.player.pos.y) &&
		!supp && env.map[(int)x - sign(dir * env.player.dir.x)][(int)y])
		return (1);
	return (0);
}
