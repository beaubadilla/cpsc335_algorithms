<br />
<p align="center">
  <h1 align="center">Algorithms</h1>

  <p align="center">
    Implementing algorithms in C++17.<br/>
    Projects for <a href="http://www.fullerton.edu/">Cal State Fullerton</a>'s Algorithm's course(CPSC 335).
    <br />
    <a href="https://github.com/beaubadilla/cpsc449_backend_engineering/issues">Report Bug or Request Feature</a>
  </p>
</p>

## Table of Contents

* [About these Projects](#about-these-projects)
  * [Technologies](#technologies)
  * [Code Snippets](#code-snippets)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [License](#license)
* [Contact](#contact)

## About these Projects
<!-- time complexity, space complexity, sorting algorithms, search algorithms -->

* **project-1-beaub-project1**: Sorting Algorithms: Lawnmower and Left-to-Right
* **project-2-beaub-project2**: Longest Decreasing Subsequence
* **project-3-beaub-project3**: Cuckoo Hashing
* **project-4-beaub-project4**: Exhaustive Optimization and Dynamic Programming


### Technologies
Languages: C++17

Text Editor: [Atom](https://atom.io/)

### Code Snippets
/project-1-beaub-project1/disks.hpp: Implementation of left_to_right(aka bubble sort) function
```cpp
sorted_disks sort_left_to_right(const disk_state& before) {
  size_t swapCount = 0, vectorSize = before.total_count(), maxIterations = vectorSize / 2;
  disk_state after = before;

  for (size_t i = 0; i < maxIterations; i++) {
    for (size_t j = i + 1; j < vectorSize; j += 2) {
      disk_color currentColor = after.get(j);
      if (currentColor == DISK_DARK) {
        size_t swapIndex = j - 1;
        after.swap(swapIndex);
        swapCount++;
      }
    }
  }
  return sorted_disks(after, swapCount);
}
```

/project-2-beaub-project2/subsequence.hpp: Helper function to check if vector is in descending order
```cpp
bool is_decreasing(const sequence& A) {
  for (size_t i = 1; i < A.size(); ++i) {
      if (A[i-1] <= A[i]) { return false; }
  }
  return true;
}
```

/project-3-beaub-project3/cuckoo.cxx: Part of the hashing algorithm logic
```cpp
// Get the value in the current "nest" i.e. kick out value to move
strcpy(temp, t[pos][index]);
// Store new value into the current "nest" i.e. put in new value
strcpy(t[pos][index], temp_s);
// Move the "kicked out" value into the 'temp_s' var
strcpy(temp_s, temp);

// Switch index value to use the other hash function and get result
index = index ? 0 : 1;
pos = f(temp_s, index);
counter ++;
```

/project-4-beaub-project4/crossing_algs.hpp: Core logic of the dynamic programming version
```cpp
for (size_t i = 0; i <= setting.rows()-1;i++) {
  for (size_t j = 0; j <= setting.columns()-1; j++) {
    if (i == 0 && j == 0) { continue; }
    if (setting.get(i,j) == CELL_THICKET) {
      A[i][j] = 0;
      continue;
    }
    int from_above = 0, from_left = 0;
    if (i > 0 && A[i-1][j] != 0) {
      from_above = A[i-1][j];
    }
    if (j > 0 && A[i][j-1] != 0) {
      from_left = A[i][j-1];
    }
    A[i][j] = from_above + from_left;
  }
}
```


## Getting Started

### Prerequisites

Linux Distribution: [Ubuntu](https://ubuntu.com/)(*Recommended*)

C++ Compiler: [GCC](https://gcc.gnu.org/)(*Recommended*)

### Installation

1. Clone the repo
```sh
git clone https://github.com/beaubadilla/cpsc335_algorithms.git
```
2. Follow the README.md for each individual part.

## License
[MIT](https://choosealicense.com/licenses/mit/)

## Contact

Beau Jayme De Guzman Badilla - beau.badilla@gmail.com - [LinkedIn](https://www.linkedin.com/in/beau-jayme-badilla/)


