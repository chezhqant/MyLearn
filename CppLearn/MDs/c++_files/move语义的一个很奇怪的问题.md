1.  代码：      
    ```
    #include <iostream>

    using namespace std;

    class A
    {
    public:

      A(int a): m_a(a) {}

      A(A& a)
      {
        m_a = a.m_a;
      }

      A(A&& a)
      {
        m_a = a.ma;
      }
    
    private:

      int m_a;
    };

    int main()
    {
      A a(1);

      // 调用移动构造函数 (1)
      A b(std::move(a));

      // 调用拷贝构造函数！(2)
      A&& c = std::move(a);
      A d(c);
    }
    ```
    运行这段代码，查看汇编代码，会发现(1)处move之后的结果（也可能时地址）存放在寄存器中，而(2)处move后的结果存在 `c` 中，是存在栈中。       
    之前看到看到右值存在于寄存器。。。      
