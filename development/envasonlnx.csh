# This set of instructions must be sourced with a 'source <thisfile>' instruction.
# This version of the shell script is meant to be used to build an ASON simulation
# to run under Linux.

#
# Build OS and Target platform variables
#
if ( `uname` == "Linux" ) then
   setenv BLD_PLAT_DIR LINUX386
   setenv BUILD_OS linux
   setenv CLEARCASE_BLD_HOST_TYPE linux
else
   echo ""
   echo "*** UNSUPPORTED BUILD OS ***"
   echo ""
   exit
endif

setenv BUILD_TARGET "linux"
setenv PLATFORM "LINUX"
setenv TOOLSET "LINUX"
setenv LINUX_ASON_SIM "YES"
unsetenv SIM_TYPE

###############################################
# Set  VIEW_NAME to /view/view_name if you want
# to debug the code as view space is mounted on 
# VMWare root linux machines -
###############################################
setenv vname `cleartool pwv -short`
setenv VIEW_NAME /view/$vname

setenv MEA_REVISION mea_d240t
# Root directories
setenv TTG_ROOT $VIEW_NAME/vobs/ots/development
setenv WRL_ROOT $VIEW_NAME/vobs/wrlinux
setenv WRL_PLAT_ROOT $VIEW_NAME/vobs/ots/wrlsp
setenv ZLIB_BASE $TTG_ROOT/tools/zlib/src1.2.8
setenv LUMOS_VOB $VIEW_NAME/vobs/ots/lumos
setenv FSS_ROOT $VIEW_NAME/vobs/ots/pss/fss
setenv XEL_ROOT $VIEW_NAME/vobs/ots/pss/xelerated/${MEA_REVISION}
setenv XEL_LIB_ROOT $VIEW_NAME/vobs/ots/pss/xelerated/${MEA_REVISION}
setenv PROJECT_ROOT $TTG_ROOT
setenv OSPF_ROOT $VIEW_NAME/vobs/ots/ospf/rev_125-E/src
setenv MARBEN_BASE $VIEW_NAME/vobs/ots/marben
setenv DCL_BASE $VIEW_NAME/vobs/common/dclCommon
setenv ATMSIM_BASE $VIEW_NAME/vobs/common/cpCommon/atmsim
setenv CNTL_PLANE_BASE $VIEW_NAME/vobs/common/cpCommon/controlPlane
setenv LR_BASE $FSS_ROOT/LR
setenv NPPROXY_DIR $TTG_ROOT/CommonPlatforms/ControllerServices/PacketServices/npproxy
setenv VRPRS_DIR $TTG_ROOT/CommonPlatforms/ControllerServices/PacketServices/vrprs
setenv COMM_PACKSERV_DIR $TTG_ROOT/CommonPlatforms/ControllerServices/PacketServices
setenv PACKETSR_DIR $TTG_ROOT/CommonPlatforms/ControllerServices/PacketServices
setenv TELLABS_DIR $VIEW_NAME/vobs/ots/pss/tellabs
setenv SMTMP_DIR $VIEW_NAME/vobs/ots/development/SMTMP
setenv SMTMP_PKT_SRV_DIR $VIEW_NAME/vobs/ots/development/SMTMP/PacketServices
setenv ESM_DIR $VIEW_NAME/vobs/ots/development/ESM
setenv ESM_PKT_SRV_DIR $VIEW_NAME/vobs/ots/development/ESM/PacketServices
setenv ESIM_DIR $VIEW_NAME/vobs/ots/development/ESIM
setenv ESIM_PKT_SRV_DIR $VIEW_NAME/vobs/ots/development/ESIM/PacketServices
setenv TELLABS_LR_DIR $VIEW_NAME/vobs/ots/pss/tellabs/linux_sim/LR
setenv ZLIB_BASE $TTG_ROOT/tools/zlib/src1.2.8

setenv LC_DIR $VIEW_NAME/vobs/ots/development/PacketServices/PKTLC
setenv LC_PKT_SRV_DIR $VIEW_NAME/vobs/ots/development/PacketServices/PKTLC
# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
setenv CP_PREFERRED /vobs/astn/
setenv CP_ALTERNATE /vobs/common/cpCommon/
setenv CP_MAKE_ROOT /vobs/common/cpCommon/atmsim/make

#FSS Dependencies
setenv TARGET_OS OS_LINUX_PTHREADS

# Clearmake declarations
setenv CMAKE_PNAME_SEP "/"
setenv CCASE_BLD_UMASK 002

setenv CCASE_IP_VERSION 4
setenv CCASE_CONC_V6_OBSOLETE yes 

#
## Add development/tools path
#
if (! $?ENV_ORIGINAL_PATH) then
    setenv ENV_ORIGINAL_PATH ${PATH}
endif
setenv PATH /usr/bin:${ENV_ORIGINAL_PATH}

echo "Environment set for Linux ASON Builds."
