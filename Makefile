.DEFAULT_GOAL := all
NAME          := containers

# =============================== SETTINGS ================================ #

NAMESPACE      ?= ft
CXXSTD         := c++98
CONTAINERS_PATH= # TODO: include your implemented containers path
ifeq ($(NAMESPACE),std)
  NAMESPACE_FLAG := -DSTD_MODE=1
  CXXSTD 		  = c++11
else
  NAMESPACE_FLAG :=
endif

MAKEFLAGS += --no-print-directory

# =============================== COMPILER ================================ #

CXX         := c++
CXXSTDFLAG  := -std=$(CXXSTD)
SANITIZE_FLAG ?= -fsanitize=address
CXXFLAGS    := $(CXXSTDFLAG) -MMD -MP -Wall -Wextra -Werror $(NAMESPACE_FLAG) $(SANITIZE_FLAG)

CPPFLAGS    := -I./$(CONTAINERS_PATH) -I./test/include
LDFLAGS     :=
LDLIBS      :=

# ============================== DIRECTORIES ============================== #

SRC_DIR   := src
TEST_DIR  := test
OBJ_DIR   := obj
BIN_DIR   := bin

# ============================== MAIN SOURCES ============================= #
CORE_MAIN    := $(TEST_DIR)/main_core_test.cpp
ADV_MAIN     := $(TEST_DIR)/main_advanced_test.cpp
STRESS_MAIN  := $(TEST_DIR)/main_stress_test.cpp

# ============================= COMMON SOURCES ============================ #

BASE_SRCS :=
BASE_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(BASE_SRCS))

# ================================ UTILS ================================= #

UTILS_DIR    := $(TEST_DIR)/utils
UTILS_PREFIX := test_utils_

# --- suffix (Core / Part 1,2)
UTILS_CORE_PART_1_SUFFIX := pair equal lexicographical_compare
UTILS_CORE_PART_2_SUFFIX := enable_if is_integral iterator_traits reverse_iterator

CORE_UTILS_PART_1_SRCS := \
  $(addprefix $(UTILS_DIR)/$(UTILS_PREFIX), $(addsuffix .cpp, $(UTILS_CORE_PART_1_SUFFIX)))
CORE_UTILS_PART_2_SRCS := \
  $(addprefix $(UTILS_DIR)/$(UTILS_PREFIX), $(addsuffix .cpp, $(UTILS_CORE_PART_2_SUFFIX)))
CORE_UTILS_SRCS := $(CORE_UTILS_PART_1_SRCS) $(CORE_UTILS_PART_2_SRCS)

# ================================ VECTOR ================================ #

VECTOR_DIR    := $(TEST_DIR)/vector
VECTOR_PREFIX := test_vector_

# --- suffix (Core / Part 1,2 + Advanced)
VECTOR_CORE_PART_1_SUFFIX := \
  constructors \
  assignment \
  capacity \
  element_access \
  at_exception

VECTOR_CORE_PART_2_SUFFIX := \
  push_pop \
  insert_erase \
  clear \
  resize_reserve \
  iterators \
  comparisons

VECTOR_ADV_SUFFIX := \
  element_access_strict iterators_strict comparisons_strict \
  exception_safety lifetime_leakcheck reallocation_stats

VECTOR_WRAPPER_SRC := $(VECTOR_DIR)/test_vector_parts.cpp

CORE_VECTOR_PART_1_SRCS := \
  $(addprefix $(VECTOR_DIR)/$(VECTOR_PREFIX), $(addsuffix .cpp, $(VECTOR_CORE_PART_1_SUFFIX))) \
  $(VECTOR_WRAPPER_SRC)
CORE_VECTOR_PART_2_SRCS := \
  $(addprefix $(VECTOR_DIR)/$(VECTOR_PREFIX), $(addsuffix .cpp, $(VECTOR_CORE_PART_2_SUFFIX))) \
  $(VECTOR_WRAPPER_SRC)
CORE_VECTOR_SRCS := $(CORE_VECTOR_PART_1_SRCS) $(CORE_VECTOR_PART_2_SRCS)

ADV_VECTOR_SRCS  := \
  $(addprefix $(VECTOR_DIR)/$(VECTOR_PREFIX), $(addsuffix .cpp, $(VECTOR_ADV_SUFFIX)))

# ================================= MAP ================================== #

MAP_DIR    := $(TEST_DIR)/map
MAP_PREFIX := test_map_

# --- suffix (Core / Part 1,2,3)
MAP_CORE_PART_1_SUFFIX := rbt_node iterators_basic insert_plain find_bracket
MAP_CORE_PART_2_SUFFIX := insert_balance erase_balance clear_swap count
MAP_CORE_PART_3_SUFFIX := bounds compare

CORE_MAP_PART_1_SRCS := \
  $(addprefix $(MAP_DIR)/$(MAP_PREFIX), $(addsuffix .cpp, $(MAP_CORE_PART_1_SUFFIX)))
CORE_MAP_PART_2_SRCS := \
  $(addprefix $(MAP_DIR)/$(MAP_PREFIX), $(addsuffix .cpp, $(MAP_CORE_PART_2_SUFFIX)))
CORE_MAP_PART_3_SRCS := \
  $(addprefix $(MAP_DIR)/$(MAP_PREFIX), $(addsuffix .cpp, $(MAP_CORE_PART_3_SUFFIX)))
CORE_MAP_SRCS := $(CORE_MAP_PART_1_SRCS) $(CORE_MAP_PART_2_SRCS) $(CORE_MAP_PART_3_SRCS)

# (선택) ADV Map 세트가 생기면 아래처럼 추가:
# MAP_ADV_SUFFIX :=
# ADV_MAP_SRCS := $(addprefix $(MAP_DIR)/$(MAP_PREFIX), $(addsuffix .cpp, $(MAP_ADV_SUFFIX)))

# ================================ STACK ================================= #

STACK_DIR    := $(TEST_DIR)/stack
STACK_PREFIX := test_stack_

# --- suffix (Core + Advanced)
STACK_CORE_SUFFIX := constructors_empty_size push_top_pop types_strings comparisons
STACK_ADV_SUFFIX  := underlying_container exception_safety comparisons_strict performance_smoke

CORE_STACK_SRCS := $(addprefix $(STACK_DIR)/$(STACK_PREFIX), $(addsuffix .cpp, $(STACK_CORE_SUFFIX)))
ADV_STACK_SRCS  := $(addprefix $(STACK_DIR)/$(STACK_PREFIX), $(addsuffix .cpp, $(STACK_ADV_SUFFIX)))

# ============================ STRESS SOURCES ============================= #

STRESS_SRCS := $(STRESS_MAIN)

# ================================= MACROS ================================ #

BUILD_DEFINES := $(addprefix -D, \
  TEST_UTILS_PART_1=$(or $(TEST_UTILS_PART_1),0) \
  TEST_UTILS_PART_2=$(or $(TEST_UTILS_PART_2),0) \
  TEST_VECTOR_PART_1=$(or $(TEST_VECTOR_PART_1),0) \
  TEST_VECTOR_PART_2=$(or $(TEST_VECTOR_PART_2),0) \
  TEST_MAP_PART_1=$(or $(TEST_MAP_PART_1),0) \
  TEST_MAP_PART_2=$(or $(TEST_MAP_PART_2),0) \
  TEST_MAP_PART_3=$(or $(TEST_MAP_PART_3),0) \
  TEST_STACK=$(or $(TEST_STACK),0) \
  TEST_UTILS=$(or $(TEST_UTILS),0) \
  TEST_VECTOR=$(or $(TEST_VECTOR),0) \
  TEST_MAP=$(or $(TEST_MAP),0))

# ================================ TARGETS ================================ #

all:
	$(MAKE) core_all
	$(MAKE) adv_all
	$(MAKE) stress_all

# ----------------------------- HELPER RULES ------------------------------ #
# $(1)=MAIN_SRC, $(2)=SRCS, $(3)=suffix name
define run_build
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) \
		$(BUILD_DEFINES) \
		$(1) $(2) \
		$(CPPFLAGS) $(LDFLAGS) $(LDLIBS) \
		-o $(BIN_DIR)/$(NAME)_$(NAMESPACE)_$(3)
endef

make_core:
	$(call run_build,$(CORE_MAIN),$(CORE_SRCS),$(TEST_NAME))

make_adv:
	$(call run_build,$(ADV_MAIN),$(ADV_SRCS),$(TEST_NAME))

make_stress:
	$(call run_build,,$(STRESS_SRCS),$(TEST_NAME))

# -------------------------- BATCH TARGETS (GROUP) ------------------------ #

core_all:
	$(MAKE) core_utils_part_1
	$(MAKE) core_utils_part_2
	$(MAKE) core_vector_part_1
	$(MAKE) core_vector_part_2
	$(MAKE) core_map_part_1
	$(MAKE) core_map_part_2
	$(MAKE) core_map_part_3
	$(MAKE) core_stack

adv_all:
	$(MAKE) adv_vector
	$(MAKE) adv_stack
# 	$(MAKE) adv_map

# ----------------------------- CORE TARGETS ------------------------------ #

# UTILS
core_utils_part_1:
	$(MAKE) make_core TEST_NAME=core_utils_part_1 \
		TEST_UTILS_PART_1=1 \
		CORE_SRCS="$(CORE_UTILS_PART_1_SRCS)"

core_utils_part_2:
	$(MAKE) make_core TEST_NAME=core_utils_part_2 \
		TEST_UTILS_PART_2=1 \
		CORE_SRCS="$(CORE_UTILS_PART_2_SRCS)"

# VECTOR
core_vector_part_1:
	$(MAKE) make_core TEST_NAME=core_vector_part_1 \
		TEST_VECTOR_PART_1=1 \
		CORE_SRCS="$(CORE_VECTOR_PART_1_SRCS)"

core_vector_part_2:
	$(MAKE) make_core TEST_NAME=core_vector_part_2 \
		TEST_VECTOR_PART_2=1 \
		CORE_SRCS="$(CORE_VECTOR_PART_2_SRCS)"

# MAP
core_map_part_1:
	$(MAKE) make_core TEST_NAME=core_map_part_1 \
		TEST_MAP_PART_1=1 \
		CORE_SRCS="$(CORE_MAP_PART_1_SRCS)"

core_map_part_2:
	$(MAKE) make_core TEST_NAME=core_map_part_2 \
		TEST_MAP_PART_2=1 \
		CORE_SRCS="$(CORE_MAP_PART_2_SRCS)"

core_map_part_3:
	$(MAKE) make_core TEST_NAME=core_map_part_3 \
		TEST_MAP_PART_3=1 \
		CORE_SRCS="$(CORE_MAP_PART_3_SRCS)"

# STACK
core_stack:
	$(MAKE) make_core TEST_NAME=core_stack \
		TEST_STACK=1 \
		CORE_SRCS="$(CORE_STACK_SRCS)"

# ----------------------------- ADV TARGETS ------------------------------- #

adv_vector:
	$(MAKE) make_adv TEST_NAME=adv_vector \
		ADV_SRCS="$(ADV_VECTOR_SRCS)"

adv_stack:
	$(MAKE) make_adv TEST_NAME=adv_stack \
		ADV_SRCS="$(ADV_STACK_SRCS)"

adv_map:
	$(MAKE) make_adv TEST_NAME=adv_map \
		ADV_SRCS="$(ADV_MAP_SRCS)"

# ----------------------------- STRESS TARGETS ---------------------------- #

stress_all:
	$(MAKE) stress_vector
	$(MAKE) stress_map
	$(MAKE) stress_stack

stress_vector:
	$(MAKE) make_stress TEST_NAME=stress_vector TEST_VECTOR=1

stress_map:
	$(MAKE) make_stress TEST_NAME=stress_map TEST_MAP=1

stress_stack:
	$(MAKE) make_stress TEST_NAME=stress_stack TEST_STACK=1

# ---------------------------- CLEAN / REBUILD ---------------------------- #

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)
	rm -f $(NAME)_*

re: fclean all

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re \
	core_all adv_all stress_all \
	core_utils_part_1 core_utils_part_2 \
	core_vector_part_1 core_vector_part_2 \
	core_map_part_1 core_map_part_2 core_map_part_3 \
	core_stack \
	adv_vector adv_stack \
	stress_vector stress_map stress_stack \
	make_core make_adv make_stress
