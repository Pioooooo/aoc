#!/bin/bash
shopt -s extglob

parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
rm "$parent_path"/*/!(*.*|in) &>/dev/null
rm "$parent_path"/*/*.out &>/dev/null
