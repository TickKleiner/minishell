NAME		=	minishell

SRC_DIR		=	./src/
SRC			=	init_data.c\
				parser.c\
				get_next_line.c\
				exit.c\
				parser_utils.c\
				split_line.c\
				get_tokens.c\
				str_mask.c\
				validate_tokens.c\
				check_syntax_error.c\
				find_env.c\
				correct_str.c\
				free_data.c\
				exec_fill.c\
				process_redirect.c\
				fill_name_path.c\
				handle_signals.c\
				main.c

O_DIR		=	./bin
OBJ			=	$(addprefix $(O_DIR)/, $(SRC:c=o))

H_DIR		=	./include
INCLUDES	=	$(H_DIR)/*

LIB			=	./libft/libft.a \

FLAGS		= -g #-Wall -Wextra -Werror

all : $(NAME)

$(NAME)	:	$(OBJ) lib
	gcc $(FLAGS) -o $(NAME) $(OBJ) -I $(H_DIR) $(LIB)

lib:
	make bonus -C ./libft/

$(O_DIR)/%.o: ./src/*/%.c $(INCLUDES) | $(O_DIR)
	@gcc $(FLAGS) -I $(H_DIR) -c $< -o $@

$(O_DIR):
	@mkdir $(O_DIR)

clean:
	@rm -rf $(O_DIR)
	@echo "$(NAME) object files deleted"

fclean: clean
	@rm -rf $(NAME)
#	@make fclean -C ./libft/
	@echo "$(NAME) deleted"

re: fclean all

.PHONY: all clean fclean re
