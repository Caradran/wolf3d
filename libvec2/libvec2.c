#include "libvec2.h"

t_vec2	vec2_init(float x, float y)
{
	return ((t_vec2){x, y});
}

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return((t_vec2){a.x + b.x, a.y + b.y});
}

float	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

float	vec2_norme(t_vec2 a)
{
	return (sqrt(a.x * a.x + b.x * b.x));
}

t_vec2	vec2_normalize(t_vec2 a)
{
	float norm;

	norm = norme_vec2(a);
	return ((t_vec2){a.x/norm, a.y/norm});
}