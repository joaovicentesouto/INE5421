# INE5421
Formal Languages and Compilers - INE5421 - Federal University of Santa Catarina

## Index:
* [Description](#description)
* [Assignment](#assignment)
* [How to compile](#howtocompile)
* [Credits](#credits)

# Description

This repository aims to develop an application for creating, modifying and manipulating the manipulation of formal devices studied in the discipline of Formal Languages and Compilers.

More information in pdf (class_work_description)

## Assignment

### Definition:
Prepare an application to handle Finite Automaton (FA), Regular Grammar (RG) and Regular Expression (RE), which involves the following operations / functionalities:
* Ed, read and write RG and RE.
* Conversion of RE to FA using the Simone algorithm.
* Transformation from RG to FA and vice versa.
* Determination and Minimization of FA.
* Obtaining FA's that represent the intersection, difference and reverse of LR's (expressed by RG, RE and FA).
* Obtaining RG resulting from union, concatenation and closure of RG's.
* Recognition of sentences accepted by an FA and enumeration of sentences of size "n" accepted by him.

### Comments:
* For the edition and reading of RG and RE the standards seen in class should be used.
    * Examples: RG: S-> aS | a and RE: a * (b? C | d) *.
* Present the AFs in the form of transition tables.
* Alphabet symbols must be size 1 and may be limited to lowercase letters and digits.
* Use & to represent epsilon.
* The edition of the productions of the RG's must be textual (direct); that is, there is no need for explicit definition of Vn and Vt and the initial symbol will be first defined Vn;
* All AFs involved (resulting and intermediate) in one operation / check shall be viewable and reusable in other operations / verifications.
* In addition to the correction, aspects of usability and robustness will be evaluated.

## How to compile

### Dependencies:
* [Cmake](https://cmake.org/) (>= 3.5.1)

[![how-to-compile](https://asciinema.org/a/Q7Mnh9KIzoaqwnB4mGWTcTYPm.png)](https://asciinema.org/a/Q7Mnh9KIzoaqwnB4mGWTcTYPm?autoplay=1)

# Credits

* [João Vicente Souto](https://github.com/joaovicentesouto)
* [Bruno Izaias Bonotto](https://github.com/Bonotto)