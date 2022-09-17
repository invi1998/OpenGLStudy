目录

- [一.嵌入式设备的 OpenGL ES 版本](https://zhuanlan.zhihu.com/p/560012304#一嵌入式设备的_OpenGL_ES_版本)
- [二.兼容性](https://zhuanlan.zhihu.com/p/560012304#二兼容性)
- 三.着色器脚本
  - [1.OpenGL ES shader 2.0](https://zhuanlan.zhihu.com/p/560012304#1OpenGL_ES_shader_20)
  - [2.OpenGL ES shader 3.0](https://zhuanlan.zhihu.com/p/560012304#2OpenGL_ES_shader_30)
  - [3.版本声明](https://zhuanlan.zhihu.com/p/560012304#3版本声明)
  - [4. 默认精度修饰符 precision](https://zhuanlan.zhihu.com/p/560012304#4_默认精度修饰符_precision)
  - [4.输入输出](https://zhuanlan.zhihu.com/p/560012304#4输入输出)
  - [5.变量赋值](https://zhuanlan.zhihu.com/p/560012304#5变量赋值)
- [四.关于顶点缓冲区对象 VBO 与顶点数组对象 VAO](https://zhuanlan.zhihu.com/p/560012304#四关于顶点缓冲区对象_VBO_与顶点数组对象_VAO)
- [五.PBO](https://zhuanlan.zhihu.com/p/560012304#五PBO)
- [六.猜你喜欢](https://zhuanlan.zhihu.com/p/560012304#六猜你喜欢)

> 零基础 OpenGL ES 学习路线推荐 : [OpenGL ES 学习目录](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es) >> [OpenGL ES 基础](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es-%e5%9f%ba%e7%a1%80)
>
> 零基础 OpenGL ES 学习路线推荐 : [OpenGL ES 学习目录](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es) >> [OpenGL ES 特效](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es-%e7%89%b9%e6%95%88)
>
> 零基础 OpenGL ES 学习路线推荐 : [OpenGL ES 学习目录](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es) >> [OpenGL ES 转场](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es-%e8%bd%ac%e5%9c%ba)
>
> 零基础 OpenGL ES 学习路线推荐 : [OpenGL ES 学习目录](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es) >> [OpenGL ES 函数](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es-%e5%87%bd%e6%95%b0)
>
> 零基础 OpenGL ES 学习路线推荐 : [OpenGL ES 学习目录](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es) >> [OpenGL ES GPUImage 使用](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-gpuimage)
>
> 零基础 OpenGL ES 学习路线推荐 : [OpenGL ES 学习目录](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es) >> [OpenGL ES GLSL 编程](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-glsl)

## 一.**嵌入式设备的 OpenGL ES** 版本

> OpenGL ES 1.x 支持 初代 iPhone 和 Android；
>
> [OpenGL ES 2.0](https://link.zhihu.com/?target=https%3A//www.codersrc.com/archives/14948.html) 支持 Android 2.2 以后的平台，支持 iPad , iPhone3GS 和后续版本，以及 iPodTouch3 代和后续版本。
>
> OpenGL ES 3.0 支持 Android 4.3 以后的平台。支持 iPhone 5s ,iPad Air ,iPad mini 2 及后续版本。

## 二.兼容性

**[OpenGL ES 3.0](https://link.zhihu.com/?target=https%3A//www.codersrc.com/archives/17356.html)** 是向下兼容 **OpenGL ES 2.0** 的。也就是说使用 2.0 编写的应用程序是可以在 3.0 中继续使用的。



![img](https://pic4.zhimg.com/80/v2-a1bdc50bc2d0b9268716f300f11e3a53_720w.jpg)



## 三.着色器脚本

### 1.**OpenGL ES** shader 2.0

```c++
//顶点着色器
attribute vec4 aPosition;                            // 应用程序传入顶点着色器的顶点位置
attribute vec2 aTextureCoord;                        // 应用程序传入顶点着色器的顶点纹理坐标

varying vec2 vTextureCoord;                          // 用于传递给片元着色器的顶点纹理数据
void main()
{
    gl_Position = aPosition;                         // 此次绘制此顶点位置
    vTextureCoord = aTextureCoord;                   // 将接收的纹理坐标传递给片元着色器
}



//片元着色器
precision mediump float;                           // 设置工作精度

varying vec2 vTextureCoord;                        // 接收从顶点着色器过来的纹理坐标
uniform sampler2D sTexture;                        // 纹理采样器，代表一幅纹理
void main()
{
    gl_FragColor = texture2D(sTexture, vTextureCoord);// 进行纹理采样
}
```

### 2.**OpenGL ES** shader 3.0

```c++
//顶点着色器
#version es 300

uniform mat4 u_matViewProj;
layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_color;
out vec3 v_color;

void main() {
    gl_Position = u_matViewProj * a_position;
    v_color = a_color;
}


//片元着色器
#version es 300
precision mediump float;

in vec3 v_color; // input form vertex shader
layout(location = 0) out vec4 o_fragColor;

void main() {
    o_fragColor = vec4(v_color, 1.0);
}
```

### 3.版本声明

在 OpenGL ES 3.0 中，顶点着色器和片段着色器的第一行必须声明着色器版本，否则编译报错：

```c++
ERROR: 0:1: '' : syntax error: #version directive must occur in a shader before anything
```

在 [OpenGL ES 3.0](https://link.zhihu.com/?target=https%3A//www.codersrc.com/archives/17356.html) 中，可以必须声明着色器版本：

```c++
#version es 300
```

在 [OpenGL ES 2.0](https://link.zhihu.com/?target=https%3A//www.codersrc.com/archives/17356.html) 中，可以不用声明着色器版本，默认为：

```c++
#version es 100
```

**备注：** 以往 2.0 刚刚出来可编程的图形管线，所以版本声明为 #version 100 es ，后来为了使版本号相匹配，OpenGL ES 3.0 的 shader 版本直接从 1.0 跳到了 3.0 。

```c++
#version 300 es 指定使用OpenGL3.0
#version 100 es 指定使用OpenGL2.0 (不指定version 默认为OpenGL2.0)
```

### 4. 默认精度修饰符 precision

在顶点语言中有如下预定义的全局默认精度语句：

```c++
precision highp float;
precision highp int;
precision lowp sampler2D;
precision lowp samplerCube;
```

在片元语言中有如下预定义的全局默认精度语句：

```c++
precision mediump int;
precision lowp sampler2D;
precision lowp samplerCube;
```

**片元语言没有默认的浮点数精度修饰符。**因此，对于浮点数，浮点数向量和矩阵变量声明，要么声明必须包含一个精度修饰符，要不默认的精度修饰符在之前已经被声明过了

```c++
precision highp float;
```

### 4.输入输出

OpenGL ES 3.0 中新增了** in，out，inout **关键字，用来取代 \**attribute 和 varying **关键字。

同时 **gl_FragColor** 和 **gl_FragData** 也删除了，片段着色器可以使用 [out](https://link.zhihu.com/?target=https%3A//www.codersrc.com/archives/17356.html) 声明字段输出。

### 5.变量赋值

[OpenGL ES 3.0](https://link.zhihu.com/?target=https%3A//www.codersrc.com/archives/17356.html) 中可以直接使用 layout 对指定位置的变量赋值。例如：

```c++
shader脚本中
layout (location = 1) uniform float a;
```

代码中，直接写上对应的 layout 的值就可以赋值

```c++
GLES30.glUniform1f(1, 1f);
```

而 OpenGL ES 2.0 中必须使用如下形式赋值：

```c++
GLES20.glUniform1f(GLES20.glGetAttribLocation(program, "a"), 1f)
```

## 四.关于顶点缓冲区对象 VBO 与顶点数组对象 VAO

**VAO (顶点数组对象：Vertex Array Object)是指顶点数组对象，主要用于管理 VBO 或 EBO ，减少 glBindBuffer 、glEnableVertexAttribArray、 glVertexAttribPointer 这些调用操作，高效地实现在顶点数组配置之间切换。**

**VBO（顶点缓冲区对象: Vertex Buffer Object）是指把顶点数据保存在显存中，绘制时直接从显存中取数据，减少了数据传输的开销，**因为顶点数据多了，就是坐标的数据多了很多的很多组，切换的时候很麻烦，就出现了这个 VAO，绑定对应的顶点数据

**OpenGL 2.0 有 VBO，没有 VAO，[VAO](https://link.zhihu.com/?target=https%3A//www.codersrc.com/archives/17356.html) 是 OpenGL 3.0 才开始支持的**，并且在 OpenGL 3.0 中，强制要求绑定一个 VAO 才能开始绘制。

例如：在 OpenGL 3.0 中，不使用 VAO ，调用完 glVertexAttribPointer， glGetError 报错 [GL_INVALID_OPERATION](https://link.zhihu.com/?target=https%3A//www.codersrc.com/archives/17356.html)。

```c++
int pos_location = glGetAttribLocation(ProgramId, "position");
glVertexAttribPointer(pos_location, 2, GL_FLOAT, GL_FALSE, 0, kVertices);
```

查看 [OpenGL](https://link.zhihu.com/?target=https%3A//www.codersrc.com/opengl-es-%e5%9f%ba%e7%a1%80) 官方文档 [http://docs.gl/gl3/glVertexAttribPointer](https://link.zhihu.com/?target=http%3A//docs.gl/gl3/glVertexAttribPointer)

> GL_INVALID_OPERATION is generated in the core context if there is no Vertex Array Object bound

在 OpenGL 3.0 中，强制要求绑定一个 VAO 才能开始绘制。因此，需要在程序初始化的时候，创建并绑定一个 VAO

```c++
GLuint vao;
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);
```

此外，OpenGL 3.0 中也不允许在 glVertexAttribPointer 直接传数组了，因此要把顶点先传入 vbo 中

```c++
GLuint vbo;
glGenBuffers(1, &vbo);

glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices), kVertices, GL_STATIC_DRAW);
```

绑定 VBO 之后，glVertexAttribPointer 后面的 pointer 参数就要填 0 了。

```c++
glVertexAttribPointer(pos_location, 2, GL_FLOAT, GL_FALSE, 0, 0);
```

## 五.PBO

**OpenGL 2.0 不支持 PBO ，3.0 支持 PBO , PBO 设计的目的就是快速地向显卡传输数据，或者从显卡读取数据，我们可以使用它更加高效的读取屏幕数据。**

**单个 PBO 读取屏幕数据效率大概和 glReadPixels 差不多，双 PBO 交换读取效率会很高。**



![img](https://pic2.zhimg.com/80/v2-d0a13b8a300cb29c8d73d8d35c4c3c51_720w.jpg)



原因是使用 [PBO](https://link.zhihu.com/?target=https%3A//www.codersrc.com/archives/17356.html) 时，屏幕上的数据不是读取到内存，而是从显卡读到 PBO 中，或者如果内部机制是读取到内存中，但这也是由 DMA 控制器来完成的，而不是 cpu 指令来做的，再加上两个 PBO 交换使用，所以读取效率很高。



![img](https://pic3.zhimg.com/80/v2-470bfcb8bf981dd47b5da8f64042b8c2_720w.jpg)



> **PBO 快速地从内存 CPU 向显卡 GPU 传输数据** **—> GL_PIXEL_PACK_BUFFER**
>
> ****PBO 快速地**从显卡 GPU 读取数据到内存 CPU** **—> GL_PIXEL_UNPACK_BUFFER**