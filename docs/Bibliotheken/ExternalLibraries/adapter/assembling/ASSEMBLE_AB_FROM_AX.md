# ASSEMBLE_AB_FROM_AX


![ASSEMBLE_AB_FROM_AX](./ASSEMBLE_AB_FROM_AX.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASSEMBLE_AB_FROM_AX** fasst acht boolesche Einzelsignale, die über AX‑Adapter (unidirektional, Bool) bereitgestellt werden, zu einem Byte zusammen und gibt dieses über einen AB‑Adapter (unidirektional, BYTE) aus. Er kapselt die Logik zur Byte‑Erzeugung und stellt eine modulare, adapterbasierte Schnittstelle für die Verarbeitung von 8 Bit zur Verfügung.

## Schnittstellenstruktur

### **Ereignis‑Eingänge**
Keine. Ereignisse werden ausschließlich über die Adapter‑Sockets empfangen.

### **Ereignis‑Ausgänge**
Keine. Ereignisse werden ausschließlich über den Adapter‑Plug ausgegeben.

### **Daten‑Eingänge**
Keine. Alle Daten werden über die Adapter‑Sockets übertragen.

### **Daten‑Ausgänge**
Keine. Alle Daten werden über den Adapter‑Plug ausgegeben.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** (Eingang) | `BIT_00` | `adapter::types::unidirectional::AX` | Boolescher Wert für Bit 0 (niederwertigstes Bit) |
| | `BIT_01` | `adapter::types::unidirectional::AX` | Boolescher Wert für Bit 1 |
| | `BIT_02` | `adapter::types::unidirectional::AX` | Boolescher Wert für Bit 2 |
| | `BIT_03` | `adapter::types::unidirectional::AX` | Boolescher Wert für Bit 3 |
| | `BIT_04` | `adapter::types::unidirectional::AX` | Boolescher Wert für Bit 4 |
| | `BIT_05` | `adapter::types::unidirectional::AX` | Boolescher Wert für Bit 5 |
| | `BIT_06` | `adapter::types::unidirectional::AX` | Boolescher Wert für Bit 6 |
| | `BIT_07` | `adapter::types::unidirectional::AX` | Boolescher Wert für Bit 7 (höchstwertiges Bit) |
| **Plug** (Ausgang) | `OUT` | `adapter::types::unidirectional::AB` | Zusammengesetztes Byte (BYTE) |

Jeder AX‑Adapter stellt über seinen Daten‑Eingang `D1` den Bool‑Wert und über seinen Ereignis‑Eingang `E1` das zugehörige Ereignis bereit. Der AB‑Adapter liefert über seinen Daten‑Ausgang `D1` das Byte und über den Ereignis‑Ausgang `E1` das Bestätigungsereignis.

## Funktionsweise

Der Funktionsblock ist als zusammengesetzter Baustein realisiert und besteht intern aus:

1. **ASSEMBLE_BYTE_FROM_BOOLS** – Nimmt die acht Bool‑Werte (von `BIT_00` bis `BIT_07`) entgegen und setzt daraus ein Byte zusammen.
2. **E_D_FF_ANY** – Ein D‑Flipflop, das den berechneten Byte‑Wert puffert und erst bei einer positiven Flanke am Takteingang weitergibt.

Ablauf:

- Sobald an **einem** der AX‑Adapter (z. B. `BIT_00`) ein Ereignis eintrifft, wird dieses an den `REQ`‑Eingang des internen Bausteins **ASSEMBLE_BYTE_FROM_BOOLS** weitergeleitet.
- Der interne Baustein berechnet aus den aktuellen Bool‑Werten aller acht Adapter das Byte und legt es an seinem Datenausgang an.
- Nach Abschluss der Berechnung sendet `ASSEMBLE_BYTE_FROM_BOOLS` ein `CNF`‑Ereignis, das den Takteingang (`CLK`) des D‑Flipflops **E_D_FF_ANY** triggert.
- Das Flipflop übernimmt den aktuellen Byte‑Wert und gibt ihn an seinem Ausgang `Q` aus.
- Gleichzeitig wird das Ereignis `EO` des Flipflops an den Ereignis‑Ausgang `OUT.E1` des AB‑Adapters weitergegeben.

Dadurch wird sichergestellt, dass das Ausgangs‑Byte nur dann aktualisiert wird, wenn sich ein Eingangs‑Bit geändert hat, und dass die Ausgabe stabil und synchronisiert erfolgt.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle** – Der Baustein verwendet ausschließlich Adapter (`AX`/`AB`) anstelle einzelner Ereignis‑ und Daten‑Ports. Dies ermöglicht eine einfache Kapselung und Wiederverwendung in modularen Entwürfen.
- **Internes D‑Flipflop** – Das Flipflop verhindert Zwischenzustände und gibt das fertige Byte erst frei, nachdem die Berechnung abgeschlossen ist. Es fungiert zudem als Puffer, falls mehrere Eingangsereignisse kurz hintereinander eintreffen.
- **Effiziente Ereignissteuerung** – Jedes Ereignis an einem der acht AX‑Sockets löst eine Neuberechnung aus. Überflüssige Aktualisierungen werden vermieden, da die Ausgabe nur nach einem Takt erfolgt.

## Zustandsübersicht

Der Funktionsblock besitzt keine eigene Zustandsmaschine; er ist als reines Netzwerk aus zwei Unterbausteinen aufgebaut. Sein Verhalten wird vollständig durch die interne Logik von **ASSEMBLE_BYTE_FROM_BOOLS** und **E_D_FF_ANY** bestimmt.

## Anwendungsszenarien

- **Zusammenfassen von 8 digitalen Sensoren** – z. B. Endschalter, Lichtschranken oder Binäreingänge einer SPS, deren Zustände als Byte übertragen werden sollen.
- **Bit‑parallele Datenübertragung** – Umwandlung eines 8‑Bit‑parallelen Signals in ein serielles Byte für einen weiteren Baustein (z. B. über Adapter‑Kopplung).
- **Modulare Automatisierungsfunktionen** – Einbindung in Hierarchien, bei denen mehrere `ASSEMBLE_AB_FROM_AX`‑Blöcke verwendet werden, um größere Datenwörter (z. B. WORD, DWORD) zusammenzusetzen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung | Unterschied |
|----------|--------------|-------------|
| `ASSEMBLE_BYTE_FROM_BOOLS` | Interner Baustein, der aus 8 Bool‑Eingängen ein Byte erzeugt (ohne Adapter) | `ASSEMBLE_AB_FROM_AX` kapselt diesen Baustein und verwendet Adapter für die Anbindung. |
| `eclipse4diac::utils::assembling::ASSEMBLE_BYTE_FROM_BOOLS` | Gleiche Funktion, aber mit direkten Ereignis‑/Datenports | `ASSEMBLE_AB_FROM_AX` bietet eine adapterbasierte Schnittstelle und fügt ein D‑Flipflop zur Synchronisation hinzu. |
| Selbst erstellter Byte‑Assembler | Beliebig realisierbar, z. B. mit ST‑Algorithmus | Adapter `AX`/`AB` sind vordefinierte Standard‑Typen in 4diac, die Wiederverwendbarkeit und Austauschbarkeit fördern. |

## Fazit

Der Funktionsblock **ASSEMBLE_AB_FROM_AX** ist ein praktischer, adapterbasierter Helfer, um acht boolesche Signale in ein Byte zu konvertieren. Durch die Integration eines D‑Flipflops arbeitet er zuverlässig und vermeidet inkonsistente Zwischenzustände. Sein modulares Design erleichtert die Wiederverwendung in größeren Projektstrukturen und macht ihn zu einer nützlichen Komponente in der Automatisierungstechnik mit 4diac.