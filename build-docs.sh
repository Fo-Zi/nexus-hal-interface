#!/bin/bash

# Convenience script to call the documentation build script
# This keeps the main interface clean while organizing files properly

exec "$(dirname "${BASH_SOURCE[0]}")/docs-utils/build-docs.sh" "$@"