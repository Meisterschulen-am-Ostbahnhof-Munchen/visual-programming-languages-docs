# Exercise_003b: DigitalInput_I1-2-3-4 to DigitalOutput_Q1-2-3-4
[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)
This article describes the logiBUS® exercise `Uebung_003b`. This exercise extends the modular control concept from `Uebung_003a` to a total of four independent channels.
----
## Objective of the Exercise
The main objective is to demonstrate scalability through typing. It shows how easily existing logic can be replicated by instantiating a predefined sub-application type multiple times. This highlights the efficiency advantage of IEC 61499 in managing many similar hardware interfaces.

-----

## Description and Components

[cite_start]The subapplication `Uebung_003b.SUB` uses four instances of type `Uebung_003b_sub` (identical to `Uebung_003a_sub`) to link four I/O pairs[cite: 1].

### Typed Subapplication: `Uebung_003b_sub`

[cite_start]This component encapsulates the one-to-one routing from a digital input (`IX`) to a digital output (`QX`)[cite: 2]. It provides two configuration parameters:

* **`Input`**: Selection of the physical input (e.g., `Input_I1` to `Input_I4`).
* **`Output`**: Selection of the physical output (e.g., `Output_Q1` to `Output_Q4`).

### Instances in the Main Application

In `Uebung_003b`, four instances (`F1` to `F4`) are used:

* **`F1`**: `I1` ➡️ `Q1`
* **`F2`**: `I2` ➡️ `Q2`
* **`F3`**: `I3` ➡️ `Q3`
* **`F4`**: `I4` ➡️ `Q4`

-----

## Functionality

The logic is completely encapsulated within the sub-applications. The main application serves only as a configuration layer. The structure shown in `Uebung_003b.SUB` illustrates the parameter assignment:

```xml
<SubApp Name="F1" Type="Uebungen::Uebung_003b_sub">
<Parameter Name="Input" Value="Input_I1"/>
<Parameter Name="Output" Value="Output_Q1"/>
</SubApp>
<!-- ... Instanzen F2 und F3 ... -->
<SubApp Name="F4" Type="Uebungen::Uebung_003b_sub">
<Parameter Name="Input" Value="Input_I4"/>
<Parameter Name="Output" Value="Output_Q4"/>
</SubApp>

[cite_start][cite: 1]

Each channel operates completely independently. When a change is detected at input `I3`, only instance `F3` reacts and switches output `Q3`. The other channels remain unaffected.

-----

## Application Example

**Modular Control Cabinet Construction**:

Imagine an I/O module with 8 or 16 channels. Instead of creating individual connections for each channel, the typed sub-application is used as a "channel driver." The software structure thus precisely reflects the modular design of the hardware, which greatly simplifies troubleshooting and documentation.
