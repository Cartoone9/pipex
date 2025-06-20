CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = pipex

O_DIR = .objs

S_DIR = srcs

SRCS =  libft/ft_lstadd_back.c libft/ft_split_utils.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_strrchr.c \
		libft/ft_split.c libft/ft_strchr.c libft/ft_strncmp.c libft/ft_strdup.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		srcs/pipex.c srcs/pipex_utils_1.c srcs/pipex_utils_2.c srcs/free.c srcs/cleaning.c srcs/pipex_utils_3.c \
		srcs/pipex_utils_4.c srcs/pipex_utils_heredoc.c

OBJS = $(addprefix $(O_DIR)/, $(SRCS))

OBJS := $(OBJS:.c=.o)

$(O_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I./hdrs/ -c $< -o $@

all : $(NAME)

bonus : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) -o $(NAME)

clean : 
	rm -rf $(O_DIR)

fclean : clean
	rm -f $(NAME) $(BONUS_NAME)

re : fclean all

.PHONY : all bonus clean fclean re
