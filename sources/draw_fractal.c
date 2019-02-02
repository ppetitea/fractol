#include "fractol.h"
#include "mlx.h"

void	draw_fractal(t_param *p)
{
	t_fractal	f;
	int		i;
	int		j;
	int		n;
	
	f.w = 5 * p->zoom;
	f.h = (f.w * p->ysize) / p->xsize;
	f.xmin = (-f.w / 2) + p->x;
	f.ymin = (-f.h / 2) + p->y;
	f.xmax = f.xmin + f.w;
	f.ymax	= f.ymin + f.h;
	f.dx = (f.xmax - f.xmin) / p->xsize;
	f.dy = (f.ymax - f.ymin) / p->ysize;
	f.y = f.ymin;
	i = -1;
	while (++i < p->ysize)
	{
		f.x = f.xmin;
		j = -1;
		while (++j < p->xsize)
		{
			f.a = f.x;
			f.b = f.y;
			n = -1;
			while (++n < 100)
			{
				f.nexta = f.a * f.a;
				f.nextb = f.b * f.b;
				f.ab = 2.0f * f.a * f.b;
				f.a = f.nexta - f.nextb + p->rangex + f.x;
				f.b = f.ab + p->rangey + f.y;
				if (f.a * f.a + f.b * f.b > 16.0)
					break ;
			}
			if (n == 100)
				p->pixels[j + i * p->xsize] = 0x00000000;
			else
				p->pixels[j + i * p->xsize] = n * 0x00000019;
				/// 100.0 * 16777215;
				//manage_color(p);
			f.x += f.dx;
		}
		f.y += f.dy;
	}
	mlx_put_image_to_window(p->init, p->window, p->img, 0, 0);
}
