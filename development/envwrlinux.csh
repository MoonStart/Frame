# Source this file.

#################################################################################
# Make script to build applications using clearmake with GNU Make compatibility #
# mode                                                                          #
#################################################################################

# Default to user-space app building
set kopt=0

# Use -k if you are building the kernel, or if you are building .ko's.
if(($# == 1) && ("$1" == "-k")) then
    set kopt=1
endif

#
# Build OS and Target platform variables
#
if ( `uname` == "Linux" ) then
   setenv BLD_PLAT_DIR LINUX386
   setenv BUILD_OS linux
   setenv CCASE_HOST_TYPE 7100_WRL
   setenv WIND_HOST_TYPE x86-linux2
   setenv CLEARCASE_BLD_HOST_TYPE linux
else
   echo ""
   echo "*** UNSUPPORTED BUILD OS ***"
   echo ""
   exit
endif

setenv BUILD_TARGET linux
setenv PLATFORM WRLINUX
#setenv TOOLSET wrppc

unsetenv SIM_TYPE
setenv WIND_HOME /vobs/wrlinux
setenv WIND_BASE $WIND_HOME/wrlinux-3.0
setenv WIND_DFW_PATH $WIND_HOME/workbench-3.1/dfw/
setenv WIND_DOCS $WIND_HOME/docs
setenv WIND_EXTENSIONS $WIND_BASE/wrlinux/rtcore/extensions:$WIND_HOME/ocd-3.1:$WIND_HOME/workbench-3.1/analysis/extensions:$WIND_HOME/workbench-3.1/wrsysviewer:$WIND_HOME/workbench-3.1/wrwb/tools:$WIND_HOME/workbench-3.1/wrwb/wrlinux:$WIND_HOME/workbench-3.1/wrwb/wrhv:$WIND_HOME/workbench-3.1/wrwb/vthreads:$WIND_HOME/workbench-3.1/wrwb/vxworksmilshae:$WIND_HOME/workbench-3.1/wrwb/vxworksmils:$WIND_HOME/workbench-3.1/wrwb/vxworkscert:$WIND_HOME/workbench-3.1/wrwb/vxworks653:$WIND_HOME/workbench-3.1/wrwb/vxworks55:$WIND_HOME/workbench-3.1/wrwb/vxworks:$WIND_HOME/workbench-3.1/wrwb/wrworkbench:$WIND_HOME/docs/extensions
setenv WIND_FOUNDATION_PATH $WIND_HOME/workbench-3.1/foundation/
setenv WIND_JRE_HOME $WIND_HOME/jre/1.5.0_11/x86-linux2
setenv WIND_LINUX_BUILD $WIND_BASE/wrlinux
setenv WIND_LINUX_CONFIGURE $WIND_LINUX_BUILD/configure
setenv WIND_LX_HOME $WIND_HOME
setenv WIND_OCD_PATH $WIND_HOME/ocd-3.1
setenv WIND_PLATFORM wrlinux-3.0
setenv WIND_PREFERRED_PACKAGES wrlinux-3.0
setenv WIND_RTC_HOME $WIND_BASE/layers/wrll-rtcore-5.2
setenv WIND_SAMPLES $WIND_BASE/layers/wrll-rtcore-5.2/samples:$WIND_BASE/samples:$WIND_HOME/workbench-3.1/analysis/target/src/linux:$WIND_HOME/workbench-3.1/analysis/target/src/vxworks:$WIND_HOME/workbench-3.1/samples
setenv WIND_SCOPETOOLS_BASE $WIND_HOME/workbench-3.1/analysis
setenv WIND_SCOPETOOLS_RPMS_BASE $WIND_HOME/workbench-3.1/analysis/target/RPMS
setenv WIND_TOOLS $WIND_HOME/workbench-3.1
setenv WIND_USERMODE_AGENT_PATH $WIND_HOME/linux-2.x/usermode-agent
setenv WIND_USERMODE_AGENT $WIND_HOME/linux-2.x/usermode-agent/bin/usermode-agent.sh
setenv WIND_UTILITIES $WIND_HOME/utilities-1.0
setenv WIND_WRLINUX_BUILDDEPS_SCRIPT $WIND_BASE/scripts/builddepsscript.sh
setenv WIND_WRLINUX_LAUNCH_SCRIPT $WIND_BASE/scripts/launch_script.sh
setenv WIND_WRLINUX_LAYERS $WIND_BASE/layers/wrll-analysis-1.0:$WIND_TOOLS/analysis/wrlinux
setenv WIND_WRLINUX_QUERY_SCRIPT $WIND_BASE/scripts/queryProperties.sh
setenv WIND_WRLINUX_TARGET_BUTTONS $WIND_BASE/scripts/wbblddefgen.txt
setenv WIND_WRSV_PATH $WIND_HOME/workbench-3.1/wrsysviewer/
setenv WIND_WRWB_PATH $WIND_HOME/workbench-3.1/wrwb/platform/eclipse
setenv DFW_PLUGIN_PATH $WIND_HOME/ocd-3.1

setenv CROSS_COMPILE powerpc-wrs-linux-gnu-ppc_e300c2-glibc_small-

setenv LINUX_KERNEL_VERSION 2.6.27

# Root directories
setenv TTG_ROOT /vobs/ots/development
setenv WRL_ROOT /vobs/wrlinux
setenv WRL_PLAT_ROOT /vobs/ots/wrlsp
setenv PROJECT_ROOT $TTG_ROOT
setenv EPILOGUE_ROOT /vobs/ots/epilogue
setenv DSET_ROOT /vobs/cots/dset_501a
setenv OSPF_ROOT /vobs/ots/ospf/rev_125-E/src
setenv FSS_ROOT /vobs/ots/pss/fss
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

# Variables needed to build the Broadcom SDK 
setenv WRL_VERSION 3.0
setenv WRL_KERNEL_VERSION 2.6.27
setenv DEVROOT ${WRL_PLAT_ROOT}/tlab_mpc837x

if ($kopt == 0) then
    ##########################################
    ### USER SPACE (APP) BUILD ENVIRONMENT ###
    ##########################################
    setenv BASE_SYSROOT ${DEVROOT}/export/sysroot/tlab_mpc837x-glibc_small/x86-linux2
    setenv SYSROOT ${DEVROOT}/export/sysroot/tlab_mpc837x-glibc_small/sysroot
    setenv TOOLCHAIN ${BASE_SYSROOT}
else
    ################################
    ### KERNEL BUILD ENVIRONMENT ###
    ################################
    unsetenv BASE_SYSROOT
    unsetenv SYSROOT
    unsetenv TOOLCHAIN
endif

###########################
# Xelerated MEA variables
#  XEL_ROOT: Root directory of include files for compilation.
#  XEL_LIB_ROOT: Root directory of the libraries to link with.
setenv MEA_REVISION mea_d240t
setenv XEL_ROOT /vobs/ots/pss/xelerated/${MEA_REVISION}
setenv XEL_LIB_ROOT /vobs/ots/pss/xelerated/${MEA_REVISION}
setenv XEL_CROSS_BASE ${WRL_PLAT_ROOT}/tlab_mpc837x/export/sysroot/tlab_mpc837x-glibc_small/sysroot/usr

# Clearmake declarations
setenv CMAKE_PNAME_SEP /
setenv CCASE_BLD_UMASK 002
setenv CCASE_IP_VERSION 4	
setenv CCASE_CONC_V6_OBSOLETE yes	

#FSS Dependencies
setenv TARGET_OS "WR"

#
# Add development/tools path
#
if (! $?ENV_ORIGINAL_PATH) then
    setenv ENV_ORIGINAL_PATH ${PATH}
endif
setenv PATH $WRL_PLAT_ROOT/tlab_mpc837x/export/sysroot/tlab_mpc837x-glibc_small/x86-linux2
setenv PATH "${PATH}:$WRL_PLAT_ROOT/tlab_mpc837x/export/toolchain/x86-linux2/bin"
setenv PATH "${PATH}:$TTG_ROOT/tools/wrlinux/bin"
setenv PATH "${PATH}:${ENV_ORIGINAL_PATH}"

if ($kopt == 0) then
    echo "Environment set for Linux builds with WR distro on a Linux host"
else
    echo "Environment set for WR Linux ${WRL_VERSION} kernel builds"
endif

