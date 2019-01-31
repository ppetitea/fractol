#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "key.h"

typedef struct		s_fractal
{
	double		w;
	double		h;
	double		a;
	double		b;
	double		x;
	double		y;
	double		dx;
	double		dy;
	double		xmin;
	double		ymin;
	double		xmax;
	double		ymax;
	double		nexta;
	double		nextb;
	double		ab;
}			t_fractal;

typedef struct		s_param
{
	int				fractal;
	void			*init;
	void			*window;
	void			*img;
	int				*pixels;
	int				xsize;
	int				ysize;
	int				key;
	int				press;
	double			zoom;
	double			translationx;
	double			translationy;
}					t_param;

void	*manage_error(t_param *p, int code, const char *message);
void	draw_fractal(t_param *p);
int		manage_callback(void *param);
int		press_callback(int key, void *param);
int		release_callback(int key, void *param);
int		pointeur_callback(int x, int y, void *param);

#endif
