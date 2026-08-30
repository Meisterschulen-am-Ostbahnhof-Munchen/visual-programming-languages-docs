# Exercise_003a: DigitalInput_I1/_I2 to DigitalOutput_Q1/_I2 - with typed Subapp

[![NotebookLM](media/NotebookLM_logo.png)(https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)
This article describes the logiBUS® exercise `Uebung_003a`. It demonstrates an advanced approach to structuring IEC 61499 applications: encapsulating logic in reusable, typed sub-applications ("Typed SubApps").
----
## Objective of the Exercise

The main objective is to avoid redundant code. Instead of manually drawing the same blocks and connections for each channel, a generic "channel type" is defined once. This can then be instantiated and individually configured as often as needed. This improves clarity and reduces errors when programming large systems.

----

The main objective is to avoid redundant code. -----

## Description and Components

[cite_start]The subapplication `Uebung_003a.SUB` uses two instances of a user-defined sub-application type to implement two signal paths[cite: 1].

### Typed Subapplication: `Uebung_003a_sub`

[cite_start]This component encapsulates the basic logic of signal routing[cite: 2]. It has two parameters for hardware assignment:

- **`Input`**: Determines the physical input (e.g., `Input_I1`).
- **`Output`**: Determines the physical output (e.g., `Output_Q1`).

Inside the type are a `logiBUS_IX` and a `logiBUS_QX` block, which are permanently connected via an event and a data connection.

### Instances in the Main Application

Two instances of this type are placed in `Uebung_003a`:

- **`F1`**: [cite_start]Parameterized for the path `I1` to `Q1`[cite: 1].
- **`F2`**: [cite_start]Parameterized for the path `I2` to `Q2`[cite: 1].

-----

## Functionality

The complexity of the individual connections is hidden within the sub-application ("information hiding"). The main application only defines the assignment of physical addresses. The structure in `Uebung_003a.SUB` is therefore extremely compact:

<SubApp Name="F1" Type="Uebungen::Uebung_003a_sub">
<Parameter Name="Input" Value="Input_I1"/>
<Parameter Name="Output" Value="Output_Q1"/>
</SubApp>
<SubApp Name="F2" Type="Uebungen::Uebung_003a_sub">
<Parameter Name="Input" Value="Input_I2"/>
<Parameter Name="Output" Value="Output_Q2"/>
</SubApp>

[cite_start][cite: 1]

Functionally, the application behaves exactly like the flat structure in Exercise 003. Each instance operates as an independent block that reacts to events at its assigned hardware input and updates the hardware output.

-----

## Application Example

**Object-Oriented Plant Control**:

Imagine a conveyor belt system with 20 identical sections. Instead of drawing the same logic 20 times, you create a "Section" type. In the main application, you place 20 instances and assign them only the start addresses of the respective hardware I/Os. If the logic needs to be changed later (e.g., an additional time delay), you only need to change it in a single place (in the type), and all 20 sections will immediately adopt the change.
