(
  echo "vectorWidth,utilization"
  for n in {2,4,8,16}; do
    echo -n "$n,"
    make clean 2>&1 >/dev/null
    make CXXFLAGS="-DVECTOR_WIDTH=$n" 2>&1 >/dev/null
    ./myexp -s 10000 | grep Utilization | awk '{print $NF}' | sed 's/%//g'
  done
) > ./data.csv
