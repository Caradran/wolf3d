/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgraph.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:02:28 by esuits            #+#    #+#             */
/*   Updated: 2018/10/05 13:02:31 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGRAPH_H
# define LIBGRAPH_H

# include <SDL.h>

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef t_pos	t_size;

void			set_pixel(t_pos pos, int col, SDL_Surface *s);
void			set_rect(t_size size, int col, t_pos pos, SDL_Surface *s);
void			set_square(int size, int col, t_pos pos, SDL_Surface *s);
int				scale_color(int color, double scale);

#endif
