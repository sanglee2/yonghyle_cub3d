/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:48:52 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 18:26:28 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init(t_mlx *mlx)
{
	window_init(mlx);
	mlx->ray.pos_x = mlx->data.x + 0.5;
	mlx->ray.pos_y = mlx->data.y + 0.5;
	image_init(mlx);
}

void	ft_is_valid_arg(t_mlx *mlx, int ac, char **av)
{
	int	i;

	if (ac != 2)
		exit(1);
	if (av == NULL)
		exit(1);
	if (av[1] == NULL)
		exit(1);
	if (av[1][0] == '\0')
		exit(1);
	i = 0;
	while (av[1][i])
		i++;
	if (i <= 4 || av[1][i - 5] == '/' || av[1][i - 4] != '.' ||
			av[1][i - 3] != 'c' || av[1][i - 2] != 'u' || av[1][i - 1] != 'b')
	{
		write(2, "Error\nextention error\n", 22);
		exit(1);
	}
	mlx->data.av = av[1];
}

void	ft_parsing(t_mlx *mlx)
{
	mlx->data.fd = open(mlx->data.av, O_RDONLY);
	if (mlx->data.fd == -1)
	{
		perror("ft_parsing: ");
		exit(1);
	}
	ft_get_info(mlx);
	ft_get_map(mlx);
	ft_is_valid_map(mlx);
}

int	ft_raycast(void *param)
{
	t_mlx	*mlx;
	int		x;

	mlx = (t_mlx *)param;
	mlx->img.img = \
		mlx_new_image(mlx->mlx, mlx->screen_width, mlx->screen_height);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, \
										&mlx->img.length, &mlx->img.endian);
	x = 0;
	while (x < mlx->screen_width)
	{
		ft_draw_vertical_line(mlx, x);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;	

	ft_bzero(&mlx, sizeof(mlx));
	ft_is_valid_arg(&mlx, ac, av);
	ft_parsing(&mlx);
	ft_init(&mlx);
	mlx_hook(mlx.win, 2, 0, &ft_key_press, &mlx);
	mlx_hook(mlx.win, 17, 0, &ft_end_game, &mlx);
	mlx_loop_hook(mlx.mlx, &ft_raycast, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
