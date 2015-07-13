########################################################################################
#
#  Environment setup script for PC simulation (Linux) for the QORIQ based boards
#
#  source this file 
#
########################################################################################

#
# Build OS and Target platform variables
#
setenv BLD_PLAT_DIR LINUX386
setenv BUILD_OS linux
setenv CCASE_HOST_TYPE 7100_WRL
setenv CLEARCASE_BLD_HOST_TYPE linux
unsetenv SIM_TYPE

setenv BUILD_TARGET linux
setenv PLATFORM QORIQ_SIM

setenv WRL_VERSION 4.2
setenv WRL_KERNEL_VERSION 2.6.34
setenv WIND_HOME /vobs/wrlinux_${WRL_VERSION}
setenv WIND_BASE ${WIND_HOME}/wrlinux-4

setenv WRL_PLAT_ROOT /vobs/ots/wrlplat
setenv WRL_P2041_PLAT_ROOT ${WRL_PLAT_ROOT}/tlab_p2041
setenv WRL_P2041_INITRAMFS_ROOT ${WRL_P2041_PLAT_ROOT}/initramfs
setenv WRL_P2041_ROOTFS_ROOT ${WRL_P2041_PLAT_ROOT}/rootfs

setenv DEVROOT 
setenv SYSROOT "/usr/bin"
setenv TOOLCHAIN 
#setenv HOST_CROSS ${DEVROOT}/host-cross/bin
setenv CROSS_COMPILE 

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
setenv ZLIB_BASE $TTG_ROOT/tools/zlib/src1.2.8
setenv LUMOS_VOB /vobs/ots/lumos

# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
setenv CP_PREFERRED /vobs/astn/
setenv CP_ALTERNATE /vobs/common/cpCommon/
setenv CP_MAKE_ROOT /vobs/common/cpCommon/atmsim/make
setenv LINUX_ASON_SIM "NO"

setenv ONGSOFT_DIR /vobs/ots/OngSoftwareServices
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
#export TARGET_OS OS_LINUX_PTHREADS

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
setenv PATH ${ENV_ORIGINAL_PATH}

echo "Environment set for SIMULATOR builds (QorIQ)"

