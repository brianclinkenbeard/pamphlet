# pamphlet
[![Build Status](https://travis-ci.com/brianclinkenbeard/pamphlet.svg?token=YYjD2LYA5ynr5RiEDZiN&branch=master)](https://travis-ci.com/brianclinkenbeard/pamphlet)

## Coding Standards

### Namespaces
* use scope resolution operator (no `using namespace std`)

### Variables
* camelCase variable names
* use descriptive names

### Functions
* camelCase
* opening bracket on following line for functions only

Bracket examples:
```
void func()
{
```

```
if (boolVal) {
```

### Classes
* start with a capital letter
* follow encapsulation paradigm (keep data members and helper functions private)

### Misc.
* include guards in header file
* test build and features before pushing to avoid compilation errors or crashes
* verify data from file after implementation
* use descriptive commit messages
