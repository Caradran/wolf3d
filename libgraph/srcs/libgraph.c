#include "libgraph.h"

void set_pixel(t_pos pos, int col, SDL_Surface *s)
{
	int *pixels;

	pixels = s->pixels;
	if (pos.x < s->w && pos.y < s->h && pos.x >= 0 && pos.y >= 0)
		pixels[pos.x + pos.y * s->w] = col;
	s->pixels = pixels;
}

void set_rect(t_size size, int col, t_pos pos, SDL_Surface *s)
{
	int i;
	int j;
	
	i = 0;
	while (i < size.x)
	{
		j = 0;
		while (j < size.y)
		{
			set_pixel((t_pos){i + pos.x, j + pos.y}, col, s);
			j++;
		}
		i++;
	}
}

void set_square(int size, int col, t_pos pos, SDL_Surface *s)
{
	set_rect((t_size){size, size}, col, pos, s);
}