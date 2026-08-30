# QX

![](https://user-images.githubusercontent.com/69573151/210781265-4dabab2d-a9e3-4da6-a14b-8df0a8ed36e5.png)

* * * * * * * * * *

## Introduction

The QX function block is an output service interface function block for Boolean output data. It serves as an interface between the control logic and physical output devices and enables the output of digital signals to external resources.
![QX](QX.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization Event
- **REQ**: Service Request Event

### **Event Outputs**

- **INITO**: Initialization Acknowledgement
- **CNF**: Acknowledgement of Requested Service Operation

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service Parameters for Configuration
- **OUT** (BOOL): Output Data for the Resource

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status Information

### **Adapters**

No adapter interfaces are available.

## Functionality

The QX block processes two main operations: initialization and service requests. The INIT event initializes the service with the specified parameters. The REQ event outputs the Boolean OUT value to the connected resource. Each operation generates a corresponding acknowledgment (INITO or CNF) containing status information.

The INIT event initializes the service with the specified parameters.

## Technical Features

- Specialized for Boolean output data
- Supports configurable service configuration
- Provides detailed status information via the STRING output STATUS
- Uses qualifiers (QI/QO) for event control

## State Overview

The block cycles through the following states:

1. **Not Initialized**: Before the first INIT operation
2. **Initialized**: After successful INIT operation, ready for REQ operations
3. **Active**: During the processing of REQ operations

## Application Scenarios

- Control of digital outputs (relays, LEDs, valves)
- Interface to actuators in automation systems
- Integration into I/O subsystems for distributed controllers
- Test and simulation environments for output signals

## ⚖️ Comparison with Similar Blocks

Compared to generic output blocks, QX offers specific service interface functionality with configurable settings and detailed status reporting. Other blocks, such as simple BOOL outputs, typically have fewer configuration options and less status information.

## 🛠️ Related exercises

- [Uebung_001](../../../Uebungen/test_B/Uebungen_doc/Uebung_001.md)
- [Uebung_001c](../../../Uebungen/test_B/Uebungen_doc/Uebung_001c.md)
- [Uebung_002](../../../Uebungen/test_B/Uebungen_doc/Uebung_002.md)
- [Uebung_002a](../../../Uebungen/test_B/Uebungen_doc/Uebung_002a.md)
- [Uebung_002a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_002a2.md)
- [Uebung_002a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_002a3.md)
- [Uebung_002a4](../../../Uebungen/test_B/Uebungen_doc/Uebung_002a4.md)
- [Uebung_002a5b](../../../Uebungen/test_B/Uebungen_doc/Uebung_002a5b.md)
- [Uebung_002b2](../../../Uebungen/test_B/Uebungen_doc/Uebung_002b2.md)
- [Uebung_002b3](../../../Uebungen/test_B/Uebungen_doc/Uebung_002b3.md)
- [Uebung_003](../../../Uebungen/test_B/Uebungen_doc/Uebung_003.md)
- [Uebung_003a0](../../../Uebungen/test_B/Uebungen_doc/Uebung_003a0.md)
- [Uebung_003a_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_003a_sub.md)
- [Uebung_003b2_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_003b2_sub.md)
- [Uebung_003b_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_003b_sub.md)
- [Uebung_003c_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_003c_sub.md)
- [Uebung_003d](../../../Uebungen/test_B/Uebungen_doc/Uebung_003d.md)
- [Uebung_004a](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a.md)
- [Uebung_004a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2.md)
- [Uebung_004a2_2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2_2.md)
- [Uebung_004a2_3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2_3.md)
- [Uebung_004a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a3.md)
- [Uebung_004a4](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a4.md)
- [Uebung_004a5](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a5.md)
- [Uebung_004a6](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a6.md)
- [Uebung_004a7](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a7.md)
- [Uebung_004a8](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a8.md)
- [Uebung_004a9](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a9.md)
- [Uebung_004b](../../../Uebungen/test_B/Uebungen_doc/Uebung_004b.md)
- [Uebung_004b2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004b2.md)
- [Uebung_004b3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004b3.md)
- [Uebung_004c1](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c1.md)
- [Uebung_004c2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c2.md)
- [Uebung_004c3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c3.md)
- [Uebung_004c4](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c4.md)
- [Uebung_004c5](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c5.md)
- [Uebung_004c6](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c6.md)
- [Uebung_004c7](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c7.md)
- [Uebung_005](../../../Uebungen/test_B/Uebungen_doc/Uebung_005.md)
- [Uebung_006](../../../Uebungen/test_B/Uebungen_doc/Uebung_006.md)
- [Uebung_006a](../../../Uebungen/test_B/Uebungen_doc/Uebung_006a.md)
- [Uebung_006a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_006a2.md)
- [Uebung_006a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_006a3.md)
- [Uebung_006a4](../../../Uebungen/test_B/Uebungen_doc/Uebung_006a4.md)
- [Uebung_006b](../../../Uebungen/test_B/Uebungen_doc/Uebung_006b.md)
- [Uebung_006c](../../../Uebungen/test_B/Uebungen_doc/Uebung_006c.md)
- [Uebung_006d](../../../Uebungen/test_B/Uebungen_doc/Uebung_006d.md)
- [Uebung_006e1](../../../Uebungen/test_B/Uebungen_doc/Uebung_006e1.md)
- [Uebung_006e2](../../../Uebungen/test_B/Uebungen_doc/Uebung_006e2.md)
- [Uebung_007](../../../Uebungen/test_B/Uebungen_doc/Uebung_007.md)
- [Uebung_007a1](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a1.md)
- [Uebung_007a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a2.md)
- [Uebung_007a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a3.md)
- [Uebung_008](../../../Uebungen/test_B/Uebungen_doc/Uebung_008.md)
- [Uebung_009](../../../Uebungen/test_B/Uebungen_doc/Uebung_009.md)
- [Uebung_010](../../../Uebungen/test_B/Uebungen_doc/Uebung_010.md)
- [Uebung_010a](../../../Uebungen/test_B/Uebungen_doc/Uebung_010a.md)
- [Uebung_010a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_010a2.md)
- [Uebung_010a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_010a3.md)
- [Uebung_010a4](../../../Uebungen/test_B/Uebungen_doc/Uebung_010a4.md)
- [Uebung_010b1](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b1.md)
- [Uebung_010b2](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b2.md)
- [Uebung_010b3](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b3.md)
- [Uebung_010b4_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b4_sub.md)
- [Uebung_010b5_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b5_sub.md)
- [Uebung_010b6](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b6.md)
- [Uebung_010b7](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b7.md)
- [Uebung_010b8](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b8.md)
- [Uebung_010b9](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b9.md)
- [Uebung_010bA](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA.md)
- [Uebung_010bA2](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA2.md)
- [Uebung_010bA3](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA3.md)
- [Uebung_010bA4](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA4.md)
- [Uebung_010c](../../../Uebungen/test_B/Uebungen_doc/Uebung_010c.md)
- [Uebung_010c2](../../../Uebungen/test_B/Uebungen_doc/Uebung_010c2.md)
- [Uebung_010c3_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_010c3_sub.md)
- [Uebung_010c4_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_010c4_sub.md)
- [Uebung_013](../../../Uebungen/test_B/Uebungen_doc/Uebung_013.md)
- [Uebung_019b](../../../Uebungen/test_B/Uebungen_doc/Uebung_019b.md)
- [Uebung_019c](../../../Uebungen/test_B/Uebungen_doc/Uebung_019c.md)
- [Uebung_020a](../../../Uebungen/test_B/Uebungen_doc/Uebung_020a.md)
- [Uebung_020b](../../../Uebungen/test_B/Uebungen_doc/Uebung_020b.md)
- [Uebung_020c](../../../Uebungen/test_B/Uebungen_doc/Uebung_020c.md)
- [Uebung_020c2](../../../Uebungen/test_B/Uebungen_doc/Uebung_020c2.md)
- [Uebung_020c3](../../../Uebungen/test_B/Uebungen_doc/Uebung_020c3.md)
- [Uebung_020d](../../../Uebungen/test_B/Uebungen_doc/Uebung_020d.md)
- [Uebung_020e](../../../Uebungen/test_B/Uebungen_doc/Uebung_020e.md)
- [Uebung_020e2](../../../Uebungen/test_B/Uebungen_doc/Uebung_020e2.md)
- [Uebung_020f](../../../Uebungen/test_B/Uebungen_doc/Uebung_020f.md)
- [Uebung_020f2](../../../Uebungen/test_B/Uebungen_doc/Uebung_020f2.md)
- [Uebung_020f3](../../../Uebungen/test_B/Uebungen_doc/Uebung_020f3.md)
- [Uebung_020g](../../../Uebungen/test_B/Uebungen_doc/Uebung_020g.md)
- [Uebung_020h](../../../Uebungen/test_B/Uebungen_doc/Uebung_020h.md)
- [Uebung_020i](../../../Uebungen/test_B/Uebungen_doc/Uebung_020i.md)
- [Uebung_021](../../../Uebungen/test_B/Uebungen_doc/Uebung_021.md)
- [Uebung_022](../../../Uebungen/test_B/Uebungen_doc/Uebung_022.md)
- [Uebung_023](../../../Uebungen/test_B/Uebungen_doc/Uebung_023.md)
- [Uebung_024](../../../Uebungen/test_B/Uebungen_doc/Uebung_024.md)
- [Uebung_025](../../../Uebungen/test_B/Uebungen_doc/Uebung_025.md)
- [Uebung_026_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_026_sub.md)
- [Uebung_028](../../../Uebungen/test_B/Uebungen_doc/Uebung_028.md)
- [Uebung_029](../../../Uebungen/test_B/Uebungen_doc/Uebung_029.md)
- [Uebung_030](../../../Uebungen/test_B/Uebungen_doc/Uebung_030.md)
- [Uebung_032](../../../Uebungen/test_B/Uebungen_doc/Uebung_032.md)
- [Uebung_033_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_033_sub.md)
- [Uebung_035](../../../Uebungen/test_B/Uebungen_doc/Uebung_035.md)
- [Uebung_035a](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a.md)
- [Uebung_035a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a2.md)
- [Uebung_035a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a3.md)
- [Uebung_035b](../../../Uebungen/test_B/Uebungen_doc/Uebung_035b.md)
- [Uebung_035c](../../../Uebungen/test_B/Uebungen_doc/Uebung_035c.md)
- [Uebung_036](../../../Uebungen/test_B/Uebungen_doc/Uebung_036.md)
- [Uebung_037](../../../Uebungen/test_B/Uebungen_doc/Uebung_037.md)
- [Uebung_038](../../../Uebungen/test_B/Uebungen_doc/Uebung_038.md)
- [Uebung_039_sub_Outputs](../../../Uebungen/test_B/Uebungen_doc/Uebung_039_sub_Outputs.md)
- [Uebung_039a_sub_Outputs](../../../Uebungen/test_B/Uebungen_doc/Uebung_039a_sub_Outputs.md)
- [Uebung_039b](../../../Uebungen/test_B/Uebungen_doc/Uebung_039b.md)
- [Uebung_040](../../../Uebungen/test_B/Uebungen_doc/Uebung_040.md)
- [Uebung_040_2](../../../Uebungen/test_B/Uebungen_doc/Uebung_040_2.md)
- [Uebung_041](../../../Uebungen/test_B/Uebungen_doc/Uebung_041.md)
- [Uebung_049](../../../Uebungen/test_B/Uebungen_doc/Uebung_049.md)
- [Uebung_051](../../../Uebungen/test_B/Uebungen_doc/Uebung_051.md)
- [Uebung_052](../../../Uebungen/test_B/Uebungen_doc/Uebung_052.md)
- [Uebung_053](../../../Uebungen/test_B/Uebungen_doc/Uebung_053.md)
- [Uebung_054](../../../Uebungen/test_B/Uebungen_doc/Uebung_054.md)
- [Uebung_055](../../../Uebungen/test_B/Uebungen_doc/Uebung_055.md)
- [Uebung_056](../../../Uebungen/test_B/Uebungen_doc/Uebung_056.md)
- [Uebung_060_sub_Outputs](../../../Uebungen/test_B/Uebungen_doc/Uebung_060_sub_Outputs.md)
- [Uebung_071](../../../Uebungen/test_B/Uebungen_doc/Uebung_071.md)
- [Uebung_071a](../../../Uebungen/test_B/Uebungen_doc/Uebung_071a.md)
- [Uebung_071b](../../../Uebungen/test_B/Uebungen_doc/Uebung_071b.md)
- [Uebung_072b](../../../Uebungen/test_B/Uebungen_doc/Uebung_072b.md)
- [Uebung_080](../../../Uebungen/test_B/Uebungen_doc/Uebung_080.md)
- [Uebung_080b](../../../Uebungen/test_B/Uebungen_doc/Uebung_080b.md)
- [Uebung_080c](../../../Uebungen/test_B/Uebungen_doc/Uebung_080c.md)
- [Uebung_081](../../../Uebungen/test_B/Uebungen_doc/Uebung_081.md)
- [Uebung_082](../../../Uebungen/test_B/Uebungen_doc/Uebung_082.md)
- [Uebung_083](../../../Uebungen/test_B/Uebungen_doc/Uebung_083.md)
- [Uebung_084](../../../Uebungen/test_B/Uebungen_doc/Uebung_084.md)
- [Uebung_085](../../../Uebungen/test_B/Uebungen_doc/Uebung_085.md)
- [Uebung_087](../../../Uebungen/test_B/Uebungen_doc/Uebung_087.md)
- [Uebung_087a1](../../../Uebungen/test_B/Uebungen_doc/Uebung_087a1.md)
- [Uebung_087a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_087a2.md)
- [Uebung_088](../../../Uebungen/test_B/Uebungen_doc/Uebung_088.md)
- [Uebung_089](../../../Uebungen/test_B/Uebungen_doc/Uebung_089.md)
- [Uebung_090a1](../../../Uebungen/test_B/Uebungen_doc/Uebung_090a1.md)
- [Uebung_090a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_090a2.md)
- [Uebung_091](../../../Uebungen/test_B/Uebungen_doc/Uebung_091.md)
- [Uebung_093](../../../Uebungen/test_B/Uebungen_doc/Uebung_093.md)
- [Uebung_093b](../../../Uebungen/test_B/Uebungen_doc/Uebung_093b.md)
- [Uebung_094](../../../Uebungen/test_B/Uebungen_doc/Uebung_094.md)
- [Uebung_094a](../../../Uebungen/test_B/Uebungen_doc/Uebung_094a.md)
- [Uebung_095](../../../Uebungen/test_B/Uebungen_doc/Uebung_095.md)
- [Uebung_110](../../../Uebungen/test_B/Uebungen_doc/Uebung_110.md)
- [Uebung_111](../../../Uebungen/test_B/Uebungen_doc/Uebung_111.md)
- [Uebung_160](../../../Uebungen/test_B/Uebungen_doc/Uebung_160.md)
- [Uebung_160b](../../../Uebungen/test_B/Uebungen_doc/Uebung_160b.md)
- [Uebung_160b2](../../../Uebungen/test_B/Uebungen_doc/Uebung_160b2.md)
- [Uebung_177](../../../Uebungen/test_B/Uebungen_doc/Uebung_177.md)
- [Uebung_178](../../../Uebungen/test_B/Uebungen_doc/Uebung_178.md)
- [Uebung_179](../../../Uebungen/test_B/Uebungen_doc/Uebung_179.md)
- [Exercise_180](../../../Uebungen/test_B/Uebungen_doc/Uebung_180.md)

## Conclusion

The QX function block provides a robust and configurable solution for Boolean output services. Its structured event handling and detailed status feedback make it particularly suitable for reliable automation applications where transparency regarding the I/O status is required.
