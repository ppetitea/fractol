/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <ppetitea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:19:26 by ppetitea          #+#    #+#             */
/*   Updated: 2019/02/12 15:21:23 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "libft.h"

t_rgb	iteration(t_param *p, t_fractal *f)
{
	double	i;
	int		n;

	i = p->fp[p->fn].iterations;
	n = -1;
	f->a = f->x;
	f->b = f->y;
	while (++n < (int)i)
	{
		f->nexta = f->a * f->a;
		f->nextb = f->b * f->b;
		f->ab = 2.0f * f->a * f->b;
		f->a = f->nexta - f->nextb;
		f->b = p->fn == 2 ? -f->ab : f->ab;
		f->a += p->fn == 0 ? p->julia_px : f->x;
		f->b += p->fn == 0 ? p->julia_py : f->y;
		if (f->a * f->a + f->b * f->b > 16.0)
			break ;
	}
	if (n == i)
		return (ft_rgb(255, 255, 255));
	return (ft_hsv_to_rgb(ft_hsv(n / i * 360.0, 1.0 - n / i, 1.0)));
}

void	initialise_fractal_param(t_param *p, t_fractal *f)
{
	double	width;
	double	height;

	width = p->fp[p->fn].range;
	height = (width * (double)p->ysize) / (double)p->xsize;
	f->xmin = (-width / 2) + p->fp[p->fn].tx;
	f->ymin = (-height / 2) + p->fp[p->fn].ty;
	f->xmax = f->xmin + width;
	f->ymax = f->ymin + height;
	f->dx = (f->xmax - f->xmin) / p->xsize;
	f->dy = (f->ymax - f->ymin) / p->ysize;
	f->y = f->ymin;
}

void	draw_fractal(t_param *p)
{
	t_fractal	f;
	int			i;
	int			j;
	t_rgb		n;

	initialise_fractal_param(p, &f);
	i = -1;
	while (++i < p->ysize)
	{
		f.x = f.xmin;
		j = -1;
		while (++j < p->xsize)
		{
			n = iteration(p, &f);
			p->pixels[j + i * p->xsize] = ft_rgb_to_int(n);
			f.x += f.dx;
		}
		f.y += f.dy;
	}
	mlx_put_image_to_window(p->init, p->window, p->img, 0, 0);
}
