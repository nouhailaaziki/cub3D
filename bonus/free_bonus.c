/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:10:44 by hajel-ho          #+#    #+#             */
/*   Updated: 2025/11/14 12:49:45 by noaziki          ###   ########.fr       */
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

void	free_and_exit(size_t i)
{
	free_all(NULL, 0);
	close_fd();
	exit (i);
}

void	*ft_alloc(size_t i)
{
	void	*res;

	res = malloc(i);
	if (!res)
		free_and_exit(0);
	free_all(res, 1);
	return (res);
}

void	close_fd(void)
{
	int	i;

	i = 3;
	while (i < OPEN_MAX)
		close(i++);
}
