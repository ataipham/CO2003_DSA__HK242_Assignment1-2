# CO2003_DSA__HK242_Assignment1-2
Implement data structures header files and application/Construct Huffman Tree to compress data by using C++

You've got it. Separating the provided interfaces from your own implementations is a great way to clarify the project's structure. Here is the updated README with that change.

DSA Inventory Management System
This repository contains the source code for an assignment for the Data Structures and Algorithms (DSA) course. The core of this project is the from-scratch implementation of several fundamental data structures based on PROVIDED abstract interfaces. These structures are then used to build a comprehensive inventory management application, complete with data compression capabilities using an N-ary Huffman tree.

🚀 Features
Custom Data Structure Implementation:
  - XArrayList: A dynamic array-based list implementation.
  - DLinkedList: A doubly linked list implementation.
  -xMap: A hash map (hash table) with collision handling via separate chaining (using DLinkedList).
  -Heap: A generic heap data structure.

Inventory Management Application:
  - Manages products with various attributes, names, and quantities.
  - Provides functionalities to add, remove, and update product information.
  - Supports querying products based on attributes and quantities.
  - Includes advanced features like merging inventories, splitting inventories, and removing duplicate products.

N-ary Huffman Tree for Data Compression:
  - Implements an N-ary Huffman tree to compress and decompress inventory data.
  - HuffmanTree class for building the tree and generating codes.
  - InventoryCompressor class to apply Huffman coding to the inventory data.

📜 Code Overview
This project is divided into the abstract interfaces that were provided and the concrete classes that were implemented to fulfill the assignment requirements.
**Provided Interfaces**
- These are the abstract base classes that define the required API for each data structure.
  + IList<T> (IList.h): Defines the standard interface for list data structures, including methods for adding, removing, and accessing elements.
  + IMap<K, V> (IMap.h): Defines the interface for a map (or dictionary), specifying operations like put, get, and remove for key-value pairs.
  + IHeap<T> (IHeap.h): Defines the API for a heap data structure, outlining core functionalities such as push, pop, and peek.

**Implemented Data Structures**
These files contain the concrete implementations of the provided interfaces.
  - XArrayList<T> (XArrayList.h): Implements the IList interface using a dynamic array. It automatically handles resizing to accommodate a growing number of elements.
  - DLinkedList<T> (DLinkedList.h): Implements the IList interface using a doubly linked list. Each Node in the list contains the data element and pointers to the previous and next nodes.
  - Heap<T> (Heap.h): Implements the IHeap interface using a dynamic array to logically represent a complete binary tree. It maintains the heap property through reheapUp and reheapDown operations.
  - xMap<K, V> (xMap.h): Implements the IMap interface as a hash map. It uses an array of DLinkedLists to handle hash collisions via the separate chaining method.

Application Logic
- inventory.h: This file leverages the data structures you implemented to build the inventory application.
    + List1D<T> & List2D<T>: These are wrapper classes that use your list implementations (XArrayList or DLinkedList) to create one-dimensional and two-dimensional data containers. 
    + InventoryManager: This is the primary application class. It uses List1D and List2D objects to store and manage all inventory data, including product names, quantities, and attributes.
    + 
- inventory_compressor.h: This file contains the logic for compressing and decompressing inventory data using Huffman coding.
    + HuffmanTree<treeOrder>: A template class that constructs an N-ary Huffman tree from character frequencies. It handles the creation of dummy nodes to ensure the tree is built correctly and provides methods to build the tree, generate encoding tables, and decode compressed strings.
    
    + InventoryCompressor<treeOrder>: This class uses the InventoryManager to calculate character frequencies from product data. It then uses the 
    HuffmanTree to build an encoding table (huffmanTable) and provides methods to encode product information into a compressed string and decode it back to its original format. 


## Acknowledgments
  The structure and prose of this README file were refined with the assistance of Gemini.
