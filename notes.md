# General notes
- You lack a readme file that explains briefly the aim of your project, how to compile and what to expect
- `.vscode` folder should be in the gitignore

# Code
## Major
- sometimes you pass values by copy instead of (const) reference
- no method has been declared `const` when many could have been
- power with integer exponent should not use `std::pow`
- in some occasion could use `emplace_back` instead of `push_back`
- Would have been nice to support clusters in n dimesions

## Minor
- improper way of including headers

