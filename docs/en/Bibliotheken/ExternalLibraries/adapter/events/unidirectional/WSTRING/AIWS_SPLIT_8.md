# AIWS_SPLIT_8
![AIWS_SPLIT_8](./AIWS_SPLIT_8.svg)

* * * * * * * * * *
## Introduction
The function block **AIWS_SPLIT_8** splits an incoming AIWS adapter signal into eight identical outputs. It functions as a generic splitter for unidirectional adapter connections and enables the parallel forwarding of a signal to multiple subsequent function blocks.
## Interface Structure

The function block has neither event nor data inputs or outputs. All communication takes place exclusively via adapters.

### Event Inputs
None.

### Event Outputs
None.

### Data Inputs
None.

### Data Outputs
None.

### Adapters

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| Input (Socket) | IN | adaptor::types::unidirectional::AIWS | Incoming AIWS signal to be split. |
| Output (Plug) | OUT1 | adaptor::types::unidirectional::AIWS | First parallel output of the signal. |
| Output (Plug) | OUT2 | adaptor::types::unidirectional::AIWS | Second parallel output of the signal. |
| Output (Plug) | OUT3 | adaptor::types::unidirectional::AIWS | Third parallel output of the signal. |
| Output (Plug) | OUT4 | adaptor::types::unidirectional::AIWS | Fourth parallel output of the signal. |
| Output (Plug) | OUT5 | adapater::types::unidirectional::AIWS | Fifth parallel output of the signal. |
| Output (Plug) | OUT6 | adapater::types::unidirectional::AIWS | Sixth parallel output of the signal. |
| Output (Plug) | OUT7 | adapater::types::unidirectional::AIWS | Seventh parallel output of the signal. |
| Output (Plug) | OUT8 | adapater::types::unidirectional::AIWS | Eighth parallel output of the signal. |

## Functionality

The module receives an AIWS (adapter) signal via the **IN** socket. This signal is duplicated to all eight **OUT** plugs without processing or delay. Changes to the input signal are immediately reflected at all outputs.

## Technical Features
- The module is generic and designed for a fixed number of eight outputs.
- There are no event-driven processes – signal transmission is purely adapter-based and continuous.
- The implementation is a pure splitter without internal logic or state management.

## State Overview

The module does not have a state machine. There are no internal states or event sequences – the output directly follows the input.

## Application Scenarios
- **Signal Distribution** in Automation Applications: An AIWS sensor value is to be made available to several independent control or monitoring blocks simultaneously.
- **Parallelization** of Algorithms: Subsequent modules require the same adapter data stream but operate in parallel on different resources.
- **Test and Simulation Environments**: An incoming signal is distributed across multiple evaluation instances to compare different processing paths.

## Comparison with Similar Components
- **AIWS_SPLIT_4** – Splitter with four outputs.
- **AIWS_SPLIT_16** – Splitter with 16 outputs.
- **AIWS_MERGE** – Combines multiple AIWS adapters into a single output (counterpart).

All split components share the feature of passing the signal through unchanged; they differ only in the number of outputs.

## Conclusion

**AIWS_SPLIT_8** is a simple yet essential component for multiplying an AIWS adapter signal across eight parallel paths. Its implementation without event-driven control or state logic makes it lightweight and reliable for use in distributed automation systems.
