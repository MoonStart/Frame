# Source this file.
# This version of the shell script works with VxWorks.

#
# Build OS and Target platform variables
#
# Give the user a chance to set the desired environment
if ( ($?ENV_UNAME) ) then
     setenv UNAME $ENV_UNAME
else
     setenv UNAME `uname`
endif

if ( "$UNAME" == "SunOS" ) then
   setenv BLD_PLAT_DIR SUNS
   setenv BUILD_OS solaris
   setenv CCASE_HOST_TYPE 7100
   setenv CLEARCASE_BLD_HOST_TYPE 7100
   setenv WIND_HOST_TYPE sun4-solaris2
else if ( "$UNAME" == "Linux" ) then
   setenv BLD_PLAT_DIR LINUX386
   setenv BUILD_OS linux
   setenv CCASE_HOST_TYPE linux
   setenv WIND_HOST_TYPE x86-linux2
   setenv CLEARCASE_BLD_HOST_TYPE linux
else
   setenv BLD_PLAT_DIR WIN32
endif

setenv PLATFORM VXWRKS67
setenv LINUX_SIM NO
unsetenv SIM_TYPE

# Root directories
setenv TTG_ROOT /vobs/ots/development
setenv WRL_ROOT /vobs/wrlinux
setenv WRL_PLAT_ROOT /vobs/ots/wrlsp
setenv WRL_P2041_PKG_DIR /vobs/ots/wrlplat/tlab_p2041
setenv FSS_PSS_ROOT /vobs/ots/pss/fss
setenv FSS_PTS_ROOT /vobs/ots/pts/fss
setenv XEL_ROOT /vobs/ots/pss/xelerated/mea_d240t
setenv PROJECT_ROOT $TTG_ROOT
setenv OSPF_ROOT /vobs/ots/ospf/rev_125-E/src
setenv MARBEN_BASE /vobs/ots/marben
setenv DCL_BASE /vobs/common/dclCommon
setenv ATMSIM_BASE /vobs/common/cpCommon/atmsim
setenv CNTL_PLANE_BASE /vobs/common/cpCommon/controlPlane
setenv NPPROXY_DIR /vobs/ots/development/CommonPlatforms/ControllerServices/PacketServices/npproxy
setenv ONGSOFT_DIR /vobs/ots/OngSoftwareServices
setenv COMM_PACKSERV_DIR /vobs/ots/development/CommonPlatforms/ControllerServices/PacketServices
setenv PACKSERV_DIR /vobs/ots/development/PacketServices
setenv ZLIB_BASE $TTG_ROOT/tools/zlib/src2
setenv LUMOS_VOB /vobs/ots/lumos

# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
setenv CP_PREFERRED /vobs/astn/
setenv CP_ALTERNATE /vobs/common/cpCommon/
setenv CP_MAKE_ROOT /vobs/common/cpCommon/atmsim/make
setenv LINUX_ASON_SIM "NO"

# site specific settings
set region=`cleartool hostinfo -l | sed -n -e 's/  Registry region: //p'`
if ( "$region" == "7100" || "$region" == "7100_nt" ) then
    set d_WRSD_LICENSE_FILE="7700@lm-nv1.hq.tellabs.com:7700@lm-nv2.hq.tellabs.com:7700@lm-nv3.hq.tellabs.com:7700@lm-pe1.ca.tellabs.com:7700@lm-pe2.ca.tellabs.com"
else if ( "$region" == "va_ashburn" || "$region" == "va_ashburn_nt" )  then
    set d_WRSD_LICENSE_FILE="7700@lm-nv2.hq.tellabs.com:7700@lm-nv1.hq.tellabs.com:7700@lm-nv3.hq.tellabs.com:7700@lm-pe1.ca.tellabs.com:7700@lm-pe2.ca.tellabs.com"
else if ( "$region" == "shanghai" || "$region" == "shanghai_nt" )  then
    set d_WRSD_LICENSE_FILE="7700@lm-cn2.tellabs.fi:7700@lm-cn1.tellabs.fi:7700@lm-in1.tellabs.fi"
else if ( "$region" == "comcc" || "$region" == "comcc_nt" )  then
    set d_WRSD_LICENSE_FILE="7700@lm-in1.tellabs.fi:7700@lm-cn1.tellabs.fi:7700@lm-cn2.tellabs.fi"
else
    # we should never get here but if we do just use the naperville settings
    set d_WRSD_LICENSE_FILE="7700@lm-nv1.hq.tellabs.com:7700@lm-nv2.hq.tellabs.com:7700@lm-nv3.hq.tellabs.com"
endif

# VxWorks license file
if ( $?WRSD_LICENSE_FILE) then
  # WRSD_LICENSE_FILE is already defined in the environment.
  # Search for the servers we need.
  set license_search=`echo $WRSD_LICENSE_FILE | grep '7700@lm-'`
  if ( "$license_search" == "" ) then
    # Place our servers at the front of the list.
    setenv WRSD_LICENSE_FILE "${d_WRSD_LICENSE_FILE}:$WRSD_LICENSE_FILE"
  endif
else
  setenv WRSD_LICENSE_FILE "${d_WRSD_LICENSE_FILE}"
endif
unset license_search

if ( -d /vobs/ots/vx1/wr ) then
  # If the vxworks vob is visible in this view, use it.
  setenv WIND_HOME /vobs/ots/vx1/wr
endif

setenv DIABPPCPATH $WIND_HOME/diab
setenv DIABPPCVER 5.8.0.0
setenv DIABLIB $DIABPPCPATH/$DIABPPCVER

# Set (new) key WindRiver parameters
setenv WIND_DIAB_PATH $DIABLIB
setenv WIND_DOCS $WIND_HOME/docs
setenv WIND_GNU_PATH $WIND_HOME/gnu/4.1.2-vxworks-6.7
setenv WIND_JRE_PATH $WIND_HOME/jre/1.4.2
setenv WIND_BASE $WIND_HOME/vxworks-6.7
setenv WIND_TOOLS $WIND_HOME/workbench-3.1
setenv WIND_DFW_PATH $WIND_TOOLS/dfw/0109h
setenv WIND_WRWB_PATH $WIND_TOOLS/wrwb/
setenv WIND_USR  $WIND_BASE/target/usr
setenv WIND_FOUNDATION_PATH $WIND_TOOLS/foundation/

#
# set up library path for tclsh
# Note: if LD_LIBRARY_PATH is not defined csh will complain about an Undefined variable
#
if ($?LD_LIBRARY_PATH) then
    setenv LD_LIBRARY_PATH ${WIND_FOUNDATION_PATH}/${WIND_HOST_TYPE}/lib:${LD_LIBRARY_PATH}
else
    setenv LD_LIBRARY_PATH ${WIND_FOUNDATION_PATH}/${WIND_HOST_TYPE}/lib
endif

setenv WIND_REGISTRY tlabco
setenv WORKBENCH_BASE $WIND_FOUNDATION_PATH/$WIND_HOST_TYPE/bin
setenv WORKBENCH_UTIL $WIND_TOOLS/$WIND_HOST_TYPE/bin
setenv WR_UTIL $WIND_HOME/utilities-1.0/$WIND_HOST_TYPE/bin

# Other variables defined by Wind River's awful 'wrenv' utility.
# Not sure if we need them, but they shouldn't hurt anything.
setenv WIND_JRE_HOME $WIND_JRE_PATH/$WIND_HOST_TYPE
setenv WIND_WRSV_PATH $WIND_TOOLS/wrsv/4.6
setenv WIND_SCOPETOOLS $WIND_HOME/scopetools-5.3

# Not sure if we need these...
setenv VXWRK_VOB $WIND_BASE
setenv VXWRK_ROOT $VXWRK_VOB/target
setenv VXWRK_IPNET $WIND_HOME/components/ip_net2-6.7

#
# Add development/tools path
#
if (! $?ENV_ORIGINAL_PATH) then
    setenv ENV_ORIGINAL_PATH ${PATH}
endif
setenv PATH ${WIND_DIAB_PATH}/${BLD_PLAT_DIR}/bin
setenv PATH "${PATH}:${TTG_ROOT}/tools"
setenv PATH "${PATH}:${WIND_BASE}/host/$WIND_HOST_TYPE/bin"
setenv PATH "${PATH}:${WORKBENCH_BASE}"
setenv PATH "${PATH}:${WORKBENCH_UTIL}"
setenv PATH "${PATH}:${WR_UTIL}"
setenv PATH "${PATH}:${ENV_ORIGINAL_PATH}"

# Clearmake declarations
setenv CMAKE_PNAME_SEP /
setenv CCASE_BLD_UMASK 002
setenv CCASE_IP_VERSION 4
setenv CCASE_CONC_V6_OBSOLETE yes

#FSS Dependencies
setenv TARGET_OS OS_VXWORKS

# Execute environment set up utility...
# Supposed to call this, but it drops you into a sub-shell which is not good.
#/home/addon/pne_ve_3.1/wrenv.sh -p vxworks-6.7
echo "Environment set for VxWorks 6.7 builds under ${BUILD_OS}."
