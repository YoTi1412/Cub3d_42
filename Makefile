# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrafai <yrafai@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 22:43:03 by yrafai            #+#    #+#              #
#    Updated: 2025/04/12 01:39:51 by yrafai           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BRIGHT_GREEN=\033[1;32m
BRIGHT_BLUE=\033[1;34m
BRIGHT_YELLOW=\033[1;33m
BRIGHT_RED=\033[1;31m
BRIGHT_PURPLE=\033[1;35m
NC=\033[0m

NAME = cub3d
NAME_BONUS = cub3d_bonus

LIB = -Imlx -Lmlx -lmlx -Imlx -lXext -lX11 -lm -lz

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

OBJSDIR = objs/
OBJSDIR_BONUS = objs_bonus/

LIBFT_SRCS = \
 libft/string_builder.c \
 libft/string_builder_utils.c \
 libft/ft_malloc.c \
 libft/ft_isspace.c \
 libft/ft_isspecial.c \
 libft/ft_strcmp.c \
 libft/ft_bzero.c \
 libft/ft_isalnum.c \
 libft/ft_isalpha.c \
 libft/ft_isascii.c \
 libft/ft_isdigit.c \
 libft/ft_isprint.c \
 libft/ft_memcpy.c \
 libft/ft_memmove.c \
 libft/ft_memset.c \
 libft/ft_strchr.c \
 libft/ft_strlcat.c \
 libft/ft_strlcpy.c \
 libft/ft_strlen.c \
 libft/ft_strrchr.c \
 libft/ft_tolower.c \
 libft/ft_toupper.c \
 libft/ft_strncmp.c \
 libft/ft_memchr.c \
 libft/ft_memcmp.c \
 libft/ft_strnstr.c \
 libft/ft_atoi.c \
 libft/ft_calloc.c \
 libft/ft_strdup.c \
 libft/ft_substr.c \
 libft/ft_strjoin.c \
 libft/ft_strtrim.c \
 libft/ft_split.c \
 libft/ft_itoa.c \
 libft/ft_strmapi.c \
 libft/ft_striteri.c \
 libft/ft_putchar_fd.c \
 libft/ft_putstr_fd.c \
 libft/ft_putendl_fd.c \
 libft/ft_putnbr_fd.c \
 libft/char_writer.c \
 libft/format_count_utils.c \
 libft/format_parser.c \
 libft/format_utilities.c \
 libft/ft_printf.c \
 libft/handle_format.c \
 libft/print_helpers.c \
 libft/printf_helper_herlper.c \
 libft/get_next_line_bonus.c \
 libft/clean.c \
 libft/ft_strappend.c \
 libft/ft_error_msg.c \
 libft/alpha_check.c \
 libft/ft_stack_new.c \
 libft/ft_lstnew_bonus.c \
 libft/ft_lstadd_front_bonus.c \
 libft/ft_lstsize_bonus.c \
 libft/ft_lstlast_bonus.c \
 libft/ft_lstadd_back_bonus.c \
 libft/ft_lstdelone_bonus.c \
 libft/ft_lstclear_bonus.c \
 libft/ft_lstiter_bonus.c \
 libft/ft_lstmap_bonus.c \
 libft/dll.c

LIBFT_OBJS = $(LIBFT_SRCS:libft/%.c=$(OBJSDIR)libft/%.o)
LIBFT_OBJS_BONUS = $(LIBFT_SRCS:libft/%.c=$(OBJSDIR_BONUS)libft/%.o)

SRCS = Mandatory/main.c \
	Mandatory/errors/errors.c \
	Mandatory/errors/free.c \
	Mandatory/game/init.c \
	Mandatory/game/keys.c \
	Mandatory/game/moves.c \
	Mandatory/game/rotate.c \
	Mandatory/parser/check_map.c \
	Mandatory/parser/init_map.c \
	Mandatory/parser/map_utils.c \
	Mandatory/parser/validate_map.c \
	Mandatory/parser/validate_map_helpers.c \
	Mandatory/raycasting/raycasting.c \
	Mandatory/raycasting/rendering.c \
	Mandatory/raycasting/textures.c \

OBJS = $(SRCS:Mandatory/%.c=$(OBJSDIR)Mandatory/%.o)

SRCS_BONUS = Bonus/main_bonus.c \
	Bonus/errors/errors_bonus.c \
	Bonus/errors/free_bonus.c \
	Bonus/game/init_bonus.c \
	Bonus/game/init_textures_bonus.c \
	Bonus/game/init_textures_helpers_bonus.c \
	Bonus/game/init_textures_helpers2_bonus.c \
	Bonus/game/keys_bonus.c \
	Bonus/game/moves_bonus.c \
	Bonus/game/door_bonus.c \
	Bonus/game/minimap_bonus.c \
	Bonus/game/minimap_helpers_bonus.c \
	Bonus/game/minimap_raycast_bonus.c \
	Bonus/game/mouse_bonus.c \
	Bonus/game/mouse_helpers_bonus.c \
	Bonus/game/weapons_bonus.c \
	Bonus/game/rotate_bonus.c \
	Bonus/parser/check_map_bonus.c \
	Bonus/parser/init_map_bonus.c \
	Bonus/parser/map_utils_bonus.c \
	Bonus/parser/validate_map_bonus.c \
	Bonus/parser/validate_map_helpers_bonus.c \
	Bonus/parser/validate_map_helpers_2_bonus.c \
	Bonus/raycasting/raycasting_bonus.c \
	Bonus/raycasting/rendering_bonus.c \
	Bonus/raycasting/textures_bonus.c \

OBJS_BONUS = $(SRCS_BONUS:Bonus/%.c=$(OBJSDIR_BONUS)%.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)/libft
	@mkdir -p $(OBJSDIR)/Mandatory
	@mkdir -p $(OBJSDIR)/Mandatory/errors
	@mkdir -p $(OBJSDIR)/Mandatory/game
	@mkdir -p $(OBJSDIR)/Mandatory/parser
	@mkdir -p $(OBJSDIR)/Mandatory/raycasting

$(OBJSDIR_BONUS):
	@mkdir -p $(OBJSDIR_BONUS)/libft
	@mkdir -p $(OBJSDIR_BONUS)
	@mkdir -p $(OBJSDIR_BONUS)/errors
	@mkdir -p $(OBJSDIR_BONUS)/game
	@mkdir -p $(OBJSDIR_BONUS)/parser
	@mkdir -p $(OBJSDIR_BONUS)/raycasting

$(OBJSDIR)libft/%.o: libft/%.c
	@printf "${BRIGHT_YELLOW}Compiling %-30s${NC}\n" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR)Mandatory/%.o: Mandatory/%.c includes/cub3d.h includes/libft.h
	@printf "${BRIGHT_BLUE}Compiling %-30s${NC}\n" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR_BONUS)libft/%.o: libft/%.c
	@printf "${BRIGHT_YELLOW}Compiling %-30s${NC}\n" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR_BONUS)%.o: Bonus/%.c includes/cub3d.h includes/libft.h
	@printf "${BRIGHT_PURPLE}Compiling %-30s${NC}\n" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJSDIR) $(LIBFT_OBJS) $(OBJS)
	@echo "${BRIGHT_GREEN}Building Cub3d...${NC}"
	@$(CC) $(LIBFT_OBJS) $(OBJS) $(CFLAGS) -o $(NAME) $(LIB)

$(NAME_BONUS): $(OBJSDIR_BONUS) $(LIBFT_OBJS_BONUS) $(OBJS_BONUS)
	@echo "${BRIGHT_GREEN}Building Cub3d Bonus...${NC}"
	@$(CC) $(LIBFT_OBJS_BONUS) $(OBJS_BONUS) $(CFLAGS) -o $(NAME_BONUS) $(LIB)

clean:
	@echo "${BRIGHT_RED}Cleaning object files...${NC}"
	@rm -rf $(OBJSDIR)
	@rm -rf $(OBJSDIR_BONUS)

fclean: clean
	@echo "${BRIGHT_RED}Cleaning executables...${NC}"
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus
