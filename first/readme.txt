中文为gbk编码
编译器为MinGW
debug gdb
编译平台 VS code
因为cmake没装成功，所以在作业中没用多文件联编。
《数据结构》第1次上机题 （线性表练习）
1．编程实现书P19  ADT List 基本操作12个：
（1）	用顺序存储结构实现； （2）用链式存储结构实现；

squenelist .c                                 linklist.c

．设元素值为整型的线性表L，分别采用顺序结构和链式结构存储，编写程序，实现线性表的就地逆置（习题集P18  2.21， 2.22）。

replacesqment_sq.c replacement_ll.c 

3．输入正整数n、m（m<n），设有n个人坐成一圈，从第1个人开始循环报数，报到m的人出列，然后再从下一个人开始报数，报到m的人又出列，如此重复，直到所有的人都出列为止。要求用链式结构和顺序结构实现，按出列的先后顺序输出每个人的信息。

1-3-ll.c 1-3-sq.c

4. CSP题目 学生排队
问题描述
　　体育老师小明要将自己班上的学生按顺序排队。他首先让学生按学号从小到大的顺序排成一排，学号小的排在前面，然后进行多次调整。一次调整小明可能让一位同学出队，向前或者向后移动一段距离后再插入队列。
　　例如，下面给出了一组移动的例子，例子中学生的人数为8人。
　　0）初始队列中学生的学号依次为1, 2, 3, 4, 5, 6, 7, 8；
　　1）第一次调整，命令为“3号同学向后移动2”，表示3号同学出队，向后移动2名同学的距离，再插入到队列中，新队列中学生的学号依次为1, 2, 4, 5, 3, 6, 7, 8；
　　2）第二次调整，命令为“8号同学向前移动3”，表示8号同学出队，向前移动3名同学的距离，再插入到队列中，新队列中学生的学号依次为1, 2, 4, 5, 8, 3, 6, 7；
　　3）第三次调整，命令为“3号同学向前移动2”，表示3号同学出队，向前移动2名同学的距离，再插入到队列中，新队列中学生的学号依次为1, 2, 4, 3, 5, 8, 6, 7。
　　小明记录了所有调整的过程，请问，最终从前向后所有学生的学号依次是多少？
　　请特别注意，上述移动过程中所涉及的号码指的是学号，而不是在队伍中的位置。在向后移动时，移动的距离不超过对应同学后面的人数，如果向后移动的距离正好等于对应同学后面的人数则该同学会移动到队列的最后面。在向前移动时，移动的距离不超过对应同学前面的人数，如果向前移动的距离正好等于对应同学前面的人数则该同学会移动到队列的最前面。
输入格式
　　输入的第一行包含一个整数n，表示学生的数量，学生的学号由1到n编号。
　　第二行包含一个整数m，表示调整的次数。
　　接下来m行，每行两个整数p, q，如果q为正，表示学号为p的同学向后移动q，如果q为负，表示学号为p的同学向前移动-q。
输出格式
　　输出一行，包含n个整数，相邻两个整数之间由一个空格分隔，表示最终从前向后所有学生的学号。
样例输入
8
3
3 2
8 -3
3 -2
样例输出
1 2 4 3 5 8 6 7
问题分析：这个问题可以通过顺序结构或（双向或单向）链表实现，但对于移动元素较多的情况，应采用哪种存储结构更优呢？

csp.c