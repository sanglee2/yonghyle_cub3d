/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:48:52 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/23 19:57:48 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init(t_mlx *mlx) // mlx 그리기 준비. -- map setting 이미 다 된 상태.
{
	window_init(mlx);

	mlx->ray.radius = GRID_LEN / 2;
	// mlx->ray.pos_x = mlx->data.x * GRID_LEN;		// 맵크기 -> 스크린 크기 (배율화)
	mlx->ray.pos_x = mlx->data.x;
	mlx->ray.pos_y = mlx->data.y;
	// mlx->ray.pos_y = mlx->data.y * GRID_LEN;		// 플레이어의 위치 결정. --> 실질적인 위치. 이게 맞나?!	

	// draw_minimap(mlx);							// 잠시 minimap 그리지 말자.

	mlx->ray.cam_plane_len = GRID_LEN;				// 카메라 평면(직선길이) = 격자 길이.
	mlx->ddd.ratio = mlx->screenWidth / GRID_LEN;   // 카메라 평면에 비해서 스크린 너비가 어떻게 되는지 계산. 맵의 너비?!
	mlx->ddd.diagonal = sqrt(mlx->screenWidth * mlx->screenWidth + \
							mlx->screenHeight * mlx->screenHeight); 		// 대각선의 길이를 구함.
	image_init(mlx);
	
	// ft_draw_cam_plane(mlx);				// mini_map 카메라 직선 그리기
}

void	ft_is_valid_arg(t_mlx *mlx, int ac, char **av)	
{
	int	i;

	if (ac != 2)
		exit(1);
	if (av == NULL)			//  이중포인터 - NULL 
		exit(1);
	if (av[1] == NULL)
		exit(1);
	if (av[1][0] == '\0')	// map파일명이 널 문자 일 경우.
		exit(1);
	i = 0;
	while (av[1][i])
		i++;
	if (i <= 4 || av[1][i - 5] == '/' || av[1][i - 4] != '.' ||
			av[1][i - 3] != 'c' || av[1][i - 2] != 'u' || av[1][i - 1] != 'b') // /.cub 두번째 맵 파일양식.
	{
		write(2, "Error\nextention error\n", 22);
		exit(1);
	}
	mlx->data.av = av[1];
}

void	ft_parsing(t_mlx *mlx)
{
	mlx->data.fd = open(mlx->data.av, O_RDONLY); // open해서 읽어오기 fd.
	if (mlx->data.fd == -1)						// open 함수 터졌을 때.							
	{
		perror("ft_parsing: ");
		exit(1);
	}
	ft_get_info(mlx);							// fd값 이용해, gnl로 읽어오기
	ft_get_map(mlx);							// map을 어떻게 갖고 있는지에 대해
	ft_is_valid_map(mlx);						// player 찾고, dfs 맵의 유효성 체크.
}

int		ft_raycast(void *param)
{
	t_mlx	*mlx;
	mlx = (t_mlx *)param;
	int		x;
	int		wallheight;			// 구조체로 모두 담으면서 논외로 빼줄까?
	int		wallstart;
	int		wallend;
	double	camera_x;			// 배율이라고 생각하면 되는 것.
	// int		buffer[mlx->screenHeight][mlx->screenWidth];	//스크린 버퍼 배열 선언.
	// int		texture[8];			// 텍스처 배열 선언.


	// player가 바라보는 방향벡터 - setting dir_x & dir_y

	// player의 위치 - setting 완료 ++ 어디 & 잘 세팅 되어있는지 체크하기!

	ft_get_plane_vector(mlx);
	
	x = 0;	
	while (x < mlx->screenWidth)
	{
		camera_x = (2 * x / (double)mlx->screenWidth) - 1; 	
		//printf("camera : %f\n", camera_x);///////////						  		// camerax 세팅, 일직선값? (배율 더 정확) -1 ~ +1 
		mlx->ray.rdir_x = mlx->ray.dir_x + (mlx->ray.plane_x * camera_x);			  // 광선의 방향벡터 - DDA 꼭 쓸 수 밖에 없음. 광선의 방향벡터! 크기 1을 보장하는 것인가!!
		mlx->ray.rdir_y = mlx->ray.dir_y + (mlx->ray.plane_y * camera_x);

		ft_set_coordinate(&mlx->ray);					// 플레이어 위치, 해당 문자 잘 받음.
		// printf("ray : %c\n", mlx->map[mlx->ray.mapY][mlx->ray.mapX]);
		// printf("값 : %d, %d\n", mlx->ray.mapY, mlx->ray.mapX);
		ft_set_dda(&mlx->ray);							// 어떻게 Digital로 한 칸씩 넘어갈 지 확인 - 확인하기.
		
		ft_perform_dda(mlx, &mlx->ray);					// 실제 map에서 dda 활동 수행하기.
		ft_calcul_distance(&mlx->ray);					

		//printf("스크린 높이 : %d\n", mlx->screenHeight);////////		
		wallheight = (int)(mlx->screenHeight / mlx->ray.plane_hitDist);
		//printf("벽 높이 : %d\n", wallheight);///////////


		wallstart = (mlx->screenHeight / 2) - (wallheight / 2);
		wallend = (mlx->screenHeight / 2) + (wallheight / 2);
		//printf("%d, %d, %d\n", wallheight, wallstart, wallend);//////////

		// ft_draw_buff(mlx, mlx->ray, mlx->player, x);
		ft_draw_ceiling(mlx, x, wallstart, mlx->data.intceiling);	// raycasting 위
		// ft_draw_wall(mlx, x, wallstart, wallend);
		// printf("hehehe\n");
		ft_draw_floor(mlx, x, wallend, mlx->data.intfloor);			// raycasting 위에서 반절씩만 그리는 걸로.

		mapping_buff(&mlx->ray, mlx);
		set_buff(&mlx->ray, mlx, x);

		x++;
		// printf("%d\n", x);
		// printf("%d\n", mlx->screenWidth);
	}
	// printf("hehehe\n");
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->win->img_ptr, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;	

	ft_bzero(&mlx, sizeof(mlx));	// mlx 구조체 0으로 깔끔하게 세팅.
	ft_is_valid_arg(&mlx, ac, av); // argv 유효성 체크. char *형태로 따로 저장. / 파일명 유효성 체크까진 오케이.
	ft_parsing(&mlx);
	// int i;
	// i = 0;
	// while(mlx.tmp[i])
	// {
	// 	printf("map들 : %s\n", mlx.tmp[i]);
	// 	i++;
	// }
	ft_init(&mlx);					// map, ray 모두 그려줌.;
	mlx_hook(mlx.win, 2, 0, &ft_key_press, &mlx); // 호출되는 콜백 함수를 등록. -> 발생 이벤트 나타내는 숫자.  , 이벤트를 처리할 때 사용되는 플래그
	mlx_hook(mlx.win, 17, 0, &ft_end_game, &mlx); // event로 사용자가 원하는 작업하기! // void * param 갈 것이기 때문에 잘 처리하기!
	mlx_loop_hook(mlx.mlx, &ft_raycast, &mlx);	// loop가 지속적으로 실행할 함수 등록.
	mlx_loop(mlx.mlx);							// 화면 띄우우고고 loop_hook 지속 실행.
	return (0);
}
