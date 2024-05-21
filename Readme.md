# Project Conventions Guide

## Table of Contents

1. [Folder Structure](#folder-structure)
2. [Naming Conventions](#naming-conventions)
3. [Code Style](#code-style)
4. [Commenting Guidelines](#commenting-guidelines)
5. [Documentation](#documentation)
6. [Testing](#testing)
7. [Commit Message Convention](#commit-message-convention)

## Folder Structure

Organize your project files in a logical and consistent manner. Here's a suggested folder structure:

```bash
birthday_list_project/
├── include/ # Header files
│ ├── birthday_list.h
│ ├── friend.h
│ └── utils.h
├── src/ # Source files
│ ├── birthday_list.c
│ ├── friend.c
│ └── main.c
├── tests/ # Test files
│ ├── test_birthday_list.c
│ ├── test_friend.c
│ └── test_utils.c
├── docs/ # Documentation
│ ├── README.md
│ └── convention_guide.md
├── .gitignore # Git ignore file
└── Makefile # Makefile for building the project
```

## Naming Conventions

- **Directories**: Use lowercase words separated by underscores (`_`).
- **Files**: Use lowercase words separated by underscores (`_`). Header files should have a `.h` extension, and source files should have a `.c` extension.
- **Functions**: Use camelCase for function names (e.g., `addFriend`).
- **Variables**: Use descriptive names in camelCase (e.g., `friendCount`).
- **Constants**: Use uppercase words separated by underscores (e.g., `MAX_FRIENDS`).

## Code Style

- **Indentation**: Use 2 spaces per indentation level. Do not use tabs.
- **Braces**: Use Allman style for braces.

  ```c
  if (condition) {
      // Code block

  } else {
      // Code block

  }
  ```

- **Line Length**: Limit lines to 80 characters.
- **Spacing**: Use a single space around operators and after commas. No space between function names and the opening parenthesis. New line before closing parenthesis.

## Commenting Guidlines

- **File Headers**: Each file should begin with a comment block describing the file's purpose.
- **Function Headers**: Each function should have a comment block describing its purpose, parameters, and return value.
- **Inline Comments**: Use inline comments sparingly and only when necessary to explain complex logic.

```c
/**
 * Function: addFriend
 * -------------------
 * Adds a new friend to the list.
 *
 *  returns: void
 */

void addFriend() {
    // Code to add a friend

}

```

## Documentation

- **README.md**: Provide an overview of the project, how to build it, and how to use it.
- **Additional Documentation**: Use the docs/ folder for additional documentation.

## Testing

- Test Files: Place test files in the `tests/` directory.

## Commit Message Convention

- **Types**:
  > - `feat`: A new feature
  > - `fix`: A bug fix
  > - `docs`: Documentation on changes
  > - `style`: Changes that do not affect the meaning of the code (white-space, formatting, missing semi-colons, etc)
  > - `refactor`: A code change that neither fixes a bug nor adds a feature
  > - `test`: Adding missing or correcting existing tests
  > - `chore`: Changes to the build process or auxiliary tools and libraries such as documentation generation
