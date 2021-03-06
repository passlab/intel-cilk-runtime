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

LIB_BASE_NAME = cilkplus

include $(WIND_KRNL_MK)/defs.library.mk
include $(WIND_KRNL_MK)/defs.layers.mk

ifneq ($(TOOL_FAMILY),icc)
# do NOT compile lib without ICC
OBJS =
else

include $(VSBL_$(VSBL_NAME)_PATH)/runtime/Makefile.vxworks.def

OBJS =   \
         bug.o                              \
         cilk-abi.o                         \
         cilk-abi-cilk-for.o                \
         cilk-abi-vla-internal.o            \
         cilk_api.o                         \
         cilk_fiber.o                       \
         cilk_fiber-unix.o                  \
         cilk_malloc.o                      \
         c_reducers.o                       \
         except-gcc.o                       \
         frame_malloc.o                     \
         full_frame.o                       \
         global_state.o                     \
         jmpbuf.o                           \
         local_state.o                      \
         metacall_impl.o                    \
         os_mutex-unix.o                    \
         os-unix.o                          \
         pedigrees.o                        \
         record-replay.o                    \
         reducer_impl.o                     \
         scheduler.o                        \
         signal_node.o                      \
         spin_mutex.o                       \
         stats.o                            \
         sysdep-unix.o                      \
         worker_mutex.o

SUBDIRS = sslib config

endif

include $(WIND_KRNL_MK)/rules.library.mk

