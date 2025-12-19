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
t_stack *find_smallest_element(t_stack *a);

// Algorithm utils functions
int	abs_i(int x);
void	set_positions(t_stack *stack);
int	find_min_index_pos(t_stack *a);
void	clear_keep(t_stack *a);
//Algorithm movements functions

t_stack	*pick_cheapest(t_stack *b);
void	move_cheapest_to_a(t_stack **a, t_stack **b);
void	final_rotate_to_min(t_stack **a);
// Algorithm movements utils functions
int	move_cost(t_stack *node);
int	common_rot_part(t_stack *node);
void	rotate_a_cost(t_stack **a, int *cost);
void	rotate_b_cost(t_stack **b, int *cost);
void	rotate_both_cost(t_stack **a, t_stack **b, int *ca, int *cb);

// Algorithm assign stack functions
void	assign_indicators(t_stack **a);
void	mark_lis_keep(t_stack *a);
void	zone_push_to_b(t_stack **a, t_stack **b);

// Algorithm assign stack utils functions
void	set_best_len(int best_len[2], int n, int *lis_len);
void	compute_lis(int *lis_len, int *lis_prev, t_stack **nodes, int n);
void	added_notes_a(t_stack **nodes, t_stack *a);

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
void	handle_error(void);

// Utils functions
long ft_atol(const char *str);
void free_stack(t_stack **stack);
char **ft_split(char const *s, char c);
void ft_free_split(char **parts);
int	count_elements(t_stack *stack);



#endif