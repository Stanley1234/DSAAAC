## Collision Resolution Policy
---

### Open Hashing(Separate Chaining)

Given a table of size M storing N records, the hash function will ideally spread the records evenly among M positions, yielding on average N/M records for each list. 

Define the load factor $\lambda$ to be the ratio of number of elements in the hash table to the table size. The expected length of each list is $\lambda$. The effort required to perform a *search* is the constant time required to compute the hash function and the time to traverse through the list. 

To perform a successful $search, it requires $1 + \lambda / 2$ nodes being traversed. To see this, note that the list that is being searched contains the node that contains the match and other nodes. The number of "other nodes" is $\lambda$. If there are many searches, then expected $\lambda / 2$ nodes are searched.

To perform an unsuccesful search, it examines $1 + \lambda$ nodes on average.

The general rule for separate chaining hashing is to *make the table size as large as the number of elements*. If the load factor exceeds one, that is the number of elements exceeding the table size, then perform a rehashing.   

---
### Closed Hashing(Open Addressing)

Closed hashing stores all records directly in the hash tbale. Each reord R with key has a home position, the slot computed by the hash function.

#### Linear Probing
In linear probing, $f$ is the linear function of $i$, where $i$ is the number of iteration. Typically, $f(i) = i$. 



