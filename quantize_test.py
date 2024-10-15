import re

# Read the original C code from a file
input_file = "random_forest_model.c"
output_file = "quantized_random_forest_model.c"

# Define the scaling factor (e.g., 1000 to preserve three decimal places)
scaling_factor = 1000

# Regular expression to match floating-point constants
float_regex = re.compile(r"(-?\d+\.\d+)")

# Regular expression to match data type declarations (double, float -> int)
data_type_regex = re.compile(r"\b(double|float)\b")

def quantize_floats(line):
    """Quantizes all floating-point numbers in a line of code."""
    def scale_match(match):
        # Scale the floating-point value by the scaling factor and convert to an integer
        float_value = float(match.group(0))  # e.g., -0.5000000149011612
        quantized_value = int(float_value * scaling_factor)
        return str(quantized_value)

    # Apply scaling to all floating-point numbers in the line
    return float_regex.sub(scale_match, line)

def convert_data_types(line):
    """Converts floating-point data types (double, float) to integer types (int)."""
    return data_type_regex.sub("int", line)

# Read, process, and save the modified C code
with open(input_file, "r") as infile, open(output_file, "w") as outfile:
    for line in infile:
        # Step 1: Convert floating-point data types to int
        line = convert_data_types(line)
        
        # Step 2: Quantize floating-point numbers in the line
        line = quantize_floats(line)
        
        # Write the modified line to the output file
        outfile.write(line)

print(f"Quantized model saved to {output_file}")
