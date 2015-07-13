# Source this file.

#################################################################################
# Make script to build applications using clearmake with GNU Make compatibility #
# mode                                                                          #
#                                                                               #
# This version builds the SMTMP code on a Linux host. The code is targeted      #
# for the SMTMP card.  Use this script when building on a Linux host.           #
#                                                                               #
#################################################################################


# This version of the shell script allows building applications
# using clearmake with GNU Make compatibility mode
# This version builds the SMTMP target code for LINUX to run on the 
# target hardware

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
setenv SMTMP_SIM no
setenv SMTMP_ENV "MVL LINUX for Target"
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
setenv FSS_PSS_ROOT /vobs/ots/pss/fss
setenv MVL_ROOT /vobs/ots/mvl/4.0.1_ppc82xx/pro
setenv MVL_CC_ROOT /vobs/ots/linux_mvl_4.0.0/pro
setenv CNTL_PLANE_BASE /vobs/common/cpCommon/controlPlane
setenv DCL_BASE /vobs/common/dclCommon
setenv ATMSIM_BASE /vobs/common/cpCommon/atmsim
setenv ECPE_ESW_BASE /vobs/ecpe_eswitch
setenv ECPE_PROTOCOL_BASE /vobs/ecpe_eswitch/iss/code/future
setenv ZLIB_BASE $TTG_ROOT/tools/zlib/src1.2.8
setenv LUMOS_VOB /vobs/ots/lumos

# When searching for source files, we'll look in
# CP_PREFERRED first, and CP_ALTERNATE second.
# Note that a '/' is required at the end of these two definitions.
setenv CP_PREFERRED /vobs/astn/
setenv CP_ALTERNATE /vobs/common/cpCommon/
setenv CP_MAKE_ROOT /vobs/common/cpCommon/atmsim/make
setenv LINUX_ASON_SIM "NO"

###########################
# Xelerated MEA variables
#  XEL_ROOT: Root directory of include files for compilation.
#  XEL_LIB_ROOT: Root directory of the libraries to link with.
setenv MEA_REVISION mea_d240t
setenv XEL_ROOT /vobs/ots/pss/xelerated/${MEA_REVISION}
setenv XEL_LIB_ROOT /vobs/ots/pss/xelerated/${MEA_REVISION}
setenv XEL_CROSS_BASE ${MVL_ROOT}/devkit/ppc/82xx/target/usr

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

echo "Environment set for Linux builds for MontaVista target on a Linux host"

