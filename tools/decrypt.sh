#!/bin/bash

set -e

encrypted_file=${1}
decrypted_file=${encrypted_file%.enc}
openssl des -d -in ${encrypted_file} -out ${decrypted_file}