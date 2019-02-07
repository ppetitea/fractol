#include "fractol.h"
#include "mlx.h"
#include "libft.h"

t_rgb		iteration(t_param *p, t_fractal *f)
{
	int n;

	n = -1;
	f->a = f->x;
	f->b = f->y;
	while (++n < p->iterations)
	{
		f->nexta = f->a * f->a;
		f->nextb = f->b * f->b;
		f->ab = 2.0f * f->a * f->b;
		f->a = f->nexta - f->nextb;
		f->b = f->ab;
		f->a += p->fractal == 1 ? p->rangex : f->x;
		f->b += p->fractal == 1 ? p->rangey : f->y;
		if (f->a * f->a + f->b * f->b > 16.0)
			break ;
	}
	if (n == p->iterations)
		return (ft_rgb(255, 255, 255));
	return (ft_hsv_to_rgb(ft_hsv(n / (double)p->iterations* 360.0, 1.0 - n / (double)p->iterations, 1.0)));
}

int		int_power_int(int nb, int power)
{
	int		tmp;

	tmp = nb;
	while (--power > 0)
		tmp *= nb;
	return (tmp);
}

t_rgb	iteration_multibrot(t_param *p, t_fractal *f)
{
	int n;

	n = -1;
	f->a = f->x;
	f->b = f->y;
	while (++n < p->iterations)
	{
		f->nexta = f->a * f->a;
		f->nextb = f->b * f->b;
		f->ab = 2.0f * f->a * f->b;
		f->a = f->nexta - f->nextb;
		f->b = f->ab;
		f->a += f->y - 2;
		f->b += f->x / (n + 1);
		if (f->a * f->a + f->b + f->b > 16.0)
			break ;
	}
	if (n == p->iterations)
		return (ft_rgb(255, 255, 255));
	return (ft_hsv_to_rgb(ft_hsv(n / (double)p->iterations * 360.0, 1.0 - n / (double)p->iterations, 1.0)));
}

void	initialise_fractal_param(t_param *p, t_fractal *f)
{
	f->w = p->zoom[p->fractal - 1];
	f->h = (f->w * p->ysize) / p->xsize;
	f->xmin = (-f->w / 2) + p->x[p->fractal - 1];
	f->ymin = (-f->h / 2) + p->y[p->fractal - 1];
	f->xmax = f->xmin + f->w;
	f->ymax	= f->ymin + f->h;
	f->dx = (f->xmax - f->xmin) / p->xsize;
	f->dy = (f->ymax - f->ymin) / p->ysize;
	f->y = f->ymin;
}

void	draw_fractal(t_param *p)
{
	t_fractal	f;
	int		i;
	int		j;
	t_rgb	n;

	initialise_fractal_param(p, &f);
	i = -1;
	while (++i < p->ysize)
	{
		f.x = f.xmin;
		j = -1;
		while (++j < p->xsize)
		{
			if (p->fractal != 3)
				n = iteration(p, &f);
			else
				n = iteration_multibrot(p, &f);
			p->pixels[j + i * p->xsize] = ft_rgb_to_int(n);
			f.x += f.dx;
		}
		f.y += f.dy;
	}
	mlx_put_image_to_window(p->init, p->window, p->img, 0, 0);
}