# Module抽象文档
## 对时序逻辑的抽象
所有模块只保留输出寄存器（Output reg），输入信号的读取通过指针直接访问其他模块的`public`成员。
组合逻辑输出信号抽象为`public function`类型，时序逻辑抽象为`public variable`类型。

### 基本模块抽象

```C++
class Module
{
public:
    /* 更新所有寄存器值，每周期调用一次 */
    virtual void run() = 0;
    /* 复位所有寄存器值 */
    virtual void reset() = 0;
    /* 模块名称 */
    const char *name;
};
```
### 端口抽象
对于输出的寄存器，采用`Output`模板类封装。
```C++
template <typename T>
class Output
{
private:
    const static uint32_t IO_BUFF_SIZE = 2;
    T data[IO_BUFF_SIZE];

/* protected 下函数提供对IO端口写支持，写入数据在下个周期生效。 */
protected:
    T *getNextDataP();
    void setNextData(T data);

/* public 下函数提供IO端口读支持，数据为当前周期值。 */
public:
    T getData();
};
```
