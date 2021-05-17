#  Personal notes / Understanding
There are two parts to this lab. The first part is to create a cache simulator while the second part is to write an optimized transpose function that causes as few cache misses as possible.


![](https://lh3.googleusercontent.com/sM50foljyeLxPhpFXRn4C9MeiosugzDPSeI39BbPUWc-Zp1Ueqhco1mFEzDk7Sg806pcmFQWST1R1UpV3U5tTlTrZZ6pwdNA85LhkVYi4ZoPjRhqTud-cLLepY-6Zmbb_334HD-d2tcfBpD3Bm9lUUNt5MBRqZMQWXmb0zyoStXbbdIkIU-6xinprVfKvLB2bmSidLF7pLxu-yrF_S4inhxTTyE1E4zJ9ZeWT9fFpYF0h6s7yPk-bt91ItiSRwl7XMzzWQrL8fWjPrWgZZkp9DwJkTjdZwslhGDwGKMEp9kbJrYCVf5Hrw9qKabQpXG0RffoCCUhMNX4zt4drl0oSYzpgYCU-s6tz1EHmzBbcRkQjuvaCTRhsX0pESOZd4gfoDmfOJdpHTwPmuRg5TbqcTzecS8TLW3sqHvPP7Xc06kQD6EnbIFbPkdCfKXR1UWYCnEwBJAsEple6-NP-wbiZ8uUPHIvSQjwVurqHg8Ciph6CM39Nwnv8LM_sQGth1jiP_uZACs8RmrDQcgnqvf8yagCZBsdyToRCU-_i4QHkXSIakVEKu2_E4sKdF0KIYVlRfnUC9W3kRnnIPEA3OuiXt5cl0d9FD7ADTph_mlPldqp096q_smfv-5B9mPa_Pe9NGVchWaakWo2g81NmFr9sQoPfXkw2Dkz-o88XnNRHM14JUhCAVkk-o2YrRMOUyWFqpHF3bQn1NrC3o9OHyBottDZ=w897-h550-no?authuser=2)

*How cache look like*

The address is split into three partition to find the cache.

![](https://lh3.googleusercontent.com/vLnU4ekoWZ_vbRhvPQGjkDi-kpjukFDmL8D1aDFYsyyUGgWynXRmZaeK47zWpryYvnIvO1yj6x9OTcHYf3K6zit3Pgt_cr2zDXK14voj9LR18Dinozfu4C3xxEZPw5UugZ1JvHEX6a82XPdlIqQKCZdS3u-C8p3JZyOjtnG8cjJr4ZktKHLRGMLcV_N53vHI9MO0PfCE6UmTvDGjIP95yRA1uIyIIX56kQKS-cMvw67v2Mift9SHV5dhZ5EYfQ_PH1G5tYpiqhc0Bu2DzoG6W0s_lI3RJoF6iywoWZrTEhzmdR9cXGwfbH4SY4AfPs6OBcW1B4UciNRURm_28yfBwMiAXHwcB6sXCqTBYABxbFIJpffGs6RM7jkGb8oNU91KNB99ev513RR3Pb0VCPLeogByxjrnY6-qaq1edxDlPGSTsjcusr8NCA2u0-e97uX3Yh_RlCPAPHlM8sEOy8o-UkRjCRHn29DpVi84VHb0HlZozxVSkrc188JGNahzyKO9i5pFkneU63OuogstB7Cb7B2v1988RmcizHPKwSxDUwlSWM9mhMYAJJZwO88iaKJtMsIMtVNFyMzBMGNMGSkdTZk7BN-7IaJGfDX9Sy7Jeq-Hh43vykW51xZVQC6lxwj3GvvywCey1_QlnwQl1LtUH-GYLyy1733PRi-_F03M5Poi8qIoRHK9h_eAwnVePe943HPMU6fY4Iiv6Y5lPnMWbmIr=w573-h132-no?authuser=2)

1. Set index bit tell us which set is the target
2. Tag index bit tell us which line of current set is the target
3. A line in the set contains our target if and only if the valied bit is set & and the tag bit match the tag bit in the address.
4. Block offset give the offset of the target.

<h3>Type of cache </h3>

1. Direct mapped cache : One cache line per set
2. Set associative cache : Multiple set and each set consists of multiple line.
3. Fully associative cache : Single set only and consists of multiple line

<h3>Locality </h3>

1. Temporal locality [ Time ] : Memory location or data item that reference likely to be reference again. ( eg: loop )
2. Spatial locality [ Space ]: Memory location or data item that reference likely to reference the nearby memory location ( eg: array )


<h2> Part 1 </h2>

 1. Make a *struct* to simulate the cache as illustrated above with one more variable to record the time / freq for LRU.
 2.  Use getopt to parse the arguments. ( Note: If a character is followed by a colon, the option requires an argument )
 3. Store and Load just need to walk the cache once , modify need to walk the cache twice.
 4. Possibility cases for modify
	a. 2 Hits
	b. 1 Hits + 1 miss
	c. 1 Hits + 1 miss + 1 evictions
 5. Manipulate the bit to get the tag and set.
 6. If cache's valid bit is set and cache's tag equal to address's tag, then it is a hit , else miss.
 7. If there is empty space in the cache, just insert into it, else replace the one that is least recently used.

<h2> Part 2 </h2>

Too lazy to do at this moment. But the idea is around the temporal / spatial locality.

	

