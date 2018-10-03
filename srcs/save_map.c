#include "wolf3d.h"

void put_nb_tab_fd(int **tab, int fd)
{
	int i;
	int j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			if (i == 0 || j == 0 || i == 63 || j == 63)
				ft_putnbr_fd(NB_TILES, fd);
			else
				ft_putnbr_fd(tab[i][j], fd);
			write(fd, " ", 1);
			j++;
		}
		write(fd, "\n", 1);
		i++;
	}
	
}

void save_map(int **map, char *mapname)
{
	int fd;

	if ((fd = open(mapname, O_RDWR | O_CREAT, S_IRWXU)) < 0)
		exit(1);
	put_nb_tab_fd(map, fd);
	close(fd);
}