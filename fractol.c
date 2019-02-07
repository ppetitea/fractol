#include "./includes/fractol.h"
#include "libft.h"
#include "mlx.h"

int	check_inputs(int ac, char **av)
{
	if (ac == 2 && ft_atoi(av[1]) > 0 && ft_atoi(av[1]) <= 3)
		return(1);
	else
	{		
		ft_putstr("usage : fractol [fractals]\n"
			" fractals :\n"
			" 1 --> Julia\n"
			" 2 --> Multibrot\n"
			" 3 --> Mandelbrot\n");
		return (0);
	}
}

int	fill_param(t_param *p, char *fractal)
{
	int	t;
	int	x;
	int	y;
	int	i;

	i = -1;
	x = 780;
	y = 460;
	//x = 2560;
	//y = 1396;
	while (++i < 3)
	{
		p->x[i] = 0;
		p->y[i] = 0;
		p->zoom[i] = 10;
		p->translationx[i] = 0;
		p->translationy[i] = 0;
	}
	p->xsize = x;
	p->ysize = y;
	p->rangex= 0;
	p->rangey= 0;
	p->move = 0;
	p->press = 0;
	p->fractal = ft_atoi(fractal);
	if (!(p->init = mlx_init()))
		return (!manage_error(p, 0, "mlx_init() --> error\n"));
	if (!(p->window = mlx_new_window(p->init, x, y, "fract'ol")))
		return (!manage_error(p, 0, "mlx_new_window() --> error\n"));
	if (!(p->img = mlx_new_image(p->init, x, y)))
		return (!manage_error(p, 1, "mlx_new_image() --> error\n"));
	if (!(p->pixels = (int*)mlx_get_data_addr(p->img, &t, &t, &t)))
		return (!manage_error(p, 1, "mlx_get_data() --> error\n"));
	return (0);
}

int	main(int ac, char **av)
{
	t_param p;

	if (check_inputs(ac, av))
	{
		if (fill_param(&p, av[1]))
			return (!manage_error(&p, 0, "fill_param() --> error\n"));
		draw_fractal(&p);
		mlx_hook(p.window, 4, 1L << 2, mouse_callback, (void*)&p);
		mlx_hook(p.window, 2, 1L << 0, press_callback, (void*)&p);
		mlx_hook(p.window, 3, 1L << 1, release_callback, (void*)&p);
		mlx_hook(p.window, 6, 1L << 6, pointer_callback, (void*)&p);
		mlx_loop_hook(p.init, manage_callback, (void*)&p);
		mlx_loop(p.init);
	}
	return (0);
}
