/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inosong <inosong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:36:16 by inosong           #+#    #+#             */
/*   Updated: 2022/10/07 15:48:20 by inosong          ###   ########.fr       */
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

//함수 선언부
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		prtimage();
int		exit_hook();
int		key_hook(int keycode, t_vars *vars);

// main function
int	main()
{
	prtimage();
	return(0);
}

// 원하는 좌표에 해당하는 주소에 color값을 넣는 함수
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	prtimage()
{
	int		color;
	t_vars	vars;
	t_data	image;

	int	img_width = 1920;
	int	img_height = 1080;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, img_width, img_height, "Hellow World");
	image.img = mlx_new_image(vars.mlx, img_width, img_height); // 이미지 객체생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);// 이미지 주소할당
	for (int i = 0 ; i < img_height - 1 ; ++i)
	{
		for (int j = 0 ; j < img_width - 1; ++j)
		{
			double r = (double)(img_width - j) / (img_width - 1);
			double g = 3;
			//(double)(i) / (img_height - 1);
			double b = 1;
			color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
			my_mlx_pixel_put(&image, j, i, color);
		}	
	}
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
	mlx_hook(vars.win, 17, 0, exit_hook, 0); // close button press event
	mlx_loop(vars.mlx);
	return (0);

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

//close button press event
int	exit_hook()
{
	exit(0);
}
