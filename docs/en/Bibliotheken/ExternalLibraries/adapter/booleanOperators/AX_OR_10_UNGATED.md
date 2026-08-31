# AX_OR_10_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AX_OR_10`](AX_OR_10.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

* * * * * * * * * *

## Introduction

The AX_OR_10_UNGATED is a generic function block for calculating the logical OR operation of 10 inputs.
![AX_OR_10_UNGATED](AX_OR_10_UNGATED.svg)

## Interface Structure

### **Adapters**

**Input Adapters:**

- **IN1** to **IN10** (adapter::types::unidirectional::AX)

**Output Adapters:**

- **OUT** (adapter::types::unidirectional::AX)

## Functionality

The function block performs a logical OR operation on the 10 input signals.

## Technical Features

- Generic function block with the specific class name 'GEN_AX_OR'
- Uses unidirectional adapters.

## State Overview

Combinatory logic block without states.

## Application Scenarios

Logical logic gates with many inputs.

## ⚖️ Comparison with similar building blocks

- **AX_OR_2...9**: Variants with fewer inputs.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

Adapter-based OR gate with 10 inputs.
