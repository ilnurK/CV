#!/usr/bin/bash
#
# The script allows you to run the reporting_client multiple times with
# randomly given correct arguments
#
# Usage:
#   data_filler.sh quantity [options] arguments
#
# Options:
#   quantity: int - Number of client launches
#   --scan - Enable the client's scan mode
#
# Examples:
#   script.sh 35
#   script.sh 42 scan

get_params() {
  ra_hour=$(($RANDOM % 24))
  ra_min=$(($RANDOM % 60))
  ra_sec=$(($RANDOM % 60))
  dec_deg=$(($RANDOM % 90))
  dec_min=$(($RANDOM % 60))
  dec_sec=$(($RANDOM % 60))
  if [ $(($RANDOM % 2)) -eq 0 ]; then
    dec_deg=-$dec_deg
  fi
  random_float1=$(python3 -c 'import random as r; print(r.random())')
  ra_sec=$(python3 -c "print($random_float1 + $ra_sec)")
  random_float2=$(python3 -c 'import random as r; print(r.random())')
  dec_sec=$(python3 -c "print($random_float2 + $dec_sec)")
  echo "$ra_hour $ra_min $ra_sec $dec_deg $dec_min $dec_sec"
}

quantity=$1
client=./reporting_client.py
is_correct=1
if [ $# -gt 2 ]; then
  is_correct=0
elif [ $# -eq 2 ] && [ $2 != '--scan' ]; then
  is_correct=0
fi
if [ $is_correct -eq 0 ]; then
  echo "argument incorrect"
else
  scan=''
  if [ $# = 2 ]; then
    scan="scan"
  fi
  while [ $quantity -gt 0 ]; do
    params=$(get_params)
    echo $params
    $client $scan $params
    quantity=$(($quantity - 1))
  done
fi
