# Scaling

Yes, in the **ISOBUS standard ISO 11783-6** (Part 6: **Virtual Terminal**), **scaling the implement screens** is indeed assigned to the **implement** and not to the virtual terminal (VT).

- **ISO 11783-6** defines the communication between the **Virtual Terminal (VT)** and the connected **implements**.
- The **user interface display** (screens, icons, text) is transferred from the implement to the VT via **object pools**.
- **Scaling** the screens is necessary to ensure correct display on different VT screen sizes and resolutions.
- **The implement is responsible** for scaling its screens, as it provides the **object pools** and defines the logical structure of the user interface.
- If the VT has a different resolution than expected by the attachment, the attachment must adjust the **scaling factors** (e.g., by dynamically generating object pools or using **scaled objects**).
- The attachment can provide **scalable objects** (e.g., **softkeys, numeric fields, graphics**).
- The **VT resolution** is communicated in the **device descriptor**, allowing the attachment to adjust the screens accordingly.
- If automatic scaling does not occur, display problems may arise (e.g., cut-off elements on small displays).

The ISOBUS standard clearly assigns the responsibility for scaling the screens to the **attachment**, while the VT is primarily responsible for the correct display of the transmitted data. This allows for flexible adaptation to different terminal sizes, but requires correct implementation by the implement manufacturers.

### Conclusion

### Praktische Umsetzung

### Zuständigkeit für das Skalieren

### Hintergrund

## Grundlegendes

## **Scaling Rules for ISOBUS Objects (ISO 11783-6)**

This analysis describes the scaling logic for ISOBUS objects based on **object ID ranges** according to the reference table. The rules distinguish between *DataMask* (scaled display) and *SoftkeyMask/Auxiliary* (centered or context-dependent handling).

---

### **Core Principles**

1. **DataMask Objects** (e.g., Inputs, Outputs, Graphics):

- Always scaled (Examples: `InputNumber: 9000–9999`, `LinearBargraph: 18000–18599`)
1. **SoftkeyMask/Auxiliary Objects**:

- Centered (no scaling, e.g., `0: Working Set Object`) or have special rules (e.g., `5000–5999: Softkey-Buttons`).
1. **Hybrid Objects** (separate ID ranges):

- Scaling depends on the **object ID range**:
- **DataMask Variant**: Scaling is active (e.g., `11000–11499: OutputString`).
- **SoftkeyMask Variant**: Scaling is disabled or handled differently (e.g., `11500–11999: OutputString`).

--

- **Problem**:
- Objects like `Container` or `OutputString` exist in both masks, but with different ID ranges (e.g., `11000–11499` vs. `11500–11999`).
- **Question**: Can a `OutputString` with ID `11000` (actually a DataMask) also be used in a *SoftkeyMask*?
- *ISO 11783-6 rule*: Mask membership is primarily defined by the **parent object context** (e.g., a `OutputString` in a `SoftKeyMask` container). The ID ranges are **recommended defaults**, but not mandatory.
- **Recommendation**:
- When in doubt, check the **parent object type** (e.g., `SoftKeyMask` container → centering).
- For differing IDs, issue a **warning log**, but scale based on the context.
- **Special Feature**:
- The **PictureGraphic** objects in the SoftkeyMask area (`20500–20999`) are declared as *Working Set Bitmaps* – unlike the DataMask variant (`20000–20499`).
- **Why "Scaling" Still?**
- Although these bitmaps are treated as part of the *Working Set*, they are still subject to **limited scaling** (e.g., for resolution adjustments or icon size control).
- *Difference from DataMask*: Here, scaling is **not viewport-relative**, but follows internal rules (e.g., fixed scaling factors for menu icons).

#### **2. Skalierungsausnahme:**

#### **1. Überschneidungen und Kontextabhängigkeit**

### **Kritische Punkte & Handlungsempfehlungen**

#### **3. Auxiliary Functions (`31000–31999`) – Centering Requirement**

- **Problem**:
- According to the standard, auxiliary objects must **always be centered** (no scaling).
- **Risk**: If an auxiliary object is incorrectly placed in the DataMask area (e.g., ID `31500`), the following may occur:), scaling could break the display.

#### **4. Lack of Clarity with "Working Set Object" (ID 0)**

- **Special Feature**:
- The "Working Set Object" (ID 0) is **always centered** and applies only to the *SoftkeyMask*.
- **Caution**: If a DataMask container incorrectly references ID 0, this should be treated as an error.

---

- **Arrows (→)**: Mark corresponding ID ranges for hybrid objects.
- **"x"**: No mapping in this context.
- **ISO Compliance**: The table follows ISO 11783-6, with the scaling load on the attachment.

Strict adherence to the ID ranges by the attachment is crucial.

### **Hinweise zur Anwendung**

## **Table**

| DATA MASK | | SOFTKEY MASK & AUX |
| ------------------------------------------------- | --------- | ------------------------------------------------ |
| x | | 0 - 0 - Centering - Working set object |
| 1000 - 1999 - Scaling - DataMask | | x |
| 2000 - 2999 - Scaling - AlarmMask | | |
| 3000 - 3499 - Scaling - Containers | → | 3500 - 3999 - Scaling - Containers |
| 6000 - 6999 - Scaling - Button | → | 5000 - 5999 - Centering – Softkeys |
| 7000 - 7999 - Scaling - InputBoolean | | |
| 8000 - 8999 - Scaling - InputString | | |
| 9000 - 9999 - Scaling - InputNumber | | |
| 10000 - 10999 - Scaling - InputList | | |
| 11000 - 11499 - Scaling - OutputString | → | 11500 - 11999 - Scaling – OutputString |
| 12000 - 12499 - Scaling - OutputNumber | → | 12500 - 12999 - Scaling - OutputNumber |
| 13000 - 13499 - Scaling - Line | → | 13500 - 13999 - Scaling Line |
| 14000 - 14499 - Scaling - Rectangle | → | 14500 - 14999 - Scaling - Rectangle |
| 15000 - 15499 - Scaling - Ellipse | → | 15500 - 15999 - Scaling - Ellipse |
| 16000 - 16499 - Scaling - Polygon | → | 16500 - 16999 - Scaling – Polygon |
| 17000 - 17599 - Scaling - Meter | | |
| 18000 - 18599 - Scaling - LinearBargraph | | |
| 19000 - 19599 - Scaling - ArchedBargraph | | |
| 20000 - 20499 - Scaling - PictureGraphic | → | 20500 - 20999 - Scaling - Working set bitmaps |
| 23000 - 23499 - Scaling - FontAttributes | → | 23500 - 23999 - Scaling - FontAttributes |
| 24000 - 24499 - Scaling - LineAttributes | → | 24500 - 24900 - Scaling - LineAttributes |
| 25000 - 25499 - Scaling - FillAttributes | → | 25500 - 25999 - Scaling – FillAttributes |
| 30000 - 30999 - Scaling – OutputList | | |
| | | 31000 - 31999 - Centering - Auxiliary function |

---
