# Exercise_003a0_AX: DigitalInput_I1/_I2 to DigitalOutput_Q1/_I2 - with untyped subapps

[![NotebookLM](media/NotebookLM_logo.png)(https://notebooklm.google.com/notebook/041f4df4-b729-484d-b786-b6dcdf151961)
This article describes the logiBUS® exercise `Uebung_003a0_AX`. Unlike the use of types (as in `Uebung_003a_AX`), this exercise demonstrates how to visually group logic without creating separate type definitions. This is achieved using so-called "untyped subapps."
----
The main objective of this exercise is to demonstrate methods for structuring applications purely visually. Untyped subapps serve as "containers" or folders within a network to encapsulate related functions. They help to clean up complex diagrams ("clean up by collapsing") without having to worry about reusability or interface definitions.

-----

## Ziel der Übung

## Description and Components

[cite_start]The subapplication `Uebung_003a0_AX.SUB` contains two embedded subapplications (`SubApp` and `SubApp_1`), each with its own signal path[cite: 1].

### Untyped Subapplications

Unlike typed subapplications, which are based on an external definition, the logic of these containers exists only within this specific instance.

* Contains the logic for channel 2.
* Internally: `DigitalInput_I2` connected to `DigitalOutput_Q2`[cite: 1].
2. **Container `SubApp_1`**:
* Contains the logic for channel 1.
* Internally: `DigitalInput_I1` connected to `DigitalOutput_Q1`[cite: 1].

### Function Blocks (FBs)

The following familiar function blocks are used within the containers:

* **`logiBUS_IXA`**: For reading signals.
* **`logiBUS_QXA`**: For outputting signals.

-----

## Functionality

The logic is identical to parallel control, however, the view is hierarchically structured. The structure in `Uebung_003a0_AX.SUB` illustrates the nesting:

<SubAppNetwork>
<SubApp Name="SubApp">
<SubAppNetwork>
<FB Name="DigitalInput_I2" ... />
<FB Name="DigitalOutput_Q2" ... />
<AdapterConnections>
<Connection Source="DigitalInput_I2.IN" Destination="DigitalOutput_Q2.OUT"/>
</AdapterConnections>
</SubAppNetwork>
</SubApp>

<SubApp Name="SubApp_1">
<SubAppNetwork>
<FB Name="DigitalInput_I1" ... />
<FB Name="DigitalOutput_Q1" ... />
<AdapterConnections>
<Connection Source="DigitalInput_I1.IN" Destination="DigitalOutput_Q1.OUT"/>
</AdapterConnections>
</SubAppNetwork>
</SubApp>
</SubAppNetwork>

Functional Flow:

The encapsulation has no impact on runtime execution. The components behave exactly as if they were all placed at the top level.

1. `SubApp_1` processes the signal from `I1` to `Q1`.
2. `SubApp` processes the signal from `I2` to `Q2`.

-----

A typical application example is the **Visual Grouping of Functional Areas**:

In a large plant, one could use untyped sub-apps to organize the logic thematically, e.g., a container for "Temperature Control," one for "Drive Control," and one for "Safety Monitoring." When the main view is opened, only these three blocks are visible, rather than hundreds of individual gates and connections. This facilitates navigation (the "zoom-in" effect) but is not intended for reuse (typed sub-apps are used for this).

## Anwendungsbeispiel