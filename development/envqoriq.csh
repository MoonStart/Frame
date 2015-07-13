########################################################################################
#
#  Environment setup script for developing software for the QORIQ based boards
#
#  source this file 
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

if(($# == 1) && ("$1" == "-k")) then
	set kopt=1
else
	set kopt=0
endif

#
# Build OS and Target platform variables
#
setenv BLD_PLAT_DIR LINUX386
setenv BUILD_OS linux
setenv CCASE_HOST_TYPE 7100_WRL
setenv CLEARCASE_BLD_HOST_TYPE linux

setenv BUILD_TARGET linux

if ($kopt == 0) then
	setenv PLATFORM QORIQ
endif

unsetenv SIM_TYPE
setenv WRL_VERSION 4.3
setenv WRL_KERNEL_VERSION 2.6.34
setenv WIND_HOME /vobs/wrlinux_${WRL_VERSION}
setenv WIND_BASE ${WIND_HOME}/wrlinux-4

setenv WRL_PLAT_ROOT /vobs/ots/wrlplat
setenv WRL_P2041_PLAT_ROOT ${WRL_PLAT_ROOT}/tlab_p2041
setenv WRL_P2041_INITRAMFS_ROOT ${WRL_P2041_PLAT_ROOT}/initramfs
setenv WRL_P2041_ROOTFS_ROOT ${WRL_P2041_PLAT_ROOT}/rootfs

setenv DEVROOT ${WRL_P2041_PLAT_ROOT}/build/initramfs/tlab_p2041
setenv SYSROOT ${DEVROOT}/export/sysroot/tlab_p2041-glibc_small/x86-linux2
setenv TOOLCHAIN ${DEVROOT}/export/export-toolchain/toolchain/x86-linux2/bin
setenv KERNDIR ${DEVROOT}/build/linux-tlab_p2041-standard-build
setenv CROSS_COMPILE ppc_e500mc-target-linux-gnu-
setenv HOST_TOOLS ${WIND_BASE}/layers/ldat-tools/host-tools/bin

# Root directories
setenv TTG_ROOT /vobs/ots/development
setenv PROJECT_ROOT $TTG_ROOT
setenv CQ_ROOT ${TTG_ROOT}/CoreServices/QorIQ
setenv EPILOGUE_ROOT /vobs/ots/epilogue
setenv DSET_ROOT /vobs/cots/dset_501a
setenv OSPF_ROOT /vobs/ots/ospf/rev_125-E/src
setenv FSS_ROOT /vobs/ots/pts/fss
setenv FSS_PSS_ROOT /vobs/ots/pss/fss
setenv FSS_PTS_ROOT /vobs/ots/pts/fss
setenv BCM_ROOT /vobs/ots/broadcom

setenv RPR_ROOT /vobs/ots/development/PacketServices/xilinx/rprmac
setenv CNTL_PLANE_BASE /vobs/common/cpCommon/controlPlane
setenv DCL_BASE /vobs/common/dclCommon
setenv ATMSIM_BASE /vobs/common/cpCommon/atmsim
setenv ECPE_ESW_BASE /vobs/ecpe_eswitch
setenv ZLIB_BASE $TTG_ROOT/tools/zlib/src1.2.8
setenv LUMOS_VOB /vobs/ots/lumos

# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
setenv CP_PREFERRED /vobs/astn/
setenv CP_ALTERNATE /vobs/common/cpCommon/
setenv CP_MAKE_ROOT /vobs/common/cpCommon/atmsim/make
setenv LINUX_ASON_SIM "NO"

setenv COMM_PACKSERV_DIR /vobs/ots/development/CommonPlatforms/ControllerServices/PacketServices
setenv COMM_PACKSERV_PTS_DIR /vobs/ots/development/CommonPlatforms/ControllerServices/PktServPTS
setenv PACKSERV_DIR /vobs/ots/development/PacketServices
###########################
# Xelerated MEA variables
#  XEL_ROOT: Root directory of include files for compilation.
#  XEL_LIB_ROOT: Root directory of the libraries to link with.
setenv MEA_REVISION mea_d240t
setenv XEL_ROOT /vobs/ots/pss/xelerated/${MEA_REVISION}
setenv XEL_LIB_ROOT /vobs/ots/pss/xelerated/${MEA_REVISION}

#
# FSS (PTS stack) Dependencies
#
setenv TARGET_OS OS_QORIQ

# Clearmake declarations
setenv CMAKE_PNAME_SEP /
setenv CCASE_BLD_UMASK 002
setenv CCASE_IP_VERSION 4
setenv CCASE_CONC_V6_OBSOLETE yes

#
# Add development/tools path
# Preserve user's original PATH settings on first envxxx invocation
# $HOST_TOOLS must be last in the PATH; it contains common tools
#
if (! $?ENV_ORIGINAL_PATH) then
    setenv ENV_ORIGINAL_PATH ${PATH}
endif
setenv PATH ${TOOLCHAIN}:${SYSROOT}:${ENV_ORIGINAL_PATH}:${HOST_TOOLS}

if ($kopt == 0) then
	echo "Environment set for WR Linux ${WRL_VERSION} builds (QORIQ)"
else 
	echo "Environment set for WR Linux ${WRL_VERSION} builds (QORIQ - Kernel Only Build)"
endif


