#pragma once

#include <assert.h>
#include <stdio.h>

#define ASSERT(cond, ...)           \
  do {                              \
    if (!(cond)) {                  \
      fflush(stdout);               \
      fprintf(stderr, "\33[1;31m"); \
      fprintf(stderr, __VA_ARGS__); \
      fprintf(stderr, "\33[0m\n");  \
      assert(cond);                 \
    }                               \
  } while (0)

#define PANIC(...) ASSERT(0, __VA_ARGS__)

#define TODO() PANIC("TO IMPLEMENT %s()\n", __func__)