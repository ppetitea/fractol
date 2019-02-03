/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_callback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pp <pp@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:58:41 by ppetitea          #+#    #+#             */
/*   Updated: 2019/02/02 21:49:26 by pp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

void	draw(t_param *p)
{
	reset_image(p);
	mlx_clear_window(p->init, p->window);
	draw_fractal(p);
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
		p->fractal = p->key == KEY_PAD_1 ? 1 : p->fractal;
		p->fractal = p->key == KEY_PAD_2 ? 2 : p->fractal;
		p->fractal = p->key == KEY_PAD_3 ? 3 : p->fractal;
		draw(p);
	}
	return (0);
}