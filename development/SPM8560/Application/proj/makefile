##
##  Copyright(c) Tellabs, Inc. All rights reserved.
##
##  ---------------------------------------------------------------------------
##
## Makefile for SPM8560 application
##
##-----------------------------------------------------------------------------
## Template for application makefile:
##
## This makefile is used to generate a card application. It generates necessary
## libraries and links them into an executable. It can also generate a target
## specific exec when the autoload target is called. User must specify the
## libraries to be generated, the full corresponding path of the generated lib
## and the application specific objects path. Also add platform specific
## dependencies for the generation of the application. For each item, the aimed
## approach is to specify everything that is common to all platforms under the
## '.._COMMON' label and platform specific stuff under the '.._plateform' label.
## As a rule of thumb, nothing should appear twice in the makefile. The
## PRJINCPATH, PROGNAME and CARD variables should also be assigned.
##

.PHONY : target_check version Application App_sym App_nosym

#==============================================================================
# User section:
# -Assign everything that is between <>
#
#==============================================================================
INCLIBS_VXWRKS67 =-lipradius-inet6
FSS_ROOT = $(FSS_PSS_ROOT)

#------------------------ Generic Libs to be generated  -----------------------
# NOTE: Only generic librairies should go here. Specific libs should go in
#       Application dependencies section
#------------------------------------------------------------------------------
GENERIC_LIBS = \
	SoftwareServices \
	TelecomServices \
	CardServices \
	CommonTypes \
	CommonPlatforms \
	Agent

MAKELIBS_COMMON = \
	$(GENERIC_LIBS)

MAKELIBS_WIN32 = \

MAKELIBS_SUN   = \

MAKELIBS_VXWRKS67= \

BSPCOMMON_SRCDIR = $(TTG_CP_CSDIR)/BspCommon/src
VXUTILS_SRCDIR   = $(TTG_CP_CSDIR)/vxUtils/bsp/src
BSPCP8560_SRCDIR = $(TTG_CP_CSDIR)/Cp8560_vx/bsp/src
BSP_SRCDIR       = $(TTG_SPM8560DIR)/CardServices/bsp/src

BCM_INC_DIR      = $(TTG_SPM8560DIR)/CardServices/bcm1
CONFIG_8560      = $(WIND_BASE)/target/config/wrSbc8560
IPAPPL_DIR	:= $(WIND_HOME)/components/ip_net2-6.7/ipappl


#-------- Extract memory locations from link file ------------

MEMORY_MAP = $(TTG_SPM8560DIR)/CardServices/bsp/mem.link

APPL_RAM_ADDR   = $(shell cat $(MEMORY_MAP) | grep Application:       | sed "s/.*o=\([0-9a-fA-FxX]*\).*/\1/")
SELFX_RAM_ADDR  = $(shell cat $(MEMORY_MAP) | grep SelfExtractBuffer: | sed "s/.*o=\([0-9a-fA-FxX]*\).*/\1/")
APPL_FLASH_ADDR = $(shell cat $(MEMORY_MAP) | grep ApplRom:           | sed "s/.*o=\([0-9a-fA-FxX]*\).*/\1/")

# Note that 'bc' requires that hex digits be in upper-case.
APPL_FLASH_HEX_SIZE=$(shell cat $(MEMORY_MAP) | grep ApplRom: | sed "s/.*l=0[xX]\([0-9a-fA-F]*\).*/\1/;y/abcdef/ABCDEF/")
APPL_FLASH_DEC_SIZE=$(shell echo "ibase=16;$(APPL_FLASH_HEX_SIZE)" | bc)
APPL_IMAGE_DEC_SIZE=$(shell echo "0$(word 5, $(shell $(LS) -l $(basename $(PROGRAM)).tlf))" | bc)

UPG_BUFFER_HEX_SIZE=$(shell cat $(MEMORY_MAP) | grep SoftwareUpgradeBuffer: | sed "s/.*l=0[xX]\([0-9a-fA-F]*\).*/\1/;y/abcdef/ABCDEF/")
UPG_BUFFER_DEC_SIZE=$(shell echo "ibase=16;$(UPG_BUFFER_HEX_SIZE)" | bc)

#-------- Filename and switch needed in generation of application  ------------

ifeq ($(PLATFORM),WIN32)
FILE_SWITCH = @
endif

ifeq ($(PLATFORM),VXWRKS67)
FILE_SWITCH =-@
LINK_FILE=ApplCmdSPM8560.link
endif

ifeq ($(PLATFORM),SUN)
endif


#-------- Filename that include the list of libraries to be linked ------------
LIB_FILE = lib$(PLATFORM).lsl

LIB_INPUT_FILE=$(FILE_SWITCH)$(LIB_FILE)

#---------------- Objects included in generation of application ----------------

MYOBJS_COMMON = \
    $(OBJDIR)/SPM8560_Application$(OBJ_SUFFIX) \
    $(OBJDIR)/CARD_SwVersion_$(PLATFORM)$(OBJ_SUFFIX) \
    $(OBJDIR)/CARD_SwVersion_C_$(PLATFORM)$(OBJ_SUFFIX) \
    $(OBJDIR)/Nm_InterfaceUtils$(OBJ_SUFFIX) \
#    $(OBJDIR)/getIfAddr$(OBJ_SUFFIX) \

MYOBJS_WIN32  = \
    $(OBJDIR)/TMButilities_SIMUL$(OBJ_SUFFIX) \
    $(OBJDIR)/psos_gate$(OBJ_SUFFIX) \
    $(OBJDIR)/psos_stubs$(OBJ_SUFFIX) \

MYOBJS_VXWRKS67  = \
    $(OBJDIR)/sysALib$(OBJ_SUFFIX) \
    $(OBJDIR)/sysLib$(OBJ_SUFFIX) \
    $(OBJDIR)/drv_conf$(OBJ_SUFFIX) \
    $(OBJDIR)/root_ppc$(OBJ_SUFFIX) \
    $(OBJDIR)/app_main$(OBJ_SUFFIX) \
    $(OBJDIR)/FC_root_ppc$(OBJ_SUFFIX) \
    $(OBJDIR)/usrConfig$(OBJ_SUFFIX) \
    $(OBJDIR)/usrNatStartup$(OBJ_SUFFIX) \
    $(OBJDIR)/usrAppInit$(OBJ_SUFFIX) \
    $(OBJDIR)/utilities$(OBJ_SUFFIX) \
    $(OBJDIR)/cerror$(OBJ_SUFFIX) \
    $(OBJDIR)/specificDriverInit$(OBJ_SUFFIX) \
    $(OBJDIR)/apdialog_vx$(OBJ_SUFFIX) \
    $(OBJDIR)/App_Custom$(OBJ_SUFFIX) \
    $(OBJDIR)/customdialog_ppc_8560$(OBJ_SUFFIX) \
    $(OBJDIR)/CustomParamInit$(OBJ_SUFFIX) \
    $(OBJDIR)/FTPServerTestMenu$(OBJ_SUFFIX) \
    $(OBJDIR)/NTPServerTestMenu$(OBJ_SUFFIX) \
    $(OBJDIR)/dfUtils$(OBJ_SUFFIX) \
    $(OBJDIR)/dcc_address$(OBJ_SUFFIX) \
    $(OBJDIR)/pkt_address$(OBJ_SUFFIX) \
    $(OBJDIR)/edrSave$(OBJ_SUFFIX) \
    $(OBJDIR)/mgmt_gtw_address$(OBJ_SUFFIX) \
    $(OBJDIR)/vx7100Cmds$(OBJ_SUFFIX) \
    $(OBJDIR)/packetSubsystemInit$(OBJ_SUFFIX) \
    $(OBJDIR)/crashLogMenu$(OBJ_SUFFIX) \
    $(OBJDIR)/storagePromCommand$(OBJ_SUFFIX) \

#    $(OBJDIR)/m85xxTimer$(OBJ_SUFFIX) \
#    $(OBJDIR)/sysAlib$(OBJ_SUFFIX) \
#    $(OBJDIR)/NTPServerTestMenu$(OBJ_SUFFIX) \
#    $(OBJDIR)/specificDriverInit$(OBJ_SUFFIX) \
#    $(OBJDIR)/FTPServerTestMenu$(OBJ_SUFFIX)
#    $(OBJDIR)/utilities$(OBJ_SUFFIX) \
#   $(OBJDIR)/diagnostics$(OBJ_SUFFIX) \
#    $(OBJDIR)/sysAlib$(OBJ_SUFFIX) \
#    $(OBJDIR)/sysLib$(OBJ_SUFFIX) \
# $(OBJDIR)/sysNetSPM$(OBJ_SUFFIX) \

MYOBJS_SUN    = \


#-------------------------- Application dependencies --------------------------
# NOTE: Only specific librairies should go here. Generic libs should go
#       in Generic Libs section
#------------------------------------------------------------------------------
APP_DEP_WIN32 = \
     cs_lib_specific \
     tel_lib_specific \

APP_DEP_VXWRKS67 = \
    cs_lib_specific \
    tel_lib_specific \
    bsp_lib \
    bcm1_lib \
    bcm2_lib \

#    ISS_lib \

APP_DEP_SUN   = \

#===============================================================================
# Target specific section:
# -Assign everything that is between <>
# -Add target rules. Target templates are included at the end of this section
#===============================================================================

MAKERULES  = $(TTG_ROOT)/proj/makerules.$(PLATFORM)
MAKELIBS   = $(TTG_ROOT)/proj/makelibs.mk
PRJINCPATH = \
	-I$(TTG_SPM8560DIR)/CardServices \
	-I$(TTG_SPM8560DIR)/TelecomServices \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/ \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/init \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/util \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/debug \
	-I$(TTG_CP_CSDIR)/vxUtils/bsp \
	-I$(TTG_CP_CSDIR)/Cp8560_vx/bsp \
	-I$(TTG_SPM8560DIR)/CardServices/bsp \
	-I$(TTG_SPM8560DIR)/CardServices/bsp/src \
	-I$(TTG_ROOT)/CommonPlatforms/CardServices/BspCommon \
	-I$(TTG_ROOT)/CommonPlatforms/CardServices/BspGeneric \
	-I$(TTG_ROOT)/CommonPlatforms/CardServices/ \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/ControllerApp \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/PMXfer \
	-I$(TTG_ROOT)/CardServices/PMXfer \
	-I$(TTG_ROOT)/CardServices/CsPii \
	-I$(TTG_SPM8560DIR)/CardServices/FPGA \
	-I$(TTG_ROOT) \
	-I$(TTG_ROOT)/CommonTypes \
	-I$(BCM_INC_DIR) \
	-I$(TTG_ROOT)/CommonPlatforms/SoftwareServices/HeapMgr \
	-I$(TTG_ROOT)/shared/inf/include \
	-I$(TTG_CP_CSDIR)/Nm \
	-I$(FSS_ROOT)/fsap2/vxworks \
	-I$(FSS_ROOT)/inc \
	-I$(FSS_ROOT)/fsap2/cmn \
	-I$(TTG_ROOT)/PacketServices \
	-I$(WIND_BASE)/target/h \
	-I$(TTG_SPM8560DIR)/CardServices/bcm1/include \
	-I$(CNTL_PLANE_BASE)/api/inc \
	-I$(CNTL_PLANE_BASE)/util/ \
	-I$(CP_PREFERRED)cca/inc \
	-I$(CP_ALTERNATE)cca/inc \
	-I$(DCL_BASE)/comn/custom \
	-I$(CP_PREFERRED)atmsim/system \
	-I$(CP_ALTERNATE)atmsim/system \
	-I$(TTG_SSDIR)/devices/logicalModel/genericDevices/hdp/hdr \
	-I$(TTG_SSDIR)/devices/logicalModel/genericDevices/pm4351/hdr \
	-I$(TTG_SSDIR)/devices/logicalModel/hdr \
	-I$(TTG_CP_CSDIR)/Devices \
	-I$(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/Devices \
	-I$(TTG_CPDIR)/CardServices/bbootPatchManager \
	-I$(VXWRKS_IPNET_DIR)/ipcom/config \
	-I$(IPCOM_DIR)/include \
	-I$(IPCOM_DIR)/port/vxworks/config \
	-I$(IPCOM_DIR)/port/vxworks/include \
	-I$(VXWRKS_IPNET_DIR)/ipnet2/include \
	-I$(VXWRKS_IPNET_DIR)/ipnet2/config \
	-I$(VXWRKS_IPNET_DIR)/ipnet2/src \
	-I$(VXWRKS_IPNET_DIR)/ipppp/include \
	-I$(VXWRKS_IPNET_DIR)/ipppp/config \
	-I$(VXWRKS_IPNET_DIR)/ipipsec2/config \
	-I$(VXWRKS_IPNET_DIR)/ipike/config \
	-I$(VXWRKS_IPNET_DIR)/ipssh/config \
	-I$(VXWRKS_IPNET_DIR)/vxcompat/include \
	-I$(VXWRKS_IPNET_DIR)/osconfig/vxworks/src \
	-I$(VXWRKS_IPNET_DIR)/ipcom/port/vxworks/config \
	-I$(VXWRKS_IPNET_DIR)/ipcom/port/vxworks/include \
	-I$(VXWRKS_IPNET_DIR)/ipcom/include \
	-I$(VXWRKS_IPNET_DIR)/ipappl/config \
	-I$(VXWRKS_IPNET_DIR)/ipappl/include \
	-I$(VXWRKS_IPNET_DIR)/ipdhcps/include \
	-I$(VXWRKS_IPNET_DIR)/ipdhcps/config \
	-I$(VXWRKS_DIR)/target/config/comps/src/net \
	-I$(IPAPPL_DIR)/config \
	-I$(IPAPPL_DIR)/include \
	-I$(CONFIG_8560) 

PRJLIBS    =


ifeq ($(WDB),1)
	INCLUDE_WDB = -DINCLUDE_WDB
endif

PRJDEFINES =	-DINCLUDE_CPM -DTARGETDEV_WRSBC -DAPPL $(INCLUDE_WDB) \
		-DTELLABS_FLASHDRVR -DROUTER_STACK -DLOG_ENABLE_MASK=0x1ff

PROGNAME   = SPM8560app
CARD       = SPM8560
TTGCARDDIR = $(TTG_SPM8560DIR)

# Added by Rick on 6/5/2008
# BUILD_OS is the operating system of the machine we are building on.
DATETIME := \diab\mksnt\date.exe
ifeq ($(BUILD_OS),solaris)
  DATETIME := date
endif
ifeq ($(BUILD_OS),linux)
  DATETIME := date
endif

default: target_check Application

# Build the libraries BEFORE the application so that they are
# available when the application build tries to link to them.
# This ordering allows parallel builds to work properly.
all: All_libs
	$(MAKE)  Application_$(PLATFORM)
	$(MAKE)  autoload debug_file

Application: version
	@printf "***Start building $@ at "
	@$(DATETIME)
ifneq ($(PLATFORM),WIN32)
	$(MAKE)  App_nosym_$(PLATFORM)
else
	$(MAKE)  Application_$(PLATFORM)
endif
	@printf "***Done building $@ at  "
	@$(DATETIME)

App_sym: version
	@printf "***Start building $@ at "
	@$(DATETIME)
	$(MAKE)  Application_$(PLATFORM)
	@printf "***Done building $@ at  "
	@$(DATETIME)

App_nosym: version
	@printf "***Start building $@ at "
	@$(DATETIME)
	$(MAKE)  App_nosym_$(PLATFORM)
	@printf "***Done building $@ at  "
	@$(DATETIME)

# Build the application with the debug version of DCL libraries.
debug:
	@printf "***Start building $@ at "
	@$(DATETIME)
	$(MAKE)  dApplication_$(PLATFORM)
	@printf "***Done building $@ at  "
	@$(DATETIME)

target_check:
ifneq ($(PLATFORM),WIN32)
	@if [ "$(PLATFORM)" != "VXWRKS67" ]; then \
	   echo "***This is a VXWRKS67 target only!!!"; \
	   false; \
	fi
endif

# Set CONTROLLER_CODE before including $(MAKERULES)
CONTROLLER_CODE=YES
include $(MAKERULES)
include $(MAKELIBS)

#ifeq ($(PLATFORM),WIN32)
#    LDDBGFLAGS  = /PDB:NONE
#endif

ifeq ($(PLATFORM),VXWRKS67)
TGT_DIR := $(WIND_BASE)/target
LIB_DIR := $(TTGCARDDIR)/CardServices/libv67
PRJLIBPATH :=	-L$(LIB_DIR) -L$(TGT_DIR)/lib -L$(TGT_DIR)/lib/ppc/PPC32/sfdiab_standard \
		-L$(TGT_DIR)/lib/ppc/PPC32/sfcommon_ppc85XX \
		-L$(TGT_DIR)/lib/ppc/PPC32/sfdiab -L$(TGT_DIR)/lib/ppc/PPC32/sfcommon
else
PRJLIBPATH =
endif

ifeq ($(BUILD_OS), $(filter $(BUILD_OS), linux solaris))
SOURCE_PATH :=  $(BSPCP8560_SRCDIR):$(BSP_SRCDIR):$(VXUTILS_SRCDIR):$(BSPCOMMON_SRCDIR):$(WIND_DIAB_PATH)/src
else
SOURCE_PATH :=  $(BSPCP8560_SRCDIR);$(BSP_SRCDIR);$(VXUTILS_SRCDIR);$(BSPCOMMON_SRCDIR);$(WIND_DIAB_PATH)/src
endif

vpath %.c    $(SOURCE_PATH)
vpath %.cpp  $(SOURCE_PATH)

#------------------------------------------------------------------------------
# Locate the following definition after the makerules include to use SLASH
# and ANTISLASH.
#------------------------------------------------------------------------------
VERSION_FILE := $(subst $(ANTISLASH),$(SLASH),..\src\CARD_SwVersion_$(PLATFORM).cpp)

$(GENERIC_LIBS):
	@echo ***Making $@ ...
	@cd $(subst $(ANTISLASH),$(SLASH),$(TTG_ROOT)/$@/proj) && \
	$(MAKE) 

cs_lib_specific:
	@echo ***Making CardServices Specific SPM8560 ...
	@cd $(subst $(ANTISLASH),$(SLASH),$(TTG_SPM8560DIR)/CardServices/proj) && \
	$(MAKE)  

tel_lib_specific:
	@echo ***Making TelecomServices Specific SPM8560 ...
	@cd $(subst $(ANTISLASH),$(SLASH),$(TTG_SPM8560DIR)/TelecomServices/proj) && \
	$(MAKE)  

ifeq ($(PLATFORM),VXWRKS67)
# The .s files built here really have C-style language, so use the compiler instead of the assembler.
$(OBJDIR)%.o : $(BSPCP8560_SRCDIR)%.s
	@printf "   Assembling $(notdir $<) at "
	@$(DATETIME)
	@$(RM) $@
	@$(SET_TEXT_RED) && $(CC) $(CFLAGS) $(COPTS) $(ASM_AS_COPTS) -DRAM_LOW_ADRS=$(APPL_RAM_ADDR) -DRAM_HIGH_ADRS=$(SELFX_RAM_ADDR) -o $@ $< || ($(SET_TEXT_BLUE) && $(ECHO) "\n$(CC) $(CFLAGS) $(COPTS) $(ASM_AS_COPTS) -DRAM_LOW_ADRS=$(APPL_RAM_ADDR) -DRAM_HIGH_ADRS=$(SELFX_RAM_ADDR) -o $@ $<" && $(SET_TEXT_NORMAL) && false)
	@$(SET_TEXT_NORMAL)
	@printf "Done building $(notdir $@) at "
	@$(DATETIME)

$(OBJDIR)/cerror.o : $(WIND_DIAB_PATH)/src/cerror.c
	@printf "    Compiling $(notdir $<) at "
	@$(DATETIME)
	@echo $(notdir $<)
	@-test -d $(dir $@) || $(MKDIR) $(dir $@)
	@$(RM) $@
	@$(SET_TEXT_RED) && $(CC) -Xsmall-data=8 -Xsmall-const=8 $(CFLAGS) $(COPTS) -o $@ $< || ($(SET_TEXT_BLUE) && $(ECHO) "\n$(CC) -Xsmall-data=8 -Xsmall-const=8 $(CFLAGS) $(COPTS) -o $@ $<" && $(SET_TEXT_NORMAL) && false)
	@$(SET_TEXT_NORMAL)
	@printf "Done building $(notdir $@) at "
	@$(DATETIME)

$(OBJDIR)/usrConfig.o : $(TTG_SPM8560DIR)/Application/src/usrConfig.c
	@printf "    Compiling $(notdir $<) at "
	@$(DATETIME)
	@echo $(notdir $<)
	@-test -d $(dir $@) || $(MKDIR) $(dir $@)
	@$(RM) $@
	@$(SET_TEXT_RED) && $(CC) -Xsmall-data=8 -Xsmall-const=8 $(CFLAGS) $(COPTS) -o $@ $< || ($(SET_TEXT_BLUE) && $(ECHO) "\n$(CC) -Xsmall-data=8 -Xsmall-const=8 $(CFLAGS) $(COPTS) -o $@ $<" && $(SET_TEXT_NORMAL) && false)
	@$(SET_TEXT_NORMAL)
	@printf "Done building $(notdir $@) at "
	@$(DATETIME)

$(OBJDIR)/sysLib.o : sysLib.c
	@printf "    Compiling $(notdir $<) at "
	@$(DATETIME)
	@echo $(notdir $<)
	@-test -d $(dir $@) || $(MKDIR) $(dir $@)
	@$(RM) $@
	@$(SET_TEXT_RED) && $(CC) -Xsmall-data=8 -Xsmall-const=8 $(CFLAGS) $(COPTS) -o $@ $< || ($(SET_TEXT_BLUE) && $(ECHO) "\n$(CC) -Xsmall-data=8 -Xsmall-const=8 $(CFLAGS) $(COPTS) -o $@ $<" && $(SET_TEXT_NORMAL) && false)
	@$(SET_TEXT_NORMAL)
	@printf "Done building $(notdir $@) at "
	@$(DATETIME)

bsp_lib:
	@echo ***Calling $(CARD) BSP makefile ...
	cd $(subst $(ANTISLASH),$(SLASH),$(TTG_SPM8560DIR)/CardServices/bsp/proj) && \
	$(MAKE)   $(MAKETARGET:mt_clean=cleanerbsp)

bcm1_lib:
	@echo ***Calling $(CARD) BCM makefile ...
	cd $(subst $(ANTISLASH),$(SLASH),$(TTG_SPM8560DIR)/CardServices/bcm1/proj) && \
	$(MAKE)   $(MAKETARGET:mt_clean=cleanerbsp)

bcm2_lib:
	@echo ***Calling $(CARD) BCM makefile ...
	cd $(subst $(ANTISLASH),$(SLASH),$(TTG_SPM8560DIR)/CardServices/bcm2/proj) && \
	$(MAKE)   $(MAKETARGET:mt_clean=cleanerbsp)
endif

ifeq ($(PLATFORM),WIN32)
$(OBJDIR)%.obj : $(TTG_ROOT)/tools/win32/psos/%.cpp
	@echo Compiling $(subst $(ANTISLASH),$(SLASH),$<)
	$(CC) -nologo $(DEFINES) $(DBGFLAGS) -MTd -W3 -EHsc -GR -Fo$(subst /,\,$(OBJDIR))\\ \
	    -I$(TTG_ROOT) -I$(TTG_ROOT)/tools/win32/psos \
	    -c $(shell echo $< | sed "s/^[^\/\\].*/$(subst \,\\,$(MAKEDIR))\\&/; s/[\/\\][\/\\]*/\\/g; s/[\\]\.[\\]/\\/g; s/[^\\][^\\]*[\\]\.\.[\\]//g")

$(OBJDIR)%.obj : $(TTG_ROOT)/tools/win32/psos/%.c
	@echo Compiling $(subst $(ANTISLASH),$(SLASH),$<)
	$(CC) -nologo $(DEFINES) $(DBGFLAGS) -MTd -W3 -EHsc -GR -Fo$(subst /,\,$(OBJDIR))\\ \
	    -I$(TTG_ROOT) -I$(TTG_ROOT)/tools/win32/psos -I/psos/prism_ppc_2.5/pssppc.250/include \
	    -c $(shell echo $< | sed "s/^[^\/\\].*/$(subst \,\\,$(MAKEDIR))\\&/; s/[\/\\][\/\\]*/\\/g; s/[\\]\.[\\]/\\/g; s/[^\\][^\\]*[\\]\.\.[\\]//g")

$(OBJDIR)%$(OBJ_SUFFIX) : $(TTG_SPM8560DIR)/CardServices/bsp/src/%.c
	@echo Compiling $(subst $(ANTISLASH),$(SLASH),$<)
	$(CC) -nologo $(DEFINES) $(DBGFLAGS) -MTd -W3 -EHsc -GR -Fo$(subst /,\,$(OBJDIR))\\ \
	    -I$(TTG_SPM8560DIR)/win32 -I$(TTG_ROOT) -I$(TTG_ROOT)/tools/win32/bsp -I$(TTG_ROOT)/tools/win32/bsp/include \
	    -I$(PSS_ROOT)/include -I$(PSS_ROOT)/bsps/devices \
	    -I$(TTG_ROOT)/shared/include -I$(TTG_ROOT)/shared/fw/include -I$(TTG_ROOT)/shared/inf/include \
	    -I$(TTG_SPM8560DIR)/fw/include -I$(TTG_SPM8560DIR)/fw/hw_control/include \
	    -c $(shell echo $< | sed "s/^[^\/\\].*/$(subst \,\\,$(MAKEDIR))\\&/; s/[\/\\][\/\\]*/\\/g; s/[\\]\.[\\]/\\/g; s/[^\\][^\\]*[\\]\.\.[\\]//g")
endif


#===============================================================================
# Build scripts section:
# -Scripts used to build libraries and applications.
#
#===============================================================================

All_libs: $(MAKELIBS_COMMON) $(MAKELIBS_$(PLATFORM)) $(LIB_FILE)

bdm:
	$(TTG_ROOT)/tools/est32/convert ../binv67/$(basename $(PROGRAM)).elf -b -c
	$(TTG_ROOT)/tools/bin2est/bin2est $(basename $(PROGRAM)).tlf $(basename $(PROGRAM)).tlf.bin /LOAD=$(APPL_FLASH_ADDR)

Application_$(PLATFORM): $(LINK_FILE) $(APP_DEP_$(PLATFORM))
	@echo ***Making $(CARD) Application for $(PLATFORM)...
	@$(MAKE)      \
	OBJS="$(MYOBJS_$(PLATFORM)) $(MYOBJS_COMMON) $(MYOBJS_$(PLATFORM)_ORIG)" \
	PRJLIBS="$(INCLIBS_COMMON) $(INCLIBS_$(PLATFORM))" \
	RAMFILE=$(LINK_FILE) \
	EXECUTION_BASE_ADDR=$(APPL_RAM_ADDR) \
	DATA_SEG_ALIGN=0x00080000 \
	ENTRYPOINT=_sysInit \
	$(MAKETARGET:default=program)

# Build the application with the debug version of DCL libraries.
dApplication_$(PLATFORM): $(LINK_FILE) $(APP_DEP_$(PLATFORM))
	@echo ***Making $(CARD) Debug Application for $(PLATFORM)...
	@$(MAKE)      \
	OBJS="$(MYOBJS_$(PLATFORM)) $(MYOBJS_COMMON) $(MYOBJS_$(PLATFORM)_ORIG)" \
	PRJLIBS="$(INCLIBS_COMMON) $(INCLIBS_$(PLATFORM))" \
	RAMFILE=$(LINK_FILE) \
	EXECUTION_BASE_ADDR=$(APPL_RAM_ADDR) \
	DATA_SEG_ALIGN=0x00080000 \
	ENTRYPOINT=_sysInit \
	LIB_FILE=lib$(PLATFORM)d.lsl \
	$(MAKETARGET:default=program)

App_nosym_$(PLATFORM): $(LINK_FILE) $(APP_DEP_$(PLATFORM))
	@echo ***Making $(CARD) Application for $(PLATFORM)...
	@$(MAKE)   PROG_PREFIX="nosym" \
	OBJS="$(MYOBJS_$(PLATFORM)) $(MYOBJS_COMMON) $(MYOBJS_$(PLATFORM)_ORIG)" \
	PRJLIBS="$(INCLIBS_COMMON) $(INCLIBS_$(PLATFORM))" \
	RAMFILE=$(LINK_FILE) \
	EXECUTION_BASE_ADDR=$(APPL_RAM_ADDR) \
	DATA_SEG_ALIGN=0x00080000 \
	ENTRYPOINT=_sysInit \
	$(MAKETARGET:default=program_nosym)

ifeq ($(PLATFORM),WIN32)
BigFiles:
	@cd $(TTG_ROOT)\CommonTypes\proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__BIG_SIMULATION__" ..\obj\CT_CardInventory.obj && \
	    $(MAKE)   link
	@cd $(TTG_CSDIR)\Nm\proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__BIG_SIMULATION__" ..\obj\Nm_ApplyInterfaceParamsAction.obj && \
	    $(MAKE)   link
	@cd $(TTG_CSDIR)\proj && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)\CommonPlatforms\SoftwareServices\T6100\proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__BIG_SIMULATION__" ..\obj\T6100_Services.obj && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)\CommonPlatforms\ControllerServices\CardServices\Nm\proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__BIG_SIMULATION__" ..\obj\Nm_EONTypeUpdateAction.obj && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)\CommonPlatforms\ControllerServices\CardServices\proj && \
	    $(MAKE)   link

BigSimulation: version $(LINK_FILE) $(APP_DEP_$(PLATFORM))
	@$(MAKE)   BigFiles
	@echo ***Making $(CARD) Big Application for $(PLATFORM)...
	@$(MAKE)      \
	OBJS="$(MYOBJS_$(PLATFORM)) $(MYOBJS_COMMON) $(MYOBJS_$(PLATFORM)_ORIG)" \
	PRJLIBS="$(INCLIBS_COMMON) $(INCLIBS_$(PLATFORM))" \
	RAMFILE=$(LINK_FILE) \
	EXECUTION_BASE_ADDR=$(APPL_RAM_ADDR) \
	DATA_SEG_ALIGN=0x00080000 \
	ENTRYPOINT=_sysInit \
	LDFLAGS="$(LDFLAGS) /LARGEADDRESSAWARE" \
	$(MAKETARGET:default=program)

MemChkFiles:
	@cd $(TTG_ROOT)\CommonTypes\proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ..\obj\CT_ControlPlane_Convert.obj && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)\Agent\ControlPlane\proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ..\obj\CMA_Region.obj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ..\obj\CXA_ConfigRegion.obj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ..\obj\LMA_LinkRegion.obj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ..\obj\LMA_TrlRegion.obj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ..\obj\NP_ExppathConfigAction.obj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ..\obj\NP_ExppathRegion.obj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ..\obj\NP_LabelSetRegion.obj && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)\Agent\proj && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)\CommonPlatforms\ControllerServices\Agent\ControlPlane\proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ..\obj\CP_TestMenu.obj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ..\obj\NP_ExppathSubApplication.obj && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)\CommonPlatforms\ControllerServices\Agent\proj && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)\CommonPlatforms\SoftwareServices\T6100\proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__BIG_SIMULATION__" ..\obj\T6100_DbValidationAction.obj && \
	    $(MAKE)   link

MaxMemUse: version $(LINK_FILE) $(APP_DEP_$(PLATFORM))
	@$(MAKE)   MemChkFiles
	@echo ***Making $(CARD) Max Memory Usage Application for $(PLATFORM)...
	@$(MAKE)      \
	OBJS="$(MYOBJS_$(PLATFORM)) $(MYOBJS_COMMON) $(MYOBJS_$(PLATFORM)_ORIG)" \
	PRJLIBS="$(INCLIBS_COMMON) $(INCLIBS_$(PLATFORM))" \
	RAMFILE=$(LINK_FILE) \
	EXECUTION_BASE_ADDR=$(APPL_RAM_ADDR) \
	DATA_SEG_ALIGN=0x00080000 \
	ENTRYPOINT=_sysInit \
	$(MAKETARGET:default=program)
endif

ifeq ($(PLATFORM),VXWRKS67)
MemChkFiles:
	@cd $(TTG_ROOT)/CommonTypes/proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/CT_ControlPlane_Convert.o && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)/Agent/ControlPlane/proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/CMA_Region.o && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/CXA_ConfigRegion.o && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/LMA_LinkRegion.o && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/LMA_TrlRegion.o && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/NP_ExppathConfigAction.o && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/NP_ExppathRegion.o && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/NP_LabelSetRegion.o && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/ControlPlane/proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/CP_TestMenu.o && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/NP_ExppathSubApplication.o && \
	    $(MAKE)   link
	@cd $(TTG_ROOT)/CommonPlatforms/SoftwareServices/T6100/proj && \
	    $(MAKE)   DEFINES="$(PRJDEFINES) $(SYSDEFINES) -D__MAX_MEM_USE__" ../objv67/T6100_DbValidationAction.o && \
	    $(MAKE)   link

MaxMemUse: version $(LINK_FILE) $(APP_DEP_$(PLATFORM))
	@$(MAKE)   MemChkFiles
	@echo ***Making $(CARD) Max Memory Usage Application for $(PLATFORM)...
	@$(MAKE)      \
	OBJS="$(MYOBJS_$(PLATFORM)) $(MYOBJS_COMMON) $(MYOBJS_$(PLATFORM)_ORIG)" \
	PRJLIBS="$(INCLIBS_COMMON) $(INCLIBS_$(PLATFORM))" \
	RAMFILE=$(LINK_FILE) \
	EXECUTION_BASE_ADDR=$(APPL_RAM_ADDR) \
	DATA_SEG_ALIGN=0x00080000 \
	ENTRYPOINT=_sysInit \
	$(MAKETARGET:default=program)
endif

link: $(LINK_FILE)
	@echo ***Linking $(CARD) Application for $(PLATFORM)...
	@$(MAKE)      \
	OBJS="$(MYOBJS_$(PLATFORM)) $(MYOBJS_COMMON) $(MYOBJS_$(PLATFORM)_ORIG)" \
	PRJLIBS="$(INCLIBS_COMMON) $(INCLIBS_$(PLATFORM))" \
	RAMFILE=$(LINK_FILE) \
	EXECUTION_BASE_ADDR=$(APPL_RAM_ADDR) \
	DATA_SEG_ALIGN=0x00080000 \
	ENTRYPOINT=_sysInit \
	$(MAKETARGET:default=program)

linknosym: $(LINK_FILE)
	@echo ***Linking $(CARD) Application for $(PLATFORM)...
	@$(MAKE)   PROG_PREFIX="nosym" \
	OBJS="$(MYOBJS_$(PLATFORM)) $(MYOBJS_COMMON) $(MYOBJS_$(PLATFORM)_ORIG)" \
	PRJLIBS="$(INCLIBS_COMMON) $(INCLIBS_$(PLATFORM))" \
	RAMFILE=$(LINK_FILE) \
	EXECUTION_BASE_ADDR=$(APPL_RAM_ADDR) \
	DATA_SEG_ALIGN=0x00080000 \
	ENTRYPOINT=_sysInit \
	$(MAKETARGET:default=program_nosym)

# Build the application with the debug version of DCL libraries.
dlink: $(LINK_FILE)
	@printf "***Start building $@ debug at "
	@$(DATETIME)
	@echo ***Linking $(CARD) Application for $(PLATFORM)...
	@$(MAKE)      \
	OBJS="$(MYOBJS_$(PLATFORM)) $(MYOBJS_COMMON) $(MYOBJS_$(PLATFORM)_ORIG)" \
	PRJLIBS="$(INCLIBS_COMMON) $(INCLIBS_$(PLATFORM))" \
	RAMFILE=$(LINK_FILE) \
	EXECUTION_BASE_ADDR=$(APPL_RAM_ADDR) \
	DATA_SEG_ALIGN=0x00080000 \
	ENTRYPOINT=_sysInit \
	LIB_FILE=lib$(PLATFORM)d.lsl \
	$(MAKETARGET:default=program)
	@printf "***Done building $@ at  "
	@$(DATETIME)

$(LINK_FILE): $(MEMORY_MAP) $(TTG_SPM8560DIR)/CardServices/bsp/ram.link
	cat $(MEMORY_MAP) $(TTG_SPM8560DIR)/CardServices/bsp/ram.link > temp.link
	$(DPATH)/dcc temp.link -EP -I$(TTG_ROOT)/CommonPlatforms/CardServices/BspCommon | sed "s/\#.*//" > $@
	$(RM) temp.link

# Default is to use the release DCL libraries.
DCL_LIB_TYPE=release

lib$(PLATFORM)d.lsl : makefile
	$(MAKE)  DCL_LIB_TYPE=debug LIB_FILE=lib$(PLATFORM)d.lsl  lib$(PLATFORM).lsl

#==============================================================================
# NOTE:  Use '\' as path name seperator
#==============================================================================
libWIN32.lsl: makefile
	@echo ***Generating $(LIB_FILE) ...
	@echo $(TTG_ROOT)\OSPortability\lib\OSPortability.lib > $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\Agent\lib\AgentApm.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\TL1Services\lib\TL1APM.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\ControllerApp\lib\CntlApp.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonTypes\lib\CommonTypes.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\Agent\lib\Agent.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\QRS\lib\QRServices.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\RadiusClient\lib\RadiusClient_WIN32.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\QRS\lib\QRServices.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\Lumos\lib\LumosControlPlane.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\SNMPServices\lib\SNMPSvc.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\CardServices\lib\CSCntlServ.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\TelecomServices\lib\TSCntlServ.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\SoftwareServices\BEIF\lib\BEIFComPlat.lib  >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\SoftwareServices\SMPR\lib\SMPR.lib  >> $(LIB_FILE)
	@echo $(TTG_ROOT)\TL1Services\lib\TL1Services.lib >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)\CardServices\lib\CS_Spm8560.lib  >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)\TelecomServices\lib\TS_Spm8560.lib  >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\Lumos\lib\LumosControlPlane.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\Lumos\lib\LumosCore.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\Lumos\lib\LumosOther.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\Lumos\lib\LumosGen.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\Lumos\lib\LumosUser.lib >> $(LIB_FILE)
	@echo $(T7100_WIN32_SC_LIB_LIST) >> $(LIB_FILE)
	@echo $(TTG_ROOT)\CommonPlatforms\ControllerServices\PacketServices\cli\lib\PsCli.lib  >> $(LIB_FILE)
	@echo $(TTG_ROOT)\SoftwareServices\devices\lib\devices.lib  >> $(LIB_FILE)
	@echo $(TTG_ROOT)\tools\EON\lib\ospf.lib >> $(LIB_FILE)
	@echo $(TTG_ROOT)\tools\zlib\lib\zlib.lib >> $(LIB_FILE)
	@echo $(CNTL_PLANE_BASE)\lib\cp_util.lib >> $(LIB_FILE)

#==============================================================================
# NOTE:  Use '/' as path name seperator
#==============================================================================
libVXWRKS67.lsl: makefile
	@echo ***Generating $(LIB_FILE) ...
	@echo $(T7100_ALL_CARD_LIB_LIST) > $(LIB_FILE)
	@echo $(TTG_ROOT)/SoftwareServices/libv67/libMemoryMapped.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/SoftwareServices/libv67/libSpi.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/SoftwareServices/libv67/libAccessibleBase.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/SoftwareServices/libv67/libpm4351.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/SoftwareServices/libv67/libHdp.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libCsPii.a  >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libCsPiiSpecificSPM8560_VXWRKS67.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libCsPii_VXWRKS67.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libNm.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libCsm.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libIdProm.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libLEDShow.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libDiag.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libPMD.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libPMXfer.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libCUD.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CardServices/libv67/libAip.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/TelecomServices/Monitoring/objv67/MON_PilotToneActionSignature.o >> $(LIB_FILE)
	@echo $(TTG_ROOT)/TelecomServices/TsPii/objv67/TSPII_PilotToneActionFFT.o >> $(LIB_FILE)
	@echo $(TTG_ROOT)/TelecomServices/XC/libv67/libXCGeneric.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/TelecomServices/SNMP/libv67/libSnmpGeneric.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/TelecomServices/CUD/libv67/libCudGeneric.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/TL1Services/libv67/libFacade.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/TL1Services/libv67/libResponse.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/TL1Services/libv67/libTL1Core.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentAS.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentBaseClass.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentEQ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentUtility.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentSM.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libFacility.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentAM.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentNM.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentAP.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentHWCapabilityMatrix.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentLayer2Management.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentSP.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentPM.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentPROT.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentXC.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentTAP.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentTM.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentDBM.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentSMAA.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentArc.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentSEC.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentSNMP.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentDCC.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentUpgrade.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentControlPlane.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/Agent/libv67/libAgentCPIF.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/QRS/libv67/libQRServices.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/SoftwareServices/BEIF/libv67/libBEIFComPlat.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/SoftwareServices/SMPR/libv67/libSMPR.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/SoftwareServices/HeapMgr/libv67/libHeapMgr.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/CardServices/libv67/libCsPiiSpecificComPlat_VXWRKS67.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/CardServices/libv67/libCsFOPCommonPlat.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/CardServices/libv67/libPmdSpecificComPlat.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/CardServices/libv67/libCudUtilSpecificComPlat.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/CardServices/libv67/libCudRmMgrSpecificComPlat.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/CardServices/libv67/libCudMgrSpecificComPlat.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/CardServices/libv67/libFpga.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/CardServices/libv67/libDevicesCommonPlat.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/CardServices/libv67/libJTAG.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/CardServices/libv67/libNTP.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/TelecomServices/XC/libv67/libXCCommonPlatform.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/TelecomServices/SNMP/libv67/libSnmpCommonPlatform.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentAG7100Apm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentAGIFApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentAMApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentAPApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentARCApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentCRApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentTAPApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentDBMApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentEQApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentNMApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentPMApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentPROTApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentSECApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentSMAAApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentSPApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentTimeMgmtApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libApmFacility.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentSNMPSpm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentDCCApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentControlPlaneApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentCPAPIApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Agent/libv67/libAgentCPIFApm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Lumos/libv67/libLumosCore.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Lumos/libv67/libLumosOther.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Lumos/libv67/libLumosGen.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Lumos/libv67/libLumosControlPlane.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Lumos/libv67/libLumosUser.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libAGCW.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libFacade.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libLumosServices.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libLW.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libLWRESP.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libT7100_Notif.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libTL1Core7100.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libTL1Protection7100.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libTL1DCC7100.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libTL1Networking7100.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libTL1Pm7100.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libTL1ControlPlane7100.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libTL1DbChg7100.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libTL1Equipment7100.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libTL1Facility7100.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TL1Services/libv67/libTL1Init.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/SNMPServices/libv67/libSNMPSvc.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libNmCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libAIPCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libAMCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libARCCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libCRCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libContCsDevices.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libCsPiiCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libCsmCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libDiagCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libSMACntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libSCFGCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libTODCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libPmZlibCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libPmdCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libPMXferCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/CardServices/libv67/libweb1.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TelecomServices/libv67/libTsPiiCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TelecomServices/libv67/libCfgCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TelecomServices/libv67/libPMCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/TelecomServices/libv67/libSPCntlServ.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/ControllerApp/libv67/libCntlApp.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/QRS/libv67/libQRServices.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libCsPiiSpecificSPM8560.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libSPM8560IdProm.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libBSP_SPM.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libSPM8560Fpga.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libDevicesSPM8560.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libCsSdSpecificSPM8560.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libCsDiagSpecificSPM8560.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libCsCUDSpecificSPM8560.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libCsNmSpecificSPM8560.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libCsNmSpecificSPM8560_VXWRKS67.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/TelecomServices/libv67/libTsPiiSpecificSPM8560.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfdiab_standard/libstl.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libdrv.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libdsi.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libgcc.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/librpc.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libtffs.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libspl.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libiptcp-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libnetapps-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libcci.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libnetwrap-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libvxcompat-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libxbd.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libdevice.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/liberfLib.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipcom-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libwindview.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipmcrypto-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipike-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipcrypto-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipcrypto_apps-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipipsec2-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipsntp-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipradius-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipnet-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipappl-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipcom-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libiphwcrypto.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipappl.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipnet_krn-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfdiab/libcplus.a>> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfdiab/libdiabcplus.a>> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon_ppc85XX/libarch.a>> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon_ppc85XX/libhwdb.a>> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libaim.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libc_wr.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipcom_vxworks-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipssh-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libnetcommon-inet6.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libos.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libfp.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libdcc.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipdhcps.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipdhcpr.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libcommoncc.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libvxmux.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libwind.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libwindview.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libwdb.a >> $(LIB_FILE)
	@echo /vobs/ots/vx1/wr/vxworks-6.7/target/lib/ppc/PPC32/sfcommon/libipfirewall-inet6.a >> $(LIB_FILE)
	@echo $(CNTL_PLANE_BASE)/libv67/libcp_api.a >> $(LIB_FILE)
	@echo $(CNTL_PLANE_BASE)/libv67/libcp_init.a >> $(LIB_FILE)
	@echo $(CNTL_PLANE_BASE)/libv67/libcp_util.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/npproxy/libv67/libPsDpmNpproxy.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/util/libv67/libPsDpmUtils.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/psmsg/libv67/libPsDpmPsmsg.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/debug/libv67/libPsDpmDebug.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/stat/libv67/libPsStat.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/spdu/ssm/libv67/libPsSsm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/spdu/eoam/libv67/libPsEoam.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/spdu/eoam/eoamfm/libv67/libPsEoamFm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/spdu/ecfm/libv67/libPsEcfm.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/rpr/libv67/libPsDpmRpr.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/init/libv67/libPsDpmInit.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/almmgmt/libv67/libPsAlmMgmt.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/mgmt7300/libv67/libPsMgmt7300Intfc.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/vrprs/libv67/libPsDpmVrprs.a  >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/PacketServices/cli/libv67/libPsCli.a  >> $(LIB_FILE)
	@echo $(FSS_ROOT)/LR/obj/ISS.o >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libbcm1.a >> $(LIB_FILE)
	@echo $(TTG_SPM8560DIR)/CardServices/libv67/libbcm2.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/Snmpd/libv67/libsnmpusr.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/CommonPlatforms/ControllerServices/libv67/libOsiSupport.a >> $(LIB_FILE)
	@echo $(MARBEN_BASE)/projd/sample/libppc67/libosiam67.a >> $(LIB_FILE)
	@echo $(TTG_ROOT)/tools/zlib/libv67/zlib.a >> $(LIB_FILE)
	@echo $(TGT_DIR)/lib/ppc/PPC32/sfcommon/libsnmp.a >> $(LIB_FILE)
	@echo $(TGT_DIR)/lib/ppc/PPC32/sfcommon/libvxsnmp.a >> $(LIB_FILE)
	@echo $(TGT_DIR)/lib/ppc/PPC32/sfcommon/libepcommon.a >> $(LIB_FILE)
	@echo $(TGT_DIR)/lib/ppc/PPC32/sfcommon/libepdes.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/nbase_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dchaf_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dcipl_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/cipr_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dcsms_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dcsm_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dci3_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dclmgr_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dcqcft_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dcqcrt_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dcqopm_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dcqonm_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dcrsvp_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/dcsck_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/lrap_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/lsci_st.a >> $(LIB_FILE)
	@echo $(DCL_BASE)/jobs/gnu/$(DCL_LIB_TYPE)_vxworks/trsm_st.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)atmsim/system/makefile $(CP_ALTERNATE)atmsim/system/makefile)))/derived.singlenopt.vx/system.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)atmsim/simfal/src/makefile $(CP_ALTERNATE)atmsim/simfal/src/makefile)))/derived.singlenopt.vx/simfal.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)util/osm/makefile $(CP_ALTERNATE)util/osm/makefile)))/derived.singlenopt.vx/util_osm.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)util/util/makefile $(CP_ALTERNATE)util/util/makefile)))/derived.singlenopt.vx/util_util.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)util/cfg/makefile $(CP_ALTERNATE)util/cfg/makefile)))/derived.singlenopt.vx/util_cfg.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)util/mibs/makefile $(CP_ALTERNATE)util/mibs/makefile)))/derived.singlenopt.vx/util_mibs.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)util/SM/makefile $(CP_ALTERNATE)util/SM/makefile)))/derived.singlenopt.vx/util_SM.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)hj/common/makefile $(CP_ALTERNATE)hj/common/makefile)))/derived.singlenopt.vx/hjcommon.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)hj/cca/makefile $(CP_ALTERNATE)hj/cca/makefile)))/derived.singlenopt.vx/cca.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)cca/node/makefile $(CP_ALTERNATE)cca/node/makefile)))/derived.singlenopt.vx/cca_node.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)astn_dev/CC/proxy/makefile $(CP_ALTERNATE)astn_dev/CC/proxy/makefile)))/derived.singlenopt.vx/ad_cc_proxy.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)astn_dev/CC/CS/src/makefile $(CP_ALTERNATE)astn_dev/CC/CS/src/makefile)))/derived.singlenopt.vx/ad_cc_cs_s.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)astn_dev/CC/CM/src/makefile $(CP_ALTERNATE)astn_dev/CC/CM/src/makefile)))/derived.singlenopt.vx/ad_cc_cm_s.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)ip/t7100/cca/makefile $(CP_ALTERNATE)ip/t7100/cca/makefile)))/derived.singlenopt.vx/t7100_cca.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)iprp/cca/common/makefile $(CP_ALTERNATE)iprp/cca/common/makefile)))/derived.singlenopt.vx/cca_common.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)iprp/cca/tdmli/src/makefile $(CP_ALTERNATE)iprp/cca/tdmli/src/makefile)))/derived.singlenopt.vx/tdmli.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)iprp/cca/ospf/makefile $(CP_ALTERNATE)iprp/cca/ospf/makefile)))/derived.singlenopt.vx/cca_ospf.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)iprp/cspf/makefile $(CP_ALTERNATE)iprp/cspf/makefile)))/derived.singlenopt.vx/cspf.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)iprp/hj/ted/common/makefile $(CP_ALTERNATE)iprp/hj/ted/common/makefile)))/derived.singlenopt.vx/ted_common.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)mpls/cca/makefile $(CP_ALTERNATE)mpls/cca/makefile)))/derived.singlenopt.vx/cca_lms.a >> $(LIB_FILE)
	@echo $(dir $(firstword $(wildcard $(CP_PREFERRED)astn_dev/Discovery_Agent/makefile $(CP_ALTERNATE)astn_dev/Discovery_Agent/makefile)))/derived.singlenopt.vx/Discovery_Agent.a >> $(LIB_FILE)




version : $(APP_DEP_$(PLATFORM))
	@echo Generating CARD_SwVersion_$(PLATFORM).cpp
	@$(subst $(ANTISLASH),$(SLASH),sh $(TTG_VERSION)/GenerateCARDVersion.sh $(CARD))
	@$(MAKE)  -V  \
	CLOBBERLIST="" \
	$(MAKETARGET:default=$(VERSION_FILE))


tbf:
	$(DUMP) -Rv $(PROGRAM) -o $(basename $(PROGRAM)).hex
	$(TTG_ROOT)/tools/tbf/tbf $(basename $(PROGRAM)).hex $(basename $(PROGRAM)).tbf

autoload:
	@if [ -f $(subst \,/,$(PROGDIR)/nosym$(strip $(PROGNAME))$(PROG_SUFFIX)) ]; then \
	   $(MAKE)  PROG_PREFIX="nosym" autoload_rule; \
	fi
	@if [ -f $(subst \,/,$(PROGDIR)/$(strip $(PROGNAME))$(PROG_SUFFIX)) ]; then \
	   $(MAKE)  autoload_rule; \
	fi

autoload_rule: tlf_image
	@$(SET_TEXT_BLUE)
	@test $(APPL_IMAGE_DEC_SIZE) -le $(APPL_FLASH_DEC_SIZE) \
		&& echo "$(CARD) APPL image ($(APPL_IMAGE_DEC_SIZE) bytes) fits within the APPL flash area ($(APPL_FLASH_DEC_SIZE) bytes)." \
		|| ($(SET_TEXT_RED) && \
		echo "ERROR: $(CARD) APPL image ($(APPL_IMAGE_DEC_SIZE) bytes) is too big to fit the APPL flash area ($(APPL_FLASH_DEC_SIZE) bytes).")
	@$(SET_TEXT_RED)
	@test $(APPL_IMAGE_DEC_SIZE) -gt $(UPG_BUFFER_DEC_SIZE) \
		&& echo "WARNING: Application image is bigger than the SoftwareUpgradeBuffer ($(UPG_BUFFER_DEC_SIZE) bytes)!" \
                && ($(SET_TEXT_BLUE) && echo "         Application loader will bypass the SoftwareUpgradeBuffer.") || true
	@$(SET_TEXT_NORMAL)
	@test $(APPL_IMAGE_DEC_SIZE) -le $(APPL_FLASH_DEC_SIZE) && true

tlf_image: $(basename $(PROGRAM))_stripped_sx.bin
	@echo ***Appending load header ...
	$(TTG_ROOT)/tools/bin/$(BUILD_OS)/AppendHeader_$(BUILD_OS) $< $(basename $(PROGRAM)).tlf \
        /TYPE=APPL /LOAD=$(SELFX_RAM_ADDR) /ENTRY=$(SELFX_RAM_ADDR) /EXEC=RAM \
        /CARD_TYPE=$(CARD) \
        /RELEASE=`strings -a $(OBJDIR)/CARD_SwVersion_$(PLATFORM)$(OBJ_SUFFIX) | grep "@(#)TCS_Version   Release Version:"  | sed "s/.*Release Version: *\(.*\)/\1/"` \
        /BUILD=`strings -a $(OBJDIR)/CARD_SwVersion_$(PLATFORM)$(OBJ_SUFFIX) | grep "@(#)TCS_Version   Build Version:"  | sed "s/.*Build Version: *\(.*\)/\1/"` \
        /PATCH_VER=`strings -a $(OBJDIR)/CARD_SwVersion_$(PLATFORM)$(OBJ_SUFFIX) | grep "@(#)TCS_Version   Patch Version:"  | sed "s/.*Patch Version: *\(.*\)/\1/"` \
	/UNCOMP_SIZE=$(shell echo "0$(word 5, $(shell $(LS) -l $(basename $(PROGRAM))_stripped.bin))" | bc)

loadpackage:
	$(CP) $(subst $(ANTISLASH),$(SLASH),../binv67/$(basename $(PROGNAME)).tlf) $(subst $(ANTISLASH),$(SLASH),$(TTG_LOADSDIR))
# Uncomment the following lines if we need to switch to packaging the SPM8560 with no embedded symbols.
	#@if [ -f $(PROGDIR)/$(PROGRAM_SYM).z.tlf ]; then \
	#    echo "	$(CP) $(PROGDIR)/$(PROGRAM_SYM).z.tlf $(subst $(ANTISLASH),$(SLASH),$(TTG_LOADSDIR))"; \
	#    $(CP) $(PROGDIR)/$(PROGRAM_SYM).z.tlf $(subst $(ANTISLASH),$(SLASH),$(TTG_LOADSDIR)); \
	#fi

##################################################################################


$(basename $(PROGRAM))_stripped.bin:
	@echo ***Converting  $(TTGCARDDIR)/Application/$(notdir  $(patsubst %$(SLASH),%,$(PROGDIR)))/$(PROGNAME).elf...
	$(WR_UTIL)/objcopyppc -O binary --binary-without-bss $(PROGRAM) $@

SX_SRC     = $(basename $(PROGRAM))_stripped.bin
SX_LOAD    = $(APPL_RAM_ADDR)
SX_ENTRY   = $(shell $(TTG_ROOT)/tools/bin/$(BUILD_OS)/readelf_$(BUILD_OS) -h $(PROGRAM)| grep Entry | sed "s/.*: *\([0-9a-fA-FxX]*\).*/\1/")
SX_BUFFER  = $(SELFX_RAM_ADDR)
SX_BSP_DIR = $(TTG_SPM8560DIR)/CardServices/bsp
SX_BSP_LIB = $(TTG_SPM8560DIR)/CardServices/libv67/libBSP_SPM.a
OBJ_DIR    = $(OBJDIR)

include $(TTG_ROOT)/CommonPlatforms/CardServices/SelfX/SelfX.mk

