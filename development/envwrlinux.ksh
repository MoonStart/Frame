#
# This set of instructions must be sourced with a '.' instruction.

################################################################################
#
# Make script to build applications using clearmake with GNU Make compatibility
#
# mode
#
#
#
#

# Default to user-space app building
kopt=0

# Use -k if you are building the kernel, or if you are building .ko's.
if [[ $1 == "-k" ]] ; then
    kopt=1;
fi

#
# Build OS and Target platform variables
#
export BLD_PLAT_DIR=LINUX386
export BUILD_OS=linux
export CCASE_HOST_TYPE=7100_WRL
export CLEARCASE_BLD_HOST_TYPE=linux
export WIND_HOST_TYPE=x86-linux2

export BUILD_TARGET=linux
export PLATFORM=WRLINUX
#export TOOLSET=wrppc

export SIM_TYPE=
export WIND_HOME=/vobs/wrlinux
export WIND_BASE=$WIND_HOME/wrlinux-3.0
export WIND_DFW_PATH=$WIND_HOME/workbench-3.1/dfw/
export WIND_DOCS=$WIND_HOME/docs
export WIND_EXTENSIONS=$WIND_BASE/wrlinux/rtcore/extensions:$WIND_HOME/ocd-3.1:$WIND_HOME/workbench-3.1/analysis/extensions:$WIND_HOME/workbench-3.1/wrsysviewer:$WIND_HOME/workbench-3.1/wrwb/tools:$WIND_HOME/workbench-3.1/wrwb/wrlinux:$WIND_HOME/workbench-3.1/wrwb/wrhv:$WIND_HOME/workbench-3.1/wrwb/vthreads:$WIND_HOME/workbench-3.1/wrwb/vxworksmilshae:$WIND_HOME/workbench-3.1/wrwb/vxworksmils:$WIND_HOME/workbench-3.1/wrwb/vxworkscert:$WIND_HOME/workbench-3.1/wrwb/vxworks653:$WIND_HOME/workbench-3.1/wrwb/vxworks55:$WIND_HOME/workbench-3.1/wrwb/vxworks:$WIND_HOME/workbench-3.1/wrwb/wrworkbench:$WIND_HOME/docs/extensions
export WIND_FOUNDATION_PATH=$WIND_HOME/workbench-3.1/foundation/
export WIND_JRE_HOME=$WIND_HOME/jre/1.5.0_11/x86-linux2
export WIND_LINUX_BUILD=$WIND_BASE/wrlinux
export WIND_LINUX_CONFIGURE=$WIND_LINUX_BUILD/configure
export WIND_LX_HOME=$WIND_HOME
export WIND_OCD_PATH=$WIND_HOME/ocd-3.1
export WIND_PLATFORM=wrlinux-3.0
export WIND_PREFERRED_PACKAGES=wrlinux-3.0
export WIND_RTC_HOME=$WIND_BASE/layers/wrll-rtcore-5.2
export WIND_SAMPLES=$WIND_BASE/layers/wrll-rtcore-5.2/samples:$WIND_BASE/samples:$WIND_HOME/workbench-3.1/analysis/target/src/linux:$WIND_HOME/workbench-3.1/analysis/target/src/vxworks:$WIND_HOME/workbench-3.1/samples
export WIND_SCOPETOOLS_BASE=$WIND_HOME/workbench-3.1/analysis
export WIND_SCOPETOOLS_RPMS_BASE=$WIND_HOME/workbench-3.1/analysis/target/RPMS
export WIND_TOOLS=$WIND_HOME/workbench-3.1
export WIND_USERMODE_AGENT_PATH=$WIND_HOME/linux-2.x/usermode-agent
export WIND_USERMODE_AGENT=$WIND_HOME/linux-2.x/usermode-agent/bin/usermode-agent.sh
export WIND_UTILITIES=$WIND_HOME/utilities-1.0
export WIND_WRLINUX_BUILDDEPS_SCRIPT=$WIND_BASE/scripts/builddepsscript.sh
export WIND_WRLINUX_LAUNCH_SCRIPT=$WIND_BASE/scripts/launch_script.sh
export WIND_WRLINUX_LAYERS=$WIND_BASE/layers/wrll-analysis-1.0:$WIND_TOOLS/analysis/wrlinux
export WIND_WRLINUX_QUERY_SCRIPT=$WIND_BASE/scripts/queryProperties.sh
export WIND_WRLINUX_TARGET_BUTTONS=$WIND_BASE/scripts/wbblddefgen.txt
export WIND_WRSV_PATH=$WIND_HOME/workbench-3.1/wrsysviewer/
export WIND_WRWB_PATH=$WIND_HOME/workbench-3.1/wrwb/platform/eclipse
export DFW_PLUGIN_PATH=$WIND_HOME/ocd-3.1

export CROSS_COMPILE=powerpc-wrs-linux-gnu-ppc_e300c2-glibc_small-
export LINUX_KERNEL_VERSION=2.6.27

# Root directories
export TTG_ROOT=/vobs/ots/development
export WRL_ROOT=/vobs/wrlinux
export WRL_PLAT_ROOT=/vobs/ots/wrlsp
export PROJECT_ROOT=$TTG_ROOT
export EPILOGUE_ROOT=/vobs/ots/epilogue
export DSET_ROOT=/vobs/cots/dset_501a
export OSPF_ROOT=/vobs/ots/ospf/rev_125-E/src
export FSS_ROOT=/vobs/ots/pss/fss
export FSS_PSS_ROOT=/vobs/ots/pss/fss
export FSS_PTS_ROOT=/vobs/ots/pts/fss
export BCM_ROOT=/vobs/ots/broadcom

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

# Variables needed to build the Broadcom SDK 
export WRL_VERSION=3.0
export WRL_KERNEL_VERSION=2.6.27
export DEVROOT=${WRL_PLAT_ROOT}/tlab_mpc837x

if [[ $kopt -eq 0 ]] ; then
    ##########################################
    ### USER SPACE (APP) BUILD ENVIRONMENT ###
    ##########################################
    export BASE_SYSROOT=${DEVROOT}/export/sysroot/tlab_mpc837x-glibc_small/x86-linux2
    export SYSROOT=${DEVROOT}/export/sysroot/tlab_mpc837x-glibc_small/sysroot
    export TOOLCHAIN=${BASE_SYSROOT}
else
    ################################
    ### KERNEL BUILD ENVIRONMENT ###
    ################################
    unset BASE_SYSROOT
    unset SYSROOT
    unset TOOLCHAIN
fi

###########################
# Xelerated MEA variables
#  XEL_ROOT: Root directory of include files for compilation.
#  XEL_LIB_ROOT: Root directory of the libraries to link with.
export MEA_REVISION=mea_d240t
export XEL_ROOT=/vobs/ots/pss/xelerated/${MEA_REVISION}
export XEL_LIB_ROOT=/vobs/ots/pss/xelerated/${MEA_REVISION}
export XEL_CROSS_BASE=${WRL_PLAT_ROOT}/tlab_mpc837x/export/sysroot/tlab_mpc837x-glibc_small/sysroot/usr

# Clearmake declarations
export CMAKE_PNAME_SEP=/
export CCASE_BLD_UMASK=002
export CCASE_IP_VERSION=4
export CCASE_CONC_V6_OBSOLETE=yes

#FSS Dependencies
export TARGET_OS="WR"

#
# Add development/tools path
# Preserve user's original PATH settings on first envxxx invocation
#
if [ -z ${ENV_ORIGINAL_PATH} ]
then
    export ENV_ORIGINAL_PATH=${PATH}
fi
export PATH=$WRL_PLAT_ROOT/tlab_mpc837x/export/sysroot/tlab_mpc837x-glibc_small/x86-linux2
export PATH=${PATH}:$WRL_PLAT_ROOT/tlab_mpc837x/export/toolchain/x86-linux2/bin
export PATH=${PATH}:$TTG_ROOT/tools/wrlinux/bin
export PATH=${PATH}:${ENV_ORIGINAL_PATH}

if [[ $kopt -eq 0 ]] ; then
    echo "Environment set for Linux builds with WR distro on a Linux host"
else
    echo "Environment set for WR Linux ${WRL_VERSION} kernel builds"
fi
