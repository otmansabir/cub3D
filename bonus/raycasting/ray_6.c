/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:51:24 by osabir            #+#    #+#             */
/*   Updated: 2024/02/27 10:53:52 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_draw_pixel(t_globel **globel, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	if (!globel || !(*globel))
		return ;
	while (j < CUB_SIZE)
	{
		i = 0;
		while (i < CUB_SIZE)
		{
			my_put_pixel(globel, x + i, y + j, color);
			i++;
		}
		j++;
	}
}
