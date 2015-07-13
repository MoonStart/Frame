##
##  Copyright(c) Tellabs Transport Group Inc. All rights reserved.
##
##
##  ---------------------------------------------------------------------------
##
## Makefile for TelCommon submodule
##

##-----------------------------------------------------------------------------
## Template for submodule makefile:
## 
## User must assign a value to the variable 'MYLIB' which is the name of the 
## library that will be generated. Change 'replace_with_your_lib_name' for your 
## library's name.
##
## 'MYOBJS' are assigned to 'FIND_SRC' macro, which automatically fetches the 
## list of '.cpp' files in the source directory pointed by variable 'SRCDIR'. 
## 'SRCDIR' defaults to '../src' but can be redefined when the '@MAKE ...' 
## command is invoked in a target. To do so, simply add the line 
## 'SRCDIR=new_src_dir \' before the 'OBJS=$(MYOBJS) \' line. The user doesn't 
## need to specify the list of objects to be compiled, unless the source files 
## aren't all '.cpp' or if it isn't suitable to compile every one of them. To 
## manually specify the source files to compile, replace '$(FIND_SRC)' in 
## 'MYOBJ' for the complete list of objects separated by spaces in the 
## '$(OBJDIR)/ObjectName$(OBJ_SUFFIX)' format.


#==============================================================================
# User section:
# -Assign the library's name to 'MYLIB'
# -'MYOBJS' is automatically assigned at each build. Reassign only if source 
#  files aren't all found in the 'SRCDIR'
# -Add platform specific code between appropriate 'if' conditions if necessary
#
#==============================================================================

MYLIB  = TelCommon

#Cleanup needed in src directory before 'FIND_SRC' macro can be used
MYOBJS = $(FIND_SRC)

#ifeq ($(PLATFORM),WIN32)
#endif
#
#ifeq ($(PLATFORM),PSOSP)
#endif
#
#ifeq ($(PLATFORM),SUN)
#endif

#===============================================================================
# Build specific section:
# -Contains the targets to be built.
#
#===============================================================================

MAKERULES   = $(TTG_ROOT)/proj/makerules.$(PLATFORM)
PRJINCPATH  =  
PRJLIBPATH  = -L../../lib  
PRJLIBS     = 
PRJDEFINES  = 

default : $(MYLIB)
all : default

include $(MAKERULES)
ifeq ($(PLATFORM),WIN32)
    DBGFLAGS = $(Z7DBGFLAGS)  #include the debug info into object instead of pdb file.
endif


$(MYLIB) :
	@$(MAKE)   \
	OBJS="$(MYOBJS)" \
	LIBNAME=$(MYLIB) \
	$(MAKETARGET:default=library)
