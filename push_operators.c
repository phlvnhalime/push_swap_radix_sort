/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:56:03 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/17 20:09:18 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void push(t_stack **copy, t_stack **main)
{
    t_stack *temp;

    if(!*main)
        return ;
    temp = *main;
    *main = (*main)->next;
    if(*main)
        (*main)->before = NULL;
    temp->before = NULL;
    if(!*copy)
    {
        *copy = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = *copy;
        temp->next->before = temp;
        *copy = temp;
    }
}

void pa(t_stack **a, t_stack **b, bool check)
{
    push(a, b);
    if(!check)
        write(1, "pa\n", 3);
}

void pb(t_stack **b, t_stack **a, bool check)
{
    push(b, a);
    if(!check)
        write(1, "pb\n", 3);
}