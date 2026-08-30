# Override_K

![Override_K](./Override_K.svg)

* * * * * * * * * *

## Introduction

The global constants package `Override_K` supplies the three named `UINT` values that
[Override_K_Select](../Override_K_Select.md) uses to populate its `K` output for `AX_AUI_MUX_3`.
Instead of wiring `UINT#0`/`UINT#1`/`UINT#2` as literals into the `F_SEL` parameters, the block
references these three constants by their descriptive name. The package is defined in the
`adapter::OverrideK::const` namespace.

## Interface Structure

Being a global-constants package, it has no event- or data-flow-based interface in the
conventional function-block sense.

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

None.

## Functionality

The constants are replaced by their fixed defined values at compile time:

-   `Override_K_Normal`: `UINT#0` — the K value for "no override" (`AX_AUI_MUX_3.IN1`, the normal
    value).
-   `Override_K_ForceFalse`: `UINT#1` — the K value for "override forced to FALSE"
    (`AX_AUI_MUX_3.IN2`).
-   `Override_K_ForceTrue`: `UINT#2` — the K value for "override forced to TRUE"
    (`AX_AUI_MUX_3.IN3`).

## Technical Details

-   **Directly coupled to `AX_AUI_MUX_3`'s input order.** The numeric values 0/1/2 correspond
    exactly to `AX_AUI_MUX_3`'s input numbering (`IN1`/`IN2`/`IN3`) — any change to that order in
    [Override_K_Select](../Override_K_Select.md) would need to be kept in sync here.
-   **Used only by `Override_K_Select`.** Unlike, say, `OPC_UA_Endpoints`, this package is tightly
    coupled to a single block rather than several independent call sites.

## State Overview

Being static, constant values, there is no state machine.

## Application Scenarios

-   Referenced in the `IN0`/`IN1` `Parameter` values of the two `F_SEL` blocks in
    [Override_K_Select](../Override_K_Select.md).
-   Comparison values for a consumer that wants to evaluate an `AX_AUI_MUX_3`'s raw `K` value
    rather than just its muxed output.

## ⚖️ Comparison with Similar Blocks

-   **[IDs](../../../isobus/UT/Q/const/IDs.md)** (ISOBUS UT library): follows the same GCF pattern
    (named constants instead of literals), but covers ISOBUS object IDs rather than a MUX
    selector.

## Conclusion

`Override_K` is a small, tightly-coupled constants package that names the three K values used by
`Override_K_Select`, making them more readable and maintainable than scattered `UINT#0/1/2`
literals.
