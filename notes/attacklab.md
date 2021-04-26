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
 ![](https://lh3.googleusercontent.com/SF_eXwLLObu0tDVrvhvBhfbVH5U_It7NLNMqK0hIlN1FRdPkB56dp_mABFhDVXbckiWn8MRNZQsxr_SwfvlvXwAa6vwJizj38QqSGEWEGc_oT3AM5A7yXdEo07XB6Dz7DGD41lzCC6nRTzF2AC8K2ks5pn_Hlyt4ZCE2TQTo0lh4wJgeZsiLNpkEPJ_aOvafF6QmkKwf7EUJb7ymAe3FVmXsWRGncSme-8bBIbvgJSpwOBghmQj_4OvM_Rl7SygedbUGMp5x2RvErQQsVhZ3C4gtqi3Gpp8z-alzqmJfd0ZkMCV7K_a2h6Xq1nPnmEHOcoQ8C_qqDSa2jIBbPQtJzsJkCUPWCaqWP1ITHuui-aFzQsodZr4dR--p2pSEWxL1QaOGJiUYug8Y608MaeoUjDFH6RhGa-VMwpVOBo0UyEM0OVV6WLJrZuPN9UjXNHSHMcUdOnQxbgNjQM0XLt1VwOVy1_71HuYtGZwwTC8sKTfcYJl8zwaDWs1BG-g9rh__JYeQMczLQHg_kygl6KPMHk_VLkN1AXBLxOPX9iBh0DerNKaa0DcCeuByqQTdjwQ_osUMip2Ue8sfbV1BLXGzRD6JR3CfMBDSRSP7mrxLegdYPhGns7dwmhTyixY5VdEKUvoI3GQC1vi_7MmxRdbbGDy7QTjKuRGSV9aCu4pz_hpiFkZTEBqEgC_B8aFtFHgJBeCcK4xq6fVvxjAj_KQ4yXg=w701-h130-no?authuser=2)
 
*^Before calling hexmatch^*

![](https://lh3.googleusercontent.com/l2uhkcyKcYk7Wr52eS1cnTIkqWVeFNorLpGmU1E7fBlsfojVw-tsOpGrbrR_Z2PWraAe3X5ikocv5E5TTLP1dYuhjHtiXqJE2kfcLypIIJttVSqoyZr01h3EFv-PaoQS0LzgX-FKH-m1b3zmsiZdV2AKxfB1KVe9FSgFQWgDvCD2UBpGb6Q-_q4VHG2ILVWG3PUPQcUOWq6mYNhMBOGSwbeTrCOmgUMBygEvdo-4DE8mxMA3YI2bpzN-eX9GOadYEYzs-HsxnJq1R124E9GgFYcNfWGaVsnk-JvqXgusNtk8DUb4wr60DoVhdcRGAeELwHVMXsyTZ0Yp9r8rIt9SLd_FwGq4rBQFbkkFkWddaJnmu0FKCFseK7yYU31ak1mZpbJZ-hVUDk9jiO8HvQtGJbdxejFQ56ybLypas5J2D_wqnU5gnVQw7tJZMNHWwfXA1mYCNvm3qXTN20K_zzsLoAhBl8zoGdZnii5517ulWhGadNVVGAB4OLu8iW8xayK7ftQLuDNhmdVnpX6pk0870VGZWM_PQRDR5w5sRUfcgQOXwXdeZwB_YGfc4I9yJ2by-bc1bDmG-thdZr-IhWRkqQNlQjZBcqGf1pALs_JEzexurELEPs2-kq8cTOzciDD8tKMlwL60-7gfy_Umir9-mdvEBviudpIJTnsrG2AUZNFVlNHVtoMKcFGgDcpVuXLl31DTEUAUposGuMguJX-By2M=w736-h132-no?authuser=2)

*^After calling hexmatch^*

11. Overrall idea : put byte representation of cookie in the stack of test frame -> overflow -> overflow addr lead to rsp -> mov the addr at test frame to rdi -> call to touch3

## Phase 4
![](https://lh3.googleusercontent.com/nZ6pWcKPtrt_Fi0klIZWYJJY5kdr43K8uM6rdoxQq-1GqhQ1O3e4JxejUwT6HD9WNPHqLjyabPiOBFbOa-swwkpU1D-16Eayu3URRbdkJ8_D1SVoiaLzhNE_D5zlS44lBBPR0YTZ-fmB4jTgxME6j5KSeiV-WWgFhwqE1O2atYCFxaSYOfXarlv1QszmqHzqwdf5cb7bTCzx-WS9IDAOeCo4l4giPvF5r59utAdcaVHw_UhMnV9Sq59v9y1VeYMdlNQ-W6t_bdvOyLuwOWLxrWDwdvvsgaSj48TqNFY3Dyq4SS9Du9gA-rcaevoeTkBN3JD3Vx9PiVlhoJazDQyT6s3JF-rqaCE6XKfJPjeA8Jua9pAYUSKL_kLxpe2TjXATna_JYt2Hy7ehdaukwoR7cb33BmKMlRdG2pikUAOiYW-4k_HqzmyX1k0drEZt9h_RU-Bn5ffsmut7yQANIdmehqoT4u0AA5uSnOPQi8jJ2kxHtLB_dmso9yqQ-EFwWS-bN5cBFcRGVMhCGIGay_g09zFditORtnMSnn2z6FTp69p0lM8MH2CDsuB5sv39GY2lJe2skamjE_J7KycU72qm97qAQS_5ce5Df9C3t0BzZlbqu5G6AiM9B3AQrF9sxn6CGyHEzeVDZq-qD-S6WU7DyixccUveuNA8OT_ROnrV4rcq0fe_tyER35D8t7IY2xPiezl_f4trpE1JnVmSym8pyDI=w677-h552-no?authuser=2)

*^ Gadgets that are available in phase 4 ^*

1. For phase 4, we will repeat the exact same attack on phase 2 except  that now the stack marks the section of memory holding the stack as nonexecutable so we cannot simply use the overflow and injection technique in the getbuf's buffer.
2. We will use Return Oriented Programming (ROP) which what it does in short is, we use the existing code/ byte sequences. It normally consist of one or more instructions followed by the instruction ret (0xc3) .  And those are normally called as gadget.
3. For this phase, we only need 2 gadgets, one to pop the data from the stack into the register, and one to store the data in the register into rdi.
4.We will first look from the table for the encoding of movq instruction , we found that 48 89 c7 fit into our requirement for storing the data into rdi , and 58 fit into our requirement for popping the data into the register
4. Next step , we will go and look at the gadget farm , and lookup for 48  89 c7 , and 58
5. First we look for the 58. We found that 4019a7 , 4019b5 and 4019ca have the 58 that we need, but only 4019a7 and 4019ca are available because we can see that both 4019a7 have 58 follow by 90. 0x90 is NOP which does nothing but just increase the PC by 1 , 4019ca have 58 follow by 90 and c3 and what it does is increase PC by 1 and return (0xc3 is ret). While 4019b5 have 58 follow by 92 , and what 0x92 does is exchange data. We can see that rax exchange it's data with rdx.
![](https://lh3.googleusercontent.com/bLZapnbPlpzxUDq-iwyKz8kbqpcTuE1JL6o7pf78BCUvAoQAMnlAX3gyRahfw79LbKyJMqfPk1rdOOMKeLANuyYGhQbNRd89rgKnENqHL2XRhB-BZxowZAbg-4_GxDoC9PEt4MPtFPWGN1hTqEaERrYFLY99uw28XuEwj2uMUo4voBw6xBI8rfVu_VEU7Ww-5_X9dCclUvsXg7pqxYmR9YAktJGb7TiTn8OWzNlkYVTXy2psSaF9M3q9N_TA4QhoU5ZlZdxgk3MYcc-7U7aeP77_GpJTDzHbrfWyykZVi1AKiWgVmzSvozAmBbXUmpoVlVWXQKyKNoPwa_-9DSRw8uF9qVPi535zZLvFX2VNkbUZXEB2359ztUSl0Pd4VKbGRQ8_Lc83BRBocJZKKpcxCCl7arvl9demQi9Jgm5CbH3OACygDxwI91toNwLy0p6I-GESbrNJZ1CktFXEn4cuP81haWOougYqWd3gk4s6GYarV14uwF2yJd28DK_-VrZIy3rlJzMAMaVh5CoS2Ut-Z6Lpx-CxNlnIGMlujMkfb_xPHck7XUirvN-Cwm3b1a-5NXkbgZM--FsOazfXkcP5urgDHd_17Q2qXnOgb21LHRw1Scy-r5Ar1OYkNXOTrzlAQ1sPf52Ca8qQzwA3cX_ilTLgrEH_A1BAdAjmF6sHTz6Mh4xWXEbUGz8xaRLLTd6Wjr7ts8r_sFMoFVrRYAk1k3Hm=w567-h472-no?authuser=2)

*^ rax before 0x92, look at the rax and rdx ^*

![](https://lh3.googleusercontent.com/xXhKQizWptnn0eHJn3ziBCnI_AWCqZSZDLSgr3N9ZOH_4iAVSR9AH53FT6lQiu34X6u09WaY2o3nfRw4tdEHojj8YM7XQrnJWzTiZ8P37Tjoij1tJS3gBA8HfiAlU1JT3HkflF_h7VwgU0kuJhawDJmUmejO9Jd_9sxCbyffyV1keAVj9D-FLH3hP3VpXhi09iPA3Rs5_GfgQq29Z13AY8HwJvtqQKMSZEL9VayqW7N3GWTrWpxMDVIpmtFDO8A6zfsoi0UMjY_EplSL3YLjd4-sOB_afFNdEokTmo02-oWvk4Dqwa7KJbdd58q6urR0F5cwLps4LrRRNL5lQg4vd7sz5s7fPSP-9m_hQ_s0Ma_4VBm5P8m7rMJn9OyS21QpeiR6Tit5PpDzC5gpZ_FIm85R_8KPMEI3AWEzxFtdHVTJqyBhr8YrnYEDoCHGzAHxfYUDrpSWymB_fxw6AivuEIOd0-IGghpDrkhEM028TMEpb4etvYOz9vyjORI9x6OnT-3043O_BET1rpQ1iCHJZ7aPjMviGeCDIrP0aXtm1W_4pbZqJiE21H5IhylgETZTDR_hxS5JOJqmyFOVPk3kJFMk_swi4Fyz1Wg5WsG5TCoT4wYEWV-n149WHZyp1oj5KTpKeVNB0cOQlvgeUp_IUdyxT8J_8wp3Xlvqf_cT5rQ1OJNWTvhuIVbY-GIicd5RGZ9NRt_-W7MpSrXQ3qg89qic=w576-h486-no?authuser=2)

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
![](https://lh3.googleusercontent.com/736zsBo29gfW6zQ4DaDp0hNhFEWkesVa92osbj_xWDgXS75ejQBTyu1rq4eYw_vRJmsOxXHz1cI05x39RmqoUiydeqEE43wUSX1LjY_VtCVph7P8fb9uLyY-9bb1UxJiNPaFFOSp1A1aolxdZZDNOVbg31izAe9GTU8zsExw4FMcrrKIIRxiBTFv5ooxK1wtArTuXBcKPgzSn849I1DEGqdNjvzLq2lMnrEvnayAm0k3hssZZlFGq4ilZ3LePq9ICLu1uVtZy1D6d0pt8RlXUANe40aYbg4jc5Zv2yXusDu-HF2hyJuiPrZGnbGAIkns6pJZRbw0PHR_mgxndKuBznsjoCG0Xc8pQKx-l3cT8chkL847jTTUi-nemcueJjwFsg0seWWWSRe6DZGT7VhNsC9-SUKJ6V0ttZ_-NbSoy-05W770w-8Sctgfly04Byih-0v8ZNIkPBzViJL2mOu-PCF7uQwaDdDxoJ1lsYuSgoLc8Qzgr1qNHgPVW53muYUphNjMnfXkKEW2l6BycSTSsVVZ_sfLycyvQK5NiPQLKzwXmDmFJz9y1Eb3IClQs6NWg5GyK98_mpAlVKZIkav3WU2fiotaAD2cS6PBl00TqCkUl7oyhXdQzkzsenCY4dRH8WzCe6TV2MpD0EtvKDCWcJSD2sDsnfNqBCDDvlgHkE3Rs5QAiAY3b5vFe4hYimD1zchdMtApFS2jVRKqcLmuc1vB=w184-h395-no?authuser=2)

1. For phase 5, we will repeat the exact same attack on phase 3 with the concept of phase 4 but because of stack randomization is enabled, hence we cannot simply insert the absolute address. The illustration of this phase is get from the internet that clearly show the instruction for each step.
2. We can see that the $rsp address is different for each run
![](https://lh3.googleusercontent.com/cWEHUa6RSZh_hR-Fi4ZSR8p_s1tt9MrCnCOoPeA03LbRpVGOJTY3eKAOdCLNfwIM9qekWF9tCWcZkX2G9vF-mfNcm7fcFvAzOdopYUVidU-SAEVPiQ_Hm8ZnIiuUntwUICeMXxiRCcaZq516pv4XI3o0upLt2QkVae25ulrmijyyAFqadcgQs8IF1puq-znTbA4AqdIu9uBBg4LPk-vJLOFqi81N25LJPHUcBsC2dBiihM4IEjl3FV-Nf3UTaJWiPy0ttvQ3oz-g5JY3QVFdQ6kF7_OVbRqWa8_mkrzLmaAhR6kkfwLE2tKbuh4W46MitIL7CffkDq3SMz0_zLSfIUZmhyNhcHf4wle83lqo0WvUbn4gAl9NxIHmNVqbKkBhBwvFtkUXjXInPl61ppWEAN7qONcpRmfIaGfIWlgjHzdW701BFaO8sULEZt5gcDX5ApePKmbmJQkMsI7vIc0PdbbEWEXvNwUqgEwHGnBt-E4wFjmx1cM_OXZVvtklz2Dxpzputrl-GvsyiB40aLCytEcVrT9lv8d7G4eBfzsH5yagAw8nsqDZ4Q_p17S8Ctc5bMJXPRtABdX3BNrdNJSKmPkmkuTqbwnBhXmPs7ZYQGpKABkAPz1lzACbr4lRmbShGbTACDMGdwEjftIkWR-8PlZds_LzjIIdSRw5b_yRrrIIwvIMQGqGHw9xshvkWdRnLTdvpG-V1rvcYZvlOErcvD2e=w745-h271-no?authuser=2)

*^ First run, observe the address for rsp^*

![](https://lh3.googleusercontent.com/45WA0MshUfCThkBKdfyTWT2feedC2U77VY1FPZFToVoHmJeRWb_LoN8VAP9Oua0tiusQ1jdRYKf2tfgWurgPsiL7Z8Po0G6zBX8d0W8wxnQlUhJXjmr53HySeqFHBy0Z5JAXua8wpGZxiVvh8eA9BlR3PBFw7rnka-qHAjoBYr_Fq4oOPftEq5BYpofBmqKXTyLDDGe_HXIPR7LKXXPBkdosqHjAseOicyqRn2aMqfezH9WRIHTYTp28H-C8719sby3cHNy3vUJ6DaEUFmDfeckMpvVXcXjrq70_WTZuN0C8sJ-X17FbOxN8ep8whhDwLMx1jjafC2rwpR8SgrLqQ6YhbfKsyltogVxpjghOrn84GrCyUA2n4DkE-FqAgWOFS4wEV53BxZsB5TD1LJPDPAvD_WvB9ML7dEpjrpanS4kknIXjoyBm_ew0_d4QM6pLk2seCOmoC5wpF4tnGj8lDqgB8AXj-BsYD6lIEwQzJobPjbX6QuV9PN1UftH4T6vr1c7nt00Y7v-SBQZPPYqbufRmuCtFEOv6SW6fdVOUccCrL0MVzYlE3KPOkyQ7baA97k3JJpzh-tVfN6zB41cTgd9ma9_KkOqjKeiLWitFJ162WWXKgIXwkKME8BMQBgUkYYvEP_AMGhAjIeY1fMUdpVf4w5Cz7E7Dg-_DVwD881CRXCfdfw_pMAr6ChU3u-hLrxuTBTydLfz6Klh2V-T0T67G=w697-h305-no?authuser=2)

*^ Second run, observe the address for rsp^*

3. So instead of using absolute address, we will now have to manually calculate the $rsp offset.
4. There isn't any $rsp to $rdi gadget in the farm, so  we will split into $rsp -> $rax , $rax to $rdi.
5. Save the offset to the $rax
6. Save $rax to $rsi but in the gadget farm we only 32 bit register.
7. So, we will use movl function to move $eax to edx, edx to ecx then only ecx to esi
8. Next, since there is no add function, we will use lea(rdi,rsi,1), rax to do the sum of the address and save it into rax
9, Save rax into rdi 
9. And lastly, save the byte sequence of our cookie.
