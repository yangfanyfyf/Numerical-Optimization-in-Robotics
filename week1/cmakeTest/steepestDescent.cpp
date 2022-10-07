#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>
// #include <opencv2/core/core.hpp>
// #include <opencv2/opencv.hpp>
// #include <opencv2/highgui/highgui.hpp>
using namespace std;


void calculateGradient(vector<double>& gradient, vector<double>& val) {
    // 计算梯度
    // 输入：当前变量值
    // 输出：当前位置的梯度
    double x_1 = val[0], x_2 = val[1];
    gradient[0] = 400 * x_1 * (x_1 * x_1 - x_2) + 2 * x_1 - 2;
    gradient[1] = -200 * (x_1 * x_1 - x_2);
}


double calculateFunctionVal(vector<double>& val) {
    // 计算Rosenbrock函数值
    // 输入：当前变量值
    // 输出：变量值对应的函数值
    double ans = 0;
    double x_1 = val[0], x_2 = val[1];
    ans = 100 * pow(x_1 * x_1 - x_2, 2) + pow(x_1 - 1, 2);
    return ans;
}

double armijoCondition(vector<double>& curVal) {
    // 使用Armijo准则确定步长
    // 输入：当前变量值
    // 输出：满足Armijo准则的步长
    double step = 0.1;                     // 步长
    double constant = 0.5;                 // 常数c
    vector<double> direction{ 0, 0 };      // 当前搜索位置的梯度，负号放在了下面的计算中
    calculateGradient(direction, curVal);
    int iteration = 0;                     // 迭代此时累计值
    while (1) {
        double funcValOrigin = calculateFunctionVal(curVal);        // 当前位置的函数值
        vector<double> searchedVal = curVal;
        searchedVal[0] -= step * direction[0];
        searchedVal[1] -= step * direction[1];
        double funcValSearched = calculateFunctionVal(searchedVal); // 按照当前步长计算出的下一个位置的函数值
        ++iteration;
        // 满足Armijo准则时退出
        if (funcValSearched <= funcValOrigin - constant * step * (pow(direction[0], 2) + pow(direction[1], 2))) {
            // cout << "Armijo Iterations: " << iteration << endl;
            return step;
        }
        // 达到最大迭代次数时退出
        else if (iteration > 100000) {
            cout << "Maximum Iterations Reached!" << endl;
            return step;
        }
        else {
            step /= 2;
        }
    }
}

int main() {
    // 变量初始化
    int dimension = 0;
    long long totalIterations = 0;
    vector<double> initialVals;
    cout << "Please enter the dimensions N of Rosenbrock function: ";
    cin >> dimension;
    cout << endl;
    if (dimension % 2 == 1) {
        cout << "N must be an even number!" << endl;
        return 0;
    }
    else if (dimension <= 0) {
        cout << "N must be a positive number!" << endl;
        return 0;
    }
    cout << "Please enter the initial values: ";
    for (int i = 1; i <= dimension; ++i) {
        double tempVal = 0;
        cin >> tempVal;
        initialVals.emplace_back(tempVal);
    }
    // 开始计算
    vector<double> ans = initialVals;
    for (int i = 0; i < dimension / 2; ++i) {
        int iterations = 0;
        vector<double> tempVal{ 0, 0 };
        // 每次只计算两个变量的最优值
        tempVal[0] = initialVals[i * 2];
        tempVal[1] = initialVals[i * 2 + 1];
        vector<double> gradient{ 1, 1 };
        // 迭代，当梯度小于1e-6时，或者迭代次数大于1e6次时，迭代终止
        while (fabs(gradient[0]) > 1e-6 || fabs(gradient[1]) > 1e-6) {
            calculateGradient(gradient, tempVal);
            double step = armijoCondition(tempVal);
            tempVal[0] -= step * gradient[0];
            tempVal[1] -= step * gradient[1];
            ++iterations;
            if (iterations > 100000) {
                break;
            }
        }
        // 保存迭代结果
        totalIterations += iterations;
        ans[i * 2] = tempVal[0];
        ans[i * 2 + 1] = tempVal[1];
    }
    cout << endl;
    cout << "The total number of iterations: " << totalIterations << endl;
    cout << "The minimum values are :" << endl;
    cout << setiosflags(ios::fixed) << setprecision(10);
    for (int i = 0; i < dimension / 2; ++i) {
        cout << ans[i * 2] << ' ' << ans[i * 2 + 1] << ' ';
    }
    cout << endl;
}
