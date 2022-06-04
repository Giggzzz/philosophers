# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 16:55:08 by gudias            #+#    #+#              #
#    Updated: 2022/06/04 04:52:45 by gudias           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pthread

INCL	= -I incs
RM		= rm -f

SRCSDIR	= srcs
OBJSDIR	= objs

SRCS	=	philosophers.c init.c ft_atoi.c\

OBJS	= $(SRCS:%.c=$(OBJSDIR)/%.o)
DBG_OBJS = $(SRCS:%.c=$(OBJSDIR)/%_dbg.o)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@echo "$(YELLOW)Compiling $(DEFAULT)$<"
	@mkdir -p $(OBJSDIR)
	@$(CC) $(CFLAGS) $(INCL) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Creating executable..$(DEFAULT)"
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN)---> ./$@ is ready$(DEFAULT)"

clean:
	@$(RM) -r $(OBJSDIR)
	@echo "$(RED)Removed $(CYAN)objs/$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removed $(CYAN)./$(NAME)$(DEFAULT)"

debug: $(DBG_OBJS)
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

re: fclean all

.PHONY: all clean fclean debug re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
DEFAULT = \033[0m
