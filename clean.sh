#!/bin/bash
shopt -s extglob
rm */!(*.*|in) &>/dev/null
rm */*.out &>/dev/null
