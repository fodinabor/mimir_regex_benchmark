import re

def match_lines(filename, output_file, regex_pattern):
    # Compile the regular expression pattern
    regex = re.compile(regex_pattern)

    # Open the file for reading
    with open(filename, 'r') as file:
        lines = file.readlines()

    # Open the file for writing
    with open(output_file, 'w') as file:
        for line in set(lines):
            # Check if the line matches the regex
            if regex.match(line):
                file.write(line.rstrip() + ",true\n")
            else:
                file.write(line.rstrip() + ",false\n")

# Usage example
filename = 'addresses.txt'  # Replace with the path to your file
output = 'annotated.txt'  # Replace with the path to your file
regex_pattern = r'^[a-zA-Z0-9](?:[a-zA-Z0-9]*[._\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*@[a-zA-Z0-9](?:[a-zA-Z0-9]*[_\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*\.(?:(?:[a-zA-Z0-9]*[_\-]+[a-zA-Z0-9])*[a-zA-Z0-9]+\.)*[a-zA-Z][a-zA-Z]+$'

match_lines(filename, output, regex_pattern)
