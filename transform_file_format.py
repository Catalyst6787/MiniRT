# This script processes a file with specific rules,
# creating a new file with the modified content.

import os
import sys

def process_file(input_filepath):
    """
    Processes the content of a file based on specific rules and
    writes the output to a new file.

    The output file will be named "{filename}_bonus.rt"
    if the input file is "{filename}.rt".

    Args:
        input_filepath (str): The path to the input file.
    """
    # 1. Check if the input file exists
    if not os.path.exists(input_filepath):
        print(f"Error: The input file '{input_filepath}' was not found. Please check the path and try again.")
        return

    # 2. Determine the output file name based on the input file
    filename, file_extension = os.path.splitext(input_filepath)
    output_filepath = f"{filename}_bonus.rt"

    try:
        # 3. Read from the input file and write to the output file
        with open(input_filepath, 'r') as infile, open(output_filepath, 'w') as outfile:
            # Write the header line first
            outfile.write("# --SCENE.RT--\n")
            
            for line in infile:
                # Remove any leading spaces or tabs from the line
                clean_line = line.lstrip(' \t')

                # Handle different line types based on the first character(s)
                if clean_line.startswith(('A', 'C', 'L', '#')):
                    # Identical lines: just write them to the new file
                    outfile.write(clean_line)
                elif clean_line.startswith('sp'):
                    # 'sp' lines require a special transformation
                    parts = clean_line.split()
                    
                    # Extract the first group of 3 numbers (parts[1])
                    first_group = parts[1]
                    
                    # Extract and divide the next number by two (parts[2])
                    number_to_half = float(parts[2])
                    new_number = number_to_half / 2
                    
                    # Format the new number as a comma-separated string
                    new_number_string = f"{new_number},{new_number},{new_number}"

                    # Extract the last group of 3 numbers (parts[3])
                    last_group = parts[3]

                    # Construct the new line with all the required parts
                    new_line = (
                        f"sp {first_group} 0,0,1 {new_number_string} {last_group} "
                        f"0.9 0.9 200 1 0,0,0,0,0,0\n"
                    )
                    outfile.write(new_line)
                elif clean_line.startswith('cy'):
                    # 'cy' lines require a special transformation
                    parts = clean_line.split()
                    
                    first_part = parts[1]
                    second_part = parts[2]
                    
                    # Extract and divide the next number by two (parts[3])
                    number_to_half = float(parts[3])
                    new_number = number_to_half / 2
                    new_number_string = f"{new_number},{new_number},{new_number}"
                    
                    # The last part is at index 5
                    last_part = parts[5]

                    # Construct the new line with all the required parts
                    new_line = (
                        f"cy {first_part} {second_part} {new_number_string} {last_part} "
                        f"0.9 0.9 200 0.3 0,0,0,0,0,0\n"
                    )
                    outfile.write(new_line)
                elif clean_line.startswith('pl'):
                    # 'pl' lines require a special transformation
                    parts = clean_line.split()
                    
                    first_part = parts[1]
                    second_part = parts[2]
                    
                    # The color is the next part (parts[3])
                    color_part = parts[3]
                    
                    # Construct the new line with all the required parts
                    # Based on the example, a hardcoded '1,1,1' is inserted
                    # and then the color part is appended.
                    new_line = (
                        f"pl {first_part} {second_part} 1,1,1 {color_part} "
                        f"0.9 0.9 200 0.8 0,0,0,0,0,0\n"
                    )
                    outfile.write(new_line)
                elif clean_line.strip() == '':
                    # Preserve empty lines
                    outfile.write('\n')
                else:
                    # For all other lines, just write them as is
                    outfile.write(clean_line)
        
        print(f"File successfully processed. New file created at '{output_filepath}'.")

    except Exception as e:
        print(f"An error occurred: {e}")

# Example Usage:
if __name__ == "__main__":
    # Check if a file path argument was provided
    if len(sys.argv) < 2:
        print("Usage: python transform_scene.py <input_file_path>")
    else:
        # Get the input file path from the command-line arguments
        input_file_name = sys.argv[1]
        process_file(input_file_name)