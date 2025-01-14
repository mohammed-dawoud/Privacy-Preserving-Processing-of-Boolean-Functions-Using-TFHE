# Privacy-Preserving-Processing-of-Boolean-Functions-Using-TFHE
A solution that enables the execution of Boolean functions on sets of binary vectors in a reduced space while maintaining privacy. This solution is an implementation for the approach presented in our paper titled <b>Privacy-Preserving Execution of Boolean Functions and
Intersections Using Constrained Polynomial Logical Zonotopes</b>.
This solution is designed to execute Boolean functions on sets of binary vectors within a reduced space while ensuring privacy preservation. Leveraging constrained polynomial logical zonotopes as a novel set representation, capable of representing up to $2^h$ binary vectors using only $h$ generators, enables the execution of Boolean functions in the reduced space of constrained polynomial logical zonotopes, i.e., the generator space. To ensure the privacy of sets throughout the computation process, the proposed solution utilizes the TFHE, which offers a fast gate-by-gate bootstrapping approach for evaluating arbitrary Boolean circuits in the encrypted domain.

# Dependencies
To run the code on your device you need to install the following:
1. [MatLab](https://www.mathworks.com/products/matlab.html)
2. [CORA Tool Box](https://tumcps.github.io/CORA/)
3. [Fast Fully Homomorphic Encryption Over Torus](https://tfhe.github.io/tfhe/)
<br></br>
The experiment was run on Ubuntu 22.04.5 LTS, CORA 2022, MatLab 2023b, and MEX Function. However, it should be fine if you had higher editions.
The MEX functions are already compiled you can simply use them using the function name without the (.mexa64) extension in the MatLab command line or within a M-file.
# How to run
1. Make sure you can use the TFHE APIs within MatLab, i.e., you can include the paths within MatLab
3. Download the repository
4. Add the CORA toolbox and the downloaded repo to your MatLab path
5. You can simply modify the TFHE_TestConPolyLogicalFunctions.m file to test the different APIs provided for the privacy-preserving Boolean functions and intersection
6. The provided MEX APIs are: <b>client_encryptor, client_decryptor, cloud_operator</b>. You can these APIs to create and perform any sequence of logical operations you would like to execute. Using these APIs you can run any arbitrary logical operations in a privacy-preserving manner on sets represented as constrained polynomial logical zonotopes or logical zonotopes.

# Support
Questions and support are welcome at eng.mohamed.dawoud@gmail.com

# Citations
To cite <b>Privacy-Preserving-Processing-of-Boolean-Functions-Using-TFHE</b> in academic papers, please use the following entry:

```text

@software{Dawoud_Privacy-Preserving_Processing_of_2025,
author = {Dawoud, Mohammed M.},
month = jan,
title = {{Privacy-Preserving Processing of Boolean Functions Using Fast Fully Homomorphic Encryption and Constrained Polynomial Logical Zonotopes}},
version = {2.0.4},
year = {2025}
}
```
