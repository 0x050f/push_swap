# push_swap

The **push_swap** project is a very simple and highly effective algorithm project: data will need to be sorted. You have at your disposal a set of int values, 2 stacks and a set of instructions to manipulate both stacks.

This project contains 2 programs:
- The first, named **checker** which takes integer arguments and reads instructions on the standard output. Once read,checker executes them and displays `OK` if integersare sorted. Otherwise, it will display `KO`.
- The second one called **push_swap** which calculates and displays on the standard output the smallest progam using *push_swap instruction language* that sorts inte-ger arguments received.

## push_swap instructions

- **sa**: *swap a* - swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements.
- **sb**: *swap b* - swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements.
- **ss**: sa and sb at the same time.
- **pa**: *push a* - take the first element at the top of b and put it at the top of a. Do nothing if b is empty.
- **pb**: *push b* - take the first element at the top of a and put it at the top of b. Do nothing if a is empty.
- **ra**: *rotate a* - shift up all elements of stack a by 1. The first element becomes the last one.
- **rb**: *rotate b* - shift up all elements of stack b by 1. The first element becomes the last one.
- **rr**: ra and rb at the same time.
- **rra**: *reverse rotate a* - shift down all elements of stack a by 1. The last element becomes the first one.
- **rrb**: *reverse rotate b* - shift down all elements of stack b by 1. The last element becomes the first one.
- **rrr**: rra and rrb at the same time.

## Compilation

Compile checker: `make checker`

Compile push_swap: `make push_swap`

Compile both: `make`

## Execute

checker: `./checker 0 2 3 1` then program's waiting for user input

push_swap: `./push_swap 0 2 3 1`

Note: You can also use option `-v` as first parameter to see stacks operations

## Tester

There is a bash script named `script.sh` that generate a array of size n and shuffle then test `push_swap | checker` x times.

```
./script.sh size_array [nb_times]
```
