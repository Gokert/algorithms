# Data Structures and Algorithms
Tasks for the course "Algorithms and Data Structures" of the course in the VK Education Center.

1. [__Binary search__](https://github.com/Gokert/algorithms/blob/main/programs/binary_search.cpp)
    
    Given a sorted array of integers A[0..n-1] and an array of integers
    B[0..m-1]. For each element of array B[i] find the minimum index k of the
    minimum element of array A equal to or greater than B[i]: A[k] >= B[i]. If there
    is no such element, print n. n, m ≤ 10000. Requirements: Search running time k
    for each element of B[i]: O(log(k)). Attention! In this problem, for each B[i],
    you first need to determine the range for binary search with a size of order k
    using exponential search, and then do binary search in it. Input data format.
    The first line contains numbers n and m. In the second and third arrays A and B,
    respectively. Do not use ready-made dynamic data structures. 
    
    For example:
    ```
    in		      out
    4 3		      1 3 0
    2 4 5 7
    4 6 1

    ```

2. [__Dynamic loop buffer__](https://github.com/Gokert/algorithms/blob/main/programs/dynamic_loop_buffer.cpp)

    Implement a queue with a dynamic loopback buffer.
    Requirements: Queue must be implemented as a class.
    Input data format.
    The first line contains n commands. n ≤ 1000000.
    Each command is specified as 2 integers: a b.
    a = 1 - push front
    a = 2 - pop front
    a = 3 - push back
    a = 4 - pop back
    Add element commands 1 and 3 are specified with non-negative parameter b.
    For the queue, commands 2 and 3 are used. For the deck, all four commands are
    used. If the pop* command is given, then the number b is the expected value. If
    the pop command is called on an empty data structure, "-1" is expected. Output
    data format. It is required to print YES - if all the expected values matched.
    Otherwise, if at least one expectation was not justified, then print NO. Do not use 
    ready-made dynamic data structures. 
    
    For Example:
    ```
    in		out
    3
    3 44		YES
    3 50
    2 44

    2
    3 44		NO
    2 66
    ```

3. [__Heap__](https://github.com/Gokert/algorithms/blob/main/programs/heap.cpp)

    Process Scheduler
    The Technux operating system has a process scheduler.
    Each process is characterized by:

        -priority P
        -the time he has already worked t
        -the time it takes to complete the process T

    The process scheduler selects the process with the minimum value P * (t + 1),
    executes it for time P, and puts it back in the process queue. If the condition
    t >= T is met, then the process is considered completed and removed from the
    queue. The solution to the problem involves the use of a heap implemented as a
    template class. It is required to count the number of processor switches. The
    solution should support passing the compare function from outside. The heap must
    be dynamic. Do not use ready-made dynamic data structures. 
    
    For example:
    ```
    in		  out
    3		    18
    1 10
    1 5
    2 5
    ```

4. [__MSD__](https://github.com/Gokert/algorithms/blob/main/programs/msd.cpp)

    MSD for strings. Given an array of strings. The number of rows is not more
    than 105. Sort the array using the MSD bitwise sorting method by characters. The
    size of the alphabet is 256 characters. Last character of the string = '\0' .Do not use ready-made dynamic data structures.

    For example:
    ```
    in		out
    ab		a
    a		  aa
    aaa		aaa
    aa		ab
    ```

5. [__Double hashing__](https://github.com/Gokert/algorithms/blob/main/programs/double_hashing.cpp)

    Implement a multi-row data structure based on a publicly addressable dynamic hash table. Stored strings are non-empty and consist of lowercase Latin letters.
    The string hash function must be implemented using Horner's polynomial value calculation.
    The initial size of the table must be equal to 8. Perform rehashing when adding elements in the case when the table fill factor reaches 3/4.
    The data structure must support the operations of adding a string to a set, deleting a string from a set, and checking whether a given string belongs to a set.
    Use double hashing to resolve collisions.
    Requirements: It is forbidden to store pointers to the element descriptor in the table.

    Each line of the input defines one operation on the set. An operation entry consists of the type of operation followed by a space-separated line on which the operation is performed.
    The operation type is one of three characters:

        + means adding the given string to the set;
        - means deleting a string from the set;
        ? means checking whether the given string belongs to the set.

    When an element is added to a set, it is NOT GUARANTEED that it is not present in the set. When an element is removed from a set, it is NOT GUARANTEED that it is present in that set.
    Output format
    The program should output for each operation one of the two lines OK or FAIL, depending on whether the given word occurs in our set.

    For example:
    ```
    stdin         stdout
    + hello       OK
    + bye         OK
    ? bye         OK
    + bye         FAIL
    - bye         OK
    ? bye         FAIL
    ? hello       OK
    ```

6. [__Merge sort__](https://github.com/Gokert/algorithms/blob/main/programs/merge_sort.cpp)

    N segments are colored on the number line.
    The coordinates of the left and right ends of each segment [Li, Ri] are known.
    Find the length of the colored part of the number line. N ≤ 10000. Li, Ri are
    integers in the range [0, 109]. Input Format

    The first line contains the number of segments.
    Each subsequent line contains space-separated coordinates of the left and right
    ends of the segment. Output Format

    Print an integer — the length of the colored part.

    In the task, it is necessary to implement and use merge sort as a template
    function. The solution should support passing the compare function from outside.
    The total running time of the algorithm is O(n log n). Do not use ready-made dynamic data structures.

    For example:
    ```
    in		out
    3		5
    1 4
    7 8
    2 5
    ```

7. [__Level order__](https://github.com/Gokert/algorithms/blob/main/programs/level_order.cpp)

    Given a number N < 106 and a sequence of integers from [-231..231] of length
    N. It is required to build a binary tree given a naive insertion order. That is,
    when adding the next number K to the tree with root root, if root→Key ≤ K, then
    node K is added to the right subtree of root; otherwise, to the left subtree of
    root. Requirements: Recursion is not allowed. Solution must support function
    passing comparisons outside. Output the elements in level-order (by layers, “in
    width").
    Output the elements in level-order (by layers, “wide”).

    For example:
    ```
    in 		    out
    3
    2 1 3	    2 1 3

    4
    3 1 4 2	    3 1 4 2    
    ```

8. [__Quick select__](https://github.com/Gokert/algorithms/blob/main/programs/quick_select.cpp)

    You are given a set of integers from [0..10^9] of size n.
    Using the search algorithm for the kth order statistics, it is required to find
    the following set parameters:

        - 10% percentile
        - median
        - 90% percentile

    Requirements: additional memory: O(n).
    Average running time: O(n)
    There must be a separate partition function.
    Recursion is prohibited.
    The solution should support passing the compare function from outside.

    The Partition function should be implemented by traversing two iterators in the
    same direction. Description for the case of passing from the beginning of the
    array to the end: The base element is selected. The reference element changes
    with the last element of the array. During Partition operation, the beginning of
    the array contains elements that are not larger than the reference. Then there
    are elements that are strictly larger than the reference one. At the end of the
    array are the unconsidered elements. The last element is the pivot. The iterator
    (index) i points to the beginning of a group of elements strictly greater than
    the reference one. The iterator j is greater than i, the iterator j points to
    the first unexamined element. Algorithm step. The element pointed to by j is
    considered. If it is greater than the reference, then we shift j. If it is not
    greater than the reference, then we change a[i] and a[j] in places, shift i and
    shift j. At the end of the algorithm, we change the reference element and the
    element pointed to by the iterator i. Implement a “random element” pivot
    selection strategy. Implement the Partition function by going through two
    iterators from the end of the array to the beginning.

    For example:
    ```
    in                              out
    10                              2
    1 2 3 4 5 6 7 8 9 10            6
                                    10
    ```

9. [__Dijkstra algorithm__](https://github.com/Gokert/algorithms/blob/main/programs/Dijkstra_algorithm.cpp)

    "Cities".
    It is required to find the most profitable route between cities.
    Requirements: running time O((N+M)logN), where N is the number of cities, M is the known roads between them.
    Input data format.
    The first line contains the number N - the number of cities.
    The second line contains the number M - the number of roads.
    Each next line contains a description of the road (from where, where, travel time).
    The last line contains the route (from where and where to get to).
    Output data format.
    Print the length of the most profitable route.

    For example:
    ```
    in        out
    6         9
    9
    0 3 1
    0 4 2
    1 2 7
    1 3 2
    1 4 3
    1 5 3
    2 5 3
    3 4 4
    3 5 6
    0 2
    ```

10. [__B tree__](https://github.com/Gokert/algorithms/blob/main/programs/B_tree.cpp)
    Build a B-tree of minimum order t and output it layer by layer.
    Numbers in the range [0..23^2-1] are used as a key

    Requirements:

        - The B-tree must be implemented as a template class.
        - The solution must support the transfer of the compare function from the outside.

    For example:
    ```
    stdin                   stdout
    2                       3
    0 1 2 3 4 5 6 7 8 9     1 5 7
                            0 2 4 6 8 9
    ```

11. [__BFS__](https://github.com/Gokert/algorithms/blob/main/programs/BFS.cpp)

    The number of different paths.
    An unweighted undirected graph is given. A graph can have several shortest paths between some vertices. Find the number of different shortest paths between the given vertices.
    Requirements: O(V+E) complexity.
    Input format.
    v: number of vertices (max. 50000),
    n: number of ribs (max. 200000),
    n pairs of edge vertices,
    a pair of vertices u, w for the query.

    Output format.
    The number of shortest paths from u to w.

    For example:
    ```
    in          out
    4           2
    5
    0 1
    0 2
    1 2
    1 3
    2 3

    0 3
    ```

12. [__AVL__](https://github.com/Gokert/algorithms/blob/main/programs/AVL_tree.cpp)

    The solution should support passing the compare function from outside. 
    Given a number of N and N rows. Each line contains a command to add or remove
    natural numbers, as well as a request to get the k-th order statistics.
    The command to add the number A is given by the positive number A, the command to remove
    number A is given by a negative number “-A”. Request for k-th ordinal
    statistics is given by the number k. The required query execution speed is O(log n).

    For example:
    ```
    in            out 
    5             
    40 0          40
    10 1          40
    4 1           10
    -10 0         4
    50 2          50
    ```