# AEMU文档

## IO: `class Output`
所有模块的IO部分只保留`output`类型端口，采用`Output`模板类封装。输入信号通过指针直接访问对应的输出端口。
```C++
template <typename T>
class Output
{
private:
    /* 端口环形缓冲区 */
    const static uint32_t IO_BUFF_SIZE = 2;
    T data[IO_BUFF_SIZE];
protected:
    /***
     * @brief 获取当前下一个周期端口数据指针，一般用于Module::run()更新模块所有寄存器值。
    */
    T *getNextDataP();
    /***
     * @brief 设置下一个周期端口数据，一般用于Module::reset()复位模块所有寄存器值。
    */
    void setNextData(T data);
    /***
     * @brief 获取当前周期端口数据指针，用于Module::updata()更新组合逻辑输出端口。
    */
    T *getDataP();
public:
    /***
     * @brief 获取当前周期端口数据，用于其他模块外部访问端口数据。
    */
    const T getData();
};
```

## 基本模块: `Module`
分离寄存器更新与组合逻辑更新逻辑，在update()中更新所有组合逻辑，在run()中更新所有寄存器值。
```C++
class Module
{
public:
    /* 更新所有寄存器值，每周期调用一次。 */
    virtual void run(){};
    /* 复位所有寄存器值。 */
    virtual void reset(){};
    /* 更新模块的组合逻辑，在更新寄存器数据之前调用。 */
    virtual void update(){};
    /* 模块名称 */
    const char *name;
};
```
## 执行流程
```C++
    /* 创建所有模块 */
    createModules();
    /* 复位所有模块 */
    resetModeles();
    /* 仿真N周期 */
    runModeles(N);
```
