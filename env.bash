#!/bin/bash

WORKING_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "Sourcing ..."
echo "WORKING_DIR => ${WORKING_DIR}"

# Add GC exe to PATH
export PATH=${WORKING_DIR}/bin/:$PATH