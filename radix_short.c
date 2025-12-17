/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_short.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 01:30:38 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/17 19:51:27 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack *find_smallest_element(t_stack *a)
{
  t_stack *small;
  t_stack *curr;

  small = NULL;
  curr = a;
  while(curr)
  {
    if(curr->index == -1)
    {
      if(small == NULL || curr->value < small->value)
        small = curr;
    }
    curr = curr->next;
  }
  return (small);

}

void assign_indicators(t_stack **a)
{
    t_stack *curr;
    t_stack *small;
    int i;
    int len;

    len = count_nodes(*a);
    if(!*a)
      return ;
    curr = *a;
    while(curr)
    {
      curr->index = -1;
      curr = curr->next;
    }
    i = 0;
    while(i < len)
    {
      small = find_smallest_element(*a);
      if(small)
        small->index = i;
      i++;
    } 
}

void radix_short(t_stack **a, t_stack **b)
{
    t_stack *head_a;
    int max_size;
    int max_bits;
    int bits_array[2];

  // order the numbers in the stack
    assign_indicators(a);

    max_size = count_nodes(*a);
    max_bits = 0;
    while((max_size - 1) >> max_bits != 0)
      max_bits++;
    bits_array[1] = 0;
    while(bits_array[1] < max_bits)
    {
      bits_array[0] = 0;
      while(bits_array[0] < max_size)
      {
        head_a = *a;
        if(((head_a->index >> bits_array[1]) & 1) == 1)
          pb(b, a, false);
        else
          ra(a, false);
        bits_array[0]++;
      }
    }

    while(*b)
    {
      pa(a,b, false);
    }
    bits_array[1]++;


}