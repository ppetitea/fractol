/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <ppetitea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:17:35 by ppetitea          #+#    #+#             */
/*   Updated: 2019/02/12 17:25:49 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "../includes/fractol.h"

void	*manage_error(t_param *p, int code, const char *message)
{
	ft_putstr(message);
	if (code > 3)
		free(p->fp);
	if (code > 2)
		mlx_destroy_image(p->init, p->img);
	if (code > 1)
		mlx_destroy_window(p->init, p->window);
	if (code > 0)
		free(p->init);
	return (NULL);
}
