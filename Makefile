# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 16:55:08 by gudias            #+#    #+#              #
#    Updated: 2022/06/02 17:00:34 by gudias           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philosophers

CC		= gcc
CFLAGS	= -g -Wall -Wextra -Werror

INCL	= -I incs
RM		= rm -f

LIBFT	= libft/libft.a

SRCSDIR	= srcs
OBJSDIR	= objs

SRCS	=	philosophers.c \

OBJS	= $(SRCS:%.c=$(OBJSDIR)/%.o)
DBG_OBJS = $(SRCS:%.c=$(OBJSDIR)/%_dbg.o)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@echo "$(YELLOW)Compiling $(DEFAULT)$<"
	@mkdir -p $(OBJSDIR)
	@$(CC) $(CFLAGS) $(INCL) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Creating executable..$(DEFAULT)"
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN)---> ./$@ is ready$(DEFAULT)"

$(LIBFT):
	@echo "$(YELLOW)Preparing Libft..$(DEFAULT)"
	@make -C libft 1>/dev/null 2>/dev/null
	@echo "$(CYAN)---> Libft ready$(DEFAULT)"

clean:
	@$(RM) -r $(OBJSDIR)
	@echo "$(RED)Removed $(CYAN)objs/$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removed $(CYAN)./$(NAME)$(DEFAULT)"

libclean: 
	@make fclean -C libft 1>/dev/null 2>/dev/null
	@echo "$(RED)Removed $(CYAN)Libft$(DEFAULT)"

debug: $(DBG_OBJS) $(LIBFT)
	@echo "$(YELLOW)Preparing files for debug...$(DEFAULT)"
	@$(CC) $(CFLAGS) $^ -o debug_$(NAME)
	@echo "$(GREEN)----> ./debug_$(NAME) is ready$(DEFAULT)"
	@echo "$(CYAN)Launching LLDB...$(DEFAULT)"
	@lldb ./debug_$(NAME)
	@echo "$(RED)Removed $(CYAN)./debug_$(NAME)$(DEFAULT)"
	@$(RM) debug_$(NAME)

$(OBJSDIR)/%_dbg.o: $(SRCSDIR)/%.c
	@mkdir -p $(OBJSDIR)
	@$(CC) -g3 $(INCL) -c $< -o $@

fullclean: fclean libclean

bonus: re

re: fclean all

.PHONY: all clean fclean re bonus libclean fullclean

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
DEFAULT = \033[0m
