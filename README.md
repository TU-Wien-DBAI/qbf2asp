# README
The QBF2ASP project implements several ASP encodings for 2-QBF formulas and 3-QBF formulas. By piping the output produced by the encodings into an ASP grounder and an ASP solver a QBF-solver is obtained.

# Compilation and Installation

Before the executable file can be generated you need to make sure the
required libraries are installed.

## Dependencies
The compilation requires the libraries `liblogichelpers` and `liblogicparsers`.
These libraries can be downloaded [here](). See their respective README files for further information about their installation.

## Compilation

Once these dependencies are installed we can compile the sources to generate the `qbf2asp` executable. Use the following command to configure the project.
```
sh autogen.sh && ./configure
```
Finally run `make` to start the compilation and then `sudo make install` to install the executable.

If the previous steps were successful a file named `qbf2asp` was generated. Use `qbf2asp` to run the executable file. The flag `-h` prints information
the command line interface of `qbf2asp`.

# ASP encodings

Currently three encodings are implemented. These are the ICLP-2016 encoding, the
Arithmetics-based encoding and the Saturation based encoding. The saturation based encoding is the classical encoding for 2-QBF formulas. It generates a fixed set of rules and a set of facts that depends on the given 2-QBF instance. The ICLP-2016 and Arithmetics-based encodings generate a set of facts and rules that depend on the given instance. One of this rules is called the main rule because its size grows as the size of the instance grows. Therefore these two encodings are also sometimes called large rule encodings.

# Input format

The input format accepted by `qbf2asp` is the QDIMACS format. This format is an extension of the DIMACS format which allows the specification of prenex QBFs in conjunctive normal form. A description of the QDIMACS format can be found [here](http://www.qbflib.org/qdimacs.html). The QDIMACS encoding of the 3-QBF ∃x<sub>6</sub>∀x<sub>5</sub>∃x<sub>4</sub>x<sub>3</sub>x<sub>2</sub>x<sub>1</sub>(¬x<sub>1</sub>∨x<sub>2</sub>)∧(x<sub>2</sub>∨¬x<sub>3</sub>∨¬x<sub>4</sub>)∧ (x<sub>5</sub>∨x<sub>2</sub>∨x<sub>1</sub>∨¬x<sub>6</sub>)∧(x<sub>2</sub>∨x<sub>3</sub>∨¬x<sub>5</sub>∨x<sub>1</sub>∨x<sub>6</sub>) is given below:
```
p cnf 6 4
e 6        0
a 5        0
e 1 2 3 4  0
-1  2      0
 2 -3 -4   0
5 2 1 -6   0
2 3 -5 1 6 0
```

# Output format

The output produced by `qbf2asp` is an ASP program that is compatible with gringo, clasp and clingo.

# Examples

The command below outputs the ICLP-2016 encoding of the 2-QBF ∀x<sub>1</sub>∃x<sub>2</sub>(x<sub>1</sub> ∨ x<sub>2</sub>).

```
qbf2asp -a1
p cnf 2 1
a 1 0
e 2 0
1 2 0
```
