---
title: 'SDA: a symbolic differential algebra package in C++'
tags:
  - differential algebra
  - truncated power series algebra
  - symbolic calculation
  - higher-order derivatives
  - accelerator physics
  - astronomy
  - beam dynamics
authors:
  - name: He Zhang^[corresponding author] # note this makes a footnote saying 'co-first author'
    orcid: 0000-0001-7701-4118
    affiliation: 1 
affiliations:
 - name: Thomas Jefferson National Accelerator Facility, Newport News, VA 23606, USA
   index: 1
date: 21 October 2024
bibliography: paper.bib
---

# Summary

Truncated Power Series Algebra (TPSA), or Differential Algebra (DA), is a well-established tool in accelerator physics, commonly used for generating high-order maps of dynamic systems, as well as in symplectic tracking, normal form analysis, verified integration, optimization, and fast multipole methods. This package is the first to perform symbolic DA computations, enabling  traceability of initial condition contributions and runtime reduction for repeated DA calculations, potentially expanding DA's applications.

# Background

The fundamental concept in DA is the DA vector, which can be considered as the Taylor expansion of a function at a specific point from a practical  perspective.

Considering a function $f(\mathbf{x})$ and its Taylor expansion $f_{\mathrm{T}}(\mathbf{x}_0)$  at the point $\mathbf{x}_0$ up to order $n$, we can define  the equivalence relation between the Taylor expansion and the DA vector as:

$$ [f]_n = f_{\mathrm{T}}(\mathbf{x}_0) = \sum {C_{n_1,n_2, ..., n_v}} \cdot d_1^{n_1} \cdot \dots \cdot d_v^{n_v}, $$ where $\mathbf{x} = (x_1, x_2, \dots, x_v)$, and $n \ge n_1 + n_2 + \dots + n_v$. Here $d_i$ is a special number: it represents a small variance in $x_i$. To add two DA vectors, we simply add  the coefficients of the like terms. To multiply two DA vectors, we multiply each term in the first with all the terms in the second and then combine like terms, ignoring all terms above order $n$. Given two DA vectors $[a]_n$ and $[b]_n$ and a scalar c, we have

\begin{eqnarray}
[a]_{n}+[b]_{n} & := & [a+b]_{n},\nonumber \\
c\cdot[a]_{n} & := & [c\cdot a]_{n},\label{eq:addmlt}\\
{}[a]_{n}\cdot[b]_{n} & := & [a\cdot b]_{n}.\nonumber 
\end{eqnarray}

According to the fixed point theorem  [@AIEP108book], the inverse of a DA vector that is not infinitely small can be calculated in a finite number of iterations. The derivation operator $\partial_v$ with respect to the $v^{\mathrm{th}}$ variable and its inverse operator $\partial^{-1}v$ can be carried out on a term-by-term basis on $[a]_n$. A DA vector can be used in calculations just as a number.

The symbolic DA combines DA with symbolic calculation. Any coefficient of a Symbolic DA (SDA) vector is an explicit expression of the symbols in lieu of a number.  

# Statement of need
DA has been used in particle beam dynamic analysis since the 1980s and gradually extended to other fields. DA provides powerful tools [@caprimap; @monthnf] for analyzing dynamic systems. It is also used in various numerical algorithms, e.g., verified integration  [@rdaint], global optimization [@makino2005verified], and fast multipole method [@FMMCPO2010].   DA tools are available in particle accelerator simulators [@COSYCAP04; @grote2003mad; @MADX; @forest2002introduction] or as stand-alone libraries  [@massari2018differential; @DACE; @zhang2024cpptpsa]. All of them only perform numerical DA calculations. This is the first and only library for symbolic DA calculations. 

The SDA package can be used in several important ways. First, in high-performance computing scenarios involving differential algebra (DA), it can produce explicit expressions for the results of complex DA calculations. These expressions enable the generation of highly efficient code that eliminates the need for runtime DA computations, resulting in significant performance improvements [@zhang2025Boosting]. This was the original motivation for developing the package. Second, as a tool for dynamic analysis, it supports parametric and time-dependent studies by allowing DA maps to vary with symbolic parameters. This makes it possible to analyze how system behavior changes with evolving settings—something difficult to achieve with numerical DA alone. Finally, it provides a new way to obtain symbolic expressions of higher-order derivatives by following the algorithmic differentiation process, thus bridging the gap between symbolic and numerical approaches  [@zhang2025higher].



# Features

This library is based on the numerical DA library, cppTPSA [@zhang2024cpptpsa]. All the DA calculations are carried out on symbols using exactly the same algorithms in cppTPSA by employing the SymEngine library [@Fernando2024SymEngine]. Users can compile the source code into a static or shared library and install it on their system. The main features of this library are:

1. A custom SDA vector type with overloaded math operations, including composition, differentiation, and inverse.
2. Extraction of explicit expressions for partial derivatives.
3. Generation of callable functions from an SDA vector.
4. Conversion of symbolic SDA to numerical DA.

The following code shows how to calculate the SDA vector of $1/\sqrt{x^2+y^2}$ up to the third order.   After initializing a memory pool for 400 SDA vectors and defining the symbols, $x$ and $y$, the SDA vector $f$ is calculated and shown in \autoref{fig:sda}. The orders of the bases, the index of each term, and the coefficient of each term as a function of $x$ and $y$ are displayed in columns. 

```c++
#include <iostream>
#include <sda.h>
typedef SymbDA::DAVector SDA;
using SymEngine::Expression;

int main() {
    int order{3}, dim{2}, pool{400};
    SymbDA::da_init(order, dim, pool);
    auto& sda = SymbDA::da;
    Expression sx("x"), sy("y");
    SDA f = 1/sqrt((sx+sda[0])*(sx+sda[0]) + (sy+sda[1])*(sy+sda[1]));
    std::cout<<f;
}
```

![Example code output.\label{fig:sda}](fig_sda.png)

 

# Verification

This library has been verified with the numerical DA library, cppTPSA, by assigning values to all the symbols in an SDA vector and checking it against direct calculation using cppTPSA. As an example, For example, \autoref{fig:veri_sda}  and \autoref{fig:veri_da} show the DA vector $v = \exp(1.5926 + d_1^2 + 5.3897\cdot d_2)$ to the fifth order, calculated by SDA and DA respectively. We calculate the relative error for each non-zero coefficient. This procedure is repeated 1,000 times for all the math functions in the SDA lib and the absolute values of the relative errors are all below $1\times 10^{-15}$. 




![SDA output.\label{fig:veri_sda}](fig_veri_sda.png)

![cppTPSA output.\label{fig:veri_da}](fig_veri_da.png)




# Acknowledgements

This material is based upon work supported by the U.S. Department of Energy, Office of Science, Office of Nuclear Physics under contract DE-AC05-06OR23177.



# References

