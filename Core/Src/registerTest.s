
  .syntax unified
  
  .cpu cortex-m3
  //软件模拟浮点运算
  .fpu softvfp
  //指令集 THUMB 
  .thumb

  .global regesiterTest
  .type regesiterTest,%function
  
  //申请内存
  .extern malloc
  /*需要注意的是，从flash启动时，0x0000 0000被映射到0x0x800 0000*/

  regesiterTest:
  //入栈
  PUSH {R0,R1,R2,LR}

  //MOV 指令

    mov R0 ,#8 //将8设置为R0寄存器的值

    mov R1 ,R0 //将R0寄存器的移动到R1寄存器

  //LDR指令

    ldr R0 ,= 0x00000000    //设置R0寄存器的值
    ldr R1 ,= 0x000000F0    //设置R1寄存器的值
    ldr R2 ,= 0x08          //设置R2寄存器的值

    ldr R1,[R0]             //将R0地址对应的值赋值给R1

    ldr R1,[R0,R2]          //将R0加上R2的地址指向的值赋值给R1

    ldr R1,[R0,#4]          //R0地址+4对应的值赋值给R1

    ldr R1,[R0],#4          //R0地址对应的值赋值给R1，同时R0的值加4

    ldr R1,[R0,#4]!         //R0地址+4，在内存中的值赋值给R1，然后r0 = r0 +4

  //STR指令

    ldr R0 ,= 0x16    //设置R0寄存器的值
    //请求分配内存，将返回的地址写入到R0寄存器
    BL malloc

    ldr R1 ,= 0xF0F0F0F0    //设置R1寄存器的值
    ldr R2 ,= 0x04          //设置R2寄存器的值

    //将R1寄存器的值保存到R0寄存器指向的地址
    str R1, [R0]

    //将R1寄存器的值保存到R0 + R2指向的地址
    str R1, [R0 , R2]

    //将R1寄存器的值保存到R0 + 8指向的地址
    str R1, [R0 , #8]

    //将R1寄存器的值保存到R0 + 12指向的地址,并更新R0 = R0 + 12
    str R1 , [R0 , #12]!

    ldr R1 ,= 0x0E0E0E0E    //设置R1寄存器的值

    //将R1寄存器的值保存到R0指向的地址,并更新R0 = R0 + 4
    str R1 , [R0] , #4

  //算数指令 add 

    //两个寄存器相加
    mov R0, 0x10
    mov R1, #5

    //将 R1 和 R2 的值相加，并将结果存储在R0,R0 = 0x15
    add R0, R1, R0  

    //将 R1 的值加上立即数 10，并将结果存储在 R0 中
    ADD R0, R1, #3 
  
  //算数指令 sub

    //两个寄存器相减
    mov R0, #5
    mov R1, #10

    //将R1减去R2,并将结果存储在R0,R0 = 5
    sub R0, R1, R0 

    //将R1的值减去3，并将结果存储在R0,R0 = 7
    sub R0, R1, #3

  //算数指令 mul

    //用于两个寄存器相乘
    mov R0, #5
    mov R1, #10
    //将R1乘R0,并将结果存储在R0,R0 = 50
    mul R0, R1, R0

  //算数指令 mla

    //用于执行乘法并加法操作(乘-累加)

    mov R0, #5
    mov R1, #10
    mov R2, #3
    MLA R0, R0, R1, R2 //R0乘上R1并加上R2，将值存在R0，R0 = 53
  
  //算数指令 UMULL
  
    //无符号长整数乘法
    mov R0, 0xFFFFFFFF
    mov R1, 0xEEEEEEEE

    //R0和R1的乘积，R2存储低32位,R3储存高32位
    UMULL R2, R3, R0, R1
  //出栈
  POP {R0,R1,R2,PC}
