# This set of instructions must be sourced with a '.' instruction.

################################################################################
# Make script to build applications using cleamake with GNU Make compatibility #
# mode                                                                         #
#                                                                              #
# This version builds the SMTMP target code for LINUX  to run on the           #
# target hardware. Use this script when building on a Solaris host             # 
#                                                                              #
################################################################################

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
export TOOLSET="mvlppc"
export SMTMP_SIM="no"
export SMTMP_ENV="MVL LINUX for Target"
export LINUX_SIM="NO"
export SIM_TYPE=

# Root directories
export TTG_ROOT="/vobs/ots/development"
export WRL_ROOT=/vobs/wrlinux
export WRL_PLAT_ROOT=/vobs/ots/wrlsp
export PROJECT_ROOT=$TTG_ROOT
export EPILOGUE_ROOT=/vobs/ots/epilogue
export DSET_ROOT=/vobs/cots/dset_501a
export OSPF_ROOT=/vobs/ots/ospf/rev_125-E/src
export FSS_PSS_ROOT=/vobs/ots/pss/fss
export MVL_ROOT=/vobs/ots/mvl/4.0.1_ppc82xx/pro
export MVL_CC_ROOT=${MVL_ROOT}
export CNTL_PLANE_BASE=/vobs/common/cpCommon/controlPlane
export DCL_BASE=/vobs/common/dclCommon
export ATMSIM_BASE=/vobs/common/cpCommon/atmsim
export ECPE_ESW_BASE=/vobs/ecpe_eswitch
export ECPE_PROTOCOL_BASE=/vobs/ecpe_eswitch/iss/code/future
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
export XEL_CROSS_BASE=${MVL_ROOT}/devkit/ppc/82xx/target/usr

# Clearmake declarations
export CMAKE_PNAME_SEP="/"
export CCASE_BLD_UMASK=002
export CCASE_IP_VERSION=4
export CCASE_CONC_V6_OBSOLETE=yes

#FSS Dependencies
export TARGET_OS=MVL

if [ -z ${ENV_ORIGINAL_PATH} ]; then
    export ENV_ORIGINAL_PATH=${PATH}
fi
export PATH=${ENV_ORIGINAL_PATH}

echo "Environment set for Linux builds for MontaVista target"
