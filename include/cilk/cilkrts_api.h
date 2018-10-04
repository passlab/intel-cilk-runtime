/**
 * @file cilkrts_api.h
 *
 * @brief This file provide macros for using cilkrts without using spawn/sync and a compiler
 *  that support Cilkplus.  
 *  
 * @author Yonghong Yan (yanyh15@) and based on the cilk_fake.h file.
 *  
 * Check test/fib_cilkrts_api.c file for how to use it.
 * This file and those in test are BSD-licensed.
 */

#ifndef __CILKRTS_API_H__
#define __CILKRTS_API_H__

#include <alloca.h>

/** headers from cilk runtime */
#include <internal/abi.h>
#include <cilk/cilk_api.h>

#define __CILKRTS_VERSION_FLAG (__CILKRTS_ABI_VERSION << 24)
//#define trace_printf(...) printf(__VA_ARGS__)
#define trace_printf(...)

/* Called from the spawn helper to push the parent continuation on the task
 * deque so that it can be stolen.
 */
/* __CILKRTS_INLINE */ void __cilkrts_enter_frame_detach_parent(__cilkrts_worker *w, __cilkrts_stack_frame *sf,
                                                                __cilkrts_stack_frame * parent_frame)
{
    sf->call_parent = parent_frame;
    sf->worker      = w;
    sf->flags       = __CILKRTS_VERSION_FLAG;
    w->current_stack_frame = sf;

    trace_printf("helper frame entered: %p by %p(W%d)\n", sf, w, w->self+1);
    sf->spawn_helper_pedigree.rank = w->pedigree.rank;
    sf->spawn_helper_pedigree.parent = w->pedigree.parent;
    sf->call_parent->spawn_helper_pedigree.rank = w->pedigree.rank;
    sf->call_parent->spawn_helper_pedigree.parent = w->pedigree.parent;
    w->pedigree.rank = 0;
    w->pedigree.parent = &(sf->spawn_helper_pedigree);

    /* Push parent onto the task deque */
    __cilkrts_stack_frame *volatile *tail = w->tail;
    *tail++ = parent_frame;
    /* The stores must be separated by a store fence (noop on x86)
     * or the second store is a release (st8.rel on Itanium)   */
    w->tail = tail;
    sf->flags |= CILK_FRAME_DETACHED;
    trace_printf("frame detached: %p by %p(W%d)\n", parent_frame, w, w->self+1);
}

/* This variable is used in __CILKRTS_FORCE_FRAME_PTR(), below */
static int __cilkrts_dummy = 8;

/* The following macro is used to force the compiler into generating a frame
 * pointer.  We never change the value of __cilkrts_dummy, so the alloca()
 * is never called, but we need the 'if' statement and the __cilkrts_dummy
 * variable so that the compiler does not attempt to optimize it away.
 */
#define __CILKRTS_FORCE_FRAME_PTR(sf) do {                              \
    if (__builtin_expect(1 & __cilkrts_dummy, 0))                     \
        (sf).worker = (__cilkrts_worker*) alloca(__cilkrts_dummy);    \
} while (0)

/**
 * NOTE: Not sure the reason, the use of __builtin_expect is not only for optimization when using with GCC, but to
 * make it sure that the code does not into bug.
 */
#define __CILKRTS_SAVE_FP(sf) __cilkrts_save_fp_ctrl_state(&__stack_frame__)

#define __CILKRTS_POP_FRAME(__stack_frame__) do {                       \
    __stack_frame__.worker->current_stack_frame = __stack_frame__.call_parent;   \
    __stack_frame__.call_parent = 0;                                  \
} while (0)

/**
 * The SPAWN_HELPER_PROLOG/EIPLOG are macros used by the helper function of a task. 
 * They must be inside the helper function, called before and after the invocation of the task function.
 */
#define CILKRTS_SPAWN_HELPER_PROLOG(__parent_frame__)                     \
    struct __cilkrts_stack_frame __stack_frame__;                         \
    __cilkrts_worker *__worker__ = ((__cilkrts_stack_frame*)__parent_frame__)->worker;                  \
    __cilkrts_enter_frame_detach_parent(__worker__, &__stack_frame__, (__cilkrts_stack_frame*)__parent_frame__)

#define CILKRTS_SPAWN_HELPER_EPILOG()                                   \
    __CILKRTS_POP_FRAME(__stack_frame__);                                         \
    __cilkrts_leave_frame(&__stack_frame__);              \
    trace_printf("left frame: %p by %p(W%d)\n", &__stack_frame__, __cilkrts_get_tls_worker(), __cilkrts_get_tls_worker()->self+1)
/**
 * CILKRTS_FUNCTION_PROLOG/EPILOG are macros used by function that makes any cilk related calls. Each should
 * be invoked only once in each function's invocation. 
 *
 * CILKRTS_FUNCTION_PROLOG must be called before the first invocation of CILKRTS_SPAWN, CILKRTS_SYNC, 
 * or other __cilkrts related runtime routine. It should be invoked only once in one function. 
 */
#define CILKRTS_FUNCTION_PROLOG()                                           \
    struct __cilkrts_stack_frame __stack_frame__;                   \
    __CILKRTS_FORCE_FRAME_PTR(__stack_frame__);                     \
    __cilkrts_enter_frame_1(&__stack_frame__);                    \
    trace_printf("spawnning frame entered: %p by %p(w%d)\n", &__stack_frame__, __cilkrts_get_tls_worker(), __cilkrts_get_tls_worker()->self+1)

/**
 * Must be called after the last invocation of CILKRTS_SPAWN, CILKRTS_SYNC, or other __cilkrts related runtime routine
 * It should be invoked only once in one function. 
 */
#define CILKRTS_FUNCTION_EPILOG() do {                                      \
    __CILKRTS_POP_FRAME(__stack_frame__);                                 \
    if (__stack_frame__.flags != __CILKRTS_VERSION_FLAG)  {             \
        trace_printf("to leave frame: %p by %p(W%d)\n", &__stack_frame__, __cilkrts_get_tls_worker(), __cilkrts_get_tls_worker()->self+1);      \
        __cilkrts_leave_frame(&__stack_frame__);                       \
    } \
} while (0)

/**
 * This macro provide cilk_spawn functionality, i.e. for spawning a task using helper function of the task.
 * The first parameter of the helper function must be __cilkrts_stack_frame *, 
 * which is the parent_frame of the spawned task. The rest parameters are the parameters/arguments for the task. 
 * The body of the helper function must start with CILKRTS_SPAWN_HELPER_PROLOG and ends with CILKRTS_SPAWN_HELPER_EPILOG. 
 *
 */
#define CILKRTS_SPAWN(helper_func, ...) do { \
    __CILKRTS_SAVE_FP(__stack_frame__);             \
    if (__builtin_expect(! CILK_SETJMP(__stack_frame__.ctx), 1)) {        \
        helper_func(&__stack_frame__, __VA_ARGS__);                                                     \
    } else {                                                              \
        trace_printf("continutation entry after being stolen by %p(W%d)\n", __cilkrts_get_tls_worker(), __cilkrts_get_tls_worker()->self+1); \
    }                   \
} while (0)

/**
 * This macro is the same as cilk_sync
 * If an CILKRTS_SYNC is not called before CILKRTS_FUNCTION_EPILOG, CILKRTS_SYNC MUST be explicitly called.
 */
#define CILKRTS_SYNC() do {                       \
    __stack_frame__.parent_pedigree = __stack_frame__.worker->pedigree;    \
    if (__builtin_expect(__stack_frame__.flags & CILK_FRAME_UNSYNCHED, 0)) {                           \
        __CILKRTS_SAVE_FP(__stack_frame__);            \
        if (CILK_SETJMP(__stack_frame__.ctx) == 0)   {         \
            trace_printf("to sync frame: %p by %p(W%d)\n", &__stack_frame__, __cilkrts_get_tls_worker(), __cilkrts_get_tls_worker()->self+1);        \
            __cilkrts_sync(&__stack_frame__);                       \
        } \
    }                                                               \
    __stack_frame__.worker->pedigree.rank++;                        \
} while (0)

#endif //__CILKRTS_API_H__
