Here is the documentation for the exercise based on the provided XML data.

# Exercise_010b5_sub_AX: IX to QX (generic)

* * * * * * * * * *

## Introduction

This sub-application (`SubAppType`) with the comment "IX to QX (generic)" serves to establish a logical bridge between an ISOBUS softkey input (IX) and a digital output (QX). It is designed as a reusable module that is configured via input parameters to map specific object IDs to specific hardware outputs.

## Function Blocks (FBs) Used

In this sub-application, two central function blocks are interconnected to implement communication between input and output.

## Sub-Blocks: Internal Logic

This section describes the internally used blocks and their configuration.

- **Type**: `SubAppNetwork`
- **Internal Function Blocks Used**:
- **Block Name**: `QXA`
- **Type**: `logiBUS::io::DQ::logiBUS_QXA`
- **Parameters**:
- `QI` = `TRUE` (Block is activated)
- `PARAMS` = "" (Empty/Invisible)
- **Data Input**:
- `Output`: Connected to the external input `Output` of the sub-application.
- **Functionality**: This block represents the interface to the digital output system (logiBUS DQ). It receives the configuration specifying which physical output should be switched.
- **Block Name**: `IXA`
- **Type**: `isobus::UT::io::Softkey::Softkey_IXA`
- **Parameters**:
- `QI` = `TRUE` (Block is activated)
- **Data Input**:
- `u16ObjId`: Connected to the external input `u16ObjId` of the sub-application.
- **Functionality**: This block handles the input page via an ISOBUS Universal Terminal (UT). It listens for events from a specific softkey, which is defined by the object ID.

## Program Flow and Connections

The flow within this sub-application is controlled by direct connections and adapter concepts:

1. **Interface Configuration**:

- The sub-application has two inputs: `u16ObjId` (of type `UINT`) and `Output` (of type `logiBUS::io::DQ::logiBUS_DO_S`).
- The value of `u16ObjId` is passed directly to the function block `IXA` to determine which softkey is being monitored.
- The definition of `Output` is passed directly to the function block `QXA` to define the output to be controlled.
1. **Adapter Connection**:

- An **adapter connection** exists between `IXA.IN` (source) and `QXA.OUT` (destination).
- This connection ensures that the status or commands of the softkey block (`IXA`) are transmitted directly to the output block (`QXA`) without the need for complex individual wiring of event or data lines.

**Learning Objectives:**

- Understanding sub-applications for encapsulating logic.
- Using adapter connections to simplify signal flows between compatible blocks (here, between ISOBUS input and logiBUS output).
- Parameterizing generic blocks via sub-application interfaces.

## Summary

The `Uebung_010b5_sub_AX` module is a generic building block that can be flexibly used to establish interaction between an ISOBUS control element (softkey) and an actuator (digital output). The use of adapter connections minimizes internal complexity and ensures clean encapsulation of functionality.
