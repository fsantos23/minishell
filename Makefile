
SRCS_DIR = srcs
PARS_DIR = srcs/parsing
NOT_PARS_DIR = srcs/builtins
PIPEX_DIR = srcs/pipex

SRCS		=	$(SRCS_DIR)/main.c \
				$(NOT_PARS_DIR)/env.c \
				$(NOT_PARS_DIR)/env_ext.c \
				$(NOT_PARS_DIR)/pwd.c \
				$(NOT_PARS_DIR)/cd.c \
				$(NOT_PARS_DIR)/echo.c \
				$(NOT_PARS_DIR)/export.c \
				$(NOT_PARS_DIR)/unset.c \
				$(NOT_PARS_DIR)/utils.c \
				$(NOT_PARS_DIR)/exit.c \
				$(NOT_PARS_DIR)/check_builtins.c \
				$(PARS_DIR)/check_args.c \
				$(PARS_DIR)/utils.c \
				$(PARS_DIR)/check_args2.c \
				$(PARS_DIR)/execute.c \
				$(PARS_DIR)/redir.c \
				$(PARS_DIR)/organize.c \
				$(PARS_DIR)/error.c \
				$(PARS_DIR)/free.c \
				$(PARS_DIR)/path.c \
				$(PARS_DIR)/type.c

OBJS		=	$(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

OBJS_DIR	=	objs

NAME		=	minishell

CC			=	cc

LIBFT		=	libft/libft.a

PIPEX		=	pipex/pipex_bonus

CFLAGS		=	 -Wall -Wextra -Werror -g #-fsanitize=address

RM			=	rm -rf

INC			=	-Iincludes -I/usr/include -Ilibft/includes -Ipipex/includes -Iget_next_line/includes 

# /* ~~~~~~~ Colors ~~~~~~~ */
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"



all:		$(NAME)

$(OBJS_DIR)/%.o :	$(SRCS_DIR)/%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME):	$(OBJS)
			@echo $(RED) "[🚀Compiling libft...🚀]" $(EOC)
			@make -C libft > /dev/null
			@echo $(GREEN) "[Libft compiled!]" $(EOC)
			@$(CC) $(OBJS) -lreadline $(LIBFT) $(GNL) $(CFLAGS) $(INC) -o $(NAME)
			@echo $(GREEN) "[Minishell compiled!]" $(EOC)

clean:
			@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
			@$(RM) $(OBJS)

fclean:		clean
			@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
			@$(RM) $(NAME)
			@$(RM) *.out
			@$(RM) $(OBJS_DIR)
			@make fclean -C libft > /dev/null
			@echo $(GREEN) "[All cleaned!]" $(EOC)

re:			fclean all

r:
	make re  > /dev/null && clear && ./$(NAME)

cl: 
	clear && make r

valgrind:
	make re  > /dev/null && valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY:		all clean fclean re