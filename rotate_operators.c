/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:56:41 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/17 20:09:04 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void rotate(t_stack **stack)
{
    t_stack *top;
    t_stack *tail; // kuyruk
    int len;

    len = count_nodes(*stack);
    if(!*stack || !stack || len == 1)
        return ;
    top = *stack;
    tail = get_tail_node(*stack);
    // yeni bas eskisinin onune gecir
    *stack = top->next;
    (*stack)->before = NULL;
    // eskisinin onune gecir
    tail->next = top;
    top->before = tail;
    top->next = NULL;
}

void ra(t_stack **a, bool check)
{
    rotate(a);
    if(!check)
        write(1, "ra\n", 3);
}

void rb(t_stack **b, bool check)
{
    rotate(b);
    if(!check)
        write(1, "rb\n", 3);
}

void rr(t_stack **a, t_stack **b, bool check)
{
    rotate(a);
    rotate(b);
    if(!check)
        write(1, "rr\n", 3);
}