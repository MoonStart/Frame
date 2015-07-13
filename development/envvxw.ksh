# This set of instructions must be sourced with a '.' instruction.
# This version of the shell script works with VxWorks.

#
# Build OS and Target platform variables
#
if [ `uname` == "SunOS" ]
then
   export BLD_PLAT_DIR=SUNS
   export BUILD_OS=solaris
   export CCASE_HOST_TYPE=7100
   export CLEARCASE_BLD_HOST_TYPE=7100
   export WIND_HOST_TYPE=sun4-solaris2
elif [ `uname` == "Linux" ]
then
   export BLD_PLAT_DIR=LINUX386
   export BUILD_OS=linux
   export CCASE_HOST_TYPE=linux
   export CLEARCASE_BLD_HOST_TYPE=linux
   export WIND_HOST_TYPE=x86-linux2
else
   export BLD_PLAT_DIR=WIN32
fi

export PLATFORM=VXWRKS
export LINUX_SIM="NO"
export SIM_TYPE=

# Root directories
export TTG_ROOT=/vobs/ots/development
export WRL_ROOT=/vobs/wrlinux
export WRL_PLAT_ROOT=/vobs/ots/wrlsp
export FSS_ROOT=/vobs/ots/pss/fss
export FSS_PSS_ROOT=/vobs/ots/pss/fss
export XEL_ROOT=/vobs/ots/pss/xelerated/mea_3_4_1
export PROJECT_ROOT=$TTG_ROOT
export OSPF_ROOT=/vobs/ots/ospf/rev_125-E/src
export MARBEN_BASE=/vobs/ots/marben
export DCL_BASE=/vobs/common/dclCommon
export ATMSIM_BASE=/vobs/common/cpCommon/atmsim
export CNTL_PLANE_BASE=/vobs/common/cpCommon/controlPlane
export NPPROXY_DIR=/vobs/ots/development/CommonPlatforms/ControllerServices/PacketServices/npproxy
export ONGSOFT_DIR=/vobs/ots/OngSoftwareServices
export COMM_PACKSERV_DIR=/vobs/ots/development/CommonPlatforms/ControllerServices/PacketServices
export PACKSERV_DIR=/vobs/ots/development/PacketServices
export ZLIB_BASE=$TTG_ROOT/tools/zlib/src2
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
    default_WRSD_LICENSE_FILE="7700@lm-nv1.hq.tellabs.com:7700@lm-nv2.hq.tellabs.com:7700@lm-nv3.hq.tellabs.com:7700@lm-pe1.ca.tellabs.com:7700@lm-pe2.ca.tellabs.com"
elif [ "$region" = "va_ashburn" -o "$region" = "va_ashburn_nt" ]; then
    default_WRSD_LICENSE_FILE="7700@lm-nv2.hq.tellabs.com:7700@lm-nv1.hq.tellabs.com:7700@lm-nv3.hq.tellabs.com:7700@lm-pe1.ca.tellabs.com:7700@lm-pe2.ca.tellabs.com"
elif [ "$region" = "shanghai" -o "$region" = "shanghai_nt" ]; then
    default_WRSD_LICENSE_FILE="7700@lm-cn2.tellabs.fi:7700@lm-cn1.tellabs.fi:7700@lm-in1.tellabs.fi"
elif [ "$region" = "comcc" -o "$region" = "comcc_nt" ]; then
    default_WRSD_LICENSE_FILE="7700@lm-in1.tellabs.fi:7700@lm-cn1.tellabs.fi:7700@lm-cn2.tellabs.fi"
else
    # we should never get here but if we do just use the naperville server
    default_WRSD_LICENSE_FILE="7700@lm-nv1.hq.tellabs.com:7700@lm-nv2.hq.tellabs.com:7700@lm-nv3.hq.tellabs.com"
fi

# VxWorks license file
if [ ! -z $WRSD_LICENSE_FILE ]; then
  # WRSD_LICENSE_FILE is already defined in the environment.
  # Search for the servers we need.
  license_search=`echo $WRSD_LICENSE_FILE | grep '7700@lm-'`
  if [ "$license_search" == "" ]; then
    # Place our servers at the front of the list.
    export WRSD_LICENSE_FILE="${default_WRSD_LICENSE_FILE}:$WRSD_LICENSE_FILE"
  fi
else
  export WRSD_LICENSE_FILE="${default_WRSD_LICENSE_FILE}"
fi
unset license_search

if [ -d /vobs/ots/vx1/wr ]; then
  # If the vxworks vob is visible in this view, use it.
  export WIND_HOME=/vobs/ots/vx1/wr
fi

export DIABPPCPATH=$WIND_HOME/diab
export DIABPPCVER=5.6.0.0
export DIABLIB=$DIABPPCPATH/$DIABPPCVER

# Set (new) key WindRiver parameters
export WIND_DIAB_PATH=$DIABLIB
export WIND_DOCS=$WIND_HOME/docs
export WIND_GNU_PATH=$WIND_HOME/gnu/3.3.2-vxworks61
export WIND_JRE_PATH=$WIND_HOME/jre/1.4.2
export WIND_BASE=$WIND_HOME/vxworks-6.1
export WIND_TOOLS=$WIND_HOME/workbench-2.3
export WIND_DFW_PATH=$WIND_TOOLS/dfw/0109h
export WIND_WRWB_PATH=$WIND_TOOLS/wrwb/2.3
export WIND_USR=$WIND_BASE/target/usr
export WIND_FOUNDATION_PATH=$WIND_TOOLS/foundation/4.0.6
export WIND_REGISTRY=tlabco
export WORKBENCH_BASE=$WIND_FOUNDATION_PATH/$WIND_HOST_TYPE/bin
export WORKBENCH_UTIL=$WIND_TOOLS/$WIND_HOST_TYPE/bin

# Other variables defined by Wind River's awful 'wrenv' utility.
# Not sure if we need them, but they shouldn't hurt anything.
export WIND_JRE_HOME=$WIND_JRE_PATH/$WIND_HOST_TYPE
export WIND_WRSV_PATH=$WIND_TOOLS/wrsv/4.6
export WIND_SCOPETOOLS=$WIND_HOME/scopetools-5.3

# Not sure if we need these...
export VXWRK_VOB=$WIND_BASE
export VXWRK_ROOT=$VXWRK_VOB/target

#
# Add development/tools path
# Preserve user's original PATH settings on first envxxx invocation
#  
if [ -z ${ENV_ORIGINAL_PATH} ]
then
    export ENV_ORIGINAL_PATH=${PATH}
fi 
export PATH=${WIND_DIAB_PATH}/${BLD_PLAT_DIR}/bin
export PATH=${PATH}:${TTG_ROOT}/tools
export PATH=${PATH}:${WIND_BASE}/host/${WIND_HOST_TYPE}/bin
export PATH=${PATH}:${WORKBENCH_BASE}
export PATH=${PATH}:${WORKBENCH_UTIL}
export PATH=${PATH}:${ENV_ORIGINAL_PATH}

#FSS Dependencies
export TARGET_OS=OS_VXWORKS

# Clearmake declarations
export CMAKE_PNAME_SEP=/
export CCASE_BLD_UMASK=002
export CCASE_IP_VERSION=4
export CCASE_CONC_V6_OBSOLETE=yes


# Execute environment set up utility...
# Supposed to call this, but it drops you into a
# non-ksh sub-shell which is not good.
# /home/addon/pne_ve_3.1/wrenv.sh -p vxworks-6.1
echo "Environment set for VxWorks builds."
