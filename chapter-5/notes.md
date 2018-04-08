## Collision Resolution Policy
---

### Open Hashing(Separate Chaining)

Given a table of size M storing N records, the hash function will ideally spread the records evenly among M positions, yielding on average N/M records for each list. 

Define the load factor $\lambda$ to be the ratio of number of elements in the hash table to the table size. The expected length of each list is $\lambda$. The effort required to perform a *search* is the constant time required to compute the hash function and the time to traverse through the list. 

**Time Complexity**
To perform a successful $search, it requires $1 + \lambda / 2$ nodes being traversed. To see this, note that the list that is being searched contains the node that contains the match and other nodes. The number of "other nodes" is $\lambda$. If there are many searches, then expected $\lambda / 2$ nodes are searched.

To perform an unsuccesful search, it examines $1 + \lambda$ nodes on average.

**Rule**
The general rule for separate chaining hashing is to *make the table size as large as the number of elements*. If the load factor exceeds one, that is the number of elements exceeding the table size, then perform a rehashing.   

---
### Closed Hashing(Open Addressing)

Closed hashing stores all records directly in the hash tbale. Each reord R with key has a home position, the slot computed by the hash function.

#### Linear Probing
In linear probing, $f$ is the linear function of $i$, where $i$ is the number of iteration. Typically, $f(i) = i$. 

**Primary Clustering**
Linear probing causes an effect called primary clustering, meaning that any key that hashes into the cluster will require several attempts to find a hole, and this key is also added to the cluster.

**Time Complexity**
The expected number of probes using linear probing is roughly $\frac{1}{2}(1 + 1/(1-\lambda)^2)$ for insertions and unsuccessful searches, and $\frac{1}{2}(1 + 1/(1-\lambda))$ for successful searches. 

Assume the hash table is very large and each probe is independent of the previous probes(thus primary clustering is not a problem). These assumptions are satisfied by *random* collision resolution and are reasonable unless $\lambda$ is very close to 1. 

The expected number of probes for an unsuccessful search is the same as the expected number of probes until we find an empty cell. The fraction of empty cell is $1 - \lambda$, thus the expected number of probes is $1 / 1 - \lambda$ since we assume a geometric distribution.

The expected number of probes for a successful search is equal to the number of probes required when the particular element was inserted. When the number is inserted, it is done as a result of unsucessful search. Thus we can use the cost of an unsuccessful search to compute the average cost of a successful search. But how can we determine when the key is inserted? We can estimate the average by using an integral to calculate the mean value of the insertion time. The average probing is $\frac{1}{\lambda} \int_0^\lambda \frac{1}{1-\lambda}$.  

#### Quadratic Probing
Quadratic probing is a collision resolution method that *eliminates primary clustering*. Typically, $f(i) = i^2$. 

For linear probing, it is a bad idea to make the hash table nearly full. For quadratic probing, there is no guarantee of finding an empty cell once the hash table gets half full, or before it gets half full if the table size is not prime.

We can prove if the table size is prime and table is half empty, then we are always guaranteed to be able to insert a new element. To be more clear, we are talking about the elements whose home position is the same. Then each key follows the same probing sequence. However, this probing sequence can merely probe the number of elements less than half of the table size.

In general, we should keep in mind that
+ once the table gets half full, the insertion could fail
+ the table size should be prime

Although the quadratic pribing eliminates primary clustering, elements that hash to the same home position will probe the same alternative cells. This is known as *secondary clustering*.

#### Double Hashing

---
### Hash Table In STL
```unordered_set``` and ```unordered_map``` includes hash table implementation. The elements in ```unordered_set``` and the keys in ```unordered_map``` need a hash function and an equality operator==. 

These unordered classes can be used if it is not important for the entries to be viewable in sorted order. 




