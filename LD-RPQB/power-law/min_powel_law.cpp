#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

int main() {
    double alpha = 2.0; // 幂律分布的指数
    std::vector<int> minPathCounts = {7, 8, 6, 7, 7, 5, 3, 1, 1, 1, 1}; // 每个长度的最小数量
    std::vector<double> weights;
    double weightSum = 0.0;

    // 计算每个长度的权重和总权重
    for (int i = 1; i <= minPathCounts.size(); ++i) {
        double weight = std::pow(i, -alpha);
        weights.push_back(weight);
        weightSum += weight;
    }

    // 计算需要满足最小数量要求的总路径数
    double totalPaths = 0.0;
    for (int i = 0; i < minPathCounts.size(); ++i) {
        double requiredPaths = minPathCounts[i] * weightSum / weights[i];
        totalPaths = std::max(totalPaths, requiredPaths);
    }

    // 根据总路径数计算每个长度的路径数量
    std::vector<int> pathCounts(minPathCounts.size(), 0);
    for (int i = 0; i < weights.size(); ++i) {
        pathCounts[i] = std::max(minPathCounts[i], static_cast<int>(std::round((weights[i] / weightSum) * totalPaths)));
    }

    // 输出结果
    std::cout << "Total Paths Needed: " << static_cast<int>(std::round(totalPaths)) << std::endl;
    std::cout << "Path Length Distribution:" << std::endl;
    for(int i = 0; i < pathCounts.size(); ++i) {
        std::cout << "Length " << i + 1 << ": " << pathCounts[i] << " path(s)" << std::endl;
    }

    return 0;
}
