import pickle 
import m2cgen as m2c
import re
import numpy as np
import csv

o = "./CatBoost.c"
qo = "./quantized_CatBoost.c"
f = '../CatBoost_cls_0.pkl'
sf = '../Scaler_per_cls_0.pkl'
out_data = '../data.csv'
data_f = "../features.npy"
out_scaler = '../scaler_vals.csv'

scaling_factor = 1000
data_type_regex = re.compile(r"\b(double|float)\b")
float_regex = re.compile(r"(-?\d+\.\d+)")

def read_in_model(model_filename):
    return pickle.load(open(model_filename,'rb'))

def read_in_scaler(scaler_filename):
    return pickle.load(open(scaler_filename,'rb'))

def read_in_data(data_filename, csv_filename):
    data = np.load(data_filename)
    with open(csv_filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(data)

def unpack_scaler(scaler, out_filename):
    center = scaler.center_
    scale = scaler.scale_
    np.savetxt(out_filename, np.vstack([center, scale]).T, delimiter=',', header='center,scale', comments='')

def make_random_forest_c(model, outfilename):
    with open(outfilename, "w") as f:
        f.write(m2c.export_to_c(model, function_name='apply_CatBoost'))

def quantize_floats(line):
    """Quantizes all floating-point numbers in a line of code."""
    def scale_match(match):
        float_value = float(match.group(0))  # e.g., -0.5000000149011612
        quantized_value = int(float_value * scaling_factor)
        return str(quantized_value)

    return float_regex.sub(scale_match, line)

def convert_data_types(line):
    """Converts floating-point data types (double, float) to integer types (int)."""
    return data_type_regex.sub("int", line)

def go_quantize(input_file, output_file):
    with open(input_file, "r") as infile, open(output_file, "w") as outfile:
        for line in infile:
            line = line.replace("apply_CatBoost", "apply_CatBoost_quantize")
            line = convert_data_types(line)
            line = quantize_floats(line)
            outfile.write(line)
    return

if __name__=='__main__':
    print("Reading Model")
    model = read_in_model(f)
    # print("Reading Scaler")
    # scaler = read_in_scaler(sf)
    # print("Dumping Scaler")
    # unpack_scaler(scaler, out_scaler)
    # print("Dumping Data")
    # read_in_data(data_f, out_data)
    print("Converting RF to C")
    make_random_forest_c(model,o)
    print("Quantizing Model")
    go_quantize(o,qo)
