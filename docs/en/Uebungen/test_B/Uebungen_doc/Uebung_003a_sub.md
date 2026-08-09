# Exercise_003a_sub: IX on QX (generic)

[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)
This article describes the sub-app type `Uebung_003a_sub`. This block serves as a reusable template for the one-to-one connection of a digital input to a digital output.
----
## Purpose of the exercise

Encapsulation of the logiBUS I/O logic. By creating a custom type, the complexity of the individual connections is hidden from view. The user only needs to assign the hardware IDs.

-----

## Description and components

[cite_start]The type `Uebung_003a_sub` bundles an input and an output block[cite: 1].

### Internal Function Blocks (FBs)

* **`IX`**: Type `logiBUS_IX`. Reads the hardware pin assigned via the parameter `Input`.
* **`QX`**: Type `logiBUS_QX`. Switches the hardware pin assigned via the parameter `Output`.

-----

## Interfaces

[cite_start]The block has two configuration inputs[cite: 1]:

* **`Input`**: Expects a constant of type `logiBUS_DI_S` (e.g., `Input_I1`). ...07qz**: Type `logiBUS_QX`. Switches the hardware pin assigned via the parameter `Output`.
* * **`Output`**: Expects a constant of type `logiBUS_DO_S` (e.g., `Output_Q1`).

Internally, the event ports (`IND -> REQ`) and the data ports (`IN -> OUT`) are hard-coded. Once this type is placed in a project, it operates completely independently on the assigned hardware channel.

## 🛠️ Related Exercises

* [Exercise_003a](Uebung_003a.md)]
