#include "libvec2.h"

t_vec2	vec2_scale(float a, t_vec2 vec)
{
	return((t_vec2){vec.x*a, vec.y*a});
}

t_vec2	vec2_rot(float a, t_vec2 vec)
{
	return((t_vec2){vec.x * cos(a) - vec.y * sin(a),
	 vec.x * sin(a) + vec.y * cos(a)});
}

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	return((t_vec2){a.x - b.x, a.y - b.y});
}

float	vec2_dist(t_vec2 a, t_vec2 b)
{
	return(vec2_norme(vec2_sub(a, b)));
}