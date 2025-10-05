/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajel-ho <hajel-ho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:10:44 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/10/05 20:34:23 by hajel-ho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes_bonus/launchpad_bonus.h"

void	free_all(void *p, int flag)
{
	static void	*list[INT_MAX];
	static int	i;

	if (flag)
	{
		list[i] = p;
		i++;
	}
	else
	{
		while (list[i])
		{
			free(list[i]);
			i--;
		}
	}
}

void	ft_done(size_t i)
{
	free_all(NULL, 0);
	exit (i);
}

void	*ft_alloc(size_t i)
{
	void	*res;

	res = malloc(i);
	if (!res)
		ft_done(0);
	free_all(res, 1);
	return (res);
}
