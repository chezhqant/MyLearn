___unstandard template type deduction.___     

below, all depend on this:    
  ```
  template <typename T>
  void func(Param param);

  func(expr); // deduction T and Param from expr
  ```

  1.  Param is reference, but no universal reference.   
      if expr is reference, ignore that.    
        remain expr match to Param(exclude `&`).        
        Param -> T.     
      else      
        expr match to Param(exclude `&`).     
        Param -> T.       

  2.  Param is universal reference.     
      if expr is left value.    
        Param and T are left reference, and i guess Param may be (cv quality) left reference.     
      else.     
        Do deduce according to case 1.      

  3.  Param is neither reference or pointer.    
      that mearns that param will be a copy of whatever is pass in--a completely new object. The fact that param will be a new object motivates the rules that govern how T is deduced from expr.    
      1.  if expr is reference, ignort that.    
      2.  after 1., if expr is const or volatile, ignore that.    
      3.  remain expr -> Param -> T.    
      4.  exception. if parameters that are ferences to or pointers to const, the constness of expr ispreserved during type deduction.    
          ```
          template <typename T>
          void func(T param);

          const char* const ptr = "Fun with Pointer";
          f(ptr); // the right const asterrisk will be ignore, so the type is const char*
          ```
    4.  others      
        1.  array arguments     
            a primary constributeor to this illusion is that, in many contexts, an array decays into a pointer to its first element. This decay is what permits code like this to compile:    
            ```
            const char name[] = "da lao"; name's type is const char[6]
            const char* ptr_to_name = name; // array decays to pointer

            template <typename T>
            void func(int param[]); 

            // will become this
            void func(int* param);


            // if Param is reference:
            template <typename T>
            void func(T& param);

            func(name); // T is const char[6], Param is const char (&) [6]

            ```
        2.  function arguments.     
            function types can decay into function pointers, and everything we have discussed regardding type deduction for arrays applies to type deduction for functions and their decay into function pointers.    
            ```
            void some_func(int, double);

            template <typename T>
            void f1(T param);

            template <typename T>
            void f2(T& param);

            f1(some_func); // void (*) (int, double);
            f2(some_func); // void (&) (int, double);
            ```
