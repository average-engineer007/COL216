#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

// Define a function to extract metrics from the output file
std::vector<double> extract_metrics(const std::string& output_file) {
    std::ifstream file(output_file);
    std::vector<double> metrics;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Parse the line and extract metrics
            std::istringstream iss(line);
            std::string token;
            if (line.find("NUMBER of loads") != std::string::npos) {
                // Extract number of loads
                iss >> token; // "NUMBER"
                iss >> token; // "of"
                iss >> token; // "loads"
                iss >> token; // "are:"
                iss >> token; // Number
                metrics.push_back(std::stod(token));
            } else if (line.find("NUMBER of stores") != std::string::npos) {
                // Extract number of stores
                iss >> token; // "NUMBER"
                iss >> token; // "of"
                iss >> token; // "stores"
                iss >> token; // "are:"
                iss >> token; // Number
                metrics.push_back(std::stod(token));
            } else if (line.find("NUMBER of load hits") != std::string::npos) {
                // Extract number of load hits
                iss >> token; // "NUMBER"
                iss >> token; // "of"
                iss >> token; // "load"
                iss >> token; // "hits"
                iss >> token; // "are:"
                iss >> token; // Number
                metrics.push_back(std::stod(token));
            } else if (line.find("NUMBER of load miss") != std::string::npos) {
                // Extract number of load misses
                iss >> token; // "NUMBER"
                iss >> token; // "of"
                iss >> token; // "load"
                iss >> token; // "miss"
                iss >> token; // "are:"
                iss >> token; // Number
                metrics.push_back(std::stod(token));
            } else if (line.find("NUMBER of store hits") != std::string::npos) {
                // Extract number of store hits
                iss >> token; // "NUMBER"
                iss >> token; // "of"
                iss >> token; // "store"
                iss >> token; // "hits"
                iss >> token; // "are:"
                iss >> token; // Number
                metrics.push_back(std::stod(token));
            } else if (line.find("NUMBER of store miss") != std::string::npos) {
                // Extract number of store misses
                iss >> token; // "NUMBER"
                iss >> token; // "of"
                iss >> token; // "store"
                iss >> token; // "miss"
                iss >> token; // "are:"
                iss >> token; // Number
                metrics.push_back(std::stod(token));
            } else if (line.find("NUMBER of cycles used") != std::string::npos) {
                // Extract number of cycles used
                iss >> token; // "NUMBER"
                iss >> token; // "of"
                iss >> token; // "cycles"
                iss >> token; // "used"
                iss >> token; // "are:"
                iss >> token; // Number
                metrics.push_back(std::stod(token));
            }
        }
        file.close();
    }

    return metrics;
}

// format of one metric is 
// [ loads(0) , stores(1) , load hits(2) , load miss(3) , store hits(4) , store miss(5) , cycles used(6) ]

double hit_rate(vector<double>& metric){
    double hit = 100 * (metric[2] + metric[4])/(metric[0]+metric[1]);
    return hit;
}

int main() {
    // Define the parameters to explore
    std::vector<int> cache_sizes = {1,2,4,8,32,64, 128, 256, 512,1024,2048,4096};  // Cache sizes in KB
    std::vector<int> associativities = {1, 2, 4, 8,16,32,64,128, 256, 512,1024,2048,4096};    // Associativity
    std::vector<int> block_sizes = {4,8,16, 32, 64, 128};    // Block sizes in bytes
    std::string trace_file = "traces/gcc.trace";              // Path to the trace file

    // Define different configurations for write policy, write strategy, and replacement policy
    std::vector<std::string> write_policies = {"write-allocate", "no-write-allocate"};
    std::vector<std::string> write_strategies = {"write-through", "write-back"};
    std::vector<std::string> replacement_policies = {"fifo", "lru"};

    // Open the analysis file
    std::ofstream analysis_file("analysis.txt");
    if (!analysis_file.is_open()) {
        std::cerr << "Failed to open analysis file!" << std::endl;
        return 1;
    }

    // Initialize variables to track the best configuration and its metrics
    std::vector<double> best_metrics = {std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()};
    std::vector<std::string> best_configuration(6); // {cache_size, associativity, block_size, write_policy, write_strategy, replacement_policy}  
    
    int cache_size=64;
    int associativity=1024;
    int block_size=4;
    // string write_policy="write-allocate";
    // string write_strategy="write-back";
    // string replacement_policy="lru";
    for (const std::string& write_policy : write_policies) {
        for (const std::string& write_strategy : write_strategies) {
            for (const std::string& replacement_policy : replacement_policies) {
        std::string command = "./cacheSim " + std::to_string(cache_size) + " " + std::to_string(associativity) + " " + std::to_string(block_size) + " " + write_policy + " " + write_strategy + " " + replacement_policy + " < " + trace_file;
        system(command.c_str());
        // Extract metrics from the output file
        std::vector<double> metrics = extract_metrics("output.txt");
        vector<double> stats;
        stats.push_back(metrics[6]); // cycles used
        stats.push_back(hit_rate(metrics)); // hit rate
        stats.push_back(cache_size * block_size * associativity); // total cache 
        // Write stats to the analysis file
        analysis_file << "Configuration: " << cache_size << " sets " << associativity << "-way " << block_size << "B " << write_policy << " " << write_strategy << " " << replacement_policy << std::endl;
        analysis_file << "Cycles Used: " << stats[0] << std::endl;
        analysis_file << "Hit Rate: " << stats[1] << "%" << std::endl;
        analysis_file << "Total Cache Size: " << stats[2] << " bytes" << std::endl;
        analysis_file << std::endl;
        // Update best configuration if the current one is better
        if (stats[0] < best_metrics[0]) { // Check hit rate
            best_metrics = stats;
            best_configuration = {std::to_string(cache_size), std::to_string(associativity), std::to_string(block_size), write_policy, write_strategy, replacement_policy};
        }
    }}}
    

    // Print the best configuration and its metrics
    std::cout << "Best Configuration:" << std::endl;
    std::cout << "Cache Size: " << best_configuration[0] << " KB" << std::endl;
    std::cout << "Associativity: " << best_configuration[1] << std::endl;
    std::cout << "Block Size: " << best_configuration[2] << " bytes" << std::endl;
    std::cout << "Write Policy: " << best_configuration[3] << std::endl;
    std::cout << "Write Strategy: " << best_configuration[4] << std::endl;
    std::cout << "Replacement Policy: " << best_configuration[5] << std::endl;
    std::cout << "Clock Cycles: " << best_metrics[0] << std::endl;
    std::cout << "Hit rate: " << best_metrics[1] << std::endl;
    std::cout << "Total Cache Size: " << best_metrics[2] << std::endl;

    // Close the analysis file
    analysis_file.close();

    std::cout << "Analysis completed. Results saved in 'analysis.txt'." << std::endl;

    return 0;
}
