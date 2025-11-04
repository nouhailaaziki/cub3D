COMPILER = cc

CFLAGS  = -Wall -Wextra -Werror -Imlx -Ofast #-fsanitize=address -g3 -g
#DBGFLAGS= -fsanitize=address -g3

FLMLX   = -framework OpenGL -framework AppKit libmlx42.a -Iinclude -lglfw -L"$(shell brew --prefix glfw)/lib"

RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
BOLD    = \033[1m
RESET   = \033[0m

NAME    = cub3D
BONUS_NAME = cub3D_bonus

HEADER  = mandatory/includes/launchpad.h
HEADER_BONUS = bonus/includes_bonus/launchpad_bonus.h

MANDATORY = mandatory/utilities/error_exit.c   mandatory/free.c \
			mandatory/utilities/ft_atoi.c mandatory/utilities/ft_putendl_fd.c \
			mandatory/utilities/ft_putstr_fd.c mandatory/utilities/ft_split.c  mandatory/utilities/ft_my_split.c \
			mandatory/utilities/ft_strchr.c mandatory/utilities/ft_strcmp.c \
			mandatory/utilities/ft_strdup.c mandatory/utilities/ft_strjoin.c \
			mandatory/utilities/ft_strlen.c mandatory/utilities/ft_strncmp.c  mandatory/utilities/ft_isdigit.c\
			mandatory/utilities/ft_substr.c mandatory/utilities/get_next_line.c \
			mandatory/utilities/ft_putchar_fd.c mandatory/textures/build_textures1.c mandatory/textures/build_textures2.c\
			mandatory/parsing/parsing.c mandatory/parsing/parsing_utils1.c  mandatory/parsing/parsing_utils2.c\
			mandatory/parsing/parsing_utils3.c mandatory/parsing/parsing_utils4.c  mandatory/parsing/main.c \
			mandatory/raycasting/master.c mandatory/raycasting/init_data.c \
			mandatory/raycasting/raycasting.c mandatory/raycasting/render.c \
			mandatory/raycasting/wanderer_controls.c mandatory/raycasting/rotation_controller.c

BONUS =	bonus/utilities_bonus/error_exit_bonus.c  bonus/free_bonus.c  bonus/textures_bonus/enemy1_bonus.c  bonus/textures_bonus/enemy2_bonus.c \
		bonus/utilities_bonus/ft_atoi_bonus.c bonus/utilities_bonus/ft_putendl_fd_bonus.c \
		bonus/utilities_bonus/ft_putstr_fd_bonus.c bonus/utilities_bonus/ft_split_bonus.c  bonus/utilities_bonus/ft_my_split_bonus.c\
		bonus/utilities_bonus/ft_strchr_bonus.c bonus/utilities_bonus/ft_strcmp_bonus.c \
		bonus/utilities_bonus/ft_strdup_bonus.c bonus/utilities_bonus/ft_strjoin_bonus.c \
		bonus/utilities_bonus/ft_strlen_bonus.c bonus/utilities_bonus/ft_strncmp_bonus.c \
		bonus/utilities_bonus/ft_substr_bonus.c bonus/utilities_bonus/get_next_line_bonus.c  bonus/utilities_bonus/ft_isdigit_bonus.c\
		bonus/utilities_bonus/ft_putchar_fd_bonus.c  bonus/textures_bonus/door_bonus.c \
		bonus/parsing_bonus/parsing_bonus.c bonus/parsing_bonus/parsing_utils1_bonus.c bonus/parsing_bonus/parsing_utils2_bonus.c\
		bonus/parsing_bonus/parsing_utils3_bonus.c bonus/parsing_bonus/parsing_utils4_bonus.c bonus/parsing_bonus/main_bonus.c \
		bonus/raycasting_bonus/master_bonus.c bonus/raycasting_bonus/init_data_bonus.c \
		bonus/raycasting_bonus/raycasting_bonus.c bonus/raycasting_bonus/render_bonus.c \
		bonus/raycasting_bonus/wanderer_controls_bonus.c bonus/raycasting_bonus/rotation_controller_bonus.c \
		bonus/raycasting_bonus/setup_minimap.c bonus/textures_bonus/build_textures1_bonus.c bonus/textures_bonus/build_textures2_bonus.c

OBJM = ${MANDATORY:.c=.o}
OBJB = ${BONUS:.c=.o}

all: ${NAME}

${NAME} : ${OBJM}
	@echo "${YELLOW} ${BOLD}➤ Launching compilation...${RESET}"
	@${COMPILER} ${CFLAGS} ${FMLX} ${OBJM} -o ${NAME} ${FLMLX}
	@echo "${GREEN} ${BOLD}➤ ${NAME} successfully compiled ✓${RESET}"

bonus : ${OBJB}
	@echo "${YELLOW} ${BOLD}➤ Launching compilation...${RESET}"
	@${COMPILER} ${CFLAGS} ${FMLX} ${OBJB} -o ${BONUS_NAME} ${FLMLX}
	@echo "${GREEN} ${BOLD}➤ ${NAME} successfully compiled ✓${RESET}"

mandatory/%.o: mandatory/%.c ${HEADER}
	@printf "${BLUE}Compiling: ${YELLOW}$<${RESET}\r"
	@${COMPILER} ${CFLAGS} ${FMLX} -c $< -o $@

bonus/%.o: bonus/%.c ${HEADER_BONUS}
	@printf "${BLUE}Compiling: ${YELLOW}$<${RESET}\r"
	@${COMPILER} ${CFLAGS} ${FMLX} -c $< -o $@

clean:
	@${RM} ${OBJM} ${OBJB}
	@echo "${BLUE}${BOLD}✓ Object files removed${RESET}"

fclean: clean
	@${RM} ${NAME} ${BONUS_NAME}
	@echo "${RED}${BOLD}✓ Executable removed${RESET}"

re: fclean all

.PHONY: all clean fclean re