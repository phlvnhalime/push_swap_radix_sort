/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:56:35 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/17 22:23:28 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void reverse_rotate(t_stack **stack)
{
    int len;
    t_stack *last;

    len = count_nodes(*stack);
    if(!*stack || !stack || len == 1)
        return ;
    last = get_tail_node(*stack);
    last->before->next = NULL;
    last->next = *stack;
    last->before = NULL;
    *stack = last;
    last->next->before = last;
}

void rra(t_stack **a, bool check)
{
    reverse_rotate(a);
    if(!check)
        write(1, "rra\n", 4);
}

void rrb(t_stack **b, bool check)
{
    reverse_rotate(b);
    if(!check)
        write(1, "rrb\n", 4);
}

void rrr(t_stack **a, t_stack **b, bool check)
{
	reverse_rotate(a);
	reverse_rotate(b);
	if (!check)
		write(1, "rrr\n", 4);
}