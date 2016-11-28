/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 10:44:30 by baparis           #+#    #+#             */
/*   Updated: 2016/11/28 12:11:44 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*int	ft_check_and_place(char **endgrid, t_list lst, int i, int j)
{
	int	k;

	k = 0;
	while (endgrid[k])
		k++;
	if (k > 4)
		return (1);
	(void)lst;
	(void)i;
	(void)j;
	return (0);
}*/

int		ft_check_a_position(char **endgrid, t_list lst, int i, int j)
{
	int		k;

	if (endgrid [i][j] != '.')
		return (0);
	k = 1;
	while (k < 4)
	{
		if (endgrid[i + (lst.tab_block[k] / 4 - lst.tab_block[0] / 4)][j + (lst.tab_block[k] % 4 - lst.tab_block[0] % 4)] != '.')
			return (0);
		k++;
	}
	endgrid[i][j] = lst.letter;
	k = 1;
	while (k < 4)
	{
		endgrid[i + (lst.tab_block[k] / 4 - lst.tab_block[0] / 4)][j + (lst.tab_block[k] % 4 - lst.tab_block[0] % 4)] = lst.letter;
		k++;
	}
	return (1);
}

int		ft_check_and_place(char **endgrid, t_list lst, int i, int j)
{
	//printf("i = %d j = %d\n", i, j);	
	if (endgrid[i + 2] == 0 && endgrid[i][j] == '\0')
		return (0);
	else
	{
		if (ft_check_a_position(endgrid, lst, i, j) == 1)
			return (1);
		j++;
		if (endgrid[i][j] == '\0' && endgrid[i + 2] != 0)
		{
			j = 1;
			i++;
		}
		if (ft_check_and_place(endgrid, lst, i, j) == 1)
			return (1);
	}
	return (0);
}


/*
 * Efface les lettres ecrite dans la grid final quand cela n'est pas valide
 */

void	ft_erase(t_list *lst, char **endgrid)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	lst->used = 0;
	while (endgrid[j])
	{
		i = 0;
		while (endgrid[j][i])
		{
			if (endgrid[j][i] == lst->letter)
				endgrid[j][i] = '.';
			i++;
		}
		j++;
	}
}

int		ft_algo(t_list *lst, char **endgrid)
{
	t_list *tmp;

	tmp = lst;
	while (tmp && tmp->used == 1)
		tmp = tmp->next;
	if (!(tmp))
		return (1);
	while (tmp)
	{
		while (tmp->used == 1 && tmp)
			tmp = tmp->next;
		if (ft_check_and_place(endgrid, *tmp, 0, 0))
		{
			tmp->used = 1;
			if (!(ft_algo(lst, endgrid)))
				ft_erase(tmp, endgrid);
			else
				return (1);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}
