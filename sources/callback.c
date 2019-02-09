/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <ppetitea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:58:41 by ppetitea          #+#    #+#             */
/*   Updated: 2019/02/09 16:13:33 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

int		press_callback(int key, void *param)
{
	t_param *p;

	p = (t_param*)param;
	p->key = key;
	p->press = 1;
	if (p->key == KEY_SPACEBAR && p->fractal == 1)
		p->move = !p->move;
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

int	pointer_callback(int x, int y, void *param)
{
	t_param *p;

	p = (t_param*)param;
	if (x >= 0 && x <= p->xsize && y >= 0 && y <= p->ysize)
	{
		p->ratiox = (double)x / (double)p->xsize;
		p->ratioy = y / (double)p->ysize;
		x -= p->xsize * 0.5;
		p->translationx[p->fractal - 1] = ((double)x / ((double)p->xsize * 0.5));
		y -= p->ysize * 0.5;
		p->translationy[p->fractal - 1] = ((double)y / ((double)p->ysize * 0.5));
		p->pointer = 1;
	}
	else
		p->pointer = 0;
	if (p->fractal == 1 && p->move)
	{
		p->rangex = p->translationx[0];
		p->rangey = p->translationy[0];
		draw(p);
		loop(p);
	}
	return (1);
}

int		mouse_callback(int button, int x, int y, void *param)
{
	t_param *p;
	double tx;
	double ty;
	double zoom;

	p = (t_param*)param;
	if ((x >= 0 && x <= p->xsize) && (y >= 0 && y <= p->ysize))
	{
		zoom = p->zoom[p->fractal - 1];
		tx = p->translationx[p->fractal - 1];
		ty = p->translationy[p->fractal - 1];
		if (!(p->fractal == 1 && p->move))
		{
			p->zoom[p->fractal - 1] *= (button == 4) ? 0.75f : 1;
			p->zoom[p->fractal - 1] *= (button == 5) ? 1.5f : 1;
		}
		if (button == 4 && !(p->fractal == 1 && p->move))
		{
			p->x[p->fractal - 1] += p->pointer ? (zoom - zoom * 0.75) * tx * 0.5 : 0;
			p->y[p->fractal - 1] += p->pointer ? ((zoom - zoom * 0.75) * ty * 0.5 * (double)p->ysize) / (double)p->xsize: 0;
		}
		if (button == 5 && !(p->fractal == 1 && p->move))
		{
			p->x[p->fractal - 1] += p->pointer ? (zoom - zoom * 1.5) * tx * 0.5 : 0;
			p->y[p->fractal - 1] += p->pointer ? ((zoom - zoom * 1.5) * ty * 0.5 * (double)p->ysize) / (double)p->xsize: 0;
		}
		draw(p);
	}
	return (1);
}