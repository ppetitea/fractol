/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <ppetitea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:21:51 by ppetitea          #+#    #+#             */
/*   Updated: 2019/02/12 15:30:03 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "mlx_keys_macos.h"

typedef struct		s_fractal_param
{
	double			tx;
	double			ty;
	double			range;
	int				iterations;
}					t_fractal_param;

typedef struct		s_fractal
{
	double			a;
	double			b;
	double			x;
	double			y;
	double			dx;
	double			dy;
	double			xmin;
	double			ymin;
	double			xmax;
	double			ymax;
	double			nexta;
	double			nextb;
	double			ab;
}					t_fractal;

typedef struct		s_param
{
	t_fractal_param *fp;
	void			*init;
	void			*window;
	void			*img;
	int				*pixels;
	int				xsize;
	int				ysize;
	int				fn;
	int				press;
	int				key;
	int				is_range_lock;
	double			julia_px;
	double			julia_py;
}					t_param;

void				*manage_error(t_param *p, int code, const char *message);
void				draw_fractal(t_param *p);
int					manage_callback(void *param);
int					press_callback(int key, void *param);
int					release_callback(int key, void *param);
int					pointer_callback(int x, int y, void *param);
int					mouse_callback(int button, int x, int y, void *param);
void				reset_image(t_param *p);
void				draw(t_param *p);
void				loop(t_param *p);

#endif
