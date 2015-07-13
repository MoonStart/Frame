# This set of instructions must be sourced with a '.' instruction.
# This version of the shell script works with VxWorks.

# Build OS and Target platform variables
export BUILD_OS="linux"
export BUILD_TARGET="linux"
export PLATFORM="LINUX"
export TOOLSET="LINUX"
export LINUX_SIM="YES"
export SIM_TYPE=

# Build DCL to support MPLSTP
export OS_TYPE_SUFFIX=_mplstp

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
export WRL_PLAT_ROOT=$TTG_ROOT/../wrlsp
export FSS_ROOT=$VIEW_NAME/vobs/ots/pts/fss
export FSS_PTS_ROOT=$VIEW_NAME/vobs/ots/pts/fss
export CLI_DEF_ROOT=/vobs/ots/pts/fss
export XEL_ROOT=/vobs/ots/pss/xelerated/${MEA_REVISION}
export XEL_LIB_ROOT=/vobs/ots/pss/xelerated/${MEA_REVISION}
export PROJECT_ROOT=$TTG_ROOT
export OSPF_ROOT=$TTG_ROOT/../ospf/rev_125-E/src
export MARBEN_BASE=$TTG_ROOT/../marben
export DCL_BASE=/vobs/common/dclCommon
export ATMSIM_BASE=/vobs/common/cpCommon/atmsim
export CNTL_PLANE_BASE=/vobs/common/cpCommon/controlPlane
export LR_BASE=$FSS_ROOT/LR
export NPPROXY_DIR=$TTG_ROOT/CommonPlatforms/ControllerServices/PktServPTS/npproxy
export VRPRS_DIR=$TTG_ROOT/CommonPlatforms/ControllerServices/PktServPTS/vrprs
export ONGSOFT_DIR=$TTG_ROOT/../OngSoftwareServices
export TTG_SSDIR=$TTG_ROOT/SoftwareServices
export COMM_PACKSERV_DIR=$TTG_ROOT/CommonPlatforms/ControllerServices/PacketServices
export PACKETSR_DIR=$TTG_ROOT/CommonPlatforms/ControllerServices/PktServPTS
export PACKSERV_DIR=/vobs/ots/development/PacketServices
export CORESR_DIR=$TTG_ROOT/CoreServices
export TELLABS_DIR=$FSS_ROOT/../tellabs
export SMTMP_DIR=$VIEW_NAME/vobs/ots/development/SMTMP
export SMTMP_PKT_SRV_DIR=$VIEW_NAME/vobs/ots/development/SMTMP/PacketServices
export ESM_DIR=$VIEW_NAME/vobs/ots/development/ESM
export ESM_PKT_SRV_DIR=$VIEW_NAME/vobs/ots/development/ESM/PacketServices
export ESIM_DIR=$VIEW_NAME/vobs/ots/development/ESIM
export ESIM_PKT_SRV_DIR=$VIEW_NAME/vobs/ots/development/ESIM/PacketServices
export TELLABS_LR_DIR=$VIEW_NAME/vobs/ots/pts/tellabs/linux_sim/LR
export ZLIB_BASE=$TTG_ROOT/tools/zlib/src1.2.8
export LUMOS_VOB=$VIEW_NAME/vobs/ots/lumos

export LC_DIR=$VIEW_NAME/vobs/ots/development/PacketServices/PKTLC
export LC_PKT_SRV_DIR=$VIEW_NAME/vobs/ots/development/PacketServices/PKTLC
# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
export CP_PREFERRED=/vobs/astn/
export CP_ALTERNATE=/vobs/common/cpCommon/
export CP_MAKE_ROOT=/vobs/common/cpCommon/atmsim/make
export LINUX_ASON_SIM="NO"


#FSS Dependencies
export TARGET_OS=OS_LINUX_PTHREADS

# Clearmake declarations
export CMAKE_PNAME_SEP="/"
export CCASE_BLD_UMASK=002

export CCASE_CONC_V6_OBSOLETE=1 

#
# Add development/tools path
# Preserve user's original PATH settings on first envxxx invocation
#
if [ -z ${ENV_ORIGINAL_PATH} ]; then
    export ENV_ORIGINAL_PATH=${PATH}
fi
export PATH=${ENV_ORIGINAL_PATH}

echo "Environment set for Linux PTS Builds."
