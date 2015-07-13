##
##  Copyright(c) Tellabs Transport Group Inc. All rights reserved.
##
##
##  ---------------------------------------------------------------------------
##
## Makefile for TL1Core submodule
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
##
#==============================================================================
# User section:
# -Assign the library's name to 'MYLIB'
# -'MYOBJS' is automatically assigned at each build. Reassign only if source 
#  files aren't all found in the 'SRCDIR'
# -Add platform specific code between appropriate 'if' conditions if necessary
#
#==============================================================================

MYLIB  = TL1Core

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
PRJINCPATH  = \
	-I$(TTG_CPDIR)/ControllerServices \
	-I$(TTG_CPDIR)/ControllerServices/TL1Services \
	-I$(TTG_CPDIR)/ControllerServices/Agent \
	-I$(CP_PREFERRED)cca/inc \
	-I$(CP_ALTERNATE)cca/inc \
	-I$(CP_PREFERRED)atmsim/system \
	-I$(CP_ALTERNATE)atmsim/system \
	-I$(CNTL_PLANE_BASE)/api/inc \
	-I$(DCL_BASE)/comn/custom


PRJLIBPATH  =   
PRJLIBS     = 
PRJDEFINES  = 
MERGE_LIBNAME = TL1Core

default : $(MYLIB)
all : default

# Set CONTROLLER_CODE before including $(MAKERULES)
CONTROLLER_CODE=YES
include $(MAKERULES)


$(MYLIB) :
	@$(MAKE)   \
	OBJS="$(MYOBJS)" \
	LIBNAME=$(MYLIB) \
	LIBDIR=../$(LIBDIR) \
	$(MAKETARGET:default=library)

