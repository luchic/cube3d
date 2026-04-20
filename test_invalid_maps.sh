#!/bin/bash

# Path to the cub3d executable
EXECUTABLE="./cub3D"
# Directory containing invalid maps
MAPS_DIR="./assets/maps/invalid"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: $EXECUTABLE not found. Please run 'make' first.${NC}"
    exit 1
fi

echo "Testing invalid maps in $MAPS_DIR..."
echo "---------------------------------------"

for map in "$MAPS_DIR"/*.cub; do
    echo "Testing $(basename "$map"):"
    # Run cub3D and show its output
    echo "--- Program Output ---"
    ./cub3D "$map"
    EXIT_STATUS=$?
    echo "----------------------"
    
    # Check if the program failed (non-zero exit status) as expected for invalid maps
    if [ $EXIT_STATUS -ne 0 ]; then
        echo -e "${GREEN}Result: OK (Failed as expected)${NC}"
    else
        echo -e "${RED}Result: KO (Accepted invalid map)${NC}"
    fi
    echo "---------------------------------------"
done

echo "---------------------------------------"
echo "Testing complete."
