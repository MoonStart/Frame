# Source this file.

# This version of the shell script works with the psosp vob and
# the /development/tools files.
# The PRISM_ROOT environment variable will eventually be replaced
# by the PSS_ROOT environment variable.

# Build OS and Target platform variables
setenv BUILD_OS solaris
setenv PLATFORM PSOSP
setenv LINUX_SIM NO
unsetenv SIM_TYPE

# Root directories
setenv TTG_ROOT /vobs/ots/development
setenv WRL_ROOT /vobs/wrlinux
setenv WRL_PLAT_ROOT /vobs/ots/wrlsp
setenv PROJECT_ROOT $TTG_ROOT
setenv PSS_ROOT /vobs/ots/psos/prism_ppc_2.5/pssppc.250
setenv OSPF_ROOT /vobs/ots/ospf/rev_125-E/src
setenv EPILOGUE_ROOT /vobs/ots/epilogue
setenv DCL_BASE /vobs/common/dclCommon
setenv ATMSIM_BASE /vobs/common/cpCommon/atmsim
setenv CNTL_PLANE_BASE /vobs/common/cpCommon/controlPlane
setenv ZLIB_BASE $TTG_ROOT/tools/zlib/src
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
    set df_LM_LICENSE_FILE="3539@lm-nv1.hq.tellabs.com"
else if ( "$region" == "shanghai" || "$region" == "shanghai_nt" )  then
    set df_LM_LICENSE_FILE="3540@lm-cn1.tellabs.fi"
else if ( "$region" == "comcc" || "$region" == "comcc_nt" )  then
    set df_LM_LICENSE_FILE="3539@lm-nv1.hq.tellabs.com"
else
    # just use the naperville settings
    set df_LM_LICENSE_FILE="3539@lm-nv1.hq.tellabs.com"
endif

# Diab license file
if ( $?LM_LICENSE_FILE) then
  # LM_LICENSE_FILE is already defined in the environment.
  # Search for the servers we need.
  set license_search=`echo $LM_LICENSE_FILE | grep "$df_LM_LICENSE_FILE"`
  if ( "$license_search" == "" ) then
    # Place our servers at the front of the list.
    setenv LM_LICENSE_FILE "${df_LM_LICENSE_FILE}:$LM_LICENSE_FILE"
  endif
else
  setenv LM_LICENSE_FILE "$df_LM_LICENSE_FILE"
endif
unset license_search

# Add development/tools path
setenv PRISM_ROOT /vobs/ots/psos/prism_ppc_2.5
setenv toolsPath $TTG_ROOT/tools
setenv sdsPath $PRISM_ROOT/sds75
setenv fromelfPath $PRISM_ROOT/sds75/cmd
setenv diabPath $PRISM_ROOT/diab/4.3g/SUNS/bin
setenv sniffPath $PRISM_ROOT/sniff
setenv pssppcPath $PRISM_ROOT/pssppc.250/bin/solaris

#
# Preserve user's original PATH settings on first envxxx invocation
#
if (! $?ENV_ORIGINAL_PATH) then
    setenv ENV_ORIGINAL_PATH ${PATH}
endif
setenv PATH "${diabPath}:${pssppcPath}:${toolsPath}:${fromelfPath}:${sdsPath}:${sniffPath}:${ENV_ORIGINAL_PATH}"

# Set the MPC860 tools path
setenv DIABPPCPATH $PRISM_ROOT/diab
setenv DIABPPCVER 4.3g
setenv DIABLIB $DIABPPCPATH/4.3g

# Clearmake declarations
setenv CMAKE_PNAME_SEP /

# DSET root directory for UNIX builds.
setenv DSET_ROOT /vobs/cots/dset_501a
setenv CCASE_BLD_UMASK 002
setenv CCASE_IP_VERSION 4
setenv CCASE_CONC_V6_OBSOLETE yes

#FSS Dependencies
setenv TARGET_OS PSOS

echo "Environment set for pSOS builds."
