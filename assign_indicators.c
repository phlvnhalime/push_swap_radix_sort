/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_indicators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 01:30:38 by hpehliva          #+#    #+#             */
/*   Updated: 2025/12/18 18:14:40 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack *find_smallest_element(t_stack *a)
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
/*
  For example stack A has 6 elements.
  Stack a = [3,1,6,2,5,4]

  Stack b = []
  indicators = [2,0,5,1,4,3]
    - First ordered element with starting 0 till length of the stack.
    - index = [1,2,3,4,5,6]
  After assigning indicators, stack a will be like this:
  3 -> 2i
  1 -> 0i
  6 -> 5i
  2 -> 1i
  5 -> 4i
  4 -> 3i
  They will compare with each other to mark_lis_keep
*/
void assign_indicators(t_stack **a)
{
    t_stack *curr;
    t_stack *small;
    int i;
    int len;

    len = elements_in_stack(*a);
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
