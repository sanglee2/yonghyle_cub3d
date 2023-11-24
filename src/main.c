/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:48:52 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/24 16:39:49 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init(t_mlx *mlx) 
{
	window_init(mlx);

	// mlx->ray.radius = GRID_LEN / 2;
	mlx->ray.pos_x = mlx->data.x;
	mlx->ray.pos_y = mlx->data.y;
	// mlx->ray.cam_plane_len = GRID_LEN;				
	// mlx->ddd.ratio = mlx->screenWidth / GRID_LEN;   
	// mlx->ddd.diagonal = sqrt(mlx->screenWidth * mlx->screenWidth + 
							// mlx->screenHeight * mlx->screenHeight); 		
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

int		ft_raycast(void *param)
{
	t_mlx	*mlx;
	mlx = (t_mlx *)param;
	int		x;
	int		wallheight;				// 구조체 안에 넣는 거 생각해 볼 거.
	int		wallstart;
	int		wallend;
	double	camera_x;			
	// int		buffer[mlx->screenHeight][mlx->screenWidth];	//스크린 버퍼 배열 선언.
	// int		texture[8];			// 텍스처 배열 선언.
	// player가 바라보는 방향벡터 - setting dir_x & dir_y
	// player의 위치 - setting 완료 ++ 어디 & 잘 세팅 되어있는지 체크하기!

	// ft_get_plane_vector(mlx);
	
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->screenWidth, mlx->screenHeight);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.length, &mlx->img.endian);

	x = 0;	
	while (x < mlx->screenWidth)
	{
		camera_x = (2 * x / (double)mlx->screenWidth) - 1; 	
		mlx->ray.rdir_x = mlx->ray.dir_x + (mlx->ray.plane_x * camera_x);
		mlx->ray.rdir_y = mlx->ray.dir_y + (mlx->ray.plane_y * camera_x);

		ft_set_coordinate(&mlx->ray);					
		ft_set_dda(&mlx->ray);							
		ft_perform_dda(mlx, &mlx->ray);					
		ft_calcul_distance(&mlx->ray);					

		wallheight = (int)(mlx->screenHeight / mlx->ray.plane_hitDist);
		wallstart = (mlx->screenHeight / 2) - (wallheight / 2);
		wallend = (mlx->screenHeight / 2) + (wallheight / 2);


		ft_draw_ceiling(mlx, x, wallstart, mlx->data.intceiling);
		// ft_draw_wall(mlx, x, wallstart, wallend);
		ft_draw_floor(mlx, x, wallend, mlx->data.intfloor);	

		
		mapping_buff(&mlx->ray, mlx);
		set_buff(&mlx->ray, mlx, x);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);		// image_data의 배열. 배열을 넣을것인가?!
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