# GreenRedBackground4

![GreenRedBackground4_network](./GreenRedBackground4_network.svg)

* * * * * * * * * *

## Einleitung

`GreenRedBackground4` schaltet die VT-Hintergrundfarbe von 4 Objekten anhand eines booleschen Selector-Signals: `TRUE` → **Grün**, `FALSE` → **Rot**. Das Selector-Signal kommt als einfacher `BOOL`-Dateneingang (`DI1`). Die Objekt-ID wird über die Eingänge `u16ObjId, u16ObjIdA, u16ObjIdB` übergeben.

| Position | Objekt-ID-Quelle | Baustein |
|---|---|---|
| 1 | `u16ObjId` | `Q_BackgroundColour` (normales Objekt) |
| 2 | `u16ObjIdA` | `Q_BackgroundColour` (normales Objekt) |
| 3 | `u16ObjIdA` | `Q_BackgroundColourAux` (Auxiliary-Function-Objekt) |
| 4 | `u16ObjIdB` | `Q_BackgroundColour` (normales Objekt) |

Allgemeines Muster (Selector → `AX_SEL`/`F_SEL` → `Q_BackgroundColour`) siehe [Background-Farbbausteine (gemeinsames Muster)](../../MyLib_AX/sys/Background-Farbbausteine.md).

## Zusammenfassung

Eine von vielen Varianten der Background-Farbbausteine-Familie: Farbpaar Grün/Rot, 4 Objekte, BOOL-Selector.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
