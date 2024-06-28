import matplotlib.pyplot as plt

def read_analysis_file(filename):
    configurations = []
    cycles_used = []
    hit_rates = []
    
    with open(filename, 'r') as file:
        lines = file.readlines()
        for i in range(0, len(lines), 5):
            config_line = lines[i].strip().split(': ')[1]
            cache_size = config_line.split()[3]
            cycles_line = lines[i+1].strip().split(': ')[1]
            hit_rate_line = lines[i+2].strip().split(': ')[1]

            configurations.append(config_line)
            cycles_used.append(float(cycles_line))
            hit_rates.append(float(hit_rate_line.strip('%')) / 100)

    return configurations, cycles_used, hit_rates

def plot_cycles_used(configurations, cycles_used):
    plt.figure(figsize=(10, 6))
    plt.plot(configurations, cycles_used, marker='o', linestyle='-')
    plt.xlabel('Configuration')
    plt.ylabel('Cycles Used')
    plt.title('Configuration vs Cycles Used')
    plt.xticks(rotation=45, ha='right')
    plt.grid(True)
    plt.tight_layout()
    plt.show()

def plot_hit_rates(configurations, hit_rates):
    plt.figure(figsize=(10, 6))
    plt.plot(configurations, hit_rates, marker='o', linestyle='-')
    plt.xlabel('Configuration')
    plt.ylabel('Hit Rate')
    plt.title('Configuration vs Hit Rate')
    plt.xticks(rotation=45, ha='right')
    plt.grid(True)
    plt.tight_layout()
    plt.show()

def main():
    filename = 'analysis.txt'
    configurations, cycles_used, hit_rates = read_analysis_file(filename)
    
    print("Choose what to plot:")
    print("1. Cycles Used")
    print("2. Hit Rate")
    choice = input("Enter your choice (1/2): ")

    if choice == '1':
        plot_cycles_used(configurations, cycles_used)
    elif choice == '2':
        plot_hit_rates(configurations, hit_rates)
    else:
        print("Invalid choice. Please enter 1 or 2.")

if __name__ == "__main__":
    main()

