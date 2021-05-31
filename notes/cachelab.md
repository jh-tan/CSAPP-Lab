#  Personal notes / Understanding
There are two parts to this lab. The first part is to create a cache simulator while the second part is to write an optimized transpose function that causes as few cache misses as possible.


![image](https://user-images.githubusercontent.com/68408911/120132673-5c0a5600-c1fd-11eb-94aa-dafe619b0fd9.png)

*How cache look like*

The address is split into three partition to find the cache.

![image](https://user-images.githubusercontent.com/68408911/120132706-69bfdb80-c1fd-11eb-8589-7e7b8f342d32.png)

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

	

