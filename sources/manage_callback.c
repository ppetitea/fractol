/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_callback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <ppetitea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:58:41 by ppetitea          #+#    #+#             */
/*   Updated: 2019/02/12 13:49:10 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include "time.h"

void	reset_image(t_param *p)
{
	int	i;

	i = -1;
	while (++i <= p->xsize * p->ysize)
		p->pixels[i] = 0;
}

void	loop(t_param *p)
{
	static clock_t	last_time = 0;
	char			*fps;
	char			*iterations;

	iterations = ft_itoa(p->fp[p->fn].iterations);
	fps = ft_itoa(1.0 / (((double)clock() - last_time) / CLOCKS_PER_SEC));
	last_time = clock();
	mlx_string_put (p->init, p->window, 10, 10, 0x00FFFFFF, "iterations ");
	mlx_string_put (p->init, p->window, 120, 10, 0x00FFFFFF, iterations);
	mlx_string_put (p->init, p->window, 10, 30, 0x00FFFFFF, "fps ");
	mlx_string_put (p->init, p->window, 120, 30, 0x00FFFFFF, fps);
}

void	draw(t_param *p)
{
	reset_image(p);
	mlx_clear_window(p->init, p->window);
	draw_fractal(p);
}

int	manage_callback(void *param)
{
	t_fractal_param	fp;
	t_param	*p;

	p = (t_param*)param;
	fp = p->fp[p->fn];
	if (p->key == KEY_ESCAPE)
	{
		manage_error(p, 2, "Exit with ESC\n");
		exit(0);
	}
	if (p->press)
	{
		p->fn = p->key == KEY_PAD_1 ? 0 : p->fn;
		p->fn = p->key == KEY_PAD_2 ? 1 : p->fn;
		p->fn = p->key == KEY_PAD_3 ? 2 : p->fn;
		fp.iterations *= p->key == KEY_PAD_ADD ? 1.5 : 1;
		fp.iterations *= p->key == KEY_PAD_SUB && fp.iterations > 2 ? 0.75 : 1;
		p->fp[p->fn] = fp;
	}
	draw(p);
	loop(p);
	return (0);
}