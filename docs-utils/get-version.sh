#!/bin/bash

# Get version from git tags
# Always returns vX.Y.Z format, preserving full git describe output

# Find git repository root (in case script is called from anywhere)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# Try to get version from git
if command -v git &> /dev/null; then
    cd "$PROJECT_ROOT"
    if git rev-parse --git-dir > /dev/null 2>&1; then
        # Get full git describe output
        VERSION_FULL=$(git describe --tags --always --dirty 2>/dev/null)
        
        if [ $? -eq 0 ] && [ -n "$VERSION_FULL" ]; then
            # If it already starts with v, use as-is
            if [[ $VERSION_FULL =~ ^v ]]; then
                echo "$VERSION_FULL"
            else
                # If no v prefix (shouldn't happen with --tags), add it
                echo "v$VERSION_FULL"
            fi
        else
            echo "unknown"
        fi
    else
        echo "unknown"
    fi
else
    echo "unknown"
fi