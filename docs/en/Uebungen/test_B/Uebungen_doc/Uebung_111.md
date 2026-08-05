# Exercise_111: Integer Overflow Exercise

[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

This article describes the logiBUS® exercise `Uebung_111`. It demonstrates how to prevent calculation errors by converting to larger data types in a timely manner.

----

## Overview

[cite_start]In `Uebung_111.SUB`, the overflow problem from Exercise 110 is solved[cite: 1].

Before the critical calculation or comparison takes place, the small data type `USINT` is converted into a large 32-bit type using the function block `F_USINT_TO_UDINT`. This provides sufficient "space" for the result, and the subsequent comparison yields the mathematically correct result. This demonstrates the proper handling of different numerical accuracies in the program flow.

![Uebung_111_network](./Uebung_111_network.svg)


![Uebung_111_network](./Uebung_111_network.svg)