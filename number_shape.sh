#!/bin/bash
make
./grpwk data/dat$1_in data/dat$1_ref
make clean