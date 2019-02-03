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
	
	double				rangex;
	double				rangey;
	double				move;
	void			*init;
	void			*window;
	void			*img;
	int				*pixels;
	int				xsize;
	int				ysize;
	int				key;
	int				press;
	int				pointer;
	double			zoom[3];
	double			translationx[3];
	double			translationy[3];
	double			x[3];
	double			y[3];
}					t_param;

void	*manage_error(t_param *p, int code, const char *message);
void	draw_fractal(t_param *p);
int		manage_callback(void *param);
int		press_callback(int key, void *param);
int		release_callback(int key, void *param);
int		pointer_callback(int x, int y, void *param);
int		mouse_callback(int button, int x, int y, void *param);
void	reset_image(t_param *p);
void	draw(t_param *p);

#endif
