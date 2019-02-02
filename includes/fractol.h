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
	double		c_r;
	double		c_i;
	double		z_r;
	double		z_i;
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
	double		imagex;
	double		imagey;
}			t_fractal;

typedef struct		s_param
{
	int				fractal;
	double				rangex;
	double				rangey;
	void			*init;
	void			*window;
	void			*img;
	int				*pixels;
	int				xsize;
	int				ysize;
	int				key;
	int				press;
	int				pointeur;
	double			zoom;
	double			zoomx;
	double			zoomy;
	double			translationx;
	double			translationy;
	double			x;
	double			y;
}					t_param;

void	*manage_error(t_param *p, int code, const char *message);
void	draw_fractal(t_param *p);
int		manage_callback(void *param);
int		press_callback(int key, void *param);
int		release_callback(int key, void *param);
int		pointeur_callback(int x, int y, void *param);
int		mouse_callback(int button, int x, int y, void *param);

#endif
