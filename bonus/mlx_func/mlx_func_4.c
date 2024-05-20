/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:11:21 by osabir            #+#    #+#             */
/*   Updated: 2024/03/10 11:31:45 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mlx_info(t_globel **globel)
{
	(*globel)->mlx->mlx_ptr = mlx_init();
	(*globel)->mlx->mlx_window
		= mlx_new_window((*globel)->mlx->mlx_ptr, X_WIDTH, Y_HEIGHT, "CUB3D");
	(*globel)->mlx->img_ptr
		= mlx_new_image((*globel)->mlx->mlx_ptr, X_WIDTH, Y_HEIGHT);
	(*globel)->mlx->buffer = mlx_get_data_addr((*globel)->mlx->img_ptr,
			&(*globel)->mlx->bpp,
			&(*globel)->mlx->size_line,
			&(*globel)->mlx->endian);
}

void	ft_globel_free(t_globel **globel, int i)
{
	ft_free_sturct1(globel, i);
	ft_free_sturct2(globel);
	ft_free_sturct3(globel);
	ft_free_sturct4(globel);
}

int	key_exit(t_globel **globel)
{
	if (!globel || !(*globel))
		return (0);
	write(2, "exit\n", 5);
	ft_globel_free(globel, 1);
	exit(0);
	return (0);
}
