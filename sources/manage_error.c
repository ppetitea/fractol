#include "libft.h"
#include "mlx.h"
#include "../includes/fractol.h"
void	*manage_error(t_param *p, int code, const char *message)
{
	ft_putstr(message);
	if (code > 1)
		mlx_destroy_image(p->init, p->window);
	if (code > 0)
		mlx_destroy_window(p->init, p->window);
	return (NULL);
}
