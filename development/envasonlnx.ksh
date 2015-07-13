# This set of instructions must be sourced with a '.' instruction.
# This version of the shell script is meant to be used to build an ASON simulation
# to run under Linux.

#
# Build OS and Target platform variables
#
if [ `uname` == "Linux" ]
then
   export BLD_PLAT_DIR=LINUX386
   export BUILD_OS=linux
   export CLEARCASE_BLD_HOST_TYPE=linux
else
   echo ""
   echo "*** UNSUPPORTED BUILD OS ***"
   echo ""
   exit
fi

export BUILD_TARGET="linux"
export PLATFORM="LINUX"
export TOOLSET="LINUX"
export LINUX_ASON_SIM="YES"
export SIM_TYPE=

###############################################
# Set  VIEW_NAME to /view/view_name if you want
# to debug the code as view space is mounted on 
# VMWare root linux machines -
###############################################
vname=`cleartool pwv -short`
export VIEW_NAME=/view/$vname

export MEA_REVISION=mea_d240t
#export MEA_REVISION=mea_3_4_1
# Root directories
export TTG_ROOT=$VIEW_NAME/vobs/ots/development
export WRL_ROOT=$VIEW_NAME/vobs/wrlinux
export WRL_PLAT_ROOT=$VIEW_NAME/vobs/ots/wrlsp
export FSS_ROOT=$VIEW_NAME/vobs/ots/pss/fss
export ZLIB_BASE=$TTG_ROOT/tools/zlib/src1.2.8
export LUMOS_VOB=$VIEW_NAME/vobs/ots/lumos
export CLI_DEF_ROOT=$VIEW_NAME/vobs/ots/pss/fss
export XEL_ROOT=$VIEW_NAME/vobs/ots/pss/xelerated/${MEA_REVISION}
export XEL_LIB_ROOT=$VIEW_NAME/vobs/ots/pss/xelerated/${MEA_REVISION}
export PROJECT_ROOT=$TTG_ROOT
export OSPF_ROOT=$VIEW_NAME/vobs/ots/ospf/rev_125-E/src
export MARBEN_BASE=$VIEW_NAME/vobs/ots/marben
export DCL_BASE=$VIEW_NAME/vobs/common/dclCommon
export ATMSIM_BASE=$VIEW_NAME/vobs/common/cpCommon/atmsim
export CNTL_PLANE_BASE=$VIEW_NAME/vobs/common/cpCommon/controlPlane
export LR_BASE=$FSS_ROOT/LR
export NPPROXY_DIR=$TTG_ROOT/CommonPlatforms/ControllerServices/PacketServices/npproxy
export VRPRS_DIR=$TTG_ROOT/CommonPlatforms/ControllerServices/PacketServices/vrprs
export COMM_PACKSERV_DIR=$TTG_ROOT/CommonPlatforms/ControllerServices/PacketServices
export PACKETSR_DIR=$TTG_ROOT/CommonPlatforms/ControllerServices/PacketServices
export TELLABS_DIR=$VIEW_NAME/vobs/ots/pss/tellabs
export SMTMP_DIR=$VIEW_NAME/vobs/ots/development/SMTMP
export SMTMP_PKT_SRV_DIR=$VIEW_NAME/vobs/ots/development/SMTMP/PacketServices
export ESM_DIR=$VIEW_NAME/vobs/ots/development/ESM
export ESM_PKT_SRV_DIR=$VIEW_NAME/vobs/ots/development/ESM/PacketServices
export ESIM_DIR=$VIEW_NAME/vobs/ots/development/ESIM
export ESIM_PKT_SRV_DIR=$VIEW_NAME/vobs/ots/development/ESIM/PacketServices
export TELLABS_LR_DIR=$VIEW_NAME/vobs/ots/pss/tellabs/linux_sim/LR
export ZLIB_BASE=$TTG_ROOT/tools/zlib/src1.2.8

export LC_DIR=$VIEW_NAME/vobs/ots/development/PacketServices/PKTLC
export LC_PKT_SRV_DIR=$VIEW_NAME/vobs/ots/development/PacketServices/PKTLC
# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
export CP_PREFERRED=/vobs/astn/
export CP_ALTERNATE=/vobs/common/cpCommon/
export CP_MAKE_ROOT=/vobs/common/cpCommon/atmsim/make


#FSS Dependencies
export TARGET_OS=OS_LINUX_PTHREADS

# Clearmake declarations
export CMAKE_PNAME_SEP="/"
export CCASE_BLD_UMASK=002

export CCASE_IP_VERSION=4
export CCASE_CONC_V6_OBSOLETE=yes

#
## Add development/tools path
#
if [ -z ${ENV_ORIGINAL_PATH} ]; then
    export ENV_ORIGINAL_PATH=${PATH}
fi
export PATH=/usr/bin:${ENV_ORIGINAL_PATH}

echo "Environment set for Linux ASON Builds."
