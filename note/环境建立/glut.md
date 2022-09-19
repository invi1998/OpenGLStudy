**OpenGL工具库 OpenGL Utility Toolkit**

包含大约30多个函数，函数名前缀为glut。
glut是不依赖于窗口平台的OpenGL工具包，由Mark KLilgrad在SGI编写（现在在Nvidia），目的是隐藏不同窗口平台API的复杂度。 函数以glut开头，它们作为aux库功能更强的替代品，提供更为复杂的绘制功能，此函数由glut.dll来负责解释执行。由于glut中的窗口管理函数是不依赖于运行环境的，因此OpenGL中的工具库可以在X-Window, Windows NT, OS/2等系统下运行，特别适合于开发不需要复杂界面的OpenGL示例程序。对于有经验的程序员来说，一般先用glut理顺3D图形代码，然后再集成为完整的应用程序。
这部分函数主要包括
窗口操作函数，窗口初始化、窗口大小、窗口位置等函数glutInit() glutInitDisplayMode() glutInitWindowSize() glutInitWindowPosition()等。
回调函数。响应刷新消息、键盘消息、鼠标消息、定时器函数等，GlutDisplayFunc() glutPostRedisplay() glutReshapeFunc() glutTimerFunc() glutKeyboardFunc() glutMouseFunc()。
创建复杂的三维物体。这些和aux库的函数功能相同。创建网状体和实心体。如glutSolidSphere()、glutWireSphere()等。在此不再叙述。
菜单函数。创建添加菜单的函数GlutCreateMenu()、glutSetMenu()、glutAddMenuEntry()、glutAddSubMenu() 和glutAttachMenu()。
程序运行函数，glutMainLoop()。