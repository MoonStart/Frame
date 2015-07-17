##
##  Copyright(c) Tellabs, Inc. All rights reserved.
##
##-----------------------------------------------------------------------------
##
## Makefile for TsPiiSpecificSPM8560 submodule
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

MYLIB  = TsPiiSpecificSPM8560

MYOBJS = $(FIND_SRC)

#===============================================================================
# Build specific section:
# -Contains the targets to be built.
#
#===============================================================================

MAKERULES   = $(TTG_ROOT)/proj/makerules.$(PLATFORM)
PRJINCPATH  = \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/TelecomServices \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/Devices \
	-I$(TTG_ROOT)/CommonPlatforms/CardServices/Devices \
	-I$(TTG_ROOT)/SoftwareServices/devices/logicalModel/hdr \
	-I$(TTG_ROOT)/SoftwareServices/devices/logicalModel/genericDevices/hdp/hdr \
	-I$(TTG_ROOT)/SoftwareServices/devices/logicalModel/genericDevices/pm4351/hdr \
	-I$(TTG_ROOT)/CardServices/CsPii \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices\OsiSupport \
	-I$(TTG_SPM8560DIR)/CardServices \
	-I$(TTG_SPM8560DIR)/CardServices/Devices \

PRJLIBPATH  =   
PRJLIBS     = 
PRJDEFINES  = 
MERGE_LIBNAME = TSPII

default : $(MYLIB)
all : default

# Set CONTROLLER_CODE before including $(MAKERULES)
CONTROLLER_CODE=YES
include $(MAKERULES)


# clean all .o's and .a's created by this makefile
# the .o's come from the top level makerules
# the .a's are listed below
CLEANLIST	+= \
	$(LIBDIR)/$(LIB_PREFIX)$(MYLIB)$(LIB_SUFFIX)

ifeq ($(PLATFORM),VXWRKS67)
# The 5.7.0.0 Wind River compiler has a bug which causes it to fall
# off the rails when building particular files with any optimization
# enabled. Override the default optimization with explicit build rules.

# Eliminate -O and -XO from CXXFLAGS for these build rules.
NO_OPT_CXXFLAGS := $(filter-out -XO -O,$(CXXFLAGS))

# Reduce compile from 14 minutes down to 54 seconds.
$(OBJDIR)/TSPII_OscMapperFpgaDrv.o : $(SRCDIR)/TSPII_OscMapperFpgaDrv.cpp
	@printf "     Compiling $< at "
	@$(DATETIME)
	@$(RM) $@
	@$(SET_TEXT_RED) && $(CXX) $(NO_OPT_CXXFLAGS) $(CXXOPTS) $< -o $@ || ($(SET_TEXT_BLUE) && $(ECHO) "\n$(NO_OPT_CXXFLAGS) $(CXXOPTS) $< -o $@" && $(SET_TEXT_NORMAL) && false)
	@printf "Done building $@ at "
	@$(SET_TEXT_NORMAL)
	@$(DATETIME)

$(OBJDIR)/TSPII_OscMapperFpgaDrv.s : $(SRCDIR)/TSPII_OscMapperFpgaDrv.cpp
	@printf " Generating assembly file for $< at "
	@$(DATETIME)
	@$(RM) $@
	@$(SET_TEXT_RED) && $(CXX) $(NO_OPT_CXXFLAGS) $(CXXOPTS) -S $< -o $@ || ($(SET_TEXT_BLUE) && $(ECHO) "\n$(CXX) $(NO_OPT_CXXFLAGS) $(CXXOPTS) -S $< -o $@" && $(SET_TEXT_NORMAL) && false)
	@$(SET_TEXT_NORMAL)
	@printf "Done generating assembly file $@ at "
	@$(DATETIME)

$(OBJDIR)/TSPII_OscMapperFpgaDrv.lst : $(SRCDIR)/TSPII_OscMapperFpgaDrv.cpp
	@printf " Generating assembly listing for $< at "
	@$(DATETIME)
	@$(RM) $@
	@$(SET_TEXT_RED) && $(CXX) $(NO_OPT_CXXFLAGS) $(CXXOPTS) -Xpass-source -Wa,$(TARGET_PROC),-L $< -o $(OBJDIR)/TSPII_OscMapperFpgaDrv.duh > $@ || ($(SET_TEXT_BLUE) && $(ECHO) "\n$(CXX) $(NO_OPT_CXXFLAGS) $(CXXOPTS) -Xpass-source -Wa,$(TARGET_PROC),-L $< -o $(OBJDIR)/TSPII_OscMapperFpgaDrv.duh > $@" && $(SET_TEXT_NORMAL) && false)
	@$(SET_TEXT_NORMAL)
	@$(RM) $(OBJDIR)/TSPII_OscMapperFpgaDrv.duh
	@printf "Done generating assembly listing $@ at "
	@$(DATETIME)
endif

$(MYLIB) :
	@$(MAKE)   \
	OBJS="$(MYOBJS)" \
	LIBNAME=$(MYLIB) \
	LIBDIR=../$(LIBDIR) \
	$(MAKETARGET:default=library)
