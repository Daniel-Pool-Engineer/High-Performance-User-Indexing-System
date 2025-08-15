## 🌲AVL Tree Implementation

This project implements an AVL tree data structure with various operations including insertion, deletion, searching, and traversal.

## 📁Files

1. **AVL.h**: Header file containing the Node structure and AVLTree class declarations.
2. **AVL.cpp**: Implementation of AVL tree operations.
3. **helper.h**: Helper functions for input validation and output formatting.
4. **helper.cpp**: Implementation of helper functions.
5. **main.cpp**: Main program that reads input and executes commands.

## Features

### + − × ÷ AVL Tree Operations
- **Insert**: Adds a new node with name and UFID while maintaining AVL balance.
- **Remove**: Deletes a node by UFID while maintaining AVL balance.
- **Search**: Finds nodes by either name or UFID.
- **Traversals**:
  - Inorder
  - Preorder
  - Postorder
- **Other Operations**:
  - Print level count
  - Remove nth node in inorder traversal

### 👉 Input Validation
- Validates UFID (must be 8 digits)
- Validates names (must contain only alphabets and spaces)
- Validates commands and parameters

## ❓How to Use

1. Compile the program using a C++ compiler (e.g., g++).
2. Run the executable.
3. Input commands in the specified format.

### 🗣️Command Format

The program reads commands from standard input. The first line specifies the number of commands to follow. Each subsequent line is a command in one of these formats:

1. `insert "NAME" UFID`
2. `remove UFID`
3. `search NAME` or `search UFID`
4. `printInorder`
5. `printPreorder`
6. `printPostorder`
7. `printLevelCount`
8. `removeInorder N`

## Example Usage

Input:
```
6
insert "John" 12345678
insert "Jane" 87654321
search 12345678
printInorder
remove 12345678
printLevelCount
```

Output:
```
successful
successful
John
John, Jane
successful
1
```

## Implementation Details

- Uses standard AVL tree rotations (left, right, left-right, right-left) to maintain balance
- Implements recursive traversal methods
- Includes comprehensive input validation
- Memory management with proper destructor

## Dependencies

- C++11 or later
- Standard Library headers: `<iostream>`, `<sstream>`, `<queue>`, `<vector>`, `<string>`

## Notes

- All UFIDs must be unique 8-digit numbers
- Names can contain spaces but must be alphabetic only
- The tree automatically rebalances after insertions and deletions
