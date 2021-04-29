#  Personal notes / Understanding

Two object code file are given, ctarget and rtarget. The first three phases are done on ctarget using code injection technique while the last two phases will be on rtarget using Return Oriented programming.  A very rough idea of how the the memory layout of ctarget/rtarget.

![image](https://user-images.githubusercontent.com/68408911/116019976-f6640080-a677-11eb-86bc-5ddaf367922b.png)


## Phase 1

 1. For phase 1, we were asked to return the program to touch1() instead of test.
 2. So, what we have to do is just simply overflow the buffer in getbuf and place the address of touch1 in the return address of the caller, then we are done.

## Phase 2

1. Same as phase 1 , getbuf allocated 40 bytes of space , so it is still an buffer overflow attack and instead of going to touch1, phase 2 we will go to touch2.
2. Now, touch2 accept an argument and it will consider success only if the parameter equal to the cookie. So,even we manage to jump to touch2, but the parameter != cookie, it still consider fail.
3. We are not allow to use jmp or call in phase 2. And one of the method that is equivalent to call is push + ret ( but this method will leave us with no return addr after jump to that function )
4. So, the idea will be, move our cookie into the rdi. (remember that  rdi is the register for first parameter) -> push touch2 addr , and return immediately.
5. The overflow byte will be the address of rsp.
6. In the end, the byte sequence in the stack will roughly look like:
| getbuf return add |: 00 00 00 00 55 61 dc 78 <-- this is the rsp addr
| rsp+32                 |: 00 00 00 00 00 00 00 00 <-- random useless byte
| rsp+24                 |: 00 00 00 00 00 00 00 00 <-- random useless byte
| rsp+16                 |: 00 00 00 00 00 00 00 00 <-- random useless byte
| rsp+8                   |: 00 00 00 c3 00 40 17 ec  <-- pushq $0x4017ec / retq
| rsp                       |: 68 59 b9 97 fa c7 c7 48  <-- mov $0x59b997fa , rdi 
7. overflow -> overflow addr lead to rsp -> mov _ into rdi , call to touch2


## Phase 3
1. Similar to phase 2 , we have to pass the cookie to the touch3. but the cookie must be in byte representation , so just lookup from man ascii or from the internet
2. Let the rsp address overflow into the return address of getbuf
3. Move the byte representation of cookie into rdi , push touch3 add , and return it.
4. But in the lab document, it state that

>  When functions hexmatch and strncmp are called, they push data onto
> the stack, overwriting portions of memory that held the buffer used by
> getbuf. As a result, you will need to be careful where you place the
> string representation of your cookie
5. So, we cant place our cookie's byte representation in the buffer of getbuf , because it will get overwritten. We will see later.
6. Since, the test function(the one who call getbuf) will not be used again , we can put the byte representation at there.
7. So, how to know what is the address of the test stack frame is by just taking the rsp (0x5561dca0) + 0x8,then we can get 0x5561dca8
8. Instead of putting the byte representation straight into the rdi, we save the address of 0x5561dca8 to rdi.
9. Now we look at the image below, we can see that the byte sequence in the buffer in getbuf,has been overwritten by the function called by hexmatch. Thats why we cannot put our cookie inside the buffer.
![image](https://user-images.githubusercontent.com/68408911/116525927-9dac9600-a90b-11eb-9465-123ba5cb1af6.png)
 
*^Before calling hexmatch^*

![image](https://user-images.githubusercontent.com/68408911/116525942-a43b0d80-a90b-11eb-9fbf-4320311738f0.png)

*^After calling hexmatch^*

11. Overrall idea : put byte representation of cookie in the stack of test frame -> overflow -> overflow addr lead to rsp -> mov the addr at test frame to rdi -> call to touch3

## Phase 4
![image](https://user-images.githubusercontent.com/68408911/116525991-b3ba5680-a90b-11eb-936f-f1842ef1516b.png)

*^ Gadgets that are available in phase 4 ^*

1. For phase 4, we will repeat the exact same attack on phase 2 except  that now the stack marks the section of memory holding the stack as nonexecutable so we cannot simply use the overflow and injection technique in the getbuf's buffer.
2. We will use Return Oriented Programming (ROP) which what it does in short is, we use the existing code/ byte sequences. It normally consist of one or more instructions followed by the instruction ret (0xc3) .  And those are normally called as gadget.
3. For this phase, we only need 2 gadgets, one to pop the data from the stack into the register, and one to store the data in the register into rdi.
4.We will first look from the table for the encoding of movq instruction , we found that 48 89 c7 fit into our requirement for storing the data into rdi , and 58 fit into our requirement for popping the data into the register
4. Next step , we will go and look at the gadget farm , and lookup for 48  89 c7 , and 58
5. First we look for the 58. We found that 4019a7 , 4019b5 and 4019ca have the 58 that we need, but only 4019a7 and 4019ca are available because we can see that both 4019a7 have 58 follow by 90. 0x90 is NOP which does nothing but just increase the PC by 1 , 4019ca have 58 follow by 90 and c3 and what it does is increase PC by 1 and return (0xc3 is ret). While 4019b5 have 58 follow by 92 , and what 0x92 does is exchange data. We can see that rax exchange it's data with rdx.
![image](https://user-images.githubusercontent.com/68408911/116526028-bd43be80-a90b-11eb-838d-47c8b1f076ff.png)

*^ rax before 0x92, look at the rax and rdx ^*

![image](https://user-images.githubusercontent.com/68408911/116526089-cc2a7100-a90b-11eb-9eb9-60df4be089f7.png)

*^ rax after 0x92, look at the rax and rdx ^*

6.  Next,we can see that 4019a0 , 4019ae , and 4019c3 have the 48 89 c7 , but only  4019a0 and 4019c3 working because c7 in 4019ae cause it jump to some other place and eventually cause the segmentation fault.
7. Now, we just add the offset to the byte sequence to make sure it point to the instruction that we want.
8. Add the cookie and the addr of touch2 to it and make sure all are padded to 8 bytes.
9. Lastly, what we get is 
|00 00 00 00 00 00 00 00 |
|00 00 00 00 00 00 00 00 |
|00 00 00 00 00 00 00 00 |
|00 00 00 00 00 00 00 00 |
|CC 19 40 00 00 00 00 00 | <- pop and save the cookie into rax
|FA 97 B9 59 00 00 00 00 | <- cookie here
|CA 19 40 00 00 00 00 00 | <- movq rax rdi
|EC 17 40 00 00 00 00 00 | <- addr of touch2
|00 00 00 00 00 00 00 00 |

## Phase 5
![image](https://user-images.githubusercontent.com/68408911/116022037-fd8d0d80-a67b-11eb-907b-533429c774ad.png)

1. For phase 5, we will repeat the exact same attack on phase 3 with the concept of phase 4 but because of stack randomization is enabled, hence we cannot simply insert the absolute address. The illustration of this phase is get from the internet that clearly show the instruction for each step.
2. We can see that the $rsp address is different for each run
![image](https://user-images.githubusercontent.com/68408911/116526162-e3695e80-a90b-11eb-9ea3-4f84638e9783.png)

*^ First run, observe the address for rsp^*

![image](https://user-images.githubusercontent.com/68408911/116526189-e82e1280-a90b-11eb-88c8-aca53225e6db.png)

*^ Second run, observe the address for rsp^*

3. So instead of using absolute address, we will now have to manually calculate the $rsp offset.
4. There isn't any $rsp to $rdi gadget in the farm, so  we will split into $rsp -> $rax , $rax to $rdi.
5. Save the offset to the $rax
6. Save $rax to $rsi but in the gadget farm we only 32 bit register.
7. So, we will use movl function to move $eax to edx, edx to ecx then only ecx to esi
8. Next, since there is no add function, we will use lea(rdi,rsi,1), rax to do the sum of the address and save it into rax
9, Save rax into rdi 
9. And lastly, save the byte sequence of our cookie.
