#!/bin/bash

function linux () {
  cd ci || exit
  if [ "${script}" == "clean" ]; then
    sudo rm ../build -rf
    return 0
  fi
  sudo docker run -it \
    -e "CXX=$CXX" \
    -e "CC=$CC" \
    -e "make_command=$make_command" \
    -e "cmake_command=$cmake_command" \
    -e "distribution=$distribution" \
    -v "$PWD/../:/jucipp" \
    --entrypoint="/jucipp/ci/${script}.sh" \
    "cppit/jucipp:$distribution"
}

#TODO Should run compile/install instructions for osx
function osx () {
  true
}

$TRAVIS_OS_NAME
