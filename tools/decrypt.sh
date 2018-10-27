#!/bin/bash

set -e

encrypted_file=${1}
decrypted_file=${encrypted_file%.enc}
openssl aes256 -d -in ${encrypted_file} -out ${decrypted_file}
