#  Personal notes / Understanding

Object code file are given and when run it, it prompts the user to type in 6 different strings. Disassembling and reverse engineering the program are required to determine what the 6 strings should be. Through out this lab, GDB debugger is used extensively and will be more familiar with the assembly language.

# Simple GDB commands that help out
| Command | Description  |
|--|--|
| r / r arg1, arg2... |  run program|
| q |  exit gdb|
| b [address / func's name / ... ] | set breakpoint at xxx  |
| q |  exit gdb|
| disas |  Disassemble current function|
| la ne |  Change the layout(Very useful, so you do not need to keep retyping disas)|
| si | s stands for step. Execute 1 instruction|
| ni | n stands for next. Similar to si but ni will not step into the function.|
| until *addressX |  Continue execute until addressX|
| print $rax|  print the content in rax|
| x/[s/d]$rax|  Dereference to $rax and print it content in string or integer.|


More instruction about GDB can be read from [Summary of GDB commands](http://csapp.cs.cmu.edu/3e/docs/gdbnotes-x86-64.pdf) 


## Phase 1
![](https://lh3.googleusercontent.com/pw/ACtC-3dcZCrj5mQ7EDP4UF4qk4RJjOMfnxlsU1i4dopN-8IgaGBhuERjTHlL9E9x71SwlAhbo8UGRMXU6hgha95tGv0hEdN6yKCIsW_1uxKWuuvfUbnH8_yOvKzuPrHqwzig2o4avEd-1IEwEjKXN7j1zBg=w603-h146-no?authuser=0)
1. Simply use the command of x/s $esi to see what is the content.

## Phase 2
![](https://lh3.googleusercontent.com/WabCXitUu1QCCr3zqOmPj17QwvefLcuHU34zrN7sOMFdRtWbbpCpIxfve5uZliwuIG2cNMLEK9XrapPDbUPwhZ9mNala8SsguCtqGBpeoR9Z8vpxnWer3MTgOplesPMiRouFSUhycuSjEjIEvqU4BPVQQLlLK-03iNWkgW_mBbnreCCc0BcyNWQ1WrjAmtNcELGn5J0uFm5jHMYFnGFL0VZxeWr0h99_jiRuDe5hjwCcIFth9c4BR5-c0fsUkKBw12o--RUGDihY77J0J4O7umxDNDPbG3plp9m7EzRWeWnlrW8GrnzA2wFFrcHMlhbLV8ZGIKz6f_WFRBbyrTTWbt7sMqnyX6HASEDXNExFDPThjjwyTqah5zRSQAnufUql32Hb1d00CHqb7ct_v831QXCU4sfMoH91qZJ-Q0KduycLtYgWxWoIoxQ09z2zHu760elIFnkyM6ravtPdQGSIEQHwDebvDCxwVKkZxCkOP7Vj59EIXK6bFfh6tb9FL65iJdexZUisag_5w9BhxBHilA9O8N3uDvNgEOpcS-VVJmStnoLgPCL-Na1ezc-_Dz9lpL8glFjD1-ePVsBkeqX8Ex00x3P8PIEnTDqczuP_QKgOsv7ejUOu4rkTLEhlegoqJzK7HknPklLPNKPAc1oVsqpiwm_johF36UwHMj_F64k4SNEsNBD815d7XpTdSP-TvyNTal-K6rY1Am7cszJR7Sc=w583-h452-no?authuser=2)
1. First, we see that <**read_six_numbers**>, then we can tell that we are required to enter six numbers.
2. Next, we also see that at <**+14**> there, it is comparing with 1, it means that our first number must be 1.
3. If equal to 1, go to <**+52**>, at there we see that it store the address of  second number to rbx and at <**+27**>, it save the previous number to eax.
4. Then, eax*2 and compare with rbx.
5. From here, we can already tell that the second number must be double to the first number and third number must be double to the second number.
6. So, the answer is 1, 2, 4, 8, 16, 32.

## Phase 3
![](https://lh3.googleusercontent.com/pw/ACtC-3fP_YjR9dDVyDa3sNS2kg0FkEhGAUuAq4qcuJ9GpPtnzsi6opSz7n36aL7LDcCOJiXhTZQQpoF0cbzPeY5lPN7QR6tGy14bxny--kTfoyXx3vEPEE-Zx08dFj9LBqwPfOLHfOKBymJn2-Nq0_u-VAc=w606-h649-no?authuser=2)
1. x/s on $rsi , we can see the result of " %d %d ", we can certainly know that the answer is 2 integer number.
2. It first check how many numbers did we insert, if less than 2, then explode.
3. After that, again, it check if the first integer is greater than 7, if yes, then explode.
4. The second integer depends on the first integer.
5. It will go to respectively address and obtain the integer to compare with.
6. **<+54>**, **<+64>**, **<+71>** and ... both are the accepted answer depend on the first integer.
7.  In my case, my first integer is 2 , and so it will go to 0x400f83, and so my second integer must be 707. There are few other answer in this phase.

## Phase 4
![](https://lh3.googleusercontent.com/pw/ACtC-3eWIgpIMrWpc9T7j45Y52_og5sSq2bLPSjaGl8m2eGLVmusSyHHmJz8L0pACVj6XtHTJUUXkFLJevLGQtAYSa4tWobARwLFU5SmuFRKBlcHoMkVSJkdeJxmGe247PDWwTa1EQE8Ak9IGR_0kbo9twE=w629-h400-no?authuser=2)
1.  Same as phase 3, we first x/s on $rsi , we can see the result of " %d %d ", we can certainly know that the answer is 2 integer number and it check if we enter 2 integers, if not then explode.
2. Then, it check if the first integer is less than 15, if greater than explode.
3. After that, it will go into some recursive function.
![](https://lh3.googleusercontent.com/pw/ACtC-3fAKDtnjs7tbLrl_KbW5-G2KV3WZ9d49M2Gy-gsqG4DUOG_gQ9_aeOHZ1phGQwq2BNHiI2_sVfptDc3gsaohSP1-_AgqCrtcO4F_kUWXhdVBtz7-1xk6YIv1LmOTh-pabgIvbR1S3HgOZcXkSDK5_c=w576-h395-no?authuser=2)
4. The recursive function will not explained detail here, but basically the return value after going through the function must be equal to 0.
5. For the second integer, we can see that at phase_4 <**+69**>, it is comparing with 0. Hence, we can tell that the second integer must be 0.
6. There are few answer to this question as well, namely 0 0 、1 0、3 0、7 0.

## Phase 5
![](https://lh3.googleusercontent.com/pw/ACtC-3e35FSHdSdSGIIVhg3dSmSeFkFmW2tJJtAefht9ztlkm4dNkphuAyfQ6-KNaq5LVDkhC5gKSkc7iSWwMHy42TNAawygXR5odZGAWtx5-P9eXLXqJaB-zcBJvg2Tce3cpiB6GtfxoYt4h0utPlhIDuk=w634-h663-no?authuser=2)
1. <**+29**> show that the string must be 6 characters, if not it will explode here.
2. We can check that what strings we have to equal to by x/s 0x40245e, and it prints "flyers"
3. Six characters, as we expected, but sadly this is not our answer because our input will be mapped into some other characters.
4. So, in other ways to say that, after mapping to our input, it should map to become "flyers"
5. Next, another important hint is the string in address 0x4024b0, we print it out, and we get 

> "maduiersnfotvbylSo you think you can stop the bomb with ctrl-c, do you?"
6. How the mapping done is, there is a loop in it, and it will iterate through each character. Every character is 'And' with 0xF.

> For example: if my first character is 'i' , its binary is 0110 1001.
> 0110 1001 & 1111 -> 1001
7. The value we get after 'And' will be used to access the sentence that we get in step 5.
8. 1001 is 9. And so we will  access the 9th character in that sentence.
> "maduiersn[ f ]otvbylSo you think you can stop the bomb with ctrl-c, do you?"
9. Then we will keep repeat until the loop end.
10. The second characters we need is 'l', and from that sentence we know that 'l' is located at the 15th character,  hence we just need to find any ascii character that after 'And' will become 15. 
11. Can just google and  lookup for the ascii table that has the binary format.
12. There are multiple answers in this question as well.
> 
> Phase 6 and secret phase cannot be done without the help and
> explaination from [here](https://caminek.rocks/2019/12/18/binary-bomb-phase-6/). Kudos to him. 
> The assembly for this phase is long , and only brief explaination is done here. Refer to that website for more detail explaination.

## Phase 6
>This phase involved linkedlist , nested loop
>
Stage 1.  Need to input 6 digits, and the number must be less than or equal to 6 , and each number must be unique
-eg : 1 3 2 4 6 5

Stage 2. Get the complement of the number by 7 minus your number , and save it into the stack 
>arr[0] = 7-1 , arr[1] = 7-2 arr[2] = 7 - 3
>
Stage 3: use the value from phase 2 to get the node and save it to the stack
eg: eax = 1 ,ecx = 3 , then eax will undergo 2 loop and reach 3 to get the third node and put it on the stack, the node value is not our input , it is some readily value inside the node , like 332, 924, 168,...

Stage 4:Link the node

Stage 5:check if the node's value is in descending order 

IF IN DESCENDING ORDER, THEN DEFUSE ELSE EXPLODE

## Guide to trigger secret phase
![](https://lh3.googleusercontent.com/pw/ACtC-3fXhUN9gOeZkv-DN1YHegTVOBlLlvUpoejovMcW2TPIMEOsLj3WEnm_ymiRZAK13OAD3n_GZ5Hw_KpT47KzP52KBe546c8ea4NxsVm5RYoQ3TDtrF2iGzovf8xFu7x8Drjd7jUPHqTNHDDhtJgt2Y8=w841-h663-no?authuser=2)
1. We can see that secret phase can be trigger from the phase that has 2 integer input, which is phase 3 and phase 4 and we believe that the secret world to trigger it is DrEvil.
2. Both Phase 3 and Phase 4 accept 'DrEvil' as third value for the ans , but only phase 4 will trigger the secret phase
## Secret Phase
> This phase involved recursive and binary tree.
1. We can tell that it compare with 0x3e8 which is 1000 with our (input - 1), hence , the max value for our input is 1001
2. We can see that the it compare with 2 at the last, we meaning that after going through some function, our return value must be 2
3.fun7 is a binary tree
4. it will first compare your input value with the current node, which is 36, if  the current node is less than or equal to the input value( Meaning ur value is greater than the current node), then go to right node.
- set eax to 0
- compare if rsi == rdx, then straight return
- after return from right node , add 1 to rax, then return
5. If current node is greater than our input ( our input is lesser than the current node), go to the left node
- after return from left node, eax= eax+eax (eax *2)
6. If the input value does not equal to any node , then return value will be 0xfffff..., than answer will definitely wrong
 
