#!/bin/bash

set -e

source_file=${1}
openssl des -in ${source_file} -out ${source_file}.enc
rm ${source_file}