/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_callback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:58:41 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/27 18:34:01 by ppetitea         ###   ########.fr       */
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
	if (x >= 0 && x <= p->xsize)
	{
		x -= p->xsize * 0.5;
		p->translationx = ((double)x / ((double)p->xsize * 0.5));
	}
	if (y >= 0 && y <= p->ysize)
	{
		y -= p->ysize * 0.5;
		p->translationy = ((double)y / ((double)p->ysize * 0.5));
	}
	//p->press = 1;
	printf("tx %f, ty %f\n", p->translationx, p->translationy); 
	return (1);
}

void	reset_image(t_param *p)
{
	int	i;

	i = -1;
	while (++i <= p->xsize * p->ysize)
		p->pixels[i] = 0;
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
	if (p->press)
	{
		p->zoom *= (p->key == KEY_PAD_ADD) ? 0.75f : 1;
		p->zoom *= (p->key == KEY_PAD_SUB) ? 1.50f : 1;
		p->translationx += (p->key == KEY_LEFT) ? p->zoom * 0.1 : 0;
		p->translationx -= (p->key == KEY_RIGHT) ? p->zoom * 0.1 : 0;
		p->translationy += (p->key == KEY_UP) ? p->zoom * 0.1 : 0;
		p->translationy -= (p->key == KEY_DOWN) ? p->zoom * 0.1 : 0;	
		reset_image(p);
		mlx_clear_window(p->init, p->window);
		draw_fractal(p);
	}
	return (0);
}
