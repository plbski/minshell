#!/bin/bash

# Check if an argument is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <directory> $1<header name> $2<tab len>"
    exit 1
fi

dir="$1"
output_file="prototypes.h"

if [ ! -d "$dir" ]; then
    echo "Error: Directory '$dir' does not exist."
    exit 1
fi

echo -e "#ifndef PROTOTYPES_H\n# define PROTOTYPES_H\n" > "$output_file"

if [ -n "$2" ]; then
    echo -e "# include \"$2\"\n" >> "$output_file"
fi

max_len=9

if [ -n "$3" ]; then
    max_len=$3
fi

# Now loop through all .c files again and format the prototypes
{
    find "$dir" -type f -name "*.c" | while read -r file; do
		relative_path=$(echo "$file" | sed "s|^$dir/||")
        echo "//		$relative_path"
        
        # Second pass: Format all function prototypes in the file
        awk -v max_len="$max_len" '
        /^[a-zA-Z_]/ && !/^static/ {
            # Extract return type and remove it from the rest of the line
            return_type = $1
            $1 = ""
            
            # Calculate the number of spaces to pad
            len = length(return_type)
            pad = max_len - len
            space_padding = sprintf("%-"pad"s", "")
            
            # Format the line to have return type aligned
            formatted = return_type space_padding $0
            # Print the formatted function prototype with a semicolon at the end
            print formatted ";"
        }' "$file"
        echo
    done
} >> "$output_file"

echo "#endif" >> "$output_file"

echo "Prototypes have been written to $output_file"
