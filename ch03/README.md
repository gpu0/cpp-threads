### README

#### Locks
If you dont guard the data structures, any pointer or reference to the data structure can leak the whole data in it.
One way to stop this from happening is to not define pointers or reference outside of the scope of locked data structure. Returning pointer to data from a function can also make data leak to other threads. 

For example, (from the book) std::stack is not thread safe as it has non-locked methods such as .pop(), .push().
