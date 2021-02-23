#!/bin/sh

script_name=$0
trace_file=$1
png_folder=$2

python_script="$(dirname "$script_name" )/heatView.py"

python $python_script $trace_file $png_folder

mkdir -p $png_folder
cd $png_folder

ffmpeg -framerate 1 -i heatmap_%d.png -start_number 1 -c:v mpeg4 -vtag xvid -qscale:v 4 -c:a libmp3lame -qscale:a 5 $trace_file.avi
