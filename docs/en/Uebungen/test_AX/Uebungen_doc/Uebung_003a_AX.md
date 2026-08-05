# Exercise_003a_AX: DigitalInput_I1/_I2 to DigitalOutput_Q1/_I2 - with typed Subapp
[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)
This article describes the logiBUS® exercise `Uebung_003a_AX`. The exercise demonstrates an advanced approach to structuring IEC 61499 applications: the use of typed sub-applications ("Typed SubApps") for encapsulating and reusing logic.
----
## Objective of the Exercise
The main objective is to show how redundant code can be avoided. Instead of drawing identical structures (e.g., connecting an input to an output) multiple times, a generic function block is defined once. This can then be instantiated and configured as often as needed. This significantly improves the clarity and maintainability of large projects.

-----

## Description and Components

[cite_start]The subapplication `Uebung_003a_AX.SUB` uses two instances of a user-defined subtype to implement two signal paths[cite: 1].

### Typed Subapplication: `Uebung_003a_AX_sub`

[cite_start]This function block encapsulates the basic logic: "Read an input and write to an output"[cite: 2]. It has interfaces for parameterization:

* **`Input`**: Determines which physical input is to be read (e.g., `Input_I1`).
* **`Output`**: Determines which physical output is to be switched (e.g., `Output_Q1`).

Internally, this subtype contains:

* A `logiBUS_IXA` block for reading the input.
* A `logiBUS_QXA` block for writing the output.
* An adapter connection that directly links both.

### Instances in the main application

Two instances of this type are created in `Uebung_003a_AX`:

* **`F1`**: Configured for `Input_I1` on `Output_Q1`.
* **`F2`**: Configured for `Input_I2` on `Output_Q2`.

-----

## Functionality

The logic is hidden within the sub-application ("information hiding"). The main application only defines the parameter connections. The structure in `Uebung_003a_AX.SUB` is therefore extremely compact:

``````xml
<SubApp Name="F1" Type="Uebungen::Uebung_003a_AX_sub">
<Parameter Name="Input" Value="Input_I1"/>
<Parameter Name="Output" Value="Output_Q1"/>
</SubApp>
<SubApp Name="F2" Type="Uebungen::Uebung_003a_AX_sub">
<Parameter Name="Input" Value="Input_I2"/>
<Parameter Name="Output" Value="Output_Q2"/>
</SubApp>

[cite_start][cite: 1]

The functional flow corresponds exactly to that of `Uebung_003_AX` (parallel control), however, the implementation is more modular. Each instance (`F1`, `F2`) operates as an independent, isolated block that executes its internal adapter logic.

-----

## Application Example

A perfect application example is **Object-Oriented Plant Control**:

Imagine a conveyor system with 50 identical conveyor belts. Each belt has a motor (output) and a light barrier (input). Instead of drawing the same blocks and connections 50 times, you create one type of "Conveyor Belt Module". In the main application, you then simply place 50 instances of this module and assign them only the physical addresses. If the logic changes later (e.g., the motor should stop with a delay), you only need to change this in one place (in the type), and all 50 tapes will be updated automatically.
