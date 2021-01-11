# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/19 23:21:49 by lmartin           #+#    #+#              #
#    Updated: 2021/01/11 12:00:01 by lmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## PIMPED MAKEFILE ##

# COLORS #

# This is a minimal set of ANSI/VT100 color codes
_END		=	\x1b[0m
_BOLD		=	\x1b[1m
_UNDER		=	\x1b[4m
_REV		=	\x1b[7m

# Colors
_GREY		=	\x1b[30m
_RED		=	\x1b[31m
_GREEN		=	\x1b[32m
_YELLOW		=	\x1b[33m
_BLUE		=	\x1b[34m
_PURPLE		=	\x1b[35m
_CYAN		=	\x1b[36m
_WHITE		=	\x1b[37m

# Inverted, i.e. colored backgrounds
_IGREY		=	\x1b[40m
_IRED		=	\x1b[41m
_IGREEN		=	\x1b[42m
_IYELLOW	=	\x1b[43m
_IBLUE		=	\x1b[44m
_IPURPLE	=	\x1b[45m
_ICYAN		=	\x1b[46m
_IWHITE		=	\x1b[47m

# **************************************************************************** #

# NORMINETTE #

NORMINETTE	:=	$(shell which norminette)

ifeq (, $(shell which norminette))
	NORMINETTE := ${HOME}/.norminette/norminette.rb
endif

## VARIABLES ##

# COMPILATION #

CC			=	gcc

CC_FLAGS	=	-Wall -Wextra -Werror


# DELETE #

RM			=	rm -rf


# DIRECTORIES #

DIR_HEADERS =	./includes/

DIR_SRCS	=	./srcs/

DIR_OBJS	=	./compiled_srcs/


# FILES #

SRC			=	push_swap.c \
				stacks.c \
				operations.c \
				instructions.c \
				movements.c \
				utils.c \
				debug.c

SRCS		=	$(SRC)

# COMPILED_SOURCES #

OBJS 		=	$(SRCS:%.c=$(DIR_OBJS)%.o)

NAME 		=	push_swap


# **************************************************************************** #

## RULES ##

all:			$(NAME)

debug:			DIR_HEADERS += -DDEBUG=1
debug:			all

# VARIABLES RULES #

$(NAME):		$(OBJS)
				@printf "\033[2K\r$(_GREEN) All files compiled into '$(DIR_OBJS)'. $(_END)✅\n"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) $(OBJS) -o $(NAME)
				@echo "$(_GREEN) Executable '$(NAME)' created. $(_END)✅"

# COMPILED_SOURCES RULES #

$(OBJS):		| $(DIR_OBJS)


$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@
				@printf "\033[2K\r $(_YELLOW)Compiling $< $(_END)⌛"

$(DIR_OBJS):
				@mkdir $(DIR_OBJS)


# OBLIGATORY PART #

clean:
				@$(RM) $(DIR_OBJS)
				@echo "$(_RED) '"$(DIR_OBJS)"' has been deleted. $(_END)🗑️"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(_RED) '"$(NAME)"' has been deleted. $(_END)🗑️"

re:				fclean all

# NORME #

norm:
				@$(NORMINETTE) $(DIR_SRCS)
				@$(NORMINETTE) $(DIR_HEADERS)

# PHONY #

.PHONY:			all clean fclean re norm
