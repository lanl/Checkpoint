# =============== Variables for compiler options ===============

# Defaults

# Compiler choice
comp = gnu

# Language standard version
OPTIONS := -std=c++11

# Optimization switch
opt = no

# MPI parallelization switch
mpi = no

# OpenMP threading switch
omp = no

# OpenMP vectorization switch
simd = no

# Boost library switch
boost = no

# Archiver choice
AR = ar rcs

# "make" command
MAKE = make

# "remove" command
RM = rm -rf

# "sed" command
SED = sed -e

# Windows specifics
ifeq ($(OS),Windows_NT)
    MAKE = C:\MinGW\bin\mingw32-make
    RM = del
    OPTIONS += -DWIN
endif

# GNU compiler
ifeq ($(comp),gnu)
    CXX = g++

    ifeq ($(opt),yes)
        OPTIONS += -O3
    else
        OPTIONS += -g -O0 -Wall -pedantic
    endif

    ifeq ($(omp),yes)
        OPTIONS += -fopenmp
    endif

    ifeq ($(simd),yes)
        OPTIONS += -DSIMD -fopenmp
    endif

endif


# GNU compiler via HomeBrew
ifeq ($(comp),brew)
    CXX = g++-14

    ifeq ($(opt),yes)
        OPTIONS += -O3
    else
        OPTIONS += -g -O0 -Wall -pedantic
    endif

    ifeq ($(omp),yes)
        OPTIONS += -fopenmp
    endif

    ifeq ($(simd),yes)
        OPTIONS += -DSIMD -fopenmp
    endif

endif


# Clang compiler
ifeq ($(comp),clang)
    CXX = clang++

    ifeq ($(opt),yes)
        OPTIONS += -O3
    else
        OPTIONS += -g -O0 -Wall -pedantic
    endif

    ifeq ($(omp),yes)
        OPTIONS += -fopenmp -L/opt/homebrew/opt/llvm/lib
    endif

    ifeq ($(simd),yes)
        OPTIONS += -DSIMD -fopenmp -L/opt/homebrew/opt/llvm/lib
    endif

endif


# Intel Classic compiler
ifeq ($(comp),intelclassic)
    CXX = icpc

    ifeq ($(opt),yes)
        OPTIONS += -O3 # -fast
    else
        OPTIONS += -g -O0 -Wall
    endif

    ifeq ($(mpi),yes)
        CXX = mpicxx
        OPTIONS += -DMPI
    endif

    ifeq ($(omp),yes)
        OPTIONS += -qopenmp
    endif

    ifeq ($(simd),yes)
        OPTIONS += -DSIMD -qopenmp
    endif

endif


# Intel OneAPI compiler
ifeq ($(comp),intel)
    CXX = icpx

    ifeq ($(opt),yes)
        OPTIONS += -O3 # -fast
    else
        OPTIONS += -g -O0 -Wall -fsanitize=address
    endif

    ifeq ($(mpi),yes)
        CXX = mpicxx
        OPTIONS += -DMPI
    endif

    ifeq ($(omp),yes)
        OPTIONS += -qopenmp
    endif

    ifeq ($(simd),yes)
        OPTIONS += -DSIMD -qopenmp
    endif

endif


# Portland compiler
ifeq ($(comp),pgi)
    CXX = pgc++

    ifeq ($(opt),yes)
        OPTIONS += -O3 # -Mipa=fast,inline
    else
        OPTIONS += -g -O0 -Mbounds
    endif

    ifeq ($(omp),yes)
        OPTIONS += -mp
    endif

    ifeq ($(simd),yes)
        OPTIONS += -DSIMD -mp
    endif

endif


# IBM XL compiler
ifeq ($(comp),xl)
    CXX = xlc++

    ifeq ($(opt),yes)
        OPTIONS += -O3
    else
        OPTIONS += -g -O0
    endif

    ifeq ($(omp),yes)
        OPTIONS += -mp
    endif

    ifeq ($(simd),yes)
        OPTIONS += -DSIMD -mp
    endif

endif


# Cray compiler
ifeq ($(comp),cray)
    CXX = CC

    ifeq ($(opt),yes)
        OPTIONS += -O3
    else
        OPTIONS += -g -O0 -Wall -pedantic
    endif

    ifeq ($(omp),yes)
        OPTIONS += -fopenmp
    endif

    ifeq ($(simd),yes)
        OPTIONS += -DSIMD -fopenmp
    endif

endif


# Nvidia compiler
ifeq ($(comp),nvidia)
    CXX = nvc++

    ifeq ($(opt),yes)
        OPTIONS += -O3
    else
        OPTIONS += -g -O0 -Wall -pedantic
    endif

    ifeq ($(omp),yes)
        OPTIONS += -fopenmp
    endif

    ifeq ($(simd),yes)
        OPTIONS += -DSIMD -fopenmp
    endif

endif


# Extensive warnings with GNU compiler
ifeq ($(comp),full)
    CXX = g++

    OPTIONS += -g -O0 -Wall -Weffc++ -pedantic -pedantic-errors -Wextra -Wcast-align \
               -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion \
               -Wdisabled-optimization -Wfloat-equal \
               -Wformat -Wformat=2 -Wformat-nonliteral -Wformat-security \
               -Wformat-y2k -Wimport -Winit-self -Winvalid-pch \
               -Wunsafe-loop-optimizations -Wlong-long -Wmissing-braces \
               -Wmissing-field-initializers -Wmissing-format-attribute \
               -Wmissing-include-dirs -Wmissing-noreturn -Wpacked \
               -Wparentheses -Wpointer-arith -Wredundant-decls -Wreturn-type \
               -Wsequence-point -Wshadow -Wsign-compare -Wstack-protector \
               -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch -Wswitch-default \
               -Wswitch-enum -Wtrigraphs -Wuninitialized \
               -Wunused-function -Wunused-label -Wunused-parameter \
               -Wunused-value -Wunused-variable -Wvariadic-macros \
               -Wvolatile-register-var -Wwrite-strings -fno-var-tracking
endif

# =============== Variables for common paths ===================

UNITEST  =   $(COMPATH)/UniTest

#BOOST    =   $(COMPATH)/boost/boost_1_67_0
#OPTIONS +=   -I$(BOOST)

#GSL      =   $(COMPATH)/gsl/gsl-2.5
#OPTIONS +=   -I$(GSL)/include
GSLLINK :=    
#GSLLINK :=   -L$(GSL)/lib -lgsl -lgslcblas -lm

ifeq ($(mpi),yes)
    OPTIONS += -I$(COMPATH)/parallel/mpi
endif


# =============== Variables for paths and file names ===========

BUILDIR  =   build

PROGRAM  =   $(patsubst %_main.cpp,%,$(wildcard *_main.cpp))
PSRCLOC  =   src
PROGSRC  =   $(PROGRAM)_main.cpp
PROGOBJ  =   $(BUILDIR)/$(PROGRAM)_main.o
PROGLIB  =   lib$(PROGRAM).a
PROGEXE  =   $(PROGRAM)

TESTLOC  =   UniTest
TESTSRC  =   $(UNITEST)/tests.cpp
TESTOBJ  =   $(BUILDIR)/tests.o
TESTLIB  =   libtest$(PROGRAM).a
TESTEXE  =   tests

CPPOBJ   =   $(patsubst $(PSRCLOC)/%.cpp, $(BUILDIR)/%.o, \
             $(wildcard $(PSRCLOC)/*.cpp))

TSTOBJ   =   $(BUILDIR)/Test.o \
             $(patsubst $(PSRCLOC)/%.cpp, $(BUILDIR)/test_%.o, \
             $(wildcard $(PSRCLOC)/*.cpp))

OPTIONS += -I$(PSRCLOC)
LOGFILE  =   $(BUILDIR)/makelog.txt

$(eval CXXPATH = $(shell which $(CXX)))
$(eval CXXINFO = $(shell $(CXXPATH) --version))
define VERSION
$(CXXINFO)
endef
export VERSION

# =============== Rule for the main program ====================

$(PROGEXE) : $(PROGOBJ) $(PROGLIB)
	@echo
	$(CXX) $(OPTIONS) -L. -o $@ $< -l$(PROGRAM) $(GSLLINK)


# =============== Rules for the program sources ================

$(BUILDIR)/$(PROGRAM)_main.o : $(PROGRAM)_main.cpp
	@echo
	$(CXX) $(OPTIONS) -o $@ -c $^

$(BUILDIR)/%.o : $(PSRCLOC)/%.cpp
	@echo
	$(CXX) $(OPTIONS) -o $@ -c $^

lib$(PROGRAM).a : $(CPPOBJ)
	@echo
	@$(MAKE) log
	$(AR) lib$(PROGRAM).a $^


# =============== Rule for the unit-test program ===============

$(TESTEXE) : $(TESTOBJ) $(TESTLIB) $(PROGLIB)
	@echo
	$(CXX) $(OPTIONS) -I$(UNITEST) -I$(TESTLOC) -L. -o $@ $< -ltest$(PROGRAM) -l$(PROGRAM) $(GSLLINK)


# =============== Rules for the unit-test sources ==============

$(TESTOBJ) : $(TESTSRC)
	@$(RM) $(TESTLOC)/tests_headers.inc $(TESTLOC)/tests_runs.inc
	@for i in $(TESTLOC)/*.cpp; do \
	echo $$i | $(SED) 's/\.cpp/(int\&, int\&);/' | $(SED) 's/$(TESTLOC)\//void /' >> $(TESTLOC)/tests_headers.inc; \
	echo $$i | $(SED) 's/\.cpp/(failed_test_count, disabled_test_count);/' | $(SED) 's/$(TESTLOC)\///' >> $(TESTLOC)/tests_runs.inc; \
	done
	@echo
	$(CXX) $(OPTIONS) -I$(UNITEST) -I$(TESTLOC) -o $@ -c $(TESTSRC)

$(BUILDIR)/Test.o : $(UNITEST)/Test.cpp
	@echo
	$(CXX) $(OPTIONS) -I$(UNITEST) -I$(TESTLOC) -o $@ -c $^

$(BUILDIR)/%.o : $(TESTLOC)/%.cpp
	@echo
	$(CXX) $(OPTIONS) -I$(UNITEST) -I$(TESTLOC) -o $@ -c $^

libtest$(PROGRAM).a : $(TSTOBJ)
	@echo
	$(AR) libtest$(PROGRAM).a $^


# =============== Rule for the log file ========================

.PHONY : log
log :
	@echo CXX = $(CXX) > $(LOGFILE)
	@echo OPTIONS = $(OPTIONS) >> $(LOGFILE)
	@echo AR = $(AR) >> $(LOGFILE)
	@echo >> $(LOGFILE)
	@echo $(CXXPATH) --version >> $(LOGFILE)
	@echo $$VERSION >> $(LOGFILE)


# =============== Rules for cleanup ============================

.PHONY : clean_obj
clean_obj :
	@$(RM) $(PROGOBJ) $(CPPOBJ) $(TSTOBJ) $(TESTOBJ)

.PHONY : clean
clean :
	@$(MAKE) clean_obj
	@$(RM) lib$(PROGRAM).a libtest$(PROGRAM).a $(LOGFILE)

.PHONY : clean_exe
clean_exe :
	@$(RM) $(PROGEXE) $(TESTEXE) *.x

.PHONY : clean_all
clean_all :
	@$(MAKE) clean
	@$(MAKE) clean_exe
	@$(RM) $(TESTLOC)/tests_headers.inc $(TESTLOC)/tests_runs.inc

