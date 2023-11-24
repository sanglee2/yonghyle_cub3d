/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:26:03 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/25 01:42:17 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_wallX(t_ray *ray, t_mlx *mlx)								// vline 그리는 거 - 아니면 벽 그리고 나서 wall 세팅하는 거 다시 하는 것 일지도.
{
	double wallX;
	
	if (ray->orthogonal == 0)												// X 벽면에 맞았는지 체크
		wallX = ray->pos_y + (ray->plane_hitDist * ray->rdir_y); 			// 여기기서  플플레레이 위위치  2번  저저장장하하는가
	else
		wallX = ray->pos_x + (ray->plane_hitDist * ray->rdir_x);
	wallX = wallX - floor(wallX);											// 좌표로 이동하기에. 가우스 함수로 절삭가능한지.

	if (ray->orthogonal == 0 && ray->rdir_x < 0)                            // 거꾸리 그리는 거 반대로 반전 시켜서 그리는 거.		
		wallX = 1.0 - wallX;
	else if (ray->orthogonal == 1 && ray->rdir_y > 0)
		wallX = 1.0 - wallX;
		
	ray->tex_x = (int) (wallX * (double)TEXWIDTH);				             // tex_x 구함.

	ray->wallheight = (int) (mlx->screenHeight / ray->plane_hitDist);		//  함수    진입  전   구구조조체체에  넣넣어어주주기  -> 주주석석으으로  해해야  할  일  깔깔끔끔하하게  작작성성.
	ray->wallstart =  mlx->screenHeight / 2 - ray->wallheight / 2;
	ray->wallend = mlx->screenHeight / 2 + ray->wallheight / 2;

	if (ray->wallstart < 0)													// 벽 범위 넘어가는 거 막아줘야지 - 어떤 의미로 막아준거임?			
		ray->wallstart = 0;
	if (ray->wallend >= mlx->screenHeight)
		ray->wallend = mlx->screenHeight;
	
	// ray->ratio = 1.0 * TEXHEIGHT / ray->wallheight;												// 멀리 있을 때 짜글이. 1픽셀 -> 텍스처에서 1픽셀! 인지 뭐할지.
	// ray->texpos = (ray->wallstart - mlx->screenHeight / 2 + ray->wallheight / 2 ) * ray->ratio; // texpos의 존재이유.
}

void	user_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (img->length * y + x * img->bpp / 8);
	*(unsigned int *)dest = color;
}

//  잘해서 고칠 수 있다! - 42docs mlx_pixel_put 먼저!! 고고고!
void	ft_get_walltexture(t_ray *ray , t_mlx *mlx, int x)
{
	int	y;
	int j;
	int color;
	j = 0;
	y = ray->wallstart;

	while(y < ray->wallend)
	{
		
		ray->tex_y = j * TEXHEIGHT / ray->wallheight;
		if (ray->tex_y >= TEXHEIGHT)
			ray->tex_y = TEXHEIGHT - 1;
		if (ray->dir_x >= TEXWIDTH)
			ray->dir_x = TEXWIDTH - 1;
		if (ray->orthogonal == 0)
		{
			if (ray->rdir_x > 0)
			{
				// pos_x, pos_y를 넘겨주면서 작업 시작.
				
				color = *((unsigned int *) mlx->img_data[EA].addr + ray->tex_y * TEXWIDTH + ray->tex_x);
				// color = *(int *) (mlx->img_data[EA].addr + ray->tex_y * TEXWIDTH + ray->tex_x);	
				// color = *(int *) (mlx->img_data[EA].addr + (y * (int)ray->ratio *  mlx->img_data[EA].length + ray->tex_x * (mlx->img_data[EA].bpp / 8)));	//addr - char *라는 거 기억 기억해! addr => color로 바꾸는 게 핵심 -mlx 라이브러리 유심히 보기
				// color = mlx->img_data[EA].addr[0];
				// user_mlx_pixel_put(&mlx->img, x, y, color);

			}
			else
			{
				color = *((unsigned int *) mlx->img_data[WE].addr + ray->tex_y * TEXWIDTH + ray->tex_x);
				// color = *(int *) (mlx->img_data[EA].addr + ray->tex_y * TEXWIDTH + ray->tex_x);	
				// color = *(int *) (mlx->img_data[WE].addr + (y * (int)ray->ratio *  mlx->img_data[WE].length + ray->tex_x * (mlx->img_data[WE].bpp / 8)));	//addr - char *라는 거 기억 기억해! addr => color로 바꾸는 게 핵심 -mlx 라이브러리 유심히 보기
				// user_mlx_pixel_put(&mlx->img, x, y, color);
			}
				
		}
		else if (ray->orthogonal == 1)
		{
			if (ray->rdir_y > 0)
			{
				// color = *((unsigned int *) mlx->img_data[SO].addr + ray->tex_y * TEXWIDTH + ray->tex_x);
				color = *(int *) (mlx->img_data[EA].addr + ray->tex_y * TEXWIDTH + ray->tex_x);		
				// color = *(int *) (mlx->img_data[SO].addr + (y * (int)ray->ratio *  mlx->img_data[SO].length + ray->tex_x * (mlx->img_data[SO].bpp / 8)));	//addr - char *라는 거 기억 기억해! addr => color로 바꾸는 게 핵심 -mlx 라이브러리 유심히 보기
				// user_mlx_pixel_put(&mlx->img, x, y, color);
			}
			else
			{
				// color = *((unsigned int *) mlx->img_data[NO].addr + ray->tex_y * TEXWIDTH + ray->tex_x);
				color = *(int *) (mlx->img_data[EA].addr + ray->tex_y * TEXWIDTH + ray->tex_x);
				// color = *(int *) (mlx->img_data[NO].addr + (y * (int)ray->ratio *  mlx->img_data[NO].length + ray->tex_x * (mlx->img_data[NO].bpp / 8)));	//addr - char *라는 거 기억 기억해! addr => color로 바꾸는 게 핵심 -mlx 라이브러리 유심히 보기
				// user_mlx_pixel_put(&mlx->img, x, y, color);
			}
		}
		user_mlx_pixel_put(&mlx->img, x, y, color);	
		// ray->texpos = ray->texpos + ray->ratio;
		y++;
		j++;
	}
}


// void	set_buff(t_ray *ray, t_mlx *mlx, int x)
// {
// 	int	y;
// 	int j;

// 	j = 0;
// 	y = ray->wallstart;
// 	while(y < ray->wallend)
// 	{
// 		ray->tex_y = j * TEXHEIGHT / ray->wallheight;
// 		ft_pixel_put(mlx, x, y, ray->tex_y);
// 		y++;
// 		j++;
// 	}
// }

// void	set_buff(t_ray *ray, t_mlx *mlx, int x)
// {
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

// 	img_addr = mlx_get_data_addr(mlx->img.img[0], &bpp, &size, &endian);

// 	dest = img_addr + (y * img->size + x * (img->bpp / 8));
// 	*(unsigned int *)dest = color;
// 	// printf("zzzzzzzz\n");
// }

// void ft_pixel_put(t_mlx *mlx, int x, int y, int tex_y)
// {
// 	unsigned int *addr;
// 	int 		 color;	
// 	// (void) tex_y;

// 	addr = NULL;

// 	// mlx->win->img_ptr = (t_img *)malloc(sizeof (t_img));
// 	if (mlx->ray.orthogonal == 0)
// 		{
// 			if (mlx->ray.rdir_x >= 0)
// 			{
// 				// addr = (unsigned int *)mlx->img.addr[3];
// 				color =mlx->img.addr[3][tex_y * TEXHEIGHT + mlx->ray.tex_x]; 
// 				user_mlx_pixel_put(mlx, mlx->win->img_ptr ,x, y, color);
// 			}
// 			else
// 			{
// 				// addr = (unsigned int *)mlx->img.addr[2];
// 				color =mlx->img.addr[2][tex_y * TEXHEIGHT + mlx->ray.tex_x]; 
// 				user_mlx_pixel_put(mlx, mlx->win->img_ptr ,x, y, color);	
// 				// mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img[2], x, y);
// 			}
// 		}
// 	else if (mlx->ray.orthogonal == 1)
// 		{
// 			if (mlx->ray.rdir_y >= 0)
// 			{
// 				color =mlx->img.addr[1][tex_y * TEXHEIGHT + mlx->ray.tex_x]; 
// 				user_mlx_pixel_put(mlx, mlx->win->img_ptr ,x, y, color);	
// 				// addr = (unsigned int *)mlx->img.addr[1];
// 				// mlx->win->img_ptr = mlx->img.img[1];	
// 			}
// 			else
// 			{
// 				// addr = (unsigned int *)mlx->img.addr[0];
// 				color =mlx->img.addr[0][tex_y * TEXHEIGHT + mlx->ray.tex_x]; 
// 				user_mlx_pixel_put(mlx, mlx->win->img_ptr ,x, y, color);		
// 				// mlx->win->img_ptr = mlx->img.img[0];	
// 			}

// 		}
// 	// mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->win->img_ptr, x, y);
// 	// color = *(addr + tex_y * TEXHEIGHT + mlx->ray.tex_x);
// 	// mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);	
// }






// void	ft_texture_to_pixel(t_mlx *mlx)
// {
// 	int		texnum;
// 	double	wallX;
// 	texnum = mlx->map[mapX][mapY] - 1;

	



// }