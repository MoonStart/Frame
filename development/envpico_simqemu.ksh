########################################################################################
#
#  Environment setup script for building the QEMU based PowerPC simulation (WRLinux5) for the mTera project.
#
#  source this file with the '.' command
#
#  cobrien 13/07/01 - added -k option : this option should be used when building 
#                     kernels. Some WRL packages do not build properly when the 
#                     PLATFORM variable is set by us. The -k option does not
#                     set PLAFTORM. This option should NOT be used for 
#                     application builds.
########################################################################################

if [[ $1 == "-k" ]] ; then
	kopt=1;
else 
	kopt=0;
fi

#
# Build OS and Target platform variables
#
if [ `uname` == "Linux" ]
then
   export BLD_PLAT_DIR=LINUX386
   export BUILD_OS=linux
   export CCASE_HOST_TYPE=7100_WRL
   export CLEARCASE_BLD_HOST_TYPE=linux
else
   echo ""
   echo "*** UNSUPPORTED BUILD OS ***"
   echo ""
   exit
fi

export BUILD_TARGET=linux

if [[ $kopt -eq 0 ]] ; then
	export PLATFORM=PICO_QEMU
fi

export SIM_TYPE=QEMU

export WRL_VERSION=4.3
export WRL_KERNEL_VERSION=2.6.34
export WIND_HOME=/vobs/wrlinux_${WRL_VERSION}
export WIND_BASE=${WIND_HOME}/wrlinux-4

export WRL_PLAT_ROOT=/vobs/ots/wrlplat
export WRL_QEMU_PLAT_ROOT=${WRL_PLAT_ROOT}/tlab_qemuppc
export WRL_QEMU_ROOTFS_ROOT=${WRL_QEMU_PLAT_ROOT}/build/rootfs

export DEVROOT=${WRL_QEMU_PLAT_ROOT}
export BASE_SYSROOT=${WRL_QEMU_ROOTFS_ROOT}/tlab_qemuppc/sysroots
export SYSROOT=${BASE_SYSROOT}/x86_64-wrlinuxsdk-linux
export WRL_BIN_PATH=${SYSROOT}/usr/bin:${SYSROOT}/usr/bin/ppc603e-wrs-linux
export TOOLCHAIN=${SYSROOT}/usr/bin/ppc603e-wrs-linux
export CROSS_COMPILE=powerpc-wrs-linux-gnu-

export WRL_PLAT_LIB=${BASE_SYSROOT}/qemuppc-wrs-linux/lib
export WRL_PLAT_USR_LIB=${BASE_SYSROOT}/qemuppc-wrs-linux/usr/lib
export WRL50_PLAT_USR_LIB=${BASE_SYSROOT}/qemuppc-wrs-linux/usr/lib

# Root directories
export TTG_ROOT=/vobs/ots/development
export PICO_ROOT=/vobs/ots/picoctrl
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
export TICPP_ROOT=/vobs/ots/ticpp
export ZLIB_BASE=$TTG_ROOT/tools/zlib/src1.2.8
export LUMOS_VOB=/vobs/ots/lumos

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

# Clearmake declarations
export CMAKE_PNAME_SEP=/
export CCASE_BLD_UMASK=002
export CCASE_IP_VERSION=4
export CCASE_CONC_V6_OBSOLETE=yes

#
# Add development/tools path
# Preserve user's original PATH settings on first envxxx invocation
#
if [ -z ${ENV_ORIGINAL_PATH} ]; then
    export ENV_ORIGINAL_PATH=${PATH}
fi
export PATH=${WRL_BIN_PATH}:${TOOLCHAIN}:${SYSROOT}:${ENV_ORIGINAL_PATH}

if [[ $kopt -eq 0 ]] ; then 
	echo "Environment set for WR Linux ${WRL_VERSION} PowerPC QEMU Simulator builds (MPC8378 or QORIQ)"
else 
	echo "Environment set for WR Linux ${WRL_VERSION} PowerPC QEMU Simulator builds (MPC8378 or QORIQ- Kernel Only Build)"
fi

