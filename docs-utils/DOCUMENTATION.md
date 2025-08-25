# Documentation Generation

This project uses [Doxygen](https://www.doxygen.nl/) to generate API documentation from the source code comments.

## Prerequisites

To generate documentation locally, you need:

- **Doxygen**: Main documentation generator
- **Graphviz** (optional): For generating diagrams
- **CMake**: For build system integration

### Installation

**Ubuntu/Debian:**
```bash
sudo apt-get install doxygen graphviz cmake
```

**macOS:**
```bash
brew install doxygen graphviz cmake
```

**Windows:**
- Download Doxygen from https://www.doxygen.nl/download.html
- Install Graphviz from https://graphviz.org/download/
- Install CMake from https://cmake.org/download/

## Building Documentation Locally

### Quick Method (Recommended)
```bash
./build-docs.sh
```

This script will:
1. Check for required dependencies
2. Configure CMake with documentation enabled  
3. Generate the documentation
4. Show you where to find the output

### Manual Method
```bash
# Create build directory and configure
mkdir build && cd build
cmake -DBUILD_DOCS=ON ..

# Build documentation
cmake --build . --target docs

# View the documentation
open docs/html/index.html  # macOS
xdg-open docs/html/index.html  # Linux
```

### Direct Doxygen (Alternative)
```bash
# Generate docs directly with Doxygen
doxygen Doxyfile

# Output will be in docs/html/
```

## Viewing Documentation

After generation, open `build/docs/html/index.html` in your browser.

For local development with live serving:
```bash
cd build/docs/html
python -m http.server 8000
# Then open http://localhost:8000
```

## Automatic Documentation (GitHub Pages)

Documentation is automatically generated and deployed to GitHub Pages on every push to the main branch.

- **Live Documentation**: Available at `https://[username].github.io/hal-interface/`
- **Workflow**: See `.github/workflows/documentation.yml`

## Documentation Structure

The generated documentation includes:

- **API Reference**: All functions, types, and structures
- **File Documentation**: Header file descriptions
- **Module Organization**: Grouped by peripheral type
- **Cross-References**: Automatic linking between related items

## Troubleshooting

**Common Issues:**

1. **"Doxygen not found"**
   - Install Doxygen as shown above
   - Ensure it's in your PATH

2. **"No documentation generated"**
   - Check that header files have proper Doxygen comments
   - Verify Doxyfile configuration

3. **"Missing diagrams"**
   - Install Graphviz for diagram generation
   - Set `HAVE_DOT = YES` in Doxyfile (already configured)

4. **"CMake can't find Doxygen"**
   - Ensure Doxygen is installed and in PATH
   - Use `-DBUILD_DOCS=OFF` to disable documentation

## Configuration

- **Doxyfile**: Main Doxygen configuration
- **CMakeLists.txt**: CMake integration with `BUILD_DOCS` option
- **.github/workflows/documentation.yml**: CI/CD automation