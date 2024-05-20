/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:35:07 by osabir            #+#    #+#             */
/*   Updated: 2024/03/10 17:15:04 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_so(t_globel **globel, char *line)
{
	if (!globel || !(*globel) || !line)
		return ;
	if (!(*globel)->g_done->so)
		(*globel)->g_map->so = check_side(line, globel);
	else
		ft_exit_error("Error dublcatet line\n", globel);
	(*globel)->g_done->so = true;
}

void	ft_we(t_globel **globel, char *line)
{
	if (!globel || !(*globel) || !line)
		return ;
	if (!(*globel)->g_done->we)
		(*globel)->g_map->we = check_side(line, globel);
	else
		ft_exit_error("Error dublcatet line\n", globel);
	(*globel)->g_done->we = true;
}

void	ft_ea(t_globel **globel, char *line)
{
	if (!globel || !(*globel) || !line)
		return ;
	if (!(*globel)->g_done->ea)
		(*globel)->g_map->ea = check_side(line, globel);
	else
		ft_exit_error("Error dublcatet line\n", globel);
	(*globel)->g_done->ea = true;
}

void	ft_c(t_globel **globel, char *line)
{
	if (!globel || !(*globel) || !line)
		return ;
	if (!globel || !(*globel) || !line)
		return ;
	if (!(*globel)->g_done->c)
		(*globel)->g_map->c = checkside2(line, globel);
	else
		ft_exit_error("Error dublcatet line\n", globel);
	(*globel)->g_done->c = true;
}

void	ft_f(t_globel **globel, char *line)
{
	if (!globel || !(*globel) || !line)
		return ;
	if (!(*globel)->g_done->f)
		(*globel)->g_map->f = checkside2(line, globel);
	else
		ft_exit_error("Error dublcatet line\n", globel);
	(*globel)->g_done->f = true;
}
