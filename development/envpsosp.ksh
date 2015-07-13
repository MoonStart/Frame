# This set of instructions must be sourced with a '.' instruction.

# This version of the shell script works with the psosp vob and
# the /development/tools files.
# The PRISM_ROOT environment variable will eventually be replaced
# by the PSS_ROOT environment variable.

# Build OS and Target platform variables
export BUILD_OS=solaris
export PLATFORM=PSOSP
export LINUX_SIM="NO"
export SIM_TYPE=

# Root directories
export TTG_ROOT=/vobs/ots/development
export WRL_ROOT=/vobs/wrlinux
export WRL_PLAT_ROOT=/vobs/ots/wrlsp
export PROJECT_ROOT=$TTG_ROOT
export PSS_ROOT=/vobs/ots/psos/prism_ppc_2.5/pssppc.250
export OSPF_ROOT=/vobs/ots/ospf/rev_125-E/src
export EPILOGUE_ROOT=/vobs/ots/epilogue
export DCL_BASE=/vobs/common/dclCommon
export ATMSIM_BASE=/vobs/common/cpCommon/atmsim
export CNTL_PLANE_BASE=/vobs/common/cpCommon/controlPlane
export ZLIB_BASE=$TTG_ROOT/tools/zlib/src
export LUMOS_VOB=/vobs/ots/lumos

# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
export CP_PREFERRED=/vobs/astn/
export CP_ALTERNATE=/vobs/common/cpCommon/
export CP_MAKE_ROOT=/vobs/common/cpCommon/atmsim/make
export LINUX_ASON_SIM="NO"

# site specific settings
region=`cleartool hostinfo -l | sed -n -e 's/  Registry region: //p'`
if [ "$region" = "7100" -o "$region" = "7100_nt" ]; then
    default_LM_LICENSE_FILE="3539@lm-nv1.hq.tellabs.com"
elif [ "$region" = "shanghai" -o "$region" = "shanghai_nt" ]; then
    default_LM_LICENSE_FILE="3540@lm-cn1.tellabs.fi"
elif [ "$region" = "comcc" -o "$region" = "comcc_nt" ]; then
    default_LM_LICENSE_FILE="3539@lm-nv1.hq.tellabs.com"
else
    # just use the naperville server
    default_LM_LICENSE_FILE="3539@lm-nv1.hq.tellabs.com"
fi

# Diab license file
if [ ! -z $LM_LICENSE_FILE ]; then
  # LM_LICENSE_FILE is already defined in the environment.
  # Search for the servers we need.
  license_search=`echo $LM_LICENSE_FILE | grep "$default_LM_LICENSE_FILE"`
  if [ "$license_search" == "" ]; then
    # Place our servers at the front of the list.
    LM_LICENSE_FILE="$default_LM_LICENSE_FILE:$LM_LICENSE_FILE"
  fi
else
  LM_LICENSE_FILE="$default_LM_LICENSE_FILE"
fi
unset license_search
export LM_LICENSE_FILE

# Add development/tools path
export PRISM_ROOT=/vobs/ots/psos/prism_ppc_2.5
toolsPath=$TTG_ROOT/tools
sdsPath=$PRISM_ROOT/sds75
fromelfPath=$PRISM_ROOT/sds75/cmd
diabPath=$PRISM_ROOT/diab/4.3g/SUNS/bin
sniffPath=$PRISM_ROOT/sniff
pssppcPath=$PRISM_ROOT/pssppc.250/bin/solaris

#
# Add development/tools path
# Preserve user's original PATH settings on first envxxx invocation
#
if [ -z ${ENV_ORIGINAL_PATH} ]
then
    export ENV_ORIGINAL_PATH=${PATH}
fi
export PATH=${diabPath}:${pssppcPath}:${toolsPath}:${fromelfPath}:${sdsPath}:${sniffPath}:${ENV_ORIGINAL_PATH}

# Set the MPC860 tools path
export DIABPPCPATH=$PRISM_ROOT/diab
export DIABPPCVER=4.3g
export DIABLIB=$DIABPPCPATH/4.3g

# Clearmake declarations
export CMAKE_PNAME_SEP=/

# DSET root directory for UNIX builds.
export DSET_ROOT=/vobs/cots/dset_501a
export CCASE_BLD_UMASK=002
export CCASE_IP_VERSION=4
export CCASE_CONC_V6_OBSOLETE=yes

#FSS Dependencies
export TARGET_OS=PSOS

echo "Environment set for pSOS builds."
