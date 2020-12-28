# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/19 23:21:49 by lmartin           #+#    #+#              #
#    Updated: 2020/12/28 16:10:30 by lmartin          ###   ########.fr        #
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

## VARIABLES ##

SRCS		=	./srcs

DIR			=	./

# DELETE #

RM			=	rm -rf

# COMPILED_SOURCES #

CHECKER		=	checker

PUSH_SWAP	=	push_swap

# **************************************************************************** #

## RULES ##

all:			$(CHECKER) $(PUSH_SWAP)

# VARIABLES RULES #

$(CHECKER):		
				@printf	"$(_BLUE)$(_BOLD)$(CHECKER) $(_END)\n"
				@$(MAKE) -C $(SRCS)/$(CHECKER) MAKEFLAGS=
				@cp -rf $(SRCS)/$(CHECKER)/$(CHECKER) $(DIR)/$(CHECKER)

$(PUSH_SWAP):	
				@printf	"$(_BLUE)$(_BOLD)$(PUSH_SWAP) $(_END)\n"
				@$(MAKE) -C $(SRCS)/$(PUSH_SWAP)/ MAKEFLAGS=
				@cp -rf $(SRCS)/$(PUSH_SWAP)/$(PUSH_SWAP) ./$(PUSH_SWAP)

# OBLIGATORY PART #

clean:
				@printf	"$(_BLUE)$(_BOLD)$(CHECKER) $(_END)\n"
				@make clean -C $(SRCS)/$(CHECKER)
				@printf	"$(_BLUE)$(_BOLD)$(PUSH_SWAP) $(_END)\n"
				@make clean -C $(SRCS)/$(PUSH_SWAP)

fclean:			
				@printf	"$(_BLUE)$(_BOLD)$(CHECKER) $(_END)\n"
				@make fclean -C $(SRCS)/$(CHECKER)
				@printf	"$(_BLUE)$(_BOLD)$(PUSH_SWAP) $(_END)\n"
				@make fclean -C $(SRCS)/$(PUSH_SWAP)
				@$(RM) $(CHECKER)
				@$(RM) $(PUSH_SWAP)

re:				fclean all

# NORME #

norm:
				@printf	"$(_BLUE)$(_BOLD)$(CHECKER) $(_END)\n"
				make norm -C $(SRCS)/$(CHECKER)
				@printf	"$(_BLUE)$(_BOLD)$(PUSH_SWAP) $(_END)\n"
				make norm -C $(SRCS)/$(PUSH_SWAP)

# PHONY #

.PHONY:			all clean fclean checker push_swap
