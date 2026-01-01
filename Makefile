.DEFAULT_GOAL := all
NAME := containers-tester

# =============================== SETTINGS ================================ #

CXX   := c++
CXXSTD := c++11
WARN  := -Wall -Wextra -Werror
OPT   ?= -O2

CPPFLAGS := -Iinclude
CXXFLAGS := -std=$(CXXSTD) $(OPT) $(WARN) -MMD -MP
LDFLAGS  :=
LDLIBS   :=

SRC_DIR := src
OBJ_DIR := bin

# ================================ SOURCES ================================ #

SRCS := \
  $(SRC_DIR)/ansi_ui.cpp \
  $(SRC_DIR)/app.cpp \
  $(SRC_DIR)/exec.cpp \
  $(SRC_DIR)/fs.cpp \
  $(SRC_DIR)/main.cpp \
  $(SRC_DIR)/scripts.cpp \
  $(SRC_DIR)/utils.cpp

OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# ================================ RULES ================================= #

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all run clean fclean re
