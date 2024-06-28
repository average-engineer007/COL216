import matplotlib.pyplot as plt

# Initialize dictionaries to store configuration, size, and time data
configurations = {}
sizes = {}
times = {}

# Read multiplication times from five files
for i in range(1, 11):
    filename = f"transpose_times.txt-{i}"
    with open(filename, "r") as file:
        lines = file.readlines()
        for line in lines:
            parts = line.strip().split(", ")
            config = parts[0].split(": ")[1]
            size = int(parts[1].split(": ")[0].split()[1])
            time = float(parts[1].split(": ")[1].split()[0])

            # Store data in dictionaries
            configurations.setdefault(config, []).append(time)
            sizes.setdefault(config, []).append(size)
            times.setdefault(config, []).append(time)

# Calculate averages for each configuration and matrix size
averages = {}
for config in configurations:
    averages[config] = {}
    for size in set(sizes[config]):
        avg_time = sum([times[config][i] for i in range(len(times[config])) if sizes[config][i] == size]) / sizes[config].count(size)
        averages[config][size] = avg_time

# Plotting
for config in averages:  # Loop through configurations
    plt.plot(list(averages[config].keys()), list(averages[config].values()), marker='o', label=f'Configuration: {config}')

plt.xlabel('Matrix Size')
plt.ylabel('Average Time (seconds)')
plt.title('Average Matrix Transpose Time vs. Matrix Size for Different Configurations')
plt.legend()
plt.grid(True)
plt.show()
