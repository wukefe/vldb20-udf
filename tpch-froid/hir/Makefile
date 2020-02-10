# Note:
# - libhorse.a must be placed before libpcre2-8.a

gcc_lynx       = gcc
gcc_tigger     = gcc-8
gcc_sableintel = gcc-8
gcc_sableamd1  = amd-gcc8

targ = compile
cccc = ${gcc_${sys}} #clang-6 / gcc-8
include_files = main.c
include_dirs  = -I$(HORSE_BASE)/libs/include/ -I$(lib_path)
include_libs  = -L${HORSE_BASE}/libs/lib -lcore -lpcre2-8
include_flags = -DQALL -std=c99 -fopenmp -lm -lstdc++ -march=native 
include_flags_c = $(include_flags) -DSELECT_C # -v -ftime-report

ifeq ($(opt),debug)
	opt_level = -g
else ifeq ($(opt),profile)
	opt_level = -g -O3
else
	opt_level = -O3
endif

all: q6

q%:
	$(cccc) -o "$(targ)-$@" \
    $(opt_level)       \
    $(include_files)   \
    $(include_dirs)    \
    $(include_libs)    \
    $(include_flags_c) \
	-DHORSE_${src} -DNO_PROFILE_INFO

