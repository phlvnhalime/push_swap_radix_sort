/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_movements_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:13:12 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/19 11:15:48 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/push_swap.h"

void	rotate_a_cost(t_stack **a, int *cost)
{
	while (*cost > 0)
	{
		ra(a, false);
		(*cost)--;
	}
	while (*cost < 0)
	{
		rra(a, false);
		(*cost)++;
	}
}


void	rotate_b_cost(t_stack **b, int *cost)
{
	while (*cost > 0)
	{
		rb(b, false);
		(*cost)--;
	}
	while (*cost < 0)
	{
		rrb(b, false);
		(*cost)++;
	}
}

void	rotate_both_cost(t_stack **a, t_stack **b, int *ca, int *cb)
{
	while (*ca > 0 && *cb > 0)
	{
		rr(a, b, false);
		(*ca)--;
		(*cb)--;
	}
	while (*ca < 0 && *cb < 0)
	{
		rrr(a, b, false);
		(*ca)++;
		(*cb)++;
	}
}

/*
	Cost model maximizing rr/rrr:
	- same sign costs => can merge rotations => total = max(|a|,|b|)
	- different sign => total = |a| + |b|
	Tie-break: prefer larger common rotation part (more rr/rrr).
*/
int	move_cost(t_stack *node)
{
	if ((node->cost_a >= 0 && node->cost_b >= 0)
		|| (node->cost_a <= 0 && node->cost_b <= 0))
	{
		if (abs_i(node->cost_a) > abs_i(node->cost_b))
			return (abs_i(node->cost_a));
		return (abs_i(node->cost_b));
	}
	return (abs_i(node->cost_a) + abs_i(node->cost_b));
}

int	common_rot_part(t_stack *node)
{
	int	a;
	int	b;

	if (!((node->cost_a >= 0 && node->cost_b >= 0)
			|| (node->cost_a <= 0 && node->cost_b <= 0)))
		return (0);
	a = abs_i(node->cost_a);
	b = abs_i(node->cost_b);
	if (a < b)
		return (a);
	return (b);
}