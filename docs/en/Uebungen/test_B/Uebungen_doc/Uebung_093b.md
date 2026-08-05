# Exercise_093b: Example for E_N_TABLE

[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

This article describes the logiBUS® exercise `Uebung_093b`.

----

## Overview

[cite_start]Extension of the table concept using the function block `E_N_TABLE`[cite: 1].

Instead of sending all events to a common output, this function block has separate outputs (`EO0` to `EOn`) for each table entry.

In this exercise, four different lamps (`Q1` to `Q4`) are switched on sequentially in a precisely defined, irregular sequence. This is the most efficient method for defining complex startup sequences for multi-actuator systems.

![Uebung_093b_network](./Uebung_093b_network.svg)

