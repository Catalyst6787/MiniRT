# This script processes multiple .rt files from a source directory,
# applies specific transformations, and saves the modified files
# to a destination directory.

import os
import sys

def process_single_file(input_filepath, output_filepath):
    """
    Processes the content of a single file based on specific rules and
    writes the output to a new file.

    Args:
        input_filepath (str): The path to the input file.
        output_filepath (str): The path for the new output file.
    """
    try:
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

                    # Check if the line has enough parts before trying to access them
                    if len(parts) >= 4:
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

                    if len(parts) >= 6:
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

                    if len(parts) >= 4:
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

        print(f"File successfully processed: '{os.path.basename(input_filepath)}'")

    except Exception as e:
        print(f"An error occurred while processing '{os.path.basename(input_filepath)}': {e}")


def main():
    """
    Main function to handle command-line arguments and process files.
    """
    # Check if the correct number of arguments was provided
    if len(sys.argv) != 3:
        print("Usage: python transform_scene.py <source_directory> <destination_directory>")
        sys.exit(1)

    source_dir = sys.argv[1]
    dest_dir = sys.argv[2]

    # Check if the source directory exists
    if not os.path.isdir(source_dir):
        print(f"Error: Source directory '{source_dir}' not found.")
        sys.exit(1)

    # Create the destination directory if it doesn't exist
    os.makedirs(dest_dir, exist_ok=True)

    # Loop through all files in the source directory
    for filename in os.listdir(source_dir):
        # Check if the file has the .rt extension
        if filename.endswith(".rt"):
            input_filepath = os.path.join(source_dir, filename)

            # Construct the output filename
            file_base, file_ext = os.path.splitext(filename)
            output_filename = f"{file_base}_bonus{file_ext}"
            output_filepath = os.path.join(dest_dir, output_filename)

            # Process the file
            process_single_file(input_filepath, output_filepath)

# Entry point of the script
if __name__ == "__main__":
    main()