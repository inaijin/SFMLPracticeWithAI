#!/bin/bash

# This script iterates through each file in the current directory,
# stages it, and commits it separately with a custom message.
# It's designed for macOS environments.

echo "Starting individual file commits..."

# Loop through all files in the current directory
for file in *; do
    # Check if it's a regular file (not a directory or special file)
    if [ -f "$file" ]; then
        echo "Processing file: $file"

        # Stage the current file
        git add "$file"

        # Check if the add command was successful
        if [ $? -eq 0 ]; then
            # Construct the commit message
            commit_message="add $file For Pacman"

            # Commit the staged file
            git commit -m "$commit_message"

            # Check if the commit was successful
            if [ $? -eq 0 ]; then
                echo "Successfully committed: '$file' with message: '$commit_message'"
            else
                echo "Error committing '$file'. It might be unchanged or Git is not configured."
            fi
        else
            echo "Error staging '$file'. It might not exist or there are Git issues."
        fi
    fi
done

echo "Individual file commit process completed."
