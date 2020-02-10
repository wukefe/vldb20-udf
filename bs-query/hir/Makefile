# Note:
# - $(HORSE_BASE)/libs/lib: (-lcore, libcore.a) and (-lpcre2-8, libpcre2-8.a) 
# - libcore.a must be placed before libpcre2-8.a
#
# Setup:
# - export LD_LIBRARY_PATH=${HORSE_BASE}/libs/linasm/lib:${LD_LIBRARY_PATH}

targ = compile
cccc = $(compiler) # gcc-8
include_files = main.c
include_dirs  = -I$(HORSE_BASE)/libs/include/ -I$(lib_header)
include_libs  = -L$(HORSE_BASE)/libs/lib -lcore -lpcre2-8 -lm -lstdc++
include_flags = -DQALL -std=c99 -fopenmp -march=native 
include_flags_c = $(include_flags) -DSELECT_C # -v -ftime-report
include_math  = -I$(HORSE_BASE)/libs/linasm/include -L$(HORSE_BASE)/libs/linasm/lib -llinasm

ifeq ($(opt),debug)
	opt_level = -g
else ifeq ($(opt),profile)
	opt_level = -g -O3
else
	opt_level = -O3
endif

all: bs0

bs%:
	$(cccc) -o "$(targ)-$@" \
    $(opt_level)       \
    $(include_files)   \
    $(include_dirs)    \
    $(include_libs)    \
    $(include_flags)   \
    $(include_math)   \
    -DNO_PROFILE_INFO # -DLINUX_ASSEMBLY


