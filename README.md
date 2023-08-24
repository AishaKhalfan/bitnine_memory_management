# Bitnine Memory Manager

**Compiling**

To compile, run:
```bash
gcc -o manager manager.c
```

**Running**

Execute the manager program:

```bash
./manager
```

This will run the built-in test driver.

**Testing**

The test driver initializes a memory pool and performs randomized allocations, deallocations, and metric collection.

Some sample runs:

```bash
// 2MB pool, 5KB block size 
pool_size: 2097152 bytes
allocations: 409 
deallocations: 205
...

// 1GB pool, 2MB block size
pool_size: 1073741824 bytes  
allocations: 512
deallocations: 249
...

// 1GB pool, variable block size
pool_size: 1073741824 bytes
allocations: 1937
deallocations: 984 
...
```

The test cases exercise different pool sizes and block sizes.

**Design**
The manager uses a preallocated global memory pool to service allocation requests. A simple first-fit algorithm walks the pool to find free blocks.

- Pros:

	- Simple linear first-fit is fast for small pools
	- Dedicated pool prevents external fragmentation
- Cons:

	- Pool must be sized appropriately upfront
	- Pool is limited to preallocated size
The APIs provide abstraction from direct use of malloc/free and facilitate testing.

