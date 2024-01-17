import json
import sys

# Check if a valid integer argument is provided
if len(sys.argv) != 2 or not sys.argv[1].isdigit():
    print("Usage: python script.py <batch_number>")
    sys.exit(1)

batch_number = int(sys.argv[1])

# Define batch names
batch_names = ['INC', 'DLIS', 'DLCS', 'JW']

# Check if the provided batch number is valid
if 0 <= batch_number < len(batch_names):
    batch_name = batch_names[batch_number]
else:
    print(f"Invalid batch number. Choose a number between 0 and {len(batch_names) - 1}.")
    sys.exit(1)

# Read rtime data from the text file
with open(f'results/{batch_name}.txt', 'r') as file:
    rtime_lines = file.readlines()

# Generate JSON structure
json_data = {"stats": {}}
for rtime_line in rtime_lines:
    # Split each line into instance number and time
    parts = rtime_line.split(':')
    if len(parts) == 2:
        instance_key = f"instance{parts[0].strip()}"
        rtime_value = float(parts[1].strip())

        if rtime_value == 600:
            # Handle instances with rtime value 600
            json_data["stats"][instance_key] = {
                "status": False,
                "rtime": rtime_value
            }
        else:
            # Handle other instances with regular rtime values
            json_data["stats"][instance_key] = {
                "status": True,
                "rtime": rtime_value
            }

# Add preamble data
json_data["preamble"] = {
    "benchmark": "my-benchmark-set",
    "prog_args": "-a hello --arg2 world -v",
    "program": "dpll_solver",
    "prog_alias": "dpll"
}

# Convert Python dictionary to JSON string
json_output = json.dumps(json_data, indent=4)

# Print or save the JSON string
print(json_output)

# Save the JSON string to a file (optional)
with open(f'cactus/{batch_name}.json', 'w') as json_file:
    json_file.write(json_output)

print(f"Saved {batch_name} batch to cactus/{batch_name}.json")
