########################################################################################
#
#  Environment setup script for building the PC simulation (Linux) for tlab_p2041 project
#
#  source this file with the '.' command
#
########################################################################################

#
# Build OS and Target platform variables
#
export BLD_PLAT_DIR=LINUX386
export BUILD_OS=linux
export CCASE_HOST_TYPE=7100_WRL
export CLEARCASE_BLD_HOST_TYPE=linux
export SIM_TYPE=

export BUILD_TARGET=linux
export PLATFORM=QORIQ_SIM

export WRL_VERSION=4.2
export WRL_KERNEL_VERSION=2.6.34
export WIND_HOME=/vobs/wrlinux_${WRL_VERSION}
export WIND_BASE=${WIND_HOME}/wrlinux-4

export WRL_PLAT_ROOT=/vobs/ots/wrlplat
export WRL_P2041_PLAT_ROOT=${WRL_PLAT_ROOT}/tlab_p2041
export WRL_P2041_INITRAMFS_ROOT=${WRL_P2041_PLAT_ROOT}/initramfs
export WRL_P2041_ROOTFS_ROOT=${WRL_P2041_PLAT_ROOT}/rootfs

export DEVROOT=
export SYSROOT=/usr/bin
export TOOLCHAIN=
#export HOST_CROSS=${DEVROOT}/host-cross/bin
export CROSS_COMPILE=


# Root directories
export TTG_ROOT=/vobs/ots/development
export PROJECT_ROOT=$TTG_ROOT
export CQ_ROOT=${TTG_ROOT}/CoreServices/QorIQ
export EPILOGUE_ROOT=/vobs/ots/epilogue
export DSET_ROOT=/vobs/cots/dset_501a
export OSPF_ROOT=/vobs/ots/ospf/rev_125-E/src
export FSS_ROOT=/vobs/ots/pts/fss
export FSS_PTS_ROOT=/vobs/ots/pts/fss
export BCM_ROOT=/vobs/ots/broadcom

export RPR_ROOT=/vobs/ots/development/PacketServices/xilinx/rprmac
export CNTL_PLANE_BASE=/vobs/common/cpCommon/controlPlane
export DCL_BASE=/vobs/common/dclCommon
export ATMSIM_BASE=/vobs/common/cpCommon/atmsim
export ECPE_ESW_BASE=/vobs/ecpe_eswitch
export ZLIB_BASE=$TTG_ROOT/tools/zlib/src1.2.8
export LUMOS_VOB=/vobs/ots/lumos

export ONGSOFT_DIR=/vobs/ots/OngSoftwareServices
export COMM_PACKSERV_DIR=/vobs/ots/development/CommonPlatforms/ControllerServices/PacketServices
export COMM_PACKSERV_PTS_DIR=/vobs/ots/development/CommonPlatforms/ControllerServices/PktServPTS
export PACKSERV_DIR=/vobs/ots/development/PacketServices
# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
export CP_PREFERRED=/vobs/astn/
export CP_ALTERNATE=/vobs/common/cpCommon/
export CP_MAKE_ROOT=/vobs/common/cpCommon/atmsim/make
export LINUX_ASON_SIM="NO"

###########################
# Xelerated MEA variables
#  XEL_ROOT: Root directory of include files for compilation.
#  XEL_LIB_ROOT: Root directory of the libraries to link with.
export MEA_REVISION=mea_d240t
export XEL_ROOT=/vobs/ots/pss/xelerated/${MEA_REVISION}
export XEL_LIB_ROOT=/vobs/ots/pss/xelerated/${MEA_REVISION}

#
# FSS (PTS stack) Dependencies
#
#export TARGET_OS=OS_LINUX_PTHREADS


# Clearmake declarations
export CMAKE_PNAME_SEP=/
export CCASE_BLD_UMASK=002
export CCASE_IP_VERSION=4
export CCASE_CONC_V6_OBSOLETE=yes

#
# Add development/tools path
# Preserve user's original PATH settings on first envxxx invocation
#
if [ -z ${ENV_ORIGINAL_PATH} ]
then
    export ENV_ORIGINAL_PATH=${PATH}
fi
export PATH=${ENV_ORIGINAL_PATH}

echo "Environment set for SIMULATOR builds (QorIQ)"
