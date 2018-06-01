#!/bin/bash
make clean
make -i > build.log 2>&1
make test -i > build.log 2>&1
([ $? -eq 0 ] && echo "Completed Build!") || echo "failure!"
