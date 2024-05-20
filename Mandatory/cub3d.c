/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:23:35 by osabir            #+#    #+#             */
/*   Updated: 2024/05/12 15:44:51 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_globel	*globel;

	if (ac != 2)
		ft_exit_error("Error\n", NULL);
	globel = NULL;
	check_file_name(av[1], ".cub");
	globel = everthing(globel);
	globel->g_map = parsing_file(av[1], globel);
	ft_player(&globel);
	mlx_info(&globel);
	ft_get_img_xpm(&globel);
	mlx_hook(globel->mlx->mlx_window, 2, 0, &key_press, &globel);
	mlx_hook(globel->mlx->mlx_window, 3, 0, &key_release, &globel);
	mlx_hook(globel->mlx->mlx_window, 17, 0, &key_exit, &globel);
	mlx_loop_hook(globel->mlx->mlx_ptr, &draw_win, &globel);
	mlx_loop(globel->mlx->mlx_ptr);
	return (0);
}
