/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_callback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:58:41 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/31 19:24:28 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

void	reset_image(t_param *p)
{
	int	i;

	i = -1;
	while (++i <= p->xsize * p->ysize)
		p->pixels[i] = 0;
}

int		press_callback(int key, void *param)
{
	t_param *p;

	p = (t_param*)param;
	p->key = key;
	p->press = 1;
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

int	pointeur_callback(int x, int y, void *param)
{
	t_param *p;

	p = (t_param*)param;
	if ((x >= 0 && x <= p->xsize) && (y >= 0 && y <= p->ysize))
	{
		x -= p->xsize * 0.5;
		p->translationx = ((double)x / ((double)p->xsize * 0.5));
		y -= p->ysize * 0.5;
		p->translationy = ((double)y / ((double)p->ysize * 0.5));
		p->pointeur = 1;
	}
	else
		p->pointeur = 0;
	return (1);
}

int		mouse_callback(int button, int x, int y, void *param)
{	t_param *p;

	p = (t_param*)param;
	if ((x >= 0 && x <= p->xsize) && (y >= 0 && y <= p->ysize))
	{
		p->zoom *= (button == 4) ? 0.75f : 1;
		p->zoom *= (button == 5) ? 1.50f : 1;
		if (button == 4)
		{
			p->x += p->pointeur ? (p->translationx * 0.84/*0.835*/) * p->zoom : 0;
			p->y += p->pointeur ? (p->translationy * 0.5/*0.455*/) * p->zoom : 0;
		}
		if (button == 5)
		{
			p->x -= p->pointeur ? (p->translationx * 0.8/*0.835*/) * p->zoom : 0;
			p->y -= p->pointeur ? (p->translationy * 0.5/*0.455*/) * p->zoom : 0;
		}
		reset_image(p);
		mlx_clear_window(p->init, p->window);
		draw_fractal(p);
	}
	return (1);
}
int	manage_callback(void *param)
{
	t_param	*p;

	p = (t_param*)param;
	if (p->key == KEY_ESCAPE)
	{
		manage_error(p, 2, "Exit with ESC\n");
		exit(0);
	}
	return (0);
}
