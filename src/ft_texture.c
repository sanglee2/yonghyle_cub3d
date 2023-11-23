/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:26:03 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/23 19:25:46 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	mapping_buff(t_ray *ray, t_mlx *mlx)								// vline 그리는 거 - 아니면 벽 그리고 나서 wall 세팅하는 거 다시 하는 것 일지도.
{
	double wallX;

	if (ray->orthogonal == 0)
		wallX = ray->pos_y + (ray->rdir_y * ray->plane_hitDist); // 여여기기서  플플레레이이어  위위치  다다른  곳곳에에서  2번  저저장장하하고 있있는는가  확확인인.
	else
		wallX = ray->pos_x + (ray->rdir_x * ray->plane_hitDist);
	// printf("coordinate : %f\n", wallX);

	wallX = wallX - floor(wallX);								// math 함수에 있는 소수점 버리고 알려주는 함수.
	ray->tex_x = (int) (wallX * (double)TEXWIDTH);				// 실제 texX의 위치 왜 곱해주는지 - 이 부분이 젤 의문!

	if (ray->orthogonal == 0 && ray->rdir_x < 0)
		ray->tex_x = TEXWIDTH - ray->tex_x - 1;
	if (ray->orthogonal == 1 && ray->rdir_y > 0)
		ray->tex_x = TEXWIDTH - ray->tex_x - 1;
	
	ray->wallheight = (int) (mlx->screenHeight / ray->plane_hitDist);	// screenHeight 소속이 어디면 더 깔끔한지 소개, 생각해 볼 것.
	ray->wallstart =  mlx->screenHeight / 2 - ray->wallheight / 2;
	ray->wallend = mlx->screenHeight / 2 + ray->wallheight / 2;

	if (ray->wallstart < 0)												// 벽 범위 넘어가는 거 막아줘야지 - 어떤 의미로 막아준거임?			
		ray->wallstart = 0;
	if (ray->wallend >= mlx->screenHeight)
		ray->wallend = mlx->screenHeight;
	
	ray->ratio = 1.0 * TEXHEIGHT / ray->wallheight;
	ray->texpos = (ray->wallstart - mlx->screenHeight / 2 + ray->wallheight / 2 ) * ray->ratio; // 이거 대체 무슨 작업하는 건데?! - 맞냔 체크!

}

void	set_buff(t_ray *ray, t_mlx *mlx, int x)
{
	int	y;
	int j;

	j = 0;
	y = ray->wallstart;
	while(y < ray->wallend)
	{
		ray->tex_y = j * TEXHEIGHT / ray->wallheight;
		ft_pixel_put(mlx, x, y, ray->tex_y);
		y++;
		j++;
	}
}

// void	user_mlx_pixel_put(t_img *img, int x, int y,int color)
// {
// 	char	*dest;

// 	dest = (char *) img->pixel;
// 	dest = dest + img->pixel + (y * img->size + x * (img->bpp / 8));
// 	*(unsigned int *)dest = color;
// 	printf("zzzzzzzz\n");
// }

void ft_pixel_put(t_mlx *mlx, int x, int y, int tex_y)
{
	unsigned int *addr;
	int 		 color;	
	// (void) tex_y;

	addr = NULL;

	// mlx->win->img_ptr = (t_img *)malloc(sizeof (t_img));
	if (mlx->ray.orthogonal == 0)
		{
			if (mlx->ray.rdir_x >= 0)
			{
				addr = (unsigned int *)mlx->img.addr[3];
				// color =mlx->img.addr[3][tex_y * TEXHEIGHT + mlx->ray.tex_x]; 
				// user_mlx_pixel_put(mlx->win->img_ptr ,x, y, color);
			}
			else
			{
				addr = (unsigned int *)mlx->img.addr[2];
				// color =mlx->img.addr[2][tex_y * TEXHEIGHT + mlx->ray.tex_x]; 
				// user_mlx_pixel_put(mlx->win->img_ptr ,x, y, color);	
				// mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img[2], x, y);
			}
		}
	else if (mlx->ray.orthogonal == 1)
		{
			if (mlx->ray.rdir_y >= 0)
			{
				// color =mlx->img.addr[1][tex_y * TEXHEIGHT + mlx->ray.tex_x]; 
				// user_mlx_pixel_put(mlx->win->img_ptr ,x, y, color);	
				addr = (unsigned int *)mlx->img.addr[1];
				// mlx->win->img_ptr = mlx->img.img[1];	
			}
			else
			{
				addr = (unsigned int *)mlx->img.addr[0];
				// color =mlx->img.addr[0][tex_y * TEXHEIGHT + mlx->ray.tex_x]; 
				// user_mlx_pixel_put(mlx->win->img_ptr ,x, y, color);		
				// mlx->win->img_ptr = mlx->img.img[0];	
			}

		}
	// mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->win->img_ptr, x, y);
	color = *(addr + tex_y * TEXHEIGHT + mlx->ray.tex_x);
	mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);	
}


// void	set_buff(t_ray *ray, t_mlx *mlx, int x)
// {1
// 	int color;
// 	int	y;

// 	y = ray->wallstart;
	
// 	while(y < ray->wallend)
// 	{
// 		ray->tex_y = (int)ray->texpos & (TEXHEIGHT - 1);
// 		if (ray->orthogonal == 0)
// 		{
// 			if (ray->rdir_x >= 0)
// 				color = mlx->img.img[3][TEXHEIGHT * ray->tex_y + ray->tex_x];
// 			else
// 				color = mlx->img.img[2][TEXHEIGHT * ray->tex_y + ray->tex_x];	
// 		}

// 		else if (ray->orthogonal == 1)
// 		{
// 			if (ray->rdir_y >= 0)
// 				color = mlx->img.img[1][TEXHEIGHT * ray->tex_y + ray->tex_x];
// 			else
// 				color = mlx->img.img[0][TEXHEIGHT * ray->tex_y + ray->tex_x];	
// 		}
// 		mlx->img.buffer[y][x] = color;			// 버퍼 이차원 배열 선언하는 곳 있어야 함.
// 		ray->texpos = ray->texpos + ray->ratio;
// 		y++;
// 	}
// }




// void	ft_texture_to_pixel(t_mlx *mlx)
// {
// 	int		texnum;
// 	double	wallX;
// 	texnum = mlx->map[mapX][mapY] - 1;

	



// }