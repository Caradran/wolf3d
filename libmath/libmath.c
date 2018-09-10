#include "libmath.h"

int		ft_ceil(float x)
{
	if ((int)x == x)
		return ((int)x);
	return ((int)x + 1);
}

int		ft_floor(float x)
{
	return ((int)x);
}

float	ft_abs(float x)
{
	return (x >= 0 ? x : -x);
}