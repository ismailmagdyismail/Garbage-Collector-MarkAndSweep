#!/bin/bash

WORKING_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "Sourcing ..."
echo "WORKING_DIR => ${WORKING_DIR}"

# Add built executables to PATH
export PATH=${WORKING_DIR}/artifacts/bin/:$PATH
export PATH=${WORKING_DIR}/examples/bin/:$PATH
