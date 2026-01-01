.DEFAULT_GOAL := all
NAME          := containers

# ================================= SETTINGS ================================= #

NAMESPACE      ?= ft
CXXSTD         := c++98

THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))
MKDIR         := $(dir $(abspath $(THIS_MAKEFILE)))
# TODO: include your implemented containers path (relative to this Makefile)
YOUR_IMPL_PATH = #/path/to/your/containers/include
# ex) YOUR_IMPL_PATH = $(abspath $(MKDIR)/../../include/ft)

MAKEFLAGS += --no-print-directory

# ================================ COMPILER ================================== #

CXX := c++
ifeq ($(NAMESPACE),std)
  NAMESPACE_FLAG := -DSTD_MODE=1 # 내부적으로 분기 처리함 (기본값: ft)
  CXXSTD         = c++11
else
  NAMESPACE_FLAG :=
endif
CXXSTDFLAG := -std=$(CXXSTD)

# BASIC
BASIC_SANITIZE_FLAG ?= -fsanitize=address -g3
BASIC_OPT_FLAGS 	?=

# STRESS
STRESS_SANITIZE_FLAG ?= -fsanitize=address -g3
STRESS_OPT_FLAGS ?=

# PERF
PERF_SANITIZE_FLAG ?= -fsanitize=address -g3
PERF_OPT_FLAGS ?= -O3 -DNDEBUG -march=native

CXXFLAGS_COMMON	:= $(CXXSTDFLAG) -MMD -MP -Wall -Wextra -Werror 
CXXFLAGS_BASIC 	:= $(CXXFLAGS_COMMON) $(NAMESPACE_FLAG) $(BASIC_SANITIZE_FLAG)
CXXFLAGS_STRESS := $(CXXFLAGS_COMMON) $(NAMESPACE_FLAG) $(STRESS_OPT_FLAGS) $(STRESS_SANITIZE_FLAG)
CXXFLAGS_PERF 	:= $(CXXFLAGS_COMMON) $(NAMESPACE_FLAG) $(PERF_OPT_FLAGS) $(PERF_SANITIZE_FLAG)

# Preprocess and Link
ifneq ($(filter clean fclean re,$(MAKECMDGOALS)),)
  CONTAINERS_PATH :=
else
  CONTAINERS_PATH := $(shell find "$(YOUR_IMPL_PATH)" -type d -print)
endif
CPPFLAGS   := $(addprefix -I,$(CONTAINERS_PATH)) -I./include
LDFLAGS    :=
LDLIBS     :=

# ============================== DIRECTORIES ============================== #

TEST_DIR := .
BIN_DIR  := ../bin
OBJ_DIR  := obj

OBJ_BASIC_DIR  := $(OBJ_DIR)/$(NAMESPACE)/basic
OBJ_STRESS_DIR := $(OBJ_DIR)/$(NAMESPACE)/stress
OBJ_PERF_DIR   := $(OBJ_DIR)/$(NAMESPACE)/perf

# ============================== MAIN SOURCES ================================ #

MAIN_SRC  := $(TEST_DIR)/main.cpp

# =========================== USER DEFINED FUNTION =========================== #

# $(call mkpath,dir,prefix,items,suffix)
# suffix는 .cpp로 고정
mk_path = $(patsubst %,$(1)/%,$(addsuffix .cpp,$(addprefix $(2),$(3))))

# $(call to_obj,OBJDIR,src.cpp) -> OBJDIR/src.o
to_obj = $(patsubst %.cpp,$(1)/%.o,$(2))

define compile_obj
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(1) -c $< -o $@
endef

# ============================= UTILS SOURCES ================================ #

UTILS_DIR        := $(TEST_DIR)/utils
UTILS_BASIC_DIR  := $(UTILS_DIR)/basic
UTILS_STRESS_DIR := $(UTILS_DIR)/stress
UTILS_PERF_DIR   := $(UTILS_DIR)/perf

UTILS_PREFIX 	    := test_utils_

BASIC_UTILS_FILES := \
  test_utils_basic_pair \
  test_utils_basic_equal \
  test_utils_basic_lexicographical_compare \
  test_utils_basic_enable_if \
  test_utils_basic_is_integral \
  test_utils_basic_iterator_traits \
  test_utils_basic_reverse_iterator

STRESS_UTILS_FILES := \
  test_utils_stress_pair \
  test_utils_stress_compare

PERF_UTILS_FILES := \
  test_utils_perf_pair \
  test_utils_perf_compare

BASIC_UTILS_SRCS  := \
  $(call mk_path,$(UTILS_BASIC_DIR),,$(BASIC_UTILS_FILES))

STRESS_UTILS_SRCS := \
  $(call mk_path,$(UTILS_STRESS_DIR),,$(STRESS_UTILS_FILES))

PERF_UTILS_SRCS   := \
  $(call mk_path,$(UTILS_PERF_DIR),,$(PERF_UTILS_FILES))

# ============================= VECTOR SOURCES =============================== #

VECTOR_DIR        := $(TEST_DIR)/vector
VECTOR_BASIC_DIR  := $(VECTOR_DIR)/basic
VECTOR_STRESS_DIR := $(VECTOR_DIR)/stress
VECTOR_PERF_DIR   := $(VECTOR_DIR)/perf

BASIC_VECTOR_FILES := \
  test_vector_basic_constructors \
  test_vector_basic_assignment \
  test_vector_basic_capacity \
  test_vector_basic_element_access \
  test_vector_basic_at_exception \
  test_vector_basic_push_pop \
  test_vector_basic_insert_erase \
  test_vector_basic_clear \
  test_vector_basic_resize_reserve \
  test_vector_basic_iterators \
  test_vector_basic_comparisons \
  test_vector_basic_element_access_strict \
  test_vector_basic_iterators_strict \
  test_vector_basic_comparisons_strict \
  test_vector_basic_exception_safety \
  test_vector_basic_lifetime_leakcheck \
  test_vector_basic_reallocation_stats

STRESS_VECTOR_FILES := \
  test_vector_stress_push_back \
  test_vector_stress_insert \
  test_vector_stress_erase

PERF_VECTOR_FILES := \
  test_vector_perf_push_back \
  test_vector_perf_random_access \
  test_vector_perf_reallocation

BASIC_VECTOR_SRCS  := \
  $(call mk_path,$(VECTOR_BASIC_DIR),,$(BASIC_VECTOR_FILES))

STRESS_VECTOR_SRCS := \
  $(call mk_path,$(VECTOR_STRESS_DIR),,$(STRESS_VECTOR_FILES))

PERF_VECTOR_SRCS   := \
  $(call mk_path,$(VECTOR_PERF_DIR),,$(PERF_VECTOR_FILES))

# ============================== MAP SOURCES ================================= #

MAP_DIR        := $(TEST_DIR)/map
MAP_BASIC_DIR  := $(MAP_DIR)/basic
MAP_STRESS_DIR := $(MAP_DIR)/stress
MAP_PERF_DIR   := $(MAP_DIR)/perf

BASIC_MAP_FILES := \
  test_map_basic_rbt_node \
  test_map_basic_iterators_basic \
  test_map_basic_insert_plain \
  test_map_basic_find_bracket \
  test_map_basic_insert_balance \
  test_map_basic_erase_balance \
  test_map_basic_clear_swap \
  test_map_basic_count \
  test_map_basic_bounds \
  test_map_basic_compare

STRESS_MAP_FILES := \
  test_map_stress_insert \
  test_map_stress_erase

PERF_MAP_FILES := \
  test_map_perf_insert \
  test_map_perf_find

BASIC_MAP_SRCS  := \
  $(call mk_path,$(MAP_BASIC_DIR),,$(BASIC_MAP_FILES))

STRESS_MAP_SRCS := \
  $(call mk_path,$(MAP_STRESS_DIR),,$(STRESS_MAP_FILES))

PERF_MAP_SRCS   := \
  $(call mk_path,$(MAP_PERF_DIR),,$(PERF_MAP_FILES))

# ============================== STACK SOURCES =============================== #

STACK_DIR        := $(TEST_DIR)/stack
STACK_BASIC_DIR  := $(STACK_DIR)/basic
STACK_STRESS_DIR := $(STACK_DIR)/stress
STACK_PERF_DIR   := $(STACK_DIR)/perf

BASIC_STACK_SUFFIX := \
  test_stack_basic_constructors_empty_size \
  test_stack_basic_push_top_pop \
  test_stack_basic_types_strings \
  test_stack_basic_comparisons \
  test_stack_basic_underlying_container \
  test_stack_basic_exception_safety \
  test_stack_basic_comparisons_strict \
  test_stack_basic_performance_smoke

STRESS_STACK_FILES := \
  test_stack_stress_push_pop

PERF_STACK_FILES := \
  test_stack_perf_push_pop

BASIC_STACK_SRCS  := \
  $(call mk_path,$(STACK_BASIC_DIR),,$(BASIC_STACK_SUFFIX))

STRESS_STACK_SRCS := \
  $(call mk_path,$(STACK_STRESS_DIR),,$(STRESS_STACK_FILES))

PERF_STACK_SRCS   := \
  $(call mk_path,$(STACK_PERF_DIR),,$(PERF_STACK_FILES))

# ================================ OUTPUTS =================================== #

# prefix
BASIC_BIN_PREFIX  := $(BIN_DIR)/$(NAMESPACE)_basic
STRESS_BIN_PREFIX := $(BIN_DIR)/$(NAMESPACE)_stress
PERF_BIN_PREFIX   := $(BIN_DIR)/$(NAMESPACE)_perf

# bin
BASIC_UTILS_BIN  := $(BASIC_BIN_PREFIX)_utils
BASIC_VECTOR_BIN := $(BASIC_BIN_PREFIX)_vector
BASIC_MAP_BIN    := $(BASIC_BIN_PREFIX)_map
BASIC_STACK_BIN  := $(BASIC_BIN_PREFIX)_stack

STRESS_UTILS_BIN  := $(STRESS_BIN_PREFIX)_utils
STRESS_VECTOR_BIN := $(STRESS_BIN_PREFIX)_vector
STRESS_MAP_BIN    := $(STRESS_BIN_PREFIX)_map
STRESS_STACK_BIN  := $(STRESS_BIN_PREFIX)_stack

PERF_UTILS_BIN  := $(PERF_BIN_PREFIX)_utils
PERF_VECTOR_BIN := $(PERF_BIN_PREFIX)_vector
PERF_MAP_BIN    := $(PERF_BIN_PREFIX)_map
PERF_STACK_BIN  := $(PERF_BIN_PREFIX)_stack

# ================================ TARGETS ================================ #

.PHONY: all basic_all stress_all perf_all \
        basic_utils basic_vector basic_map basic_stack \
        stress_utils stress_vector stress_map stress_stack \
        perf_utils perf_vector perf_map perf_stack \
        clean fclean re

all: basic_all stress_all perf_all

# ------------------------------- BASIC ---------------------------------- #

# src
BASIC_UTILS_ALL_SRCS  := $(MAIN_SRC) $(BASIC_UTILS_SRCS)  $(UTILS_DISPATCH_SRC)
BASIC_VECTOR_ALL_SRCS := $(MAIN_SRC) $(BASIC_VECTOR_SRCS) $(VECTOR_DISPATCH_SRC)
BASIC_MAP_ALL_SRCS    := $(MAIN_SRC) $(BASIC_MAP_SRCS)    $(MAP_ALL_PARTS_SRC)
BASIC_STACK_ALL_SRCS  := $(MAIN_SRC) $(BASIC_STACK_SRCS)  $(STACK_DISPATCH_SRC)

# obj
BASIC_UTILS_OBJS  := $(call to_obj,$(OBJ_BASIC_DIR),$(BASIC_UTILS_ALL_SRCS))
BASIC_VECTOR_OBJS := $(call to_obj,$(OBJ_BASIC_DIR),$(BASIC_VECTOR_ALL_SRCS))
BASIC_MAP_OBJS    := $(call to_obj,$(OBJ_BASIC_DIR),$(BASIC_MAP_ALL_SRCS))
BASIC_STACK_OBJS  := $(call to_obj,$(OBJ_BASIC_DIR),$(BASIC_STACK_ALL_SRCS))

# .d
BASIC_DEPS := $(BASIC_UTILS_OBJS:.o=.d) $(BASIC_VECTOR_OBJS:.o=.d) \
              $(BASIC_MAP_OBJS:.o=.d)  $(BASIC_STACK_OBJS:.o=.d)

basic_all: $(BASIC_UTILS_BIN) $(BASIC_VECTOR_BIN) $(BASIC_MAP_BIN) $(BASIC_STACK_BIN)

basic_utils:  $(BASIC_UTILS_BIN)
basic_vector: $(BASIC_VECTOR_BIN)
basic_map:    $(BASIC_MAP_BIN)
basic_stack:  $(BASIC_STACK_BIN)

$(BASIC_UTILS_BIN): CXXFLAGS_BASIC += -DTEST_UTILS_BASIC=1
$(BASIC_UTILS_BIN): $(BASIC_UTILS_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_BASIC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(BASIC_VECTOR_BIN): CXXFLAGS_BASIC += -DTEST_VECTOR_BASIC=1
$(BASIC_VECTOR_BIN): $(BASIC_VECTOR_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_BASIC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(BASIC_MAP_BIN): CXXFLAGS_BASIC += -DTEST_MAP_BASIC=1
$(BASIC_MAP_BIN): $(BASIC_MAP_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_BASIC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(BASIC_STACK_BIN): CXXFLAGS_BASIC += -DTEST_STACK_BASIC=1
$(BASIC_STACK_BIN): $(BASIC_STACK_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_BASIC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_BASIC_DIR)/%.o: %.cpp
	$(call compile_obj,$(CXXFLAGS_BASIC))

# ------------------------------ STRESS ---------------------------------- #

STRESS_UTILS_ALL_SRCS  := $(MAIN_SRC) $(STRESS_UTILS_SRCS)  $(UTILS_DISPATCH_SRC)
STRESS_VECTOR_ALL_SRCS := $(MAIN_SRC) $(STRESS_VECTOR_SRCS) $(VECTOR_DISPATCH_SRC)
STRESS_MAP_ALL_SRCS    := $(MAIN_SRC) $(STRESS_MAP_SRCS)    $(MAP_ALL_PARTS_SRC)
STRESS_STACK_ALL_SRCS  := $(MAIN_SRC) $(STRESS_STACK_SRCS)  $(STACK_DISPATCH_SRC)

STRESS_UTILS_OBJS  := $(call to_obj,$(OBJ_STRESS_DIR),$(STRESS_UTILS_ALL_SRCS))
STRESS_VECTOR_OBJS := $(call to_obj,$(OBJ_STRESS_DIR),$(STRESS_VECTOR_ALL_SRCS))
STRESS_MAP_OBJS    := $(call to_obj,$(OBJ_STRESS_DIR),$(STRESS_MAP_ALL_SRCS))
STRESS_STACK_OBJS  := $(call to_obj,$(OBJ_STRESS_DIR),$(STRESS_STACK_ALL_SRCS))

STRESS_DEPS := $(STRESS_UTILS_OBJS:.o=.d) $(STRESS_VECTOR_OBJS:.o=.d) \
               $(STRESS_MAP_OBJS:.o=.d)  $(STRESS_STACK_OBJS:.o=.d)

stress_all: $(STRESS_UTILS_BIN) $(STRESS_VECTOR_BIN) $(STRESS_MAP_BIN) $(STRESS_STACK_BIN)

stress_utils:  $(STRESS_UTILS_BIN)
stress_vector: $(STRESS_VECTOR_BIN)
stress_map:    $(STRESS_MAP_BIN)
stress_stack:  $(STRESS_STACK_BIN)

$(STRESS_UTILS_BIN): CXXFLAGS_STRESS += -DTEST_UTILS_STRESS=1
$(STRESS_UTILS_BIN): $(STRESS_UTILS_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_STRESS) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(STRESS_VECTOR_BIN): CXXFLAGS_STRESS += -DTEST_VECTOR_STRESS=1
$(STRESS_VECTOR_BIN): $(STRESS_VECTOR_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_STRESS) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(STRESS_MAP_BIN): CXXFLAGS_STRESS += -DTEST_MAP_STRESS=1
$(STRESS_MAP_BIN): $(STRESS_MAP_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_STRESS) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(STRESS_STACK_BIN): CXXFLAGS_STRESS += -DTEST_STACK_STRESS=1
$(STRESS_STACK_BIN): $(STRESS_STACK_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_STRESS) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_STRESS_DIR)/%.o: %.cpp
	$(call compile_obj,$(CXXFLAGS_STRESS))

# ------------------------------- PERF ----------------------------------- #

PERF_UTILS_ALL_SRCS  := $(MAIN_SRC) $(PERF_UTILS_SRCS)  $(UTILS_DISPATCH_SRC)
PERF_VECTOR_ALL_SRCS := $(MAIN_SRC) $(PERF_VECTOR_SRCS) $(VECTOR_DISPATCH_SRC)
PERF_MAP_ALL_SRCS    := $(MAIN_SRC) $(PERF_MAP_SRCS)    $(MAP_ALL_PARTS_SRC)
PERF_STACK_ALL_SRCS  := $(MAIN_SRC) $(PERF_STACK_SRCS)  $(STACK_DISPATCH_SRC)

PERF_UTILS_OBJS  := $(call to_obj,$(OBJ_PERF_DIR),$(PERF_UTILS_ALL_SRCS))
PERF_VECTOR_OBJS := $(call to_obj,$(OBJ_PERF_DIR),$(PERF_VECTOR_ALL_SRCS))
PERF_MAP_OBJS    := $(call to_obj,$(OBJ_PERF_DIR),$(PERF_MAP_ALL_SRCS))
PERF_STACK_OBJS  := $(call to_obj,$(OBJ_PERF_DIR),$(PERF_STACK_ALL_SRCS))

PERF_DEPS := $(PERF_UTILS_OBJS:.o=.d) $(PERF_VECTOR_OBJS:.o=.d) \
             $(PERF_MAP_OBJS:.o=.d)  $(PERF_STACK_OBJS:.o=.d)

perf_all: $(PERF_UTILS_BIN) $(PERF_VECTOR_BIN) $(PERF_MAP_BIN) $(PERF_STACK_BIN)

perf_utils:  $(PERF_UTILS_BIN)
perf_vector: $(PERF_VECTOR_BIN)
perf_map:    $(PERF_MAP_BIN)
perf_stack:  $(PERF_STACK_BIN)

$(PERF_UTILS_BIN): CXXFLAGS_PERF += -DTEST_UTILS_PERF=1
$(PERF_UTILS_BIN): $(PERF_UTILS_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_PERF) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(PERF_VECTOR_BIN): CXXFLAGS_PERF += -DTEST_VECTOR_PERF=1
$(PERF_VECTOR_BIN): $(PERF_VECTOR_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_PERF) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(PERF_MAP_BIN): CXXFLAGS_PERF += -DTEST_MAP_PERF=1
$(PERF_MAP_BIN): $(PERF_MAP_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_PERF) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(PERF_STACK_BIN): CXXFLAGS_PERF += -DTEST_STACK_PERF=1
$(PERF_STACK_BIN): $(PERF_STACK_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS_PERF) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_PERF_DIR)/%.o: %.cpp
	$(call compile_obj,$(CXXFLAGS_PERF))

# ------------------------------- DEPS INCLUDE ------------------------------- #

-include $(BASIC_DEPS) $(STRESS_DEPS) $(PERF_DEPS)

# ----------------------------- CLEAN / REBUILD ------------------------------ #

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(BIN_DIR)

re: fclean all
