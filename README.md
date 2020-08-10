# KiCAD Module Checker
Reads a module file to check if PAD numbering is correct. The following are asserted:

* From 1 to the higgest PAD number, are all present?
* Any of the PADs are repeated?

## Building
Being a single C file no need for a Makefile, use GCC:

```
$ gcc -o checkPads checkPads.c
```

## Use

```
$ checkPads [-h] {file name} [-0|-v|-h]
```

* **{file name}**: *kicad_mod* to be verified (mandatory);
* **-h**: Display help menu;
* **-0**: Lowest PAD number required starts at zero;
* **-v**: Verbose mode.

## Future Implementations

* Alphanumeric PADS, *eg.* A1, C11, ...;
* Positionning and pitch verification;
* Separation and isolation rules.

## Handbonning capabilities

None!
