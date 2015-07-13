########################################################################################
#
#  Environment setup script for developing software for the tlab_p2041 project
#
#  source this file with the '.' command
#
#  arossett 12/09/28 - added -k option : this option should be used when building 
#                      kernels. Some WRL packages do not build properly when the 
#                      PLATFORM variable is set by us. The -k option does not
#                      set PLAFTORM. This option should NOT be used for 
#                      application builds. 
#
#  arossett 13/03/14 - modified to pass WRL and kernel version to Broadcom build
#                      Broadcom build imports WRL_VERSION, WRL_KERNEL_VERSION,
#                      WIND_BASE and TOOLCHAIN
#
########################################################################################

if [[ $1 == "-k" ]] ; then
	kopt=1;
else 
	kopt=0;
fi
 
# Build OS and Target platform variables
export BUILD_OS=linux
export BUILD_TARGET=linux

if [[ $kopt -eq 0 ]] ; then
	export PLATFORM=PICO_QORIQ;
fi

export SIM_TYPE=
export WRL_VERSION=4.3
export WRL_KERNEL_VERSION=2.6.34
export WIND_HOME=/vobs/wrlinux_${WRL_VERSION}
export WIND_BASE=${WIND_HOME}/wrlinux-4

export WRL_PLAT_ROOT=/vobs/ots/wrlplat
export WRL_P2041_PLAT_ROOT=${WRL_PLAT_ROOT}/tlab_p2041
export WRL_P2041_INITRAMFS_ROOT=${WRL_P2041_PLAT_ROOT}/initramfs
export WRL_P2041_ROOTFS_ROOT=${WRL_P2041_PLAT_ROOT}/rootfs

export CCASE_HOST_TYPE=7100_WRL

export DEVROOT=${WRL_P2041_PLAT_ROOT}/build/rootfs/tlab_p2041
export SYSROOT=${DEVROOT}/export/sysroot/tlab_p2041-glibc_small/sysroot
export TOOLCHAIN=${DEVROOT}/export/sysroot/tlab_p2041-glibc_small/x86-linux2
export TOOLCHAINPATH=${DEVROOT}/export/export-toolchain/toolchain/x86-linux2/bin
export KERNDIR=${DEVROOT}/build/linux-tlab_p2041-standard-build
export CROSS_COMPILE=ppc_e500mc-target-linux-gnu-
export HOST_TOOLS=${WIND_BASE}/layers/ldat-tools/host-tools/bin

# Root directories
export TTG_ROOT=/vobs/ots/development
export PICO_ROOT=/vobs/ots/picoctrl
export PROJECT_ROOT=$TTG_ROOT
export CQ_ROOT=${TTG_ROOT}/CoreServices/QorIQ
export EPILOGUE_ROOT=/vobs/ots/epilogue
export DSET_ROOT=/vobs/cots/dset_501a
export OSPF_ROOT=/vobs/ots/ospf/rev_125-E/src
export FSS_ROOT=/vobs/ots/pts/fss
export FSS_PSS_ROOT=/vobs/ots/pss/fss
export FSS_PTS_ROOT=/vobs/ots/pts/fss
export BCM_ROOT=/vobs/ots/broadcom
export TICPP_ROOT=/vobs/ots/ticpp
export WRL_PLAT_USR_LIB=${DEVROOT}/export/sysroot/tlab_p2041-glibc_small/sysroot/usr/lib

export RPR_ROOT=/vobs/ots/development/PacketServices/xilinx/rprmac
export CNTL_PLANE_BASE=/vobs/common/cpCommon/controlPlane
export DCL_BASE=/vobs/common/dclCommon
export ATMSIM_BASE=/vobs/common/cpCommon/atmsim
export ECPE_ESW_BASE=/vobs/ecpe_eswitch
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
export CCASE_CONC_V6_OBSOLETE=1

#
# Add development/tools path
# Preserve user's original PATH settings on first envxxx invocation
# $HOST_TOOLS must be last in the PATH; it contains common tools
#
if [ -z ${ENV_ORIGINAL_PATH} ]; then
    export ENV_ORIGINAL_PATH=${PATH}
fi
export PATH=${TOOLCHAIN}:${TOOLCHAINPATH}:${SYSROOT}:${ENV_ORIGINAL_PATH}:${HOST_TOOLS}

if [[ $kopt -eq 0 ]] ; then 
	echo "Environment set for WR Linux ${WRL_VERSION} builds (PICO on QorIQ)"
else 
	echo "Environment set for WR Linux ${WRL_VERSION} builds (PICO on QORIQ - Kernel Only Build)"
fi

