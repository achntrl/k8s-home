#!/bin/bash

set -e

source_file=${1}
openssl aes256 -in ${source_file} -out ${source_file}.enc
