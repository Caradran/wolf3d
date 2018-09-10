typedef struct	s_vec2
{
	float x;
	float y;
}				t_vec2;

typedef struct	s_player
{
	float x;
	float y;
	t_vec2 dir;
}				t_player;

typedef struct  s_ray
{
	int		pos_x;
	int		pos_y;
	int		side;
	t_vec2	dist;
	t_vec2	delta;
}				t_ray;