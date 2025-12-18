#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
    int value;
    int index;
	bool keep;
	int pos;
	int target_pos;
	int cost_a;
	int cost_b;
    struct s_stack *next;
    struct s_stack *before;
} t_stack;

// Algorithm utils functions
t_stack	*get_tail_node(t_stack *stack);
int		elements_in_stack(t_stack *stack);

// Push operators
void pa(t_stack **a, t_stack **b, bool check);
void pb(t_stack **b, t_stack **a, bool check);
void rra(t_stack **a, bool check);
void rrb(t_stack **b, bool check);
void rrr(t_stack **a, t_stack **b, bool check);
void sa(t_stack **a, bool check);
void sb(t_stack **b, bool check);
void ss(t_stack **a, t_stack **b, bool check);
void ra(t_stack **a, bool check);
void rb(t_stack **b, bool check);
void rr(t_stack **a, t_stack **b, bool check);

// Radix short algorithm
void assign_indicators(t_stack **a);
void small_sort(t_stack **a, t_stack **b);
void sorting_advanced(t_stack **a, t_stack **b);

// Parse and initialize and error handling
bool parse_and_init(t_stack **stack_a, int ac, char **av);
int invalid_entries(char *str);
bool is_ordered(t_stack *stack);
int check_dub(t_stack *a, int value);
void add_to_stack(t_stack **stack, int value);
void handle_error();

// Utils functions
long ft_atol(const char *str);
void free_stack(t_stack **stack);
char **ft_split(char const *s, char c);
void ft_free_split(char **parts);



#endif