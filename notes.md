# General notes
- You lack a readme file that explains briefly the aim of your project, how to compile and what to expect
- `.vscode` folder should be in the gitignore
- `Makefile` is not compatible with modules, check the fix
- Standtard output of the executable is not very significant, it is diffucult to understand what happens

# Code
## Major
- the function to read from a file `read_leos` should be generic not specific for a fixed dataset
- `using namespace std;` is bad practice, especially if the scope is not limited
- random number should be generated like follows https://en.cppreference.com/w/cpp/numeric/random, not in C-style with `rand()`
- sometimes you pass values by copy instead of (const) reference
- data structured could have been devised in a more clever way
- no method has been declared `const` when many could have been
- power with integer exponent should not use `std::pow`
- there is no parallel version
- it is very nice to have a plot, but you should decouple the features of plotting and actually running the algorithm
- in some occasion could use `emplace_back` instead of `push_back`

## Minor
- having a header file with only the list of includes, like `kross.hpp` is not standard practice and it does not seem to have a particular aim
- `read_leos` would be sintactically more significant if it were to return a `std::vector` instead of modifying it when passed by reference. Thanks to RVO there would't even be an extra copy.

