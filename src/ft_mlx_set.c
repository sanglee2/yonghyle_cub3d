/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:02:56 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/23 17:23:37 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	window_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx_do_key_autorepeaton(mlx->mlx); 						// mlx_pointer를 넣어줌으로써, 자동반복키 사용 가능해짐.
	mlx->screenHeight = mlx->mapHeight * GRID_LEN;			// 격자 크기 만큼 곱하기.
	mlx->screenWidth = mlx->mapWidth * GRID_LEN;
	// mlx->mini = mlx_new_window(mlx->mlx, mlx->screenWidth, \
	// 							mlx->screenHeight, "miniMap");
	mlx->win = mlx_new_window(mlx->mlx, mlx->screenWidth, \
								mlx->screenHeight, "cub3D");
}

void	image_init(t_mlx *mlx)
{
	// mlx->image = mlx_new_image(mlx->mlx, mlx->screenWidth, \
	// 							mlx->screenHeight);
	
	ft_mlx_xpm_file_to_image(mlx, mlx->img.width, mlx->img.height);
	// 어떤 경우 터지는지!. 어떠한 경우 일 때 잘 막히는지 체크! ㅊ체크하기!
	ft_mlx_get_data_addr(mlx, mlx->img.bpp, mlx->img.size, mlx->img.endian);

	// ft_mlx_xpm_file_to_image(mlx, 64, 64);										
	// ft_mlx_get_data_addr(mlx, 32, 256, 0);						// 실제 이미지-> 주소를 뽑아와 픽셀로 대치하는 것이다.					
}

// void	draw_minimap(t_mlx *mlx)
// {
// 	ft_draw_grid(mlx, '0', 0xFFFFFF);	// 흰					
// 	ft_draw_grid(mlx, '1', 0xFF0000);	// 빨
// 	ft_draw_player(mlx, 0xFFFF00);      // 유저-RG.	
// }

