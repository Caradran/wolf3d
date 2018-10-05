/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:06:54 by esuits            #+#    #+#             */
/*   Updated: 2018/10/05 13:06:58 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32			getpixel(SDL_Surface *surface, int x, int y)
{
	int			bpp;
	Uint8		*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		return (*(Uint32 *)p);
	else
		return (0);
}

void			cpy_px_map(t_text *texture, SDL_Surface *img)
{
	Uint32		pixel;
	int			x;
	int			y;

	x = 0;
	while (x < img->w)
	{
		y = 0;
		while (y < img->h)
		{
			texture->map[x + y * img->w] = getpixel(img, x, y);
			y++;
		}
		x++;
	}
}

t_text			get_texture_datas(char *path)
{
	SDL_Surface	*img;
	t_text		texture;

	img = NULL;
	if (!(img = IMG_Load(path)))
	{
		ft_putendl("image load failed");
		exit(1);
	}
	else
	{
		texture.img_w = img->w;
		texture.img_h = img->h;
		if (!(texture.map = malloc(sizeof(int) * (img->w * img->h))))
		{
			ft_putendl(MALLOC_FAIL);
			exit(1);
		}
		SDL_LockSurface(img);
		cpy_px_map(&texture, img);
		SDL_UnlockSurface(img);
		SDL_FreeSurface(img);
	}
	return (texture);
}

t_text			*get_texture(void)
{
	static t_text textures[NB_TEXT];

	textures[0] = get_texture_datas("./textures/mosaique.png");
	textures[1] = get_texture_datas("./textures/metal.jpg");
	textures[2] = get_texture_datas("./textures/brick.jpg");
	textures[3] = get_texture_datas("./textures/wood.jpg");
	textures[4] = get_texture_datas("./textures/stainedGlass1.png");
	textures[5] = get_texture_datas("./textures/tilesStainedGlass.png");
	textures[6] = get_texture_datas("./textures/anvil_base.png");
	textures[7] = get_texture_datas("./textures/ice_packed.png");
	textures[8] = get_texture_datas("./textures/log_birch_top.png");
	textures[9] = get_texture_datas("./textures/planks_oak.png");
	textures[10] = get_texture_datas("./textures/prismarine_bricks.png");
	textures[11] = get_texture_datas("./textures/quartz_block_bottom.png");
	textures[12] = get_texture_datas("./textures/stone_diorite.png");
	textures[13] = get_texture_datas("./textures/stone_andesite.png");
	return (textures);
}

int				uv_wall(t_text text, double x, double y)
{
	int i;
	int j;

	i = x * text.img_h;
	j = y * text.img_w;
	return (text.map[i * text.img_w + j]);
}
