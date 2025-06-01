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

The truncated power series algebra (TPSA), or differential algebra (DA), is a well-established and widely used method in particle accelerator physics. It is typically used to generate high-order map of a nonlinear dynamical system but is also used in symplectic tracking, normal form analysis, verified integration, global optimization, fast multipole method, etc.  This package is the first  to carry out symbolic DA-based calculations. Symbolic DA makes it possible to trace the contribution of initial conditions to the final result in a DA calculation process and improve the efficiency of  repeated DA calculations, which potentially broadens the usage of DA. 

# Background

The fundamental concept in DA is the DA vector, which can be considered as the Taylor expansion of a function at a specific point from a practical  perspective.

Considering a function $f(\mathbf{x})$ and its Taylor expansion $f_{\mathrm{T}}(\mathbf{x}_0)$  at the point $\mathbf{x}_0$ up to order $n$, we can define  the equivalence relation between the Taylor expansion and the DA vector as follows

$$ [f]_n = f_{\mathrm{T}}(\mathbf{x}_0) = \sum {C_{n_1,n_2, ..., n_v}} \cdot d_1^{n_1} \cdot \dots \cdot d_v^{n_v}, $$ where $\mathbf{x} = (x_1, x_2, \dots, x_v)$, and $n \ge n_1 + n_2 + \dots + n_v$. Here $d_i$ is a special number: it represents a small variance in $x_i$. To add two DA vectors, we simply add  the coefficients of the like terms. To multiply two DA vectors, we multiply each term in the first one with all the terms in the second one and  then combine like terms while ignoring all terms above order $n$. Given two DA vectors $[a]_n$ and $[b]_n$ and a scalar c, we have

\begin{eqnarray}
[a]_{n}+[b]_{n} & := & [a+b]_{n},\nonumber \\
c\cdot[a]_{n} & := & [c\cdot a]_{n},\label{eq:addmlt}\\
{}[a]_{n}\cdot[b]_{n} & := & [a\cdot b]_{n}.\nonumber 
\end{eqnarray}

According to the fixed point theorem  [@AIEP108book], the inverse of a DA vector that is not infinitely small can be calculated in a finite number of iterations. 

The derivation operator $\partial_v$ with respect to the $v^{\mathrm{th}}$ variable and its inverse operator $\partial^{-1}v$ can be defined and carried out on a term by term basis on $[a]n$. Once the fundamental operators are defined, the DA vector can be used in calculations just as a number.

The symbolic DA combines DA with symbolic calculation. Any coefficient of a Symbolic DA (SDA) vector is an explicit expression of the symbols in lieu of a number.  

# Statement of need
DA was used in particle beam dynamic analysis in the 1980s and was gradually extended to other fields. DA provides powerful analyzing tools [@caprimap; @monthnf], for a dynamic system. It is also used in various numerical algorithms [@rdaint; @makino2005verified; @FMMCPO2010].   DA tools are available in particle accelerator simulators [@COSYCAP04; @grote2003mad; @MADX; @forest2002introduction], or as stand-alone libraries  [@massari2018differential; @DACE; @zhang2024cpptpsa]. All of them only perform numerical DA calculation. This library is the first and currently the only one that carries out symbolic DA calculations. 

We developed SDA to improve the efficiency of repetitive DA processes. By performing the computation once with SDA, we obtain an explicit expression for how the final DA vector depends on the initial inputs. Evaluating this expression—rather than rerunning the full DA process for each new input—significantly reduces computation time [@zhang2025Boosting]. SDA also provides an efficient method for computing higher‐order derivatives of any given function.

# Features

This library performs symbolic DA calculations. It is based on the numerical DA library, cppTPSA [@zhang2024cpptpsa]. All the DA calculations are carried out on symbols using exactly the same algorithms in cppTPSA by employing the SymEngine library [@Fernando2024SymEngine]. Users can compile the source code into a static or shared library and install it on their system. The main features of this library are listed as follows. 

1. Define the SDA vector data type and overload common math operators/functions for it. 
2. Support the composition, derivation, and inverse derivation on SDA vectors. 
4. Obtain the explicit expression of a partial derivative for a function. 
4. Obtain the callable function on the symbols from an SDA.
7. Obtain the numerical DA from an SDA by assigning values to all the symbols.

The following code shows how to calculate the SDA vector of $1/\sqrt{x^2+y^2}$ up to the third order.   After initializing a memory pool for 400 SDA vectors and defining the symbols, $x$ and $y$, the SDA vector $f$ is calculated and printed. The value of the SDA vector is shown in \autoref{fig:sda}. The first column shows the orders of the bases, the second column displays the index of each term in the SDA vector, and the last column lists the coefficient of each term as a function of $x$ and $y$. 

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

