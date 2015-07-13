##
##  Copyright(c) Tellabs, Inc. All rights reserved.
##
##  ---------------------------------------------------------------------------
##
## Makefile for TsPii submodule
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

MYLIB  = TsPii

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
PRJLIBPATH  =   
PRJLIBS     = 
PRJDEFINES  = 
MERGE_LIBNAME = TSPII

ifeq ($(PLATFORM),WIN32)
default : $(MYLIB)
else
default : $(MYLIB)
	@$(MAKE)   \
	CLEANLIST="$(OBJDIR)/TSPII_PilotToneActionFFTFPU.o $(OBJDIR)/TSPII_PilotToneActionFFT.o" \
	$(MAKETARGET:default=$(OBJDIR)/TSPII_PilotToneActionFFTFPU.o $(OBJDIR)/TSPII_PilotToneActionFFT.o)
endif

all : default

include $(MAKERULES)


# clean all .o's and .a's created by this makefile
# the .o's come from the top level makerules
# the .a's are listed below
CLEANLIST	+= \
	$(LIBDIR)/$(LIB_PREFIX)$(MYLIB)$(LIB_SUFFIX)


ifeq ($(PLATFORM),WIN32)
    DBGFLAGS = $(Z7DBGFLAGS)  #include the debug info into object instead of pdb file.
endif

# For PSOS, make sure we do not include TSPII_PilotToneActionFFT.o in library since linker should specify 
# which version (with or without floating point unit usage) he will use.
ifeq ($(PLATFORM),PSOSP)
FIND_SRC = \$$(patsubst %.cpp,\$$(OBJDIR)/%\$$(OBJ_SUFFIX),\$$(notdir \$$(patsubst %TSPII_PilotToneActionFFT.cpp,,\$$(wildcard \$$(SRCDIR)/*.cpp))))
FPU_OPT = -tPPCEH:psos
endif

ifneq ($(findstring ${PLATFORM},VXWRKS VXWRKS67),)
FIND_SRC = \$$(patsubst %.cpp,\$$(OBJDIR)/%\$$(OBJ_SUFFIX),\$$(notdir \$$(patsubst %TSPII_PilotToneActionFFT.cpp,,\$$(wildcard \$$(SRCDIR)/*.cpp))))
FPU_OPT = -tPPCE500FF
endif


$(MYLIB) :
	@$(MAKE)   \
	OBJS="$(MYOBJS)" \
	LIBNAME=$(MYLIB) \
	$(MAKETARGET:default=library)

$(OBJDIR)/TSPII_PilotToneActionFFTFPU.o : $(SRCDIR)/TSPII_PilotToneActionFFT.cpp
	@echo Compiling $(subst \,/,$<)     - diab ppc$(DIABVERSION) ...
	$(CXX) $(CXXFLAGS) $(CXXOPTS) -DFPU $(FPU_OPT) -c $(SRCDIR)/TSPII_PilotToneActionFFT.cpp -o $@



ifneq ($(findstring ${PLATFORM},VXWRKS VXWRKS67 PSOSP),)

$(OBJDIR)/TSPII_PilotToneActionFFTFPU.i : $(SRCDIR)/TSPII_PilotToneActionFFT.cpp
	@echo Platform is $(PLATFORM)
	@echo Pre-processing $(subst \,/,$<)     - diab ppc$(DIABVERSION) ...
	$(CXX) $(CXXFLAGS) $(CXXOPTS) -DFPU $(FPU_OPT) -PC -c $(SRCDIR)/TSPII_PilotToneActionFFT.cpp -o $@

$(OBJDIR)/TSPII_PilotToneActionFFTFPU.lst : $(SRCDIR)/TSPII_PilotToneActionFFT.cpp
	@echo Platform is $(PLATFORM)
	@echo Generating assembly listing for $(subst \,/,$<)     - diab ppc$(DIABVERSION) ...
	$(CXX) $(CXXFLAGS) $(CXXOPTS) -DFPU $(FPU_OPT) -Xpass-source -Wa,$(FPU_OPT),-L $< -o $(OBJDIR)$*.duh > $@
	@$(RM) $(OBJDIR)$*.duh

endif


TSPII_HWTF_Common :
	@$(MAKE)   \
	OBJS="$(OBJDIR)/TSPII_PilotToneAction$(OBJ_SUFFIX) \
	$(OBJDIR)/TSPII_PilotToneActionFFT$(OBJ_SUFFIX)" \
	CXXFLAGS="-I/HWTestSoftware/SoftwareServices/FC -I/HWTestSoftware/SoftwareServices/FC/iostream $(CXXFLAGS) -DHWTF=1" \
	$(MAKETARGET:default=objects)
