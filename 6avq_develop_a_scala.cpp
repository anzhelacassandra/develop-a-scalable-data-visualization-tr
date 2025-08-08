// 6avq_develop_a_scala.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// Data structure to store data points
struct DataRow {
    std::string date;
    double value;
    std::stringcategory;
};

// Data visualization tracker class
class DataVisualizationTracker {
private:
    std::vector<DataRow> data_;
    std::map<std::string, std::vector<double>> category_values_;

public:
    // Add data point to tracker
    void addDataPoint(const DataRow& data) {
        data_.push_back(data);
        category_values_[data.category].push_back(data.value);
    }

    // Calculate mean for each category
    std::map<std::string, double> calculateMeans() {
        std::map<std::string, double> means;
        for (auto& category : category_values_) {
            double sum = 0;
            for (auto& value : category.second) {
                sum += value;
            }
            means[category.first] = sum / category.second.size();
        }
        return means;
    }

    // Calculate standard deviation for each category
    std::map<std::string, double> calculateStds() {
        std::map<std::string, double> stds;
        for (auto& category : category_values_) {
            double sum = 0;
            for (auto& value : category.second) {
                sum += pow(value - calculateMeans()[category.first], 2);
            }
            stds[category.first] = sqrt(sum / category.second.size());
        }
        return stds;
    }

    // Generate visualization output
    void visualize() {
        std::ofstream file("output.txt");
        file << "Category\tMean\tStd Dev\n";
        for (auto& category : calculateMeans()) {
            file << category.first << "\t" << category.second << "\t" << calculateStds()[category.first] << "\n";
        }
        file.close();
    }
};

int main() {
    DataVisualizationTracker tracker;

    // Sample data
    DataRow data1 = {"2022-01-01", 10.0, "A"};
    DataRow data2 = {"2022-01-02", 20.0, "A"};
    DataRow data3 = {"2022-01-03", 30.0, "B"};
    DataRow data4 = {"2022-01-04", 40.0, "B"};
    DataRow data5 = {"2022-01-05", 50.0, "C"};

    tracker.addDataPoint(data1);
    tracker.addDataPoint(data2);
    tracker.addDataPoint(data3);
    tracker.addDataPoint(data4);
    tracker.addDataPoint(data5);

    tracker.visualize();

    return 0;
}