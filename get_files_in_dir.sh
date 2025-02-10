find "$1" -type f -name "*.c" | awk -v pwd="$(pwd)" '
{
    sub(pwd"/", "", $0); 
    line = line $0 " ";
    if (length(line) > 100)
	{
        printf "%s\\\n", line;  # Print line with "\n " at the end (no backslash at line start)
        line = "";
	}
}
END { if (line) printf "%s", line; 
}'
