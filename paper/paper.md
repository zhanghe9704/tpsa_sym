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

The truncated power series algebra (TPSA), also referred to as differential algebra (DA), is a well-established and widely used method in particle accelerator physics. It is typically used to generate high-order map of a nonlinear dynamical system. The DA calculation is based on the DA vector that can be practically viewed as the Taylor expansion  of a given function at a specific point up to a predetermined order $n$. Besides map generation, the DA/TPSA technique can also be used in symplectic tracking, normal form analysis, verified integration, global optimization, fast multipole method, etc.  This package is the first one to combine the DA/TPSA algorithm with symbolic calculation, and it allows users to carry out symbolic DA-based calculations. The coefficient of any element in a symbolic DA vector is an explicit expression of preselected symbols, in lieu of a number in a numerical DA vector. This capability makes it possible to trace the contribution of initial conditions to the final result in a DA calculation process and improve the efficiency of  repeated DA calculations. It also provides a method to obtain explicit expressions for the higher-order derivatives of an arbitrary function. 

# Background

In the following, we give a very brief introduction to (symbolic) TPSA/DA from a practical computational perspective. Please refer to [@AIEP108book] and [@chao2002lecture]  for the complete theory with more details.

The fundamental concept in DA is the DA vector. To make this concept easier to understand, we can consider a DA vector as the Taylor expansion of a function at a specific point.  

Considering a function $f(\mathbf{x})$ and its Taylor expansion $f_{\mathrm{T}}(\mathbf{x}_0)$  at the point $\mathbf{x}_0$ up to order $n$, we can define  the equivalence relation between the Taylor expansion and the DA vector as follows

$$ [f]_n = f_{\mathrm{T}}(\mathbf{x}_0) = \sum {C_{n_1,n_2, ..., n_v}} \cdot d_1^{n_1} \cdot \dots \cdot d_v^{n_v}, $$ where $\mathbf{x} = (x_1, x_2, \dots, x_v)$, and $n \ge n_1 + n_2 + \dots + n_v$. Here $d_i$ is a special number: it represents a small variance in $x_i$. Generally, one can define a DA vector by directly setting values to respective terms, without defining the function $f$. The addition and multiplication of two DA vectors can be defined straightforwardly. To add two DA vectors, we simply add  the coefficients of the like terms. To multiply two DA vectors, we multiply each term in the first one with all the terms in the second one. We  then combine like terms while ignoring all terms above order $n$. So, given two DA vectors $[a]_n$ and $[b]_n$ and a scalar c, we have the following formulae:

\begin{eqnarray}
[a]_{n}+[b]_{n} & := & [a+b]_{n},\nonumber \\
c\cdot[a]_{n} & := & [c\cdot a]_{n},\label{eq:addmlt}\\
{}[a]_{n}\cdot[b]_{n} & := & [a\cdot b]_{n},\nonumber 
\end{eqnarray}

According to the fixed point theorem  [@AIEP108book], the inverse of a DA vector that is not infinitely small can be calculated in a finite number of iterations. 

The derivation operator $\partial_v$ with respect to the $v^{\mathrm{th}}$ variable can be defined as 

$$ \partial_v[a]_n = \left[ \frac{\partial}{\partial x_v} a \right]_{n-1}, $$

which can be carried out on a term by term basis on $[a]_n$. The operator $\partial_v$ satisfies the chain rule:

$$ \partial_v([a]\cdot [b]) = [a]\cdot (\partial_v [b]) + (\partial_v [a])\cdot [b]. $$

The inverse operator $\partial^{-1}_v$ can also be defined and applied easily on a term-by-term basis. Once the fundamental operators are defined, the DA vector can be used in calculations just as a number.

The symbolic DA/TPSA combines the DA/TPSA with symbolic calculation. Exactly the same DA/TPSA algorithms are implemented on symbols rather than numbers. Compared to the numerical DA/TPSA, the only difference is any coefficient of a Symbolic DA (SDA) vector is an explicit expression of the symbols in lieu of a number.  

# Statement of need
 DA/TPSA methods for particle beam dynamic analysis were developed in the 1980s. Since then,  their application has been gradually extended to other fields. DA provides powerful analyzing tools, *i.e.*, map generation,  symplectic tracking [@caprimap], and normal form analysis [@monthnf], for a dynamic system. In addition, it can also be used in verified integration [@rdaint], global optimization [@makino2005verified], and fast multipole method for pairwise interactions between particles [@FMMCPO2010].   DA tools are available in several popular programs for particle accelerator design and simulations, such as COSY Infinity [@COSYCAP04], MAD-X [@grote2003mad; @MADX], and PTC [@forest2002introduction]. Stand-alone DA/TPSA libraries include DACE [@massari2018differential; @DACE] and cppTPSA/pyTPSA [@zhang2024cpptpsa]. All of them only perform numerical DA calculation. To the best of our knowledge, this library is the first and currently the only one that can carry out symbolic DA calculations. 

We developed SDA to improve the efficiency of repetitive DA processes. In some scenarios, we need to implement a complicated DA method repetitively on the same object with different initial conditions, *i.e.*, different positions and velocities of particles.  Some DA calculations are relatively slow. For example, calculating the inverse of a DA vector includes iterations and the number of iterations is determined by the order of the DA vector. This limits the use of DA in high-efficiency simulations. Using numerical DA, we lose track of the initial conditions in the calculation and have to repeat the same DA calculation for each case. Using symbolic DA, we only need to carry out the DA calculation once to obtain the final result as explicit expressions of the initial conditions. We then use those expressions on all the different initial conditions. By reducing the calculation on DA vectors to calculation on numbers, we can significantly enhance the efficiency. 

SDA can also be used in higher-order derivative calculation. DA calculates the Taylor expansion of an arbitrary function. The partial derivatives of that function can be extracted from the coefficients of its Taylor expansion. Numerical DA calculates all the derivatives up to a predetermined order at a specific point. It is not possible to calculate a specific derivative without calculating the others. SDA provides explicit expressions for all the derivatives, allowing to calculate any specific derivative at any point. Calculating the derivatives using the expressions from SDA is usually faster. If only a few derivatives are needed, SDA can save even more time by avoiding redundant calculations on unnecessary derivatives.

# Features

This library performs symbolic DA/TPSA calculations. It is based on the numerical DA library, cppTPSA [@zhang2024cpptpsa]. All the DA calculations are carried out using exactly the same algorithms in cppTPSA, except they are implemented on symbols by employing the SymEngine library [@Fernando2024SymEngine], rather than numbers. Users can compile the source code into a static or shared library and install it on their system. The main features of this library are listed as follows. 

1. An SDA vector data type is defined and the commonly used math operators are overloaded for it, so that users can use an SDA vector as simple as a normal number in calculations. 
2. Common mathematical functions are overloaded for the SDA vector data type. (A list of the functions supported can be found in the README file of the repository)
3. Support the composition of SDA vectors. 
4. Support derivation and inverse derivation of a SDA vector.
5. Obtain the explicit expression of a partial derivative from a Taylor Expansion, *i.e.*, an SDA vector. 
6. Obtain the callable function on the symbols from an SDA.
7. Obtain the numerical DA from an SDA by assigning values to all the symbols.

The following C++ code shows an example of a simple SDA calculation. This code calculates the SDA vector of $1/\sqrt{x^2+y^2}$ up to the third order.   First we initialize a memory pool that can contain 400 two-dimensional DA vectors up to the third order, which is much larger than what is needed for this calculation. Then we define the symbols, $x$ and $y$. Finally we calculate the SDA vector and print it out. The value of the SDA vector is shown in \autoref{fig:sda}. The first column shows the orders of the bases, the second column displays the index of each term in the SDA vector, and the last column lists the coefficients of each term. Each coefficient of the SDA vector is an explicit expression in x and y. The number 13 in "V [13]" means the SDA vector is saved in the 13th slot in the memory pool. "[ 10 / 10 ]" means the SDA has 10 non-zero elements and the total number of elements is also 10. This indicates a full vector. For a sparse vector, the first number is smaller than the second number because some elements are zero and not shown. More examples can be found in the repository.  

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

This library has been verified with the numerical DA library, cppTPSA, by assigning values to all the symbols in an SDA vector, which results in a numerical DA vector. This vector is then checked against direct calculation using cppTPSA. For example, we calculate an SDA vector $v_1 = \exp(x + d_1^2 + y\cdot d_2)$, in which $x$ and $y$ are symbols and $d_1$, $d_2$ are the bases of the SDA vector. By setting $x=1.5926$ and $y=5.3897$, we obtain the numerical DA vector shown in \autoref{fig:veri_sda} up to the fifth order. It should agree with the numerical DA $v_2 = \exp(1.5926 + d_1^2 + 5.3897\cdot d_2)$, as shown in \autoref{fig:veri_da}. We calculate the relative error for each non-zero coefficient. This procedure is repeated 1,000 times for all the math functions in the SDA lib with randomly generated $x$ and $y$. For the three inverse trigonometric functions, asin, acos, and atan, $x$ ranges in (0, 0.5) and $y$ ranges in (0,1), while for all the other functions, both $x$ and $y$ range in (0,10). In all the cases, the absolute values of the relative errors are less than $1\times 10^{-15}$. 




![SDA output.\label{fig:veri_sda}](fig_veri_sda.png)

![cppTPSA output.\label{fig:veri_da}](fig_veri_da.png)




# Acknowledgements

This material is based upon work supported by the U.S. Department of Energy, Office of Science, Office of Nuclear Physics under contract DE-AC05-06OR23177.



# References

