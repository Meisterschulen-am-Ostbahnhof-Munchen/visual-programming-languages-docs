# Scaling

## Grundlegendes

Ja, im **ISOBUS-Standard ISO 11783-6** (Teil 6: **Virtual Terminal**) ist das **Skalieren der Anbaugerätemasken** tatsächlich dem **Anbaugerät (Implement) zugeordnet** und nicht dem virtuellen Terminal (VT).

### Hintergrund

- **ISO 11783-6** definiert die Kommunikation zwischen dem **Virtuellen Terminal (VT)** und den angeschlossenen **Anbaugeräten (Implements)**.
- Die **Darstellung der Benutzeroberfläche** (Masken, Symbole, Texte) wird vom Anbaugerät über **Object Pools** an das VT übertragen.
- Das **Skalieren** der Masken ist notwendig, um die korrekte Darstellung auf unterschiedlichen VT-Bildschirmgrößen und Auflösungen zu gewährleisten.

### Zuständigkeit für das Skalieren

- **Das Anbaugerät ist verantwortlich** für die Skalierung seiner Masken, da es die **Object Pools** bereitstellt und die logische Struktur der Benutzeroberfläche definiert.
- Das VT skaliert Positionen und Größen nicht eigenständig, sondern nutzt die vom Anbaugerät gelieferten Daten (ISO 11783-6, 4.6.16.2). Ausnahme: **Picture-Graphic-Objekte** werden vom VT automatisch anhand ihres Breiten-Attributs skaliert (4.6.16.4).
- Falls das VT eine andere Auflösung hat als vom Anbaugerät erwartet, muss das Anbaugerät die **Skalierungsfaktoren anpassen** (z. B. durch dynamische Generierung der Object Pools oder Nutzung von **Scaled Objects**).

### Praktische Umsetzung

- Das Anbaugerät kann **skalierbare Objekte** (z. B. **Softkeys, Zahlenfelder, Grafiken**) bereitstellen.
- Die **VT-Fähigkeiten** (Größe der Data-Mask-Fläche, Softkey-Designator, Schriften, Farben) fragt das Anbaugerät über die Nachrichten **Get Hardware** und **Get Memory** ab und passt danach seine Object Pools an (ISO 11783-6, 4.6.16.1). Der Device Descriptor gehört nicht zu ISO 11783-6.
- Für Schriften gilt ein **Best-Fit-Algorithmus**; die kleinste Schriftgröße ist 6×8. Unterschreitet die skalierte Schrift 6×8, wird 6×8 verwendet, was zu Clipping oder Textüberlappung führen kann (4.6.16.3).
- Falls keine automatische Skalierung erfolgt, kann es zu Darstellungsproblemen kommen (z. B. abgeschnittene Elemente auf kleinen Displays).

### Fazit

Die ISOBUS-Norm weist die Verantwortung für das Skalieren der Masken klar dem **Anbaugerät** zu, während das VT primär für die korrekte Darstellung der übermittelten Daten zuständig ist. Dies ermöglicht eine flexible Anpassung an verschiedene Terminalgrößen, erfordert aber eine korrekte Implementierung seitens der Anbaugeräte-Hersteller.

## **Skalierungsregeln für ISOBUS-Objekt-IDs (projektinterne Konvention)**

Diese Analyse beschreibt die Skalierungslogik für ISOBUS-Objekte basierend auf **Objekt-ID-Bereichen** gemäß der Referenztabelle. Die Regeln unterscheiden zwischen *DataMask* (skalierte Darstellung) und *SoftkeyMask/Auxiliary* (zentrierte oder kontextabhängige Behandlung).

*Hinweis: Die ISO 11783-6 selbst kennt keine Unterteilung der Type-IDs in ID-Subranges pro Maskentyp und keine Scaling-/Centering-Zuordnung nach Objekt-ID-Bereich – das ist eine reine Konvention dieses Projekts (Object-Pool-Generator), die auf den offiziellen Type-IDs (Table A.1) aufbaut, aber nicht Teil der Norm ist.*

---

### **Kernprinzipien**

1. **DataMask-Objekte** (z. B. Inputs, Outputs, Grafiken):
   - Immer skaliert (Beispiele: `InputNumber: 9000–9999`, `LinearBargraph: 18000–18999`)
2. **SoftkeyMask/Auxiliary-Objekte**:
   - Zentriert (keine Skalierung, z. B. `0: Working Set Object`) oder haben spezielle Regeln (z. B. `5000–5999: Softkey-Buttons`).
3. **Hybrid-Objekte** (getrennte ID-Bereiche):
   - Die Skalierung hängt vom **Bereich der Objekt-ID** ab:
     - **DataMask-Variante**: Skalierung aktiv (z. B. `11000–11499: OutputString`).
     - **SoftkeyMask-Variante**: Skalierung deaktiviert oder anders behandelt (z. B. `11500–11999: OutputString`).

---

### **Kritische Punkte & Handlungsempfehlungen**

#### **1. Überschneidungen und Kontextabhängigkeit**

- **Problem**:
  - Objekte wie `Container` oder `OutputString` existieren in beiden Masken, aber mit unterschiedlichen ID-Bereichen (z. B. `11000–11499` vs. `11500–11999`).
  - **Frage**: Darf ein `OutputString` mit ID `11000` (eigentlich DataMask) auch in einer *SoftkeyMask* verwendet werden?
    - *Hinweis*: ISO 11783-6 definiert keine ID-Bereiche pro Maske (Object IDs müssen lediglich eindeutig sein, 0–65534; 65535 ist die NULL-Object-ID). Die Maskenzugehörigkeit ergibt sich aus dem **Parent-Object-Kontext** (z. B. ein `OutputString` in einem `SoftKeyMask`-Container). Die ID-Bereiche sind eine **projektinterne Konvention**.
  - **Empfehlung**:
    - Im Zweifel den **Parent-Object-Typ** prüfen (z. B. `SoftKeyMask`-Container → Zentrierung).
    - Bei abweichenden IDs ein **Warning-Log** ausgeben, aber Skalierung anhand des Kontexts durchführen.

#### **2. Skalierungsausnahme:**

- **Besonderheit**:
  - Die **PictureGraphic**-Objekte im SoftkeyMask-Bereich (`20500–20999`) sind als *Working Set Bitmaps* deklariert – im Gegensatz zur DataMask-Variante (`20000–20499`).
  - **Warum "Scaling" trotzdem?**
    - Nach ISO 11783-6 (4.6.16.4) skaliert das **VT** Picture Graphics automatisch anhand des **Breiten-Attributs** im Objekt. Das Anbaugerät muss daher nur die Breite (und die Position) anpassen, nicht die Bitmap-Daten.
    - Dass für Softkey-Bitmaps „begrenzte Skalierung“ nach internen Regeln gelte, ist **keine Vorgabe der Norm**; im Projekt entscheidet allein der ID-Bereich über die Behandlung.

#### **3. Auxiliary Functions (`31000–31999`) – Zentrierungspflicht**

- **Problem**:
  - Auxiliary-Objekte müssen laut Projektkonvention **immer zentriert** werden (keine Skalierung; die Norm schreibt das nicht vor).
  - **Risiko**: Wenn ein Auxiliary-Object fälschlich im DataMask-Bereich platziert wird (z. B. ID `31500`), könnte die Skalierung die Darstellung brechen.

#### **4. Fehlende Klarheit bei "Working Set Object" (ID 0)**

- **Besonderheit**:
  - Das "Working Set Object" (ID 0) ist **immer zentriert** und gilt nur für die *SoftkeyMask*.
  - **Achtung**: Wenn ein DataMask-Container fälschlich ID 0 referenziert, sollte dies als Fehler behandelt werden.

---

### **Hinweise zur Anwendung**

- **Pfeile (→)**: Markieren korrespondierende ID-Bereiche für Hybrid-Objekte.
- **"x"**: Keine Zuordnung in diesem Kontext.
- **ISO-Konformität**: Die verwendeten Type-IDs entsprechen ISO 11783-6 (Table A.1); die ID-Subranges und die Scaling-/Centering-Zuordnung je Bereich sind jedoch eine projektinterne Konvention und keine Norm-Vorgabe. Dass die Skalierungslast grundsätzlich beim Anbaugerät liegt, folgt aus dem allgemeinen VT-Konzept der Norm (siehe „Grundlegendes" oben).

Die strikte Einhaltung der ID-Bereiche durch das Anbaugerät ist entscheidend.

## **Tabelle**

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

Wo keine Operation (Scaling, Centering) angegeben ist, wird das Objekt nicht manipuliert. Die Tabelle enthält nicht alle Objekttypen aus ISO 11783-6 Table A.1 (z. B. Window Mask, Graphics Context, Extended Input Attributes, Colour Map, Animation fehlen); für diese erfolgt keine ID-bereichsbasierte Manipulation.

**(\*) Sonderfall Macro:** Das Macro-Objekt selbst hat keine Pixel-Felder, kann aber Befehle mit fest codierten Pixelwerten enthalten (z. B. Change Child Position). Diese eingebetteten Werte werden vom ID-Bereichs-Scaling-Mechanismus nicht erfasst, da dieser nur Objekt-Definitionen beim Pool-Load skaliert, nicht den Befehls-Bytestrom innerhalb eines Macros.

**(\*\*) V1-Aux-Objekte (AuxFunction1, AuxInput1):** logiBUS konvertiert diese immer per `AuxToV2` aus dem jeweiligen V2-Pendant (`AuxFunction2`/`AuxInput2`) — sie kommen in einem Pool daher nie tatsächlich vor, nur der Vollständigkeit halber gelistet.

---
