#!/bin/bash

# NHAL Interface Documentation Build Script
# This script builds the documentation locally using CMake and Doxygen

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Ensure we're in project root directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_ROOT"

# Get version from git
PROJECT_VERSION=$("$SCRIPT_DIR/get-version.sh")

echo -e "${GREEN}NHAL Interface Documentation Builder${NC}"
echo "======================================"
echo "Version: ${PROJECT_VERSION}"
echo "Project root: $PROJECT_ROOT"

# Check if doxygen is installed
if ! command -v doxygen &> /dev/null; then
    echo -e "${RED}Error: Doxygen is not installed${NC}"
    echo "Please install Doxygen first:"
    echo "  Ubuntu/Debian: sudo apt-get install doxygen graphviz"
    echo "  macOS: brew install doxygen graphviz"
    echo "  Windows: Download from https://www.doxygen.nl/download.html"
    exit 1
fi

echo -e "${GREEN}✓${NC} Doxygen found: $(doxygen --version)"

# Check for graphviz (optional but recommended)
if command -v dot &> /dev/null; then
    echo -e "${GREEN}✓${NC} Graphviz found: $(dot -V 2>&1 | head -1)"
else
    echo -e "${YELLOW}⚠${NC} Graphviz not found - diagrams will not be generated"
fi

# Create build directory
BUILD_DIR="build"
echo ""
echo "Setting up build directory..."
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# Configure CMake with documentation enabled
echo ""
echo "Configuring CMake with documentation enabled..."
cmake -DBUILD_DOCS=ON ..

# Build documentation
echo ""
echo "Building documentation..."
cmake --build . --target docs

# Check if documentation was generated (Doxygen outputs to project root, not build dir)
cd ..
if [ -f "docs/html/index.html" ]; then
    echo ""
    echo -e "${GREEN}✅ Documentation generated successfully!${NC}"
    echo ""
    echo "📁 Documentation location: $(pwd)/docs/html/"
    echo "🌐 Open in browser: file://$(pwd)/docs/html/index.html"
    echo ""
    echo "To serve locally with Python:"
    echo "  cd $(pwd)/docs/html && python -m http.server 8000"
    echo "  Then open: http://localhost:8000"
else
    echo ""
    echo -e "${RED}❌ Documentation generation failed${NC}"
    echo "Expected to find: $(pwd)/docs/html/index.html"
    echo "Check the output above for errors"
    exit 1
fi