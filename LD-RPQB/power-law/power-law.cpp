#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

int main() {
    int totalPaths;
    std::cout << "Enter total number of paths: ";
    std::cin >> totalPaths;

    double alpha = 2.0; // 幂律分布的指数
    int minLength = 1, maxLength = 7; // 路径长度的最小和最大值

    // 计算每个长度的理论权重
    std::vector<double> weights;
    for (int i = minLength; i <= maxLength; ++i) {
        weights.push_back(std::pow(i, -alpha));
    }

    // 标准化权重，使得它们加起来为1
    double weightSum = std::accumulate(weights.begin(), weights.end(), 0.0);
    for (double& weight : weights) {
        weight /= weightSum;
    }

    // 根据权重分配路径数量
    std::vector<int> pathCounts(maxLength, 0);
    for (int i = 0; i < weights.size(); ++i) {
        pathCounts[i] = static_cast<int>(round(weights[i] * totalPaths));
    }

    // 输出结果
    std::cout << "Path Length Distribution:" << std::endl;
    for(int i = 0; i < pathCounts.size(); ++i) {
        if (pathCounts[i] > 0) { // 仅显示数量大于0的路径长度
            std::cout << "Length " << i + 1 << ": " << pathCounts[i] << " path(s)" << std::endl;
        }
    }

    return 0;
}
