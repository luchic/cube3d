#!/bin/bash

# Path to the cub3d executable
EXECUTABLE="./cub3D"
# Directory containing valid maps
MAPS_DIR="./assets/maps/valid"
# How long to wait before closing each map (in seconds)
TIMEOUT=2

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: $EXECUTABLE not found. Please run 'make' first.${NC}"
    exit 1
fi

echo "Testing valid maps in $MAPS_DIR..."
echo "Each map will be displayed for $TIMEOUT seconds before closing."
echo "-------------------------------------------------------------"

for map in "$MAPS_DIR"/*.cub; do
    echo -n "Testing $(basename "$map"): "
    
    # Create a temporary file for output
    OUT=$(mktemp)
    
    # Run cub3D in the background and redirect all output to the temp file
    "$EXECUTABLE" "$map" > "$OUT" 2>&1 &
    PID=$!
    
    # Wait for the timeout
    sleep "$TIMEOUT"
    
    # Check if the process is still running
    if ps -p $PID > /dev/null; then
        kill $PID
        echo -e "${GREEN}OK (Rendered and closed)${NC}"
    else
        # If it finished early, check its exit code
        wait $PID
        EXIT_CODE=$?
        if [ $EXIT_CODE -eq 0 ]; then
            echo -e "${GREEN}OK (Finished early with success)${NC}"
        else
            echo -e "${RED}KO (Failed with exit code $EXIT_CODE)${NC}"
            # Display the captured output if it failed
            cat "$OUT"
        fi
    fi
    rm -f "$OUT"
done

echo "---------------------------------------"
echo "Valid map testing complete."
