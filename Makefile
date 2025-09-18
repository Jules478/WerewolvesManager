NAME = Werewolves

CFLAGS = -Wall -Wextra -Werror 

GFLAG = -g

STD = -std=c++17

INC_DIR = ./inc

SRC_DIR = ./src

INIH_DIR = ./inih

OBJ_DIR = ./obj

CPP_SRCS = \
    $(SRC_DIR)/main.cpp \
    $(SRC_DIR)/ACard.cpp \
    $(SRC_DIR)/Game.cpp \
    $(SRC_DIR)/Roles.cpp \
    $(SRC_DIR)/Doppelganger.cpp \
    $(SRC_DIR)/GameUtils.cpp \
    $(INIH_DIR)/cpp/INIReader.cpp

C_SRCS = \
    $(INIH_DIR)/ini.c

CPP_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter $(SRC_DIR)/%.cpp,$(CPP_SRCS)))
CPP_OBJS += $(patsubst $(INIH_DIR)/cpp/%.cpp,$(OBJ_DIR)/INIReader.o,$(filter $(INIH_DIR)/cpp/%.cpp,$(CPP_SRCS)))
C_OBJS = $(patsubst $(INIH_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
OBJS = $(CPP_OBJS) $(C_OBJS)

GREEN = \e[1;32m
PURPLE = \e[1;35m
YELLOW = \e[1;33m
RESET = \e[0m

TOTAL_FILES := $(words $(OBJS))
CURRENT_FILE = 0

all: $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@c++ $(CFLAGS) $(STD) -c $< -o $@
	@files_compiled=$$(ls $(OBJ_DIR)/*.o 2>/dev/null | wc -l); \
	printf "$(YELLOW)\r[%3d%%] Compiling %-30s$(RESET)" $$((files_compiled * 100 / $(TOTAL_FILES))) $<

$(OBJ_DIR)/INIReader.o: $(INIH_DIR)/cpp/INIReader.cpp
	@mkdir -p $(OBJ_DIR)
	@c++ $(CFLAGS) $(STD) -c $< -o $@
	@files_compiled=$$(ls $(OBJ_DIR)/*.o 2>/dev/null | wc -l); \
	printf "$(YELLOW)\r[%3d%%] Compiling %-30s$(RESET)" $$((files_compiled * 100 / $(TOTAL_FILES))) $<

$(OBJ_DIR)/%.o: $(INIH_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@cc -Wall -Wextra -Werror -c $< -o $@
	@files_compiled=$$(ls $(OBJ_DIR)/*.o 2>/dev/null | wc -l); \
	printf "$(YELLOW)\r[%3d%%] Compiling %-30s$(RESET)" $$((files_compiled * 100 / $(TOTAL_FILES))) $<


$(OBJ_DIR)/%.debug.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@c++ $(CFLAGS) $(GFLAG) $(STD) -c $< -o $@


$(OBJ_DIR)/%.debug.o: $(INIH_DIR)/%.c
	@mkdir -p $(dir $@)
	@cc -Wall -Wextra -Werror -g -c $< -o $@

shadow: CFLAGS := -Wall -Wextra -Werror -Wshadow
shadow: re

$(NAME): $(OBJS)
	@printf "\r%-50s\r" " "
	@c++ $(CFLAGS) $(STD) $(OBJS) -o $(NAME)
	@echo "$(GREEN) \n$(NAME) Compiled\n$(RESET)"
	@echo "$(PURPLE)------------------------------------$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)\nObject files cleaned\n$(RESET)"
	@echo "$(PURPLE)------------------------------------$(RESET)"

fclean: clean
	@rm -rf $(NAME) *_shrubbery
	@echo "$(GREEN)\n$(NAME) Cleaned\n$(RESET)"
	@echo "$(PURPLE)------------------------------------$(RESET)"

debug: $(DEBUG_OBJS)
	@c++ $(CFLAGS) $(GFLAG) $(STD) $(DEBUG_OBJS) -o $(NAME)
	@echo "$(GREEN) \n$(NAME) Compiled with Debug Flags\n$(RESET)"
	@echo "$(PURPLE)------------------------------------$(RESET)"

re: fclean all

.PHONY: all clean fclean debug shadow re