#include <stdio.h>

#include "CS149intrin.h"
#include "logger.h"

void dump_memory(const void *ptr, size_t size) {
  const unsigned char *bytes = (const unsigned char *)ptr;

  for (size_t i = 0; i < size; i++) {
    printf("%02X ", bytes[i]);

    if ((i + 1) % 16 == 0)
      printf("\n");
  }

  printf("\n");
}

Logger CS149Logger;

int main() {
  __cs149_vec_float v;
  __cs149_vec_float result;

  int seedi[] = {0x01020304, 0x05060708, 0x08070605, 0x04030201};
  float seed[] = {
      *(float *)&seedi[0],
      *(float *)&seedi[1],
      *(float *)&seedi[2],
      *(float *)&seedi[3],
  };
  auto all_ones = _cs149_init_ones(4);
  _cs149_vload_float(v, seed, all_ones);

  _cs149_interleave_float(result, v);

  puts("all_ones:");
  dump_memory(&all_ones, sizeof(all_ones));
  puts("");

  puts("v:");
  dump_memory(&v, sizeof(v));
  puts("result:");
  dump_memory(&result, sizeof(result));
  return 0;
}
