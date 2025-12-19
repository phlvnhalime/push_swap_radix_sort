/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:56:47 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/19 09:28:10 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void swap(t_stack **stack)
{
    int len;

    len = count_elements(*stack);
    if(!*stack || !stack || len == 1)
        return ;
    *stack = (*stack)->next;
    (*stack)->before->before = *stack;
    (*stack)->before->next = (*stack)->next;
    if((*stack)->next)
        (*stack)->next->before = (*stack)->before;
    (*stack)->next = (*stack)->before;
    (*stack)->before = NULL;
}

void sa(t_stack **a, bool check)
{
    swap(a);
    if(!check)
        write(1, "sa\n", 3);
}

void sb(t_stack **b, bool check)
{
    swap(b);
    if(!check)
        write(1, "sb\n", 3);
}

void ss(t_stack **a, t_stack **b, bool check)
{
	swap(a);
	swap(b);
	if (!check)
		write(1, "ss\n", 3);
}