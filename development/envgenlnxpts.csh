# This set of instructions must be sourced with a '.' instruction.
# This version of the shell script works with VxWorks.

# Build OS and Target platform variables
setenv BUILD_OS "linux"
setenv BUILD_TARGET "linux"
setenv PLATFORM "LINUX"
setenv TOOLSET "LINUX"
setenv LINUX_SIM "YES"
unsetenv SIM_TYPE

# Build DCL to support MPLSTP
setenv OS_TYPE_SUFFIX _mplstp

###############################################
# Set  VIEW_NAME to /view/view_name if you want
# to debug the code as view space is mounted on 
# VMWare root linux machines -
###############################################
setenv vname `cleartool pwv -short`
setenv VIEW_NAME /view/$vname

setenv MEA_REVISION mea_d240t
#setenv MEA_REVISION mea_3_4_1
# Root directories
setenv TTG_ROOT $VIEW_NAME/vobs/ots/development
setenv WRL_ROOT $VIEW_NAME/vobs/wrlinux
setenv WRL_PLAT_ROOT $TTG_ROOT/../wrlsp
setenv FSS_ROOT $VIEW_NAME/vobs/ots/pts/fss
setenv FSS_PTS_ROOT $VIEW_NAME/vobs/ots/pts/fss
setenv CLI_DEF_ROOT /vobs/ots/pts/fss
setenv XEL_ROOT /vobs/ots/pss/xelerated/${MEA_REVISION}
setenv XEL_LIB_ROOT /vobs/ots/pss/xelerated/${MEA_REVISION}
setenv PROJECT_ROOT $TTG_ROOT
setenv OSPF_ROOT $TTG_ROOT/../ospf/rev_125-E/src
setenv MARBEN_BASE $TTG_ROOT/../marben
setenv DCL_BASE /vobs/common/dclCommon
setenv ATMSIM_BASE /vobs/common/cpCommon/atmsim
setenv CNTL_PLANE_BASE /vobs/common/cpCommon/controlPlane
setenv LR_BASE $FSS_ROOT/LR
setenv NPPROXY_DIR $TTG_ROOT/CommonPlatforms/ControllerServices/PktServPTS/npproxy
setenv VRPRS_DIR $TTG_ROOT/CommonPlatforms/ControllerServices/PktServPTS/vrprs
setenv ONGSOFT_DIR $TTG_ROOT/../OngSoftwareServices
setenv TTG_SSDIR $TTG_ROOT/SoftwareServices
setenv COMM_PACKSERV_DIR $TTG_ROOT/CommonPlatforms/ControllerServices/PacketServices
setenv PACKETSR_DIR $TTG_ROOT/CommonPlatforms/ControllerServices/PktServPTS
setenv CORESR_DIR $TTG_ROOT/CoreServices
setenv TELLABS_DIR $FSS_ROOT/../tellabs
setenv SMTMP_DIR $VIEW_NAME/vobs/ots/development/SMTMP
setenv SMTMP_PKT_SRV_DIR $VIEW_NAME/vobs/ots/development/SMTMP/PacketServices
setenv ESM_DIR $VIEW_NAME/vobs/ots/development/ESM
setenv ESM_PKT_SRV_DIR $VIEW_NAME/vobs/ots/development/ESM/PacketServices
setenv ESIM_DIR $VIEW_NAME/vobs/ots/development/ESIM
setenv ESIM_PKT_SRV_DIR $VIEW_NAME/vobs/ots/development/ESIM/PacketServices
setenv TELLABS_LR_DIR $VIEW_NAME/vobs/ots/pts/tellabs/linux_sim/LR
setenv ZLIB_BASE $TTG_ROOT/tools/zlib/src1.2.8
setenv LUMOS_VOB $VIEW_NAME/vobs/ots/lumos

setenv LC_DIR $VIEW_NAME/vobs/ots/development/PacketServices/PKTLC
setenv LC_PKT_SRV_DIR $VIEW_NAME/vobs/ots/development/PacketServices/PKTLC
# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
setenv CP_PREFERRED /vobs/astn/
setenv CP_ALTERNATE /vobs/common/cpCommon/
setenv CP_MAKE_ROOT /vobs/common/cpCommon/atmsim/make
setenv LINUX_ASON_SIM "NO"


#FSS Dependencies
setenv TARGET_OS OS_LINUX_PTHREADS

# Clearmake declarations
setenv CMAKE_PNAME_SEP "/"
setenv CCASE_BLD_UMASK 002

setenv CCASE_CONC_V6_OBSOLETE 1 

#
# Add development/tools path
# Preserve user's original PATH settings on first envxxx invocation
#
if (! $?ENV_ORIGINAL_PATH) then
    setenv ENV_ORIGINAL_PATH ${PATH}
endif
setenv PATH ${ENV_ORIGINAL_PATH}

echo "Environment set for Linux PTS Builds."
