(
  echo "numThreads,speedup"
  for n in {1..64}; do
    echo -n "$n,"
    ./mandelbrot -t $n |
      grep speedup |
      tr '(' ' ' |
      tr 'x' ' ' |
      awk '{print $1}'
  done
) > ./thread_data_view_1_policy_2.csv

(
  echo "numThreads,speedup"
  for n in {1..64}; do
    echo -n "$n,"
    ./mandelbrot -t $n --view 2 |
      grep speedup |
      tr '(' ' ' |
      tr 'x' ' ' |
      awk '{print $1}'
  done
) > ./thread_data_view_2_policy_2.csv
