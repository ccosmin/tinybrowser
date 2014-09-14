// Copyright (c) 2011, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ---
//
// Some generically useful utility routines that in google-land would
// be their own projects.  We make a shortened version here.

#ifndef TESTING_HPP
#define TESTING_HPP

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// -- CHECK macros ---------------------------------------------------------

// CHECK dies with a fatal error if condition is not true.  It is *not*
// controlled by NDEBUG, so the check will be executed regardless of
// compilation mode.  Therefore, it is safe to do things like:
//    CHECK(fp->Write(x) == 4)
// We allow stream-like objects after this for debugging, but they're ignored.
#define CHECK(condition)                                        \
  if (true) {                                                   \
    if (!(condition)) {                                         \
      fprintf(stderr, "Check failed: %s\n", #condition);        \
      exit(1);                                                  \
    }                                                           \
  } else std::cerr << ""

#define CHECK_OP(op, val1, val2)                                        \
  if (true) {                                                           \
    if (!((val1) op (val2))) {                                          \
      fprintf(stderr, "Check failed: %s %s %s\n", #val1, #op, #val2);   \
      exit(1);                                                          \
    }                                                                   \
  } else std::cerr << ""

#define CHECK_EQ(val1, val2) CHECK_OP(==, val1, val2)
#define CHECK_NE(val1, val2) CHECK_OP(!=, val1, val2)
#define CHECK_LE(val1, val2) CHECK_OP(<=, val1, val2)
#define CHECK_LT(val1, val2) CHECK_OP(< , val1, val2)
#define CHECK_GE(val1, val2) CHECK_OP(>=, val1, val2)
#define CHECK_GT(val1, val2) CHECK_OP(> , val1, val2)
// Synonyms for CHECK_* that are used in some unittests.
#define EXPECT_EQ(val1, val2) CHECK_EQ(val1, val2)
#define EXPECT_NE(val1, val2) CHECK_NE(val1, val2)
#define EXPECT_LE(val1, val2) CHECK_LE(val1, val2)
#define EXPECT_LT(val1, val2) CHECK_LT(val1, val2)
#define EXPECT_GE(val1, val2) CHECK_GE(val1, val2)
#define EXPECT_GT(val1, val2) CHECK_GT(val1, val2)
#define EXPECT_TRUE(cond)     CHECK(cond)
#define EXPECT_FALSE(cond)    CHECK(!(cond))
#define EXPECT_STREQ(a, b)    CHECK(strcmp(a, b) == 0)
#define ASSERT_TRUE(cond)     EXPECT_TRUE(cond)
// LOG(FATAL) is an alias for CHECK(FALSE).  We define FATAL, but no
// other value that is reasonable inside LOG(), so the compile will
// fail if someone tries to use LOG(DEBUG) or the like.
#define LOG(x)                INTERNAL_DO_LOG_ ## x
#define INTERNAL_DO_LOG_FATAL CHECK(false)

// These are used only in debug mode.
#ifdef NDEBUG
#define DCHECK(condition)     CHECK(condition)
#define DCHECK_EQ(val1, val2) CHECK_EQ(val1, val2)
#define DCHECK_NE(val1, val2) CHECK_NE(val1, val2)
#define DCHECK_LE(val1, val2) CHECK_LE(val1, val2)
#define DCHECK_LT(val1, val2) CHECK_LT(val1, val2)
#define DCHECK_GE(val1, val2) CHECK_GE(val1, val2)
#define DCHECK_GT(val1, val2) CHECK_GT(val1, val2)
#else
#define DCHECK(condition)     if (true) {} else std::cerr << ""
#define DCHECK_EQ(val1, val2) if (true) {} else std::cerr << ""
#define DCHECK_NE(val1, val2) if (true) {} else std::cerr << ""
#define DCHECK_LE(val1, val2) if (true) {} else std::cerr << ""
#define DCHECK_LT(val1, val2) if (true) {} else std::cerr << ""
#define DCHECK_GE(val1, val2) if (true) {} else std::cerr << ""
#define DCHECK_GT(val1, val2) if (true) {} else std::cerr << ""
#endif

#define PCHECK(cond)  CHECK(cond) << ": " << strerror(errno)
#define PFATAL(s)     do { perror(s); exit(1); } while (0)


extern std::vector<void (*)()> g_testlist;

// Call this in a .cc file where you will later call RUN_ALL_TESTS in main().
#define TEST_INIT                                                       \
  std::vector<void (*)()> g_testlist;  /* the tests to run */    \
  static int RUN_ALL_TESTS() {                                          \
    std::vector<void (*)()>::const_iterator it;                         \
    for (it = g_testlist.begin(); it != g_testlist.end(); ++it) {       \
      (*it)();   /* The test will error-exit if there's a problem. */   \
    }                                                                   \
    fprintf(stderr, "\nPassed %d tests\n\nPASS\n",                      \
            static_cast<int>(g_testlist.size()));                       \
    return 0;                                                           \
  }

#define TEST(a, b)                                      \
  class Test_##a##_##b {                                \
   public:                                              \
    Test_##a##_##b() { g_testlist.push_back(&Run); }    \
    static void Run();                                  \
  };                                                    \
  static Test_##a##_##b g_test_##a##_##b;               \
  void Test_##a##_##b::Run()


#endif

