#!/bin/bash
make clean
make all -i > build.log 2>&1
make cleanobj
([ $? -eq 0 ] && echo "success!") || echo "failure!"
