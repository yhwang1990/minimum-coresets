#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

include ../Make-config

# define the C source files
SRCS = coreset.cpp 

MAIN = coreset


# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.cpp=.o) 

.PHONY: depend clean

all: $(MAIN)     
  

$(MAIN): $(OBJS) $(LIBDIR)/$(CORESETLIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
    $(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@ 

clean:
    $(RM) *.o *~ $(MAIN)

depend: $(SRCS)
    makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

coreset.o: /usr/include/stdio.h /usr/include/features.h
coreset.o: /usr/include/stdc-predef.h /usr/include/libio.h
coreset.o: /usr/include/_G_config.h /usr/include/wchar.h
coreset.o: /usr/include/stdlib.h /usr/include/alloca.h /usr/include/assert.h
coreset.o: /usr/include/math.h ../Point.h ../IOUtil.h ../Point.h
coreset.o: ../RandUtil.h
