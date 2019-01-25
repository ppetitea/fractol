#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "key.h"

typedef struct		s_param
{
	int		fractal;
	void		*init;
	void		*window;
	void		*img;
	int		*pixels;
	int		xsize;
	int		ysize;
}			t_param;

void	*manage_error(t_param *p, int code, const char *message);


#endif
