# 使用steepest descent和Armijo准则计算Rosenbrock函数的最优值

## 使用方法

代码使用Visual Studio 2022编译，VS可以直接打开 ```./steepestDescent/steepestDescent.sln```并运行，main函数位于```./steepestDescent/steepestDescent/steepestDescent.cpp```中。

运行程序后，需要先命令行窗口中输入Rosenbrock函数的阶数N，再输入对应的N个变量的初始值，然后程序每次迭代求解两个变量的最优值（也就是需要分为N/2次求解），并依次输出N个变量的最优值。

## 主要函数
1. void calculateGradient(vector<double>& gradient, vector<double>& val) 
   
   计算给定的变量值***val***处对应的梯度，并在***gradient***中返回。

2. double calculateFunctionVal(vector<double>& val)

   计算变量***val***对应的函数值。

3. double armijoCondition(vector<double>& curVal)

   使用Armijo准则计算变量***val***对应的步长。

   