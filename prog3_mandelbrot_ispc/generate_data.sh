(
  echo "taskCount,speedup"
  for n in {2,4,8,16,32}; do
    echo -n "$n,"

    make clean 2>&1 >/dev/null
    make ISPCFLAGS="-O3 --target=avx512skx-i32x16 --arch=x86-64 --opt=disable-fma --pic -DTASK_COUNT=$n" 2>&1 >/dev/null
    ./mandelbrot_ispc --task | grep "speedup from task ISPC" | tr '(x' ' ' | awk '{print $1}'
  done
) > ./data.csv
