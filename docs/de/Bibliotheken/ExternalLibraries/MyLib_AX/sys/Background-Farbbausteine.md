# Background-Farbbausteine: Gemeinsames Muster

* * * * * * * * * *

## Einleitung

`MyLib::sys` enthält in beiden Trainingssystemen (`test_AX` und `test_B`) eine große Familie fast identischer Bausteine, die **die VT-Hintergrundfarbe eines oder mehrerer Objekte anhand eines einzigen booleschen Signals** umschalten — z. B. `GreenWhiteBackground1_AX`, `GreenRedBackground4_AXS`, `RedWhiteBackground2_AXC`. Diese Seite erklärt das gemeinsame Muster einmal vollständig; die einzelnen Bausteinseiten verweisen hierher zurück und nennen nur noch die konkreten Abweichungen (Farbpaar, Objektanzahl, Variante).

## Namensschema

`<Farbe1><Farbe2>Background<N>[_aux][_AX][S][C]`

| Bestandteil | Bedeutung |
|---|---|
| **Farbpaar** (`GreenWhite`, `GreenRed`, `GreenBlue`, `RedGreen`, `RedWhite`) | `TRUE` → erste Farbe, `FALSE` → zweite Farbe (z. B. `GreenWhiteBackground`: TRUE→Grün, FALSE→Weiß) |
| **N** (1–4) | Anzahl der VT-Objekte, die **gleichzeitig aus demselben Selector-Bit** eingefärbt werden (nicht: Anzahl unabhängiger Kanäle) |
| **`_aux`** (nur bei N=1) | Nutzt `Q_BackgroundColourAux` statt `Q_BackgroundColour` — zielt auf ein ISOBUS-**Auxiliary-Function**-Objekt statt ein normales Softkey-/Button-/DataMask-Objekt. Bei N≥2-Varianten ist diese Rolle ggf. bereits fest in eine der Positionen eingebaut (siehe Einzelseite). |
| **`_AX`** (nur test_AX) | Das Selector-Signal kommt über einen `AX`-Adapter-Socket (`DI1`), nicht als reine Dateneingang. In test_B fehlt dieses Suffix — dort ist `DI1` ein einfacher `BOOL`-Dateneingang. |
| **`S`** | Objekt-ID(s) werden über den strukturierten Typ `isobus::UT::Q::types::s1ObjectID` (`u16ObjIds`, intern per `F_MOVE` entpackt) übergeben statt über einzelne `UINT u16ObjId`-Eingänge — eine spätere Vereinheitlichung der Objekt-ID-Übergabe in der Bibliothek. |
| **`C`** ("Kompakt") | Dünner Wrapper, der nur die Basisvariante (`_AX` bzw. `_AXS`) instanziiert und die `CNF`-Ereignisausgänge/Zwischenwerte (`STATUS_n`, `u8OldColour_n`, `result_n`) nicht nach außen führt — für den Regelfall, wo diese Diagnosewerte nicht gebraucht werden. |

Beispiele: `GreenWhiteBackground1_AX` (Basis, 1 Objekt, Adapter), `GreenWhiteBackground1_AXC` (Kompakt-Wrapper davon), `GreenWhiteBackground1_AXS` (mit Struct-Objekt-ID), `GreenWhiteBackground1_AXSC` (Struct-ID + Kompakt), `GreenWhiteBackground1_aux_AX` (wie Basis, aber AUX-Funktion-Objekt).

## Funktionsweise (Basisvariante, N=1)

1. Das Selector-Signal (`DI1`-Adapter bei `_AX`, sonst `DI1`-Datenwert) geht an `AX_SEL`/`F_SEL` (Binärauswahl), parametriert mit den beiden Farbkonstanten (`IN0`=zweite Farbe, `IN1`=erste Farbe, z. B. `IN0=COLOR_WHITE`, `IN1=COLOR_GREEN`).
2. `AX_SEL.CNF` löst `Q_BackgroundColour.REQ` (bzw. `Q_BackgroundColourAux.REQ` bei `_aux`) aus.
3. `Q_BackgroundColour` setzt die Hintergrundfarbe des per `u16ObjId` identifizierten VT-Objekts und meldet `CNF` mit `STATUS`, `u8OldColour` (vorherige Farbe) und `s16result` (Fehlercode) zurück.

## Funktionsweise (N≥2)

Bei mehreren Objekten (`GreenRedBackground4_AX` u. ä.) gibt es weiterhin **nur einen** Selector (`DI1`/`AX_SEL`), dessen Ausgang parallel an mehrere `Q_BackgroundColour_n`-Instanzen (nummeriert `_1`.._N`) verteilt wird — jede mit eigenem `u16ObjId`/`u16ObjIdA`/`u16ObjIdB` (unterschiedliche Objekt-IDs, teils für unterschiedliche Objektrollen wie Softkey/AUX/Button) und eigenen `STATUS_n`/`u8OldColour_n`/`result_n`/`CNF_n`-Ausgängen. **Welche Position `Q_BackgroundColourAux` statt `Q_BackgroundColour` nutzt, ist pro Baustein individuell** (nicht immer dieselbe Position) — die Einzelseite jedes Bausteins nennt die konkrete Zuordnung.

## Technische Besonderheiten

- **Ein Selector, mehrere Ziele**: Der Sinn von N>1 ist, dieselbe boolesche Bedingung (z. B. "Kanal aktiv") gleichzeitig auf mehrere VT-Repräsentationen desselben logischen Zustands anzuwenden (z. B. Softkey-Hintergrund UND Auxiliary-Function-Hintergrund UND Button-Hintergrund derselben Funktion).
- **`_aux`/`Q_BackgroundColourAux`**: ISOBUS-Auxiliary-Function-Objekte (Bedienelemente, die dem Fahrer frei zuweisbar sind) benötigen einen eigenen Q-Baustein, da sie einen anderen ObjectID-Bereich/eine andere VT-Nachricht verwenden als normale Softkeys/Buttons.
- **`S`-Variante als spätere Vereinheitlichung**: Erkennbar an den späteren `VersionInfo`-Daten (2026 vs. 2022) — die `S`-Varianten sind ein Nachzügler-Refactoring, das die Objekt-ID-Übergabe an einen später etablierten Standard (`s1ObjectID`) angleicht, ohne die älteren Basisvarianten zu ersetzen.

## Übersicht der Familie

| Farbpaar | test_AX (Basis/_aux, jeweils auch S/SC/C) | test_B (Basis/_aux, jeweils auch S/SC/C) |
|---|---|---|
| Green/White | 1, 2, 3, 4 | 1, 2, 3, 4 |
| Green/Red | 1, 2, 3, 4 | 1, 2, 3, 4 |
| Green/Blue | 1 | 1 |
| Red/Green | 1, 4 | 1, 4 |
| Red/White | 1, 2, 3, 4 | 1, 2, 3, 4 |

In test_AX trägt jede Kombination zusätzlich das Suffix `_AX`; in test_B entfällt es (Selector als `BOOL`-Dateneingang statt Adapter-Socket) — siehe [MyLib (test_B) → sys](../../MyLib_B/sys/index.md).

## Zusammenfassung

Die Background-Farbbausteine sind eine einzige wiederkehrende Idee (boolesches Signal → Farbauswahl → `Q_BackgroundColour`) in vielen kleinen Varianten für unterschiedliche Farbpaare, Objektanzahlen und Objekt-ID-Konventionen. Wer eine Variante versteht, versteht alle — die Einzelseiten nennen nur noch die konkreten Parameter.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
