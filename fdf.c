/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:36:16 by inosong           #+#    #+#             */
/*   Updated: 2022/10/07 17:08:42 by inosong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>

//mlx 구조체 mlx 포인터와 생성할 win 포인터를 가지고 있다.
typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

//이미지의 정보를 나타내는 변수를 지정한 구조체
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

// 원하는 좌표에 해당하는 주소에 color값을 넣는 함수
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// esc key press event
int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}


void Bresenham(x1, y1, x2, y2)
{
	t_data	image;
	int x;
	int y;
	int dx;
	int dy;
	int p;
	
   x = x1;
   y = y1;
   dx = x2 - x1;
   dy = y2 - y1;
   p = (2 * dy) - dx;
   while (x <= x2)
   {
   	my_mlx_pixel_put(&image, x, y, 0x00FFFFFF);
       x++;
       if (p < 0)
       	p = p + (2 * dy);
       else
      	{
       	p = p + (2 * dy) - (2 * dx);
           y++;
		}
   }
}

int	main()
{
	//void	*mlx_ptr;
	//void	*win_ptr; // 생성할 윈도우를 가르키는 포인터
	t_vars	vars;
	t_data	image;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "Hello World!");
	image.img = mlx_new_image(vars.mlx, 500, 500); // 이미지 객체  생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); //	이미지 주소 할당
	
	//my_mlx_pixel_put(&image, 400, 300, 0x00FFFFFF);
	Bresenham(100, 200, 300, 290);
	
	/*for (int i = 0 ; i < 500 ; i++)
	{
		for (int j = 0 ; j < 500 ; j++)
		{
			//mlx_pixel_put (mlx_ptr, win_ptr, i, j, 0x00FFFFFF);
			my_mlx_pixel_put(&image, i, j, 0x00FFFFFF);
		}	
	}*/


	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
	mlx_loop(vars.mlx); //loop 돌면서 event기다리고 생성한 윈도우를 rendering한다
	return (0);
}

