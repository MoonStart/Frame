########################################################################################
#
#  Environment setup script for building the QEMU based PowerPC simulation (WRLinux5) for the mTera project.
#
#  source this file 
#
#  cobrien 13/07/25 - added -k option : this option should be used when building
#                     kernels. Some WRL packages do not build properly when the 
#                     PLATFORM variable is set by us. The -k option does not
#                     set PLAFTORM. This option should NOT be used for 
#                     application builds.
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
if ( `uname` == "Linux" ) then
   setenv BLD_PLAT_DIR LINUX386
   setenv BUILD_OS linux
   setenv CCASE_HOST_TYPE 7100_WRL
   setenv CLEARCASE_BLD_HOST_TYPE linux
else
   echo ""
   echo "*** UNSUPPORTED BUILD OS ***"
   echo ""
   exit
endif

setenv BUILD_TARGET linux

if ($kopt == 0) then
	setenv PLATFORM PICO_QEMU
endif

setenv SIM_TYPE QEMU

setenv WRL_VERSION 4.3
setenv WRL_KERNEL_VERSION 2.6.34
setenv WIND_HOME /vobs/wrlinux_${WRL_VERSION}
setenv WIND_BASE ${WIND_HOME}/wrlinux-4
setenv PICO_ROOT /vobs/ots/picoctrl

setenv WRL_PLAT_ROOT /vobs/ots/wrlplat
setenv WRL_QEMU_PLAT_ROOT ${WRL_PLAT_ROOT}/tlab_qemuppc
setenv WRL_QEMU_ROOTFS_ROOT ${WRL_QEMU_PLAT_ROOT}/build/rootfs

setenv DEVROOT ${WRL_QEMU_PLAT_ROOT}
setenv BASE_SYSROOT ${WRL_QEMU_ROOTFS_ROOT}/tlab_qemuppc/sysroots
setenv SYSROOT ${BASE_SYSROOT}/x86_64-wrlinuxsdk-linux
setenv WRL_BIN_PATH ${SYSROOT}/usr/bin:${SYSROOT}/usr/bin/ppc603e-wrs-linux
setenv TOOLCHAIN ${SYSROOT}/usr/bin/ppc603e-wrs-linux
setenv CROSS_COMPILE powerpc-wrs-linux-gnu-

setenv WRL_PLAT_LIB ${BASE_SYSROOT}/qemuppc-wrs-linux/lib
setenv WRL_PLAT_USR_LIB ${BASE_SYSROOT}/qemuppc-wrs-linux/usr/lib
setenv WRL50_PLAT_USR_LIB ${BASE_SYSROOT}/qemuppc-wrs-linux/usr/lib

# Root directories
setenv TTG_ROOT /vobs/ots/development
setenv PROJECT_ROOT $TTG_ROOT
setenv CQ_ROOT ${TTG_ROOT}/CoreServices/QorIQ
setenv EPILOGUE_ROOT /vobs/ots/epilogue
setenv DSET_ROOT /vobs/cots/dset_501a
setenv OSPF_ROOT /vobs/ots/ospf/rev_125-E/src
setenv FSS_ROOT /vobs/ots/pts/fss
setenv FSS_PTS_ROOT /vobs/ots/pts/fss
setenv BCM_ROOT /vobs/ots/broadcom

setenv RPR_ROOT /vobs/ots/development/PacketServices/xilinx/rprmac
setenv CNTL_PLANE_BASE /vobs/common/cpCommon/controlPlane
setenv DCL_BASE /vobs/common/dclCommon
setenv ATMSIM_BASE /vobs/common/cpCommon/atmsim
setenv ECPE_ESW_BASE /vobs/ecpe_eswitch
setenv TICPP_ROOT /vobs/ots/ticpp
setenv ZLIB_BASE $TTG_ROOT/tools/zlib/src1.2.8
setenv LUMOS_VOB /vobs/ots/lumos

# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
setenv CP_PREFERRED /vobs/astn/
setenv CP_ALTERNATE /vobs/common/cpCommon/
setenv CP_MAKE_ROOT /vobs/common/cpCommon/atmsim/make
setenv LINUX_ASON_SIM "NO"

###########################
# Xelerated MEA variables
#  XEL_ROOT: Root directory of include files for compilation.
#  XEL_LIB_ROOT: Root directory of the libraries to link with.
setenv MEA_REVISION mea_d240t
setenv XEL_ROOT /vobs/ots/pss/xelerated/${MEA_REVISION}
setenv XEL_LIB_ROOT /vobs/ots/pss/xelerated/${MEA_REVISION}

# Clearmake declarations
setenv CMAKE_PNAME_SEP /
setenv CCASE_BLD_UMASK 002
setenv CCASE_IP_VERSION 4
setenv CCASE_CONC_V6_OBSOLETE yes

#
## Add development/tools path
#
if (! $?ENV_ORIGINAL_PATH) then
    setenv ENV_ORIGINAL_PATH ${PATH}
endif
setenv PATH ${WRL_BIN_PATH}:${TOOLCHAIN}:${SYSROOT}:${ENV_ORIGINAL_PATH}

if ($kopt == 0) then
	echo "Environment set for WR Linux ${WRL_VERSION} PowerPC QEMU Simulator builds (MPC8378 or QORIQ)"
else 
	echo "Environment set for WR Linux ${WRL_VERSION} PowerPC QEMU Simulator builds (MPC8378 or QORIQ - Kernel Only Build)"
endif
