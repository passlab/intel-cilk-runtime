# Makefile - makefile for CilkPlus
#
# Copyright (C) 2015-2018, Intel Corporation
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in
#     the documentation and/or other materials provided with the
#     distribution.
#   * Neither the name of Intel Corporation nor the names of its
#     contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
# WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# 
# *********************************************************************
# 
# PLEASE NOTE: This file is a downstream copy of a file maintained in
# a repository at cilkplus.org. Changes made to this file that are not
# submitted through the contribution process detailed at
# http://www.cilkplus.org/submit-cilk-contribution will be lost the next
# time that a new version is released. Changes only submitted to the
# GNU compiler collection or posted to the git repository at
# https://bitbucket.org/intelcilkruntime/intel-cilk-runtime are
# not tracked.
# 
# We welcome your contributions to this open source project. Thank you
# for your assistance in helping us improve Cilk Plus.
#
# modification history
# --------------------
# 01a,12sep14,ghs created
#
# DESCRIPTION
# This file contains the makefile rules for building the CilkPlus library
#
#

include $(WIND_USR_MK)/defs.library.mk

LIB_BASE_NAME = $(LIB_VX_BASE_NAME)

CILKROOT = $(_WRS_CONFIG_$(VSBL_NAME)_PATH)/runtime

ifneq ($(TOOL_FAMILY),icc)
# do NOT compile lib without ICC
OBJS =
else

include $(CILKROOT)/Makefile.vxworks.def

OBJS =   \
         safe_str_constraint.o        \
         snprintf_support.o           \

#        ignore_handler_s.o
#        strcpy_s.o
#        strncpy_s.o
#        strnlen_s.o

endif

include $(WIND_USR_MK)/rules.library.mk

