# This set of instructions must be sourced with a '.' instruction.

################################################################################
# Make script to build applications using cleamake with GNU Make compatibility #
# mode                                                                         #
#                                                                              #
# This version builds the SMTMP simulation code for LINUX  to run on the       #
# target hardware                                                              # 
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
export SMTMP_SIM="yes"
export SMTMP_ENV="MVL LINUX for Simulation"
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
export CNTL_PLANE_BASE=/vobs/common/cpCommon/controlPlane
export DCL_BASE=/vobs/common/dclCommon
export ATMSIM_BASE=/vobs/common/cpCommon/atmsim
export ZLIB_BASE=$TTG_ROOT/tools/zlib/src1.2.8

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

echo "Environment set for Linux builds for MontaVista simulation"
