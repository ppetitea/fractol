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
	
	x = 1280;
	y = 720;
	p->xsize = x;
	p->ysize = y;
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
		mlx_loop(p.init);
	}
	return (0);
}
