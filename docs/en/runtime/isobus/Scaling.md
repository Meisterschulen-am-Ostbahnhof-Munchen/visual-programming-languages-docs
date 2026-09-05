# Scaling

## Basics

Yes, in the **ISOBUS standard ISO 11783-6** (Part 6: **Virtual Terminal**), **scaling the implement's masks** is indeed assigned to the **implement** and not to the Virtual Terminal (VT).

### Background

- **ISO 11783-6** defines the communication between the **Virtual Terminal (VT)** and the connected **implements**.
- The **user interface presentation** (masks, icons, texts) is transferred from the implement to the VT via **object pools**.
- **Scaling** the masks is necessary to ensure correct presentation across different VT screen sizes and resolutions.

### Responsibility for scaling

- **The implement is responsible** for scaling its masks, since it provides the **object pools** and defines the logical structure of the user interface.
- The VT does not perform scaling on its own; it uses the data supplied by the implement.
- If the VT has a different resolution than the implement expects, the implement must adjust the **scaling factors** (e.g. by dynamically generating the object pools or using **scaled objects**).

### Practical implementation

- The implement can provide **scalable objects** (e.g. **softkeys, numeric fields, graphics**).
- The **VT resolution** is communicated in the **device descriptor**, so the implement can adapt its masks accordingly.
- If no automatic scaling occurs, display problems can result (e.g. clipped elements on small displays).

### Conclusion

The ISOBUS standard clearly assigns responsibility for scaling the masks to the **implement**, while the VT is primarily responsible for correctly presenting the transmitted data. This allows flexible adaptation to different terminal sizes, but requires correct implementation on the part of implement manufacturers.

## **Scaling rules for ISOBUS object IDs (project-internal convention)**

This analysis describes the scaling logic for ISOBUS objects based on **object ID ranges** according to the reference table. The rules distinguish between *DataMask* (scaled presentation) and *SoftKeyMask/Auxiliary* (centered or context-dependent handling).

*Note: ISO 11783-6 itself does not define any subdivision of the Type IDs into ID subranges per mask type, nor any scaling/centering assignment by object ID range - this is a purely project-internal convention (of this project's object pool generator) that builds on the official Type IDs (Table A.1) but is not part of the standard.*

---

### **Core principles**

1. **DataMask objects** (e.g. inputs, outputs, graphics):
   - Always scaled (examples: `InputNumber: 9000–9999`, `LinearBargraph: 18000–18599`)
2. **SoftKeyMask/Auxiliary objects**:
   - Centered (no scaling, e.g. `0: Working Set Object`) or have special rules (e.g. `5000–5999: softkey buttons`).
3. **Hybrid objects** (separate ID ranges):
   - Scaling depends on the **object ID range**:
     - **DataMask variant**: scaling active (e.g. `11000–11499: OutputString`).
     - **SoftKeyMask variant**: scaling disabled or handled differently (e.g. `11500–11999: OutputString`).

---

### **Critical points & recommendations**

#### **1. Overlaps and context-dependency**

- **Problem**:
  - Objects such as `Container` or `OutputString` exist in both mask types, but with different ID ranges (e.g. `11000–11499` vs. `11500–11999`).
  - **Question**: May an `OutputString` with ID `11000` (actually DataMask) also be used in a *SoftKeyMask*?
    - *ISO 11783-6 rule*: Mask membership is primarily defined by the **parent-object context** (e.g. an `OutputString` inside a `SoftKeyMask` container). The ID ranges are **recommended defaults**, but not mandatory.
  - **Recommendation**:
    - When in doubt, check the **parent object type** (e.g. `SoftKeyMask` container → centering).
    - For deviating IDs, log a **warning**, but scale based on context.

#### **2. Scaling exception**

- **Special case**:
  - The **PictureGraphic** objects in the SoftKeyMask range (`20500–20999`) are declared as *Working Set Bitmaps* - unlike the DataMask variant (`20000–20499`).
  - **Why "Scaling" anyway?**
    - These bitmaps are treated as part of the *Working Set*, but are nevertheless subject to **limited scaling** (e.g. for resolution adjustments or icon-size control).
    - *Difference from DataMask*: scaling here is **not viewport-relative**, but follows internal rules (e.g. fixed scaling factors for menu icons).

#### **3. Auxiliary Functions (`31000–31999`) - centering requirement**

- **Problem**:
  - Auxiliary objects must **always be centered** per convention (no scaling).
  - **Risk**: If an auxiliary object is incorrectly placed in the DataMask range (e.g. ID `31500`), scaling could break the display.

#### **4. Lack of clarity for "Working Set Object" (ID 0)**

- **Special case**:
  - The "Working Set Object" (ID 0) is **always centered** and applies only to the *SoftKeyMask*.
  - **Caution**: If a DataMask container incorrectly references ID 0, this should be treated as an error.

---

### **Notes on usage**

- **Arrows (→)**: mark corresponding ID ranges for hybrid objects.
- **"x"**: no mapping in this context.
- **ISO compliance**: the Type IDs used correspond to ISO 11783-6 (Table A.1); the ID subranges and the scaling/centering assignment per range are, however, a project-internal convention and not a standard requirement. That the scaling load lies with the implement in general follows from the standard's general VT concept (see "Basics" above).

Strict adherence to the ID ranges by the implement is essential.

## **Table**

| DATA MASK                                |         | SOFTKEY MASK & AUX                             |
|------------------------------------------|---------|------------------------------------------------|
| x                                        |         | 0 -    0 - Centering - Working set object      |
| 1 - 999 - Macro (*)                      |         | x                                              |
| 1000 - 1999 - Scaling - DataMask         |         | x                                              |
| 2000 - 2999 - Scaling - AlarmMask        |         |                                                |
| 3000 - 3499 - Scaling - Container        | →       | 3500 - 3999 - Scaling - Container              |
|                                          |         | 4000 - 4999 - SoftKeyMask                      |
| 6000 - 6999 - Scaling - Button           | →       | 5000 - 5999 - Centering – Softkeys             |
| 7000 - 7999 - Scaling - InputBoolean     |         |                                                |
| 8000 - 8999 - Scaling - InputString      |         |                                                |
| 9000 - 9999 - Scaling - InputNumber      |         |                                                |
| 10000 - 10999 - Scaling - InputList      |         |                                                |
| 11000 - 11499 - Scaling - OutputString   | →       | 11500 - 11999 - Scaling – OutputString         |
| 12000 - 12499 - Scaling - OutputNumber   | →       | 12500 - 12999 - Scaling - OutputNumber         |
| 13000 - 13499 - Scaling - Line           | →       | 13500 - 13999 - Scaling - Line                 |
| 14000 - 14499 - Scaling - Rectangle      | →       | 14500 - 14999 - Scaling - Rectangle            |
| 15000 - 15499 - Scaling - Ellipse        | →       | 15500 - 15999 - Scaling - Ellipse              |
| 16000 - 16499 - Scaling - Polygon        | →       | 16500 - 16999 - Scaling – Polygon              |
| 17000 - 17999 - Scaling - Meter          |         |                                                |
| 18000 - 18999 - Scaling - LinearBargraph |         |                                                |
| 19000 - 19999 - Scaling - ArchedBargraph |         |                                                |
| 20000 - 20499 - Scaling - PictureGraphic | →       | 20500 - 20999 - Scaling - Working set bitmaps  |
| 21000 - 21999 - NumberVariable           |         |                                                |
| 22000 - 22999 - StringVariable           |         |                                                |
| 23000 - 23499 - Scaling - FontAttributes | →       | 23500 - 23999 - Scaling - FontAttributes       |
| 24000 - 24499 - Scaling - LineAttributes | →       | 24500 - 24999 - Scaling - LineAttributes       |
| 25000 - 25499 - Scaling - FillAttributes | →       | 25500 - 25999 - Scaling – FillAttributes       |
| 26000 - 26999 - InputAttributes         |         |                                                |
| 27000 - 27999 - ObjectPointer           |         |                                                |
|                                          |         | 29000 - 29999 - AuxFunction1 (**)              |
|                                          |         | 30000 - 30999 - AuxInput1 (**)                 |
|                                          |         | 31000 - 31999 - Centering - AuxFunction2       |
|                                          |         | 32000 - 32999 - Centering - AuxInput2          |
|                                          |         | 33000 - 33999 - AuxObjectPointer               |
|                                          |         | 35000 - 35999 - Centering - KeyGroup           |
| 37000 - 37999 - Scaling – OutputList     |         |                                                |

Where no operation (Scaling, Centering) is listed, the object is not manipulated.

**(\*) Special case Macro:** the Macro object itself has no pixel fields, but it can contain commands with hardcoded pixel values (e.g. Change Child Position). These embedded values are not covered by the ID-range scaling mechanism, since it only scales object *definitions* at pool load, not the command byte stream inside a macro.

**(\*\*) V1 Aux objects (AuxFunction1, AuxInput1):** logiBUS always converts these from their V2 counterpart (`AuxFunction2`/`AuxInput2`) via `AuxToV2` - they never actually occur in a pool, and are listed here for completeness only.

---
