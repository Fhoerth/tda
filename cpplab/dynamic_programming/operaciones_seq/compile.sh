#!/bin/sh
DIR=$(dirname "$0")
sh "$DIR/../../compile_template.sh" operaciones_seq_dp
sh "$DIR/../../compile_template.sh" operaciones_seq_bt
