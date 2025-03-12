NAME = so_long
# CFLAGS = -Wall -Wextra -Werror
MLXFLAG = -lmlx -framework OpenGL -framework AppKit
COMP = cc
HEADRES = so_long.h Libft/libft.h
SRCS = so_long.c utils/utils.c utils/img.c utils/map.c utils/parcing_map.c gnl/get_next_line.c gnl/get_next_line_utils.c 

OBGS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBGS)
	make -C Libft
	$(COMP) $(CFLAGS) $(MLXFLAG) Libft/libft.a $(OBGS) -o $@

%.o: %.c $(HEADRES)
	$(COMP) $(CFLAGS) -c -o $@ $<

clean:
	make clean -C Libft
	rm -rf $(OBGS)

fclean: clean
	make fclean -C Libft
	rm -rf $(NAME)

re: fclean all

.PHONY: clean