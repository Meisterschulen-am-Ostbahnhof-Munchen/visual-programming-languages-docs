# E_T_FF
## 🎧 Podcast
![E_T_FF_ecc](./E_T_FF_ecc.svg)
* [The E_T_FF in IEC 61499: Modular Toggle for Industry 4.0 ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_T_FF-in-IEC-61499-Modulares-Kippen-fr-die-Industrie-4-0-e3674m7)
* [The E_T_FF_SR Component: Heart of IEC 61499 – Storing, Switching, Responding ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Der-E_T_FF_SR-Baustein-Herzstck-der-IEC-61499--Speichern--Umschalten--Reagieren-e3682dm)
* [Unpacking E_T_FF_SR: The Secret Toggle Switch of Industrial Control Systems ](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/Unpacking-E_T_FF_SR-The-Secret-Toggle-Switch-of-Industrial-Control-Systems-e367ntv)

## Introduction
The `E_T_FF` (Event-driven Toggle Flip-Flop) is an event-driven toggle switch that changes its state (`Q`) with each incoming clock event (`CLK`). It is the digital equivalent of an impulse relay, where a short pulse permanently changes the state.

![E_T_FF](E_T_FF.svg)

## Interface Structure

### **Event Inputs:**
- **CLK (Clock)**: The clock event that toggles the state of `Q`.

### **Event Outputs:**
- **EO (Event Output)**: Triggered when the state of `Q` changes.
- **Associated Data**: `Q`

### **Data Outputs:**
- **Q**: The current state of the flip-flop (data type: `BOOL`).

#
## ## Functionality

The `E_T_FF` component is a simple toggle flip-flop:

1. **State Change**: Upon each incoming `CLK` event, the output `Q` changes its state: If `Q` was `TRUE`, it becomes `FALSE`, and if `Q` was `FALSE`, it becomes `TRUE`.

2. **Event Triggering**: Each state change of `Q` triggers the `EO` event.

## Technical Features
- **Impulse Switch Analogy**: The component behaves like an impulse switch: A short pulse (`CLK`) switches the light (`Q`) on, the next pulse switches it off.
- **Memory Function**: `Q` stores the last state of the flip-flop.
- **Stateless Between Clock Cycles**: Changes to the `CLK` input only affect `Q` at the time of the event.

## Application Examples

### Push Button for a Lamp
A push button logic for a lamp can be implemented using a `E_T_FF`:

- **Concept**: A push button generates a `CLK` event. Each press turns the lamp (`Q`) on or off.
- **Graphical Representation**:
- Mapping: ![E_T_FF Anwendung Taster Mapping](https://user-images.githubusercontent.com/69573151/200582493-3b7830e9-6c99-48c8-8edb-3c51c2ec61f1.png)
- Application: ![E_T_FF Anwendung Taster App](https://user-images.githubusercontent.com/69573151/200582537-03463197-4460-447e-b246-f11bafed81d3.png)
- Embedded Resource: ![E_T_FF Anwendung Taster EMB_RES](https://user-images.githubusercontent.com/69573151/200582652-15139148-a200-49fb-a683-93e341eab607.png)

### Blinker
A blinker can be implemented using feedback with a timer:

- **Concept**: The `EO` event of `E_T_FF` triggers a `E_DELAY` event, whose `EO` event, in turn, serves as the `CLK` event for `E_T_FF`. This creates a periodic state change.

### Blinker - **Graphical representation**:
- Mapping: ![E_T_FF Anwendung Blinker Mapping](https://user-images.githubusercontent.com/69573151/200581547-83f78279-e1a1-4748-8240-8755630638a9.png)
- Application: ![E_T_FF Anwendung Blinker App](https://user-images.githubusercontent.com/69573151/200581603-62aadee2-2a3a-4562-994f-51475817da3b.png)
- Embedded resource: ![E_T_FF Anwendung Blinker EMB_RES](https://user-images.githubusercontent.com/69573151/200581674-613cabbc-86a6-45b7-ad57-a9c16bd6262d.png)

## 🛠️ Related exercises
* [Uebung_004a](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a.md)
* [Uebung_004a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2.md)
* [Uebung_004a2_2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2_2.md)
* [Uebung_004a2_3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a2_3.md)
* [Uebung_004a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a3.md)
* [Uebung_004a4](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a4.md)
* [Uebung_004a5](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a5.md)
* [Uebung_004a6](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a6.md)
* [Uebung_004a8](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a8.md)
* [Uebung_004a9](../../../Uebungen/test_B/Uebungen_doc/Uebung_004a9.md)
* [Uebung_004c1](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c1.md)
* [Uebung_004c2](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c2.md)
* [Uebung_004c3](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c3.md)
* [Uebung_004c4](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c4.md)
* [Uebung_004c5](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c5.md)
* [Uebung_004c6](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c6.md)
* [Uebung_004c7](../../../Uebungen/test_B/Uebungen_doc/Uebung_004c7.md)
* [Uebung_005](../../../Uebungen/test_B/Uebungen_doc/Uebung_005.md)
* [Uebung_006a3_sub](../../../Uebungen/test_B/Uebungen_doc/Uebung_006a3_sub.md)
* [Uebung_007](../../../Uebungen/test_B/Uebungen_doc/Uebung_007.md)
* [Uebung_007a1](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a1.md)
* [Uebung_007a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_007a2.md)
* [Uebung_010b2](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b2.md)
* [Uebung_010b3](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b3.md)
* [Uebung_010b6](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b6.md)
* [Uebung_010b7](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b7.md)
* [Uebung_010b8](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b8.md)
* [Uebung_010b9](../../../Uebungen/test_B/Uebungen_doc/Uebung_010b9.md)
* [Uebung_010bA](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA.md)
* [Uebung_010bA2](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA2.md)
* [Uebung_010bA3](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA3.md)
* [Uebung_010bA4](../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA4.md)
* [Uebung_035a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a2.md)
* [Uebung_080c](../../../Uebungen/test_B/Uebungen_doc/Uebung_080c.md)
* [Uebung_087](../../../Uebungen/test_B/Uebungen_doc/Uebung_087.md)
* [Uebung_087a1](../../../Uebungen/test_B/Uebungen_doc/Uebung_087a1.md)
* [Uebung_088](../../../Uebungen/test_B/Uebungen_doc/Uebung_088.md)
* [Uebung_089](../../../Uebungen/test_B/Uebungen_doc/Uebung_089.md)
* [Uebung_091](../../../Uebungen/test_B/Uebungen_doc/Uebung_091.md)
* [Uebung_093](../../../Uebungen/test_B/Uebungen_doc/Uebung_093.md)
* [Uebung_093b](../../../Uebungen/test_B/Uebungen_doc/Uebung_093b.md)
* [Uebung_094](../../../Uebungen/test_B/Uebungen_doc/Uebung_094.md)
* [Exercise_094a](../../../Uebungen/test_B/Uebungen_doc/Uebung_094a.md)
* [Exercise_095](../../../Uebungen/test_B/Uebungen_doc/Uebung_095.md)
* [Exercise_152](../../../Uebungen/test_B/Uebungen_doc/Uebung_152.md)
* [Exercise_153](../../../Uebungen/test_B/Uebungen_doc/Uebung_153.md)

## Conclusion
The `E_T_FF` module is a simple yet extremely versatile memory module. Its impulse relay function is fundamental for implementing push-button logic, flashers, and other bistable control circuits in IEC 61499 applications.
