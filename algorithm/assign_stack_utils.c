/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_stack_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:08:17 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/19 12:57:31 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/push_swap.h"

void	set_best_len(int best_len[2], int n, int *lis_len)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (lis_len[i] > best_len[0])
		{
			best_len[0] = lis_len[i];
			best_len[1] = i;
		}
		i++;
	}
}

void	compute_lis(int *lis_len, int *lis_prev, t_stack **nodes, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < n)
	{
		lis_len[i] = 1;
		lis_prev[i] = -1;
		j = 0;
		while (j < i)
		{
			if (nodes[j]->index < nodes[i]->index && lis_len[j]
				+ 1 > lis_len[i])
			{
				lis_len[i] = lis_len[j] + 1;
				lis_prev[i] = j;
			}
			j++;
		}
		i++;
	}
}

void	added_notes_a(t_stack **nodes, t_stack *a)
{
	int	i;

	i = 0;
	while (a)
	{
		nodes[i++] = a;
		a = a->next;
	}
}

