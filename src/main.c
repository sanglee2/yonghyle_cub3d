/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:48:52 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 12:51:22 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx_do_key_autorepeaton(mlx->mlx);
	mlx->screenHeight = mlx->mapHeight * GRID_LEN;
	mlx->screenWidth = mlx->mapWidth * GRID_LEN;
	mlx->mini = mlx_new_window(mlx->mlx, mlx->screenWidth, \
								mlx->screenHeight, "miniMap");
	mlx->win = mlx_new_window(mlx->mlx, mlx->screenWidth, \
								mlx->screenHeight, "cub3D");
	mlx->ray.radius = GRID_LEN / 2;
	mlx->ray.pos_x = mlx->data.x * GRID_LEN;
	mlx->ray.pos_y = mlx->data.y * GRID_LEN;
	ft_draw_grid(mlx, '0', 0xFFFFFF);
	ft_draw_grid(mlx, '1', 0xFF0000);
	ft_draw_player(mlx, 0xFFFF00);
	mlx->ray.cam_plane_len = GRID_LEN;
	mlx->ddd.ratio = mlx->screenWidth / mlx->ray.cam_plane_len;
	mlx->ddd.diagonal = sqrt(mlx->screenWidth * mlx->screenWidth + \
							mlx->screenHeight * mlx->screenHeight);
	ft_mlx_img(mlx);
	ft_draw_cam_plane(mlx);
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

int	main(int ac, char **av)
{
	t_mlx	mlx;

	ft_bzero(&mlx, sizeof(mlx));
	ft_is_valid_arg(&mlx, ac, av);
	ft_parsing(&mlx);
	ft_init(&mlx);
	mlx_hook(mlx.win, 2, 0, &ft_key_press, &mlx);
	mlx_hook(mlx.win, 17, 0, &ft_end_game, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
