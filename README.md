## **大规模矩阵乘法优化试题说明**

### **1. 赛题任务**

本次特殊招新试题的任务为优化大规模矩阵乘法算法。我们将提供一个基于 C 语言的基准代码，该代码使用了最基础的三重循环算法。你的任务是在此基础上进行优化，提高代码运行的时间效率。

**你的目标是：**

1.  **实现优化：** 在 `src/task.c` 文件中实现你的优化算法，使其在保持正确性的前提下，提升代码运行效率。
2.  **验证正确性：** 确保你的优化版本在计算结果上与基准代码完全一致。
3.  **提交报告：** 提交一份简要的优化报告，说明你的优化思路、使用的技术以及性能分析。
### **2. 运行环境**

该项目依赖环境及推荐版本如下：
1. Intel CPU
2. Ubuntu 22.04 LTS (WSL2)
3. GCC 11.4.0
4. CMake 3.22.1

> 如果 CPU 为 AMD 版本，可以在进行专一性优化时联系张wh或况y学长进行优化测试

为了确保公平性，最终提交作品将在统一的环境（如上）下进行测试。请确保你的代码可以在该环境下正确编译和运行。
### **3. 项目结构**

赛题提供了如下项目结构：

```
matrix_multiplication_c/
├── src/
│   ├── main.c          // 主程序，包含基准测试和性能计时，无需修改
│   └── task.c          // == 你的任务文件，请在此处编写优化代码 ==
├── include/
│   └── task.h          // task.c 的头文件
├── CMakeLists.txt      // 构建脚本，无需修改
└── README.md           // 本说明文档
```

### **4. 运行步骤**

请按照以下步骤编译和运行你的程序：

1.  **打开 WSL2 终端**，进入项目根目录 `matrix_multiplication_c/`。

2.  **编译项目：**

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

    这个过程会生成一个名为 `run_matrix_multiplication` 的可执行文件。

3.  **运行程序：**

      * **正确性验证：** 

        ```bash
        ./run_matrix_multiplication test
        ```
	    >此命令会启动较小规模的矩阵进行正确性验证
        如果你的优化代码正确，输出将显示 "Correctness test passed\!"。

      * **性能基准测试：** 

        ```bash
        ./run_matrix_multiplication
        ```
		>此命令将执行优化代码并与基准代码进行性能对比。
        程序将自动测试不同大小的矩阵，并输出各自运行时间以及加速比。

### 5. 评分规则
本次试题的最终评分将采用**加权评分**，其中：

  * **性能排名：** 占总分的 **80%**。你的程序在不同测试用例下的综合加速比将作为主要评判依据。
  * **优化报告：** 占总分的 **20%**。报告内容包括但不限于：
	
	Excel文件：    
	- 记录不同优化方法的加速比变化。
	
	文本文件：
	- 简述你使用的优化方法（例如，循环分块、OpenMP 并行化、内存访问优化等）。
	- 分析你的优化方法为何能提升性能。
#### 性能得分规则
+ 每道样例运行后将会生成对应的加速比
+ 各样例加速比加权计算得到最终的综合加速比
+ 排名根据综合加速比确定，分数按照排名分配

**各样例加速比权重**
样例1 : 样例2 : 样例3 : 样例4  ==  2 : 2 : 2 : 4
> 样例分布：case1、2：普通矩阵乘，case3：稀疏矩阵乘，case4：大规模矩阵乘

**分数排名**
+ 第一名：100
+ 第二名：90
+ 第三名：80
+ ....每往后一次名次，分数递减10名，直到第十名
>所得分数\*80%即为性能分数


### 6. 提交要求

请将你修改后的整个项目文件夹（包括**优化代码** 、**优化报告**、以及**最终加速比截图**）打包提交到。



请记住，一份清晰、有逻辑的优化报告能让你在比赛中脱颖而出。

### 附：示例交互流程
``` bash
ziyang@LAPTOP-SPPQSEGM:/mnt/d/Users/ASUS/Desktop/SRQ-25$ git clone https://github.com/ziyang22/SRQ-25.git
# some information ~
ziyang@LAPTOP-SPPQSEGM:/mnt/d/Users/ASUS/Desktop/SRQ-25$ cd build 
ziyang@LAPTOP-SPPQSEGM:/mnt/d/Users/ASUS/Desktop/SRQ-25/build$ cmake ..
-- OpenMP found, enabling C support.
-- Configuring done (0.1s)
-- Generating done (0.2s)
-- Build files have been written to: /mnt/d/Users/ASUS/Desktop/SRQ-25/build
ziyang@LAPTOP-SPPQSEGM:/mnt/d/Users/ASUS/Desktop/SRQ-25/build$ ./run_matrix_multiplication test
-bash: ./run_matrix_multiplication: No such file or directory
ziyang@LAPTOP-SPPQSEGM:/mnt/d/Users/ASUS/Desktop/SRQ-25/build$ make
[ 33%] Building C object CMakeFiles/run_matrix_multiplication.dir/src/main.c.o
[ 66%] Building C object CMakeFiles/run_matrix_multiplication.dir/src/task.c.o
[100%] Linking C executable run_matrix_multiplication
[100%] Built target run_matrix_multiplication
ziyang@LAPTOP-SPPQSEGM:/mnt/d/Users/ASUS/Desktop/SRQ-25/build$ ./run_matrix_multiplication test
--- Running performance benchmark ---
Testing matrix size: 1024x1024
Naive multiplication took: 7.574566 seconds.
Optimized multiplication took: 7.478565 seconds.
...
```

### 附：参考资料与配置教程

#### 1. 矩阵乘简介

https://www.bilibili.com/video/BV1Nq421w7vH?t=0.7
#### **2. WSL的安装与vscode远程连接WSL**

1. 前提：vscode需要下载Remote - SSH插件，下载完后vscode左侧会出现"远程资源管理器"的图标。

2. wsl安装和vscode远程连接的相关参考链接：https://blog.csdn.net/weixin_47603083/article/details/133999982?sharetype=blog&shareId=133999982&sharerefer=APP&sharesource=2501_93355781&sharefrom=link

   注意：注意安装的wsl的版本是wsl2，Ubuntu版本是22.04 LTS

3. 远程连接后可在"资源管理器"里打开文件夹，进行文件管理。

4. 打开终端，安装gcc和cmake：

   gcc：

   ```
   sudo apt update
   sudo apt install gcc-11 -y
   sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100（需要输密码）
   ```

   cmake:

   ```
   sudo apt update
   sudo apt install cmake -y
   ```

   **可以通过gcc --version和cmake --version进行验证是否安装成功**
