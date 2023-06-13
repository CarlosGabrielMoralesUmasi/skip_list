## Skip List

This is an implementation of a Skip List data structure in C++. A Skip List is a data structure that allows for efficient insertion, search, and deletion operations with an average time complexity of O(log n), where n is the number of elements in the list.

### Classes

#### `nodo` Class

The `nodo` class represents a node in the Skip List. It contains the key-value pair and the level of the node. Each node has an array of pointers to the next nodes at different levels.

#### `SLiist` Class

The `SLiist` class represents the Skip List data structure. It contains the maximum level, current level, number of nodes, and the header node. It also has file input/output functionalities.

### Public Methods

- `SLiist(int nivel_max)`: Constructor to initialize the Skip List with the maximum level.
- `~SLiist()`: Destructor to clean up resources and close the file streams.
- `bool insertar_elemento(const K& key, const V& val)`: Inserts a key-value pair into the Skip List.
- `bool buscar(const K& key)`: Searches for a key in the Skip List.
- `bool borrar(const K& key)`: Deletes a key from the Skip List.
- `void mostrarSkip()`: Displays the contents of the Skip List.
- `void file()`: Dumps the data in memory to a file.
- `void cargar_file()`: Loads data from a file into the Skip List.
- `int size()`: Returns the number of nodes in the Skip List.

### Usage

1. Create an instance of the `SLiist` class, providing the maximum level for the Skip List.
2. Use the `insertar_elemento`, `buscar`, and `borrar` methods to perform operations on the Skip List.
3. Optionally, use the `mostrarSkip` method to visualize the contents of the Skip List.
4. Use the `file` method to save the data in memory to a file, and `cargar_file` method to load data from a file into the Skip List.

