#include <cstdlib>
#include <stdio.h>
#include <thread>

#include "CycleTimer.h"

typedef struct {
  float x0, x1;
  float y0, y1;
  unsigned int width;
  unsigned int height;
  int maxIterations;
  int *output;
  int threadId;
  int numThreads;
} WorkerArgs;

extern void mandelbrotSerial(float x0, float y0, float x1, float y1, int width,
                             int height, int startRow, int numRows,
                             int maxIterations, int output[]);

//
// workerThreadStart --
//
// Thread entrypoint.
void workerThreadStart(WorkerArgs *const args) {
  double startTime = CycleTimer::currentSeconds();

  if (false) {
    // initial work division policy by blocks
    auto rowsPerThread = args->height / args->numThreads;
    auto remainder = args->height % args->numThreads;

    auto startRow = rowsPerThread * args->threadId;
    auto numRows = rowsPerThread;
    if (remainder && args->threadId == args->numThreads - 1) {
      numRows += remainder;
    }

    mandelbrotSerial(args->x0, args->y0, args->x1, args->y1, args->width,
                     args->height, startRow, numRows, args->maxIterations,
                     args->output);
  } else {
    // new work division policy by rows
    for (auto row = args->threadId; row < (int)args->height;
         row += args->numThreads) {
      mandelbrotSerial(args->x0, args->y0, args->x1, args->y1, args->width,
                       args->height, row, 1, args->maxIterations, args->output);
    }
  }
  double endTime = CycleTimer::currentSeconds();

  printf("time to run thread: %d: %fms\n", args->threadId,
         (endTime - startTime) * 1000);
}

//
// MandelbrotThread --
//
// Multi-threaded implementation of mandelbrot set image generation.
// Threads of execution are created by spawning std::threads.
void mandelbrotThread(int numThreads, float x0, float y0, float x1, float y1,
                      int width, int height, int maxIterations, int output[]) {
  static constexpr int MAX_THREADS = 64;

  if (numThreads > MAX_THREADS) {
    fprintf(stderr, "Error: Max allowed threads is %d\n", MAX_THREADS);
    exit(1);
  }

  // Creates thread objects that do not yet represent a thread.
  std::thread workers[MAX_THREADS];
  WorkerArgs args[MAX_THREADS];

  for (int i = 0; i < numThreads; i++) {
    args[i].x0 = x0;
    args[i].y0 = y0;
    args[i].x1 = x1;
    args[i].y1 = y1;
    args[i].width = width;
    args[i].height = height;
    args[i].maxIterations = maxIterations;
    args[i].numThreads = numThreads;
    args[i].output = output;

    args[i].threadId = i;
  }

  // Spawn the worker threads.  Note that only numThreads-1 std::threads
  // are created and the main application thread is used as a worker
  // as well.
  for (int i = 1; i < numThreads; i++) {
    workers[i] = std::thread(workerThreadStart, &args[i]);
  }

  workerThreadStart(&args[0]);

  // join worker threads
  for (int i = 1; i < numThreads; i++) {
    workers[i].join();
  }
}
