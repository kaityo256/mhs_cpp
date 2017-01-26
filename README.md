[Jananese](README_ja.md)/ English

# Enumerating Minimal Hitting sets

## Summary

Enumerate minimal hitting sets for given inputs.

## Usage

    $ make
    $ ./a.out inputfile

## Fileformat

Two types of formats are supported. We prepared two identical inputs with two different styles, `input1.dat` and `input2.dat`. The program identifies fileformat automatically.

### Bit array style

    $ cat input1.dat
    01101010
    11001010
    11000110
    00111010

    $ ./a.out input1.dat
    00000010
    00001100
    10001000
    10100000
    01001000
    01010000
    01100000

### Array style

    $ cat input2.dat
    7 6 4 2
    8 7 4 2
    8 7 3 2
    6 5 4 2

    $ ./a.out input2.dat
    2
    4 3
    8 4
    8 6
    7 4
    7 5
    7 6

## Preparing inputs

We prepare a ruby script `gen.rb` for input file generator.

    $ ruby gen.rb max n num

- `max` Maximum length of bit array.
- `n` n of max bits are on.
- `num` A number of input sets

For example,

   $ ruby gen.rb 8 3 4
   01101000
   10011000
   01010001
   10010010

It produces 4 sets of 8-bit arrays in which 3 of 8 bits are set.

## Reference

We adopt the reverse search algorithm. But the pruning method is slightly different from the following paper.

- Efficient algorithms for dualizing large-scale hypergraphs
    - Keisuke Murakami and Takeaki Uno
    - Discrete Applied Mathematics
    - Volume 170, 19 June 2014, Pages 83–94
    - http://dx.doi.org/10.1016/j.dam.2014.01.012
