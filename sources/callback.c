/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <ppetitea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:58:41 by ppetitea          #+#    #+#             */
/*   Updated: 2019/02/12 15:18:07 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

int		press_callback(int key, void *param)
{
	t_param *p;

	p = (t_param*)param;
	p->press = 1;
	p->key = key;
	if (key == KEY_SPACEBAR && p->fn == 0)
		p->is_range_lock = !p->is_range_lock;
	return (1);
}

int		release_callback(int key, void *param)
{
	t_param *p;

	(void)key;
	p = (t_param*)param;
	p->press = 0;
	return (1);
}

int		pointer_callback(int x, int y, void *param)
{
	t_param *p;

	p = (t_param*)param;
	if (x >= 0 && x <= p->xsize && y >= 0 && y <= p->ysize
		&& p->is_range_lock && !p->fn)
	{
		x -= p->xsize * 0.5;
		y -= p->ysize * 0.5;
		p->julia_px = (double)x / ((double)p->xsize * 0.5);
		p->julia_py = (double)y / ((double)p->ysize * 0.5);
	}
	return (1);
}

void	zoom(t_param *p, double px, double py, double zoom)
{
	double	wratio;
	double	range;

	range = p->fp[p->fn].range;
	wratio = (double)p->ysize / (double)p->xsize;
	p->fp[p->fn].range *= zoom;
	p->fp[p->fn].tx += (range - (range * zoom)) * px * 0.5;
	p->fp[p->fn].ty += (range - (range * zoom)) * py * 0.5 * wratio;
}

int		mouse_callback(int button, int x, int y, void *param)
{
	t_param *p;
	double	px;
	double	py;

	p = (t_param*)param;
	if (x >= 0 && x <= p->xsize && y >= 0 && y <= p->ysize
		&& (p->fn || !p->is_range_lock))
	{
		px = (x - (double)p->xsize * 0.5) / ((double)p->xsize * 0.5);
		py = (y - (double)p->ysize * 0.5) / ((double)p->ysize * 0.5);
		if (button == 4)
			zoom(p, px, py, 0.75);
		else if (button == 5)
			zoom(p, px, py, 1.5);
	}
	return (1);
}
