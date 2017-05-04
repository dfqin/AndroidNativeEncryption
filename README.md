# AndroidNativeEncryption
A native encryp/decrypt solution
一个C/C++实现AES加密的例子，使用native实现AES加密解密、请求签名生成。
在native层做了包名和签名校验，防止非法调用此库。另外JNI采用动态注册的方式，可以任意指定java native method对应的C函数名。

注意：在自己项目中使用时，需要修改Utils.h中的包名和签名的定义。运行结果如下：

![默认](https://github.com/dfqin/AndroidNativeEncryption/blob/master/demo.jpg)