# Exercise_003a0: DigitalInput_I1/_I2 to DigitalOutput_Q1/_I2 - with Untyped SubApps

[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)
This article describes the logiBUS® exercise `Uebung_003a0`. Unlike using types (as in `Uebung_003a`), this exercise demonstrates how to visually group logic without creating separate type definitions in the library. This is achieved using so-called "Untyped SubApps."
----
The main objective of this exercise is to demonstrate methods for structuring applications purely visually. Untyped sub-applications serve as "containers" or folders within a network to encapsulate related functions. They help to tidy up complex diagrams ("tidy up by collapsing") without having to worry about reusability or interface definitions.

-----

## Ziel der Übung

## Description and Components

[cite_start]The subapplication `Uebung_003a0.SUB` contains two embedded subapplications (`SubApp` and `SubApp_1`), each with its own signal path[cite: 1].

### Untyped Subapplications

Unlike typed subapplications, which are based on an external definition, the logic of these containers exists only within this specific instance. They have no external inputs or outputs in the interface (in this example) but access the hardware directly.

* Contains the logic for channel 2.
* Internally: `DigitalInput_I2` connected to `DigitalOutput_Q2`[cite: 1].
2. **Container `SubApp_1`**:
* Contains the logic for channel 1.
* Internally: `DigitalInput_I1` connected to `DigitalOutput_Q1`[cite: 1].

### Function Blocks (FBs)

The familiar standard function blocks are used within the containers:

* **`logiBUS_IX`**: For event-based signal reading.
* **`logiBUS_QX`**: For event-based signal output.

-----

## Functionality

The logic is identical to parallel control, however, the view is hierarchically structured. The structure in `Uebung_003a0.SUB` shows the nesting:

<SubAppNetwork>
<SubApp Name="SubApp">
<SubAppNetwork>
<FB Name="DigitalInput_I2" ... />
<FB Name="DigitalOutput_Q2" ... />
<EventConnections> ... </EventConnections>
<DataConnections> ... </DataConnections>
</SubAppNetwork>
</SubApp>

<SubApp Name="SubApp_1">
<SubAppNetwork>
<FB Name="DigitalInput_I1" ... />
<FB Name="DigitalOutput_Q1" ... />
<EventConnections> ... </EventConnections>
<DataConnections> ... </DataConnections>
</SubAppNetwork>
</SubApp>
</SubAppNetwork>

[cite_start][cite: 1]

Functional Flow:

The encapsulation has no impact on runtime execution. The components behave exactly as if they were all placed at the top level.

1. `SubApp_1` processes the signal from `I1` to `Q1`.
2. `SubApp` processes the signal from `I2` to `Q2`.

-----

**Visual Grouping of Functional Areas**:

In a large plant, untyped SubApps could be used to organize the logic thematically, e.g., a container for "Temperature Control," one for "Drive Control," and one for "Safety Monitoring." When you open the main view, you only see these three blocks and not hundreds of individual gates and connections. This makes navigation easier (the "zoom-in" effect), but it's not intended for reuse across multiple projects (for that, you use typed subapps).

## Anwendungsbeispiel