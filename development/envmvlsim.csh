# Source this file.

# This version of the shell script allows building applications
# using clearmake with GNU Make compatibility mode
# This version builds the SMTMP similation code to run on the target hardware

#
# Build OS and Target platform variables
#
if ( `uname` == "Linux" ) then
   setenv BLD_PLAT_DIR LINUX386
   setenv BUILD_OS linux
   setenv CLEARCASE_BLD_HOST_TYPE linux
else
   echo ""
   echo "*** UNSUPPORTED BUILD OS ***"
   echo ""
   exit
endif

setenv BUILD_TARGET linux
setenv PLATFORM LINUX
setenv TOOLSET mvlppc
setenv SMTMP_SIM yes
setenv SMTMP_ENV "MVL LINUX for Simulation"
setenv LINUX_SIM NO
unsetenv SIM_TYPE

# Root directories
setenv TTG_ROOT /vobs/ots/development
setenv WRL_ROOT /vobs/wrlinux
setenv WRL_PLAT_ROOT /vobs/ots/wrlsp
setenv PROJECT_ROOT $TTG_ROOT
setenv EPILOGUE_ROOT /vobs/ots/epilogue
setenv DSET_ROOT /vobs/cots/dset_501a
setenv OSPF_ROOT /vobs/ots/ospf/rev_125-E/src
setenv CNTL_PLANE_BASE /vobs/common/cpCommon/controlPlane
setenv DCL_BASE /vobs/common/dclCommon
setenv ATMSIM_BASE /vobs/common/cpCommon/atmsim
setenv ZLIB_BASE $TTG_ROOT/tools/zlib/src1.2.8
# Clearmake declarations
setenv CMAKE_PNAME_SEP /
setenv CCASE_BLD_UMASK 002
setenv CCASE_IP_VERSION 4
setenv CCASE_CONC_V6_OBSOLETE yes

#FSS Dependencies
setenv TARGET_OS MVL

#
## Add development/tools path
#
if (! $?ENV_ORIGINAL_PATH) then
    setenv ENV_ORIGINAL_PATH ${PATH}
endif
setenv PATH ${ENV_ORIGINAL_PATH}

echo "Environment set for Linux builds for MontaVista simulation"

