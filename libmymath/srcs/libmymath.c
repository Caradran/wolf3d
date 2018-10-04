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

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

int		sign(double x)
{
	return (x > 0 ? 1 : -1);
}