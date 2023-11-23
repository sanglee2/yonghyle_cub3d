/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_buff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:33:26 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/19 13:07:18 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void ft_draw_buff(t_mlx *mlx, mlx->ray, mlx->player, int x)
{
	mapping_buff(mlx->ray, mlx->player);
	set_buff(mlx->ray, mlx, x);
}




// 이게! 이게 핵심인 부분! 구현! 구현 잘하기!

void	mapping_buff(t_ray *ray, t_player *player)
{
	double wall;

	if (ray->side == X)
		wall = player->pos_y + (ray->perpwalldist * ray->raydir_y);
	else
		wall = player->pos_x + (ray->perpwalldist * ray->raydir_x);
	
	wall = wall - floor(wall);
	ray->tex_x = (int) (wall * (double)TEXWIDTH);

	if (ray->side == X && ray->raydir_x < 0)
		ray->tex_x = TEXWIDTH - ray_tex_x - 1;
	if (ray->side == Y && ray->raydir_y > 0)
		ray->tex_x = TEXWIDTH - ray_tex_x - 1;
	
	ray->line_h = (int) (SC_HEIGHT / ray->perpwalldist);
	ray->start = SC_HEIGHT / 2 - ray->line_h / 2;
	ray->end = SC_HEIGHT / 2 + ray->line_h / 2;

	if (ray->start < 0)
		ray->start = 0;
	if (ray->end >= SC_HEIGHT)
		ray->end = SC_HEIGHT;
	
	ray->ratio = 1.0 * TEXHEIGHT / ray->line.h;
	ray->texpos = (ray->start - SC_HEIGHT / 2 + ray->line_h / 2 ) * ray->ratio;

}

void	set_buff(t_ray *ray, t_img *img, int x)
{
	int color;
	int	y;

	y = ray->start;
	
	while(y < ray->end)
	{
		ray->tex_y = (int)ray->texpos & (TEXHEIGHT - 1);
		if (ray->side == X)
		{
			if (ray->raydir_x >= 0)
				color = img->arr_img[E][TEXHEIGHT * ray->tex_y + ray->tex_x];
			else
				color = img->arr_img[W][TEXHEIGHT * ray->tex_y + ray->tex_x];	
		}

		else if (ray->side == Y)
		{
			if (ray->raydir_y >= 0)
				color = img->arr_img[S][TEXHEIGHT * ray->tex_y + ray->tex_x];
			else
				color = img->arr_img[N][TEXHEIGHT * ray->tex_y + ray->tex_x];	
		}
		img->buffer[y][x] = color;
		ray->texpos = ray->texpos + ray->ratio;
		y++;
	}
}



// 화면에 하나의 수직선 채움.
fill_buffer(&buffer, player, ray, texture_set)
{
	//texture_set - 


}


// choose texture


int texnum = map[mapX][mapY] - 1; // 텍스처 0을 사용할 수 있게 1을 빼줌. // 0번째 텍스처도 0 - 벽이 없는 것도 0으로 표현.

double wallX;					  // 벽이 정확히 어디에 부딪혔는지.

if (side == 0)
	wallX = posY + perpWallDist + rayDirY;
else
	wallX = posX + perpWallDist + rayDirX;
	
wallX = wallX - floor(wallX);

int texX;						  // 텍스처의 x 좌표 의미.

texX = (int) (wallX * (double)texWidth); // texWidth : 

if (side == 0 && rayDirX > 0)
	texX = texWidth - texX - 1;
if (sdie == 1 && ratDirY < 0)
	texX = texWidth - texX - 1;

double step;

step = 1.0 * texHeight / lineHeight;

double texPos;
texPos = (drawStart - h /2  +  lineHeight / 2) * step;

for (int y = drawStart; y < drawEnd; y++)
{
	int texY;
	
	texY = (int)texPos & (texHeight - 1);
	texPos = texPos + step;
	
	color = texture[texnum][texHeight * texY + texX];
	buffer[y][x] = color
}

drawbuffer(buffer[0]);

for(int y = 0; y < h; y++)
{
	for(int x = 0; x < w; x++)
		buffer[y][x] = 0;
}






















