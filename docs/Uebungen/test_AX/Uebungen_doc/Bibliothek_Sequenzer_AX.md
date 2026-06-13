# 📚 Bibliotheken: Sequenzer (AX Adapter)



Dieser Abschnitt beschreibt die in der logiBUS®-Bibliothek verfügbaren Sequenzer-Bausteine, die für die Verwendung mit dem **AX Adapter** optimiert sind.

---

## ℹ️ Allgemeines

Die Sequenzer-Bausteine ermöglichen die Implementierung von Schrittketten (Sequential Function Charts). Die AX-Versionen zeichnen sich dadurch aus, dass sie **AX-Adapter** (Plug/Socket) für die Ansteuerung der Ausgänge nutzen. Dies reduziert den Verdrahtungsaufwand erheblich, da Status-Events und Datenbits in einer Verbindung gebündelt werden.

---

## ⚙️ Event-gesteuerte Sequenzer (`sequence_ET_xx_AX`)

Diese Bausteine schalten zum nächsten Schritt, wenn entweder ein externes Ereignis (`S1_S2`, `S2_S3`, etc.) eintritt oder eine definierte Zeit (`DT_S*_S*`) abgelaufen ist.

### Verfügbare Typen
- `sequence_ET_04_AX`: 4 Schritte, 4 Ausgänge.
- `sequence_ET_04_loop_AX`: 4 Schritte, zyklisch (loop).
- `sequence_ET_05_AX`: 5 Schritte, 5 Ausgänge.
- `sequence_ET_05_loop_AX`: 5 Schritte, zyklisch.
- `sequence_ET_08_AX`: 8 Schritte, 8 Ausgänge.
- `sequence_ET_08_loop_AX`: 8 Schritte, zyklisch.

---

## ⚙️ Zeit-gesteuerte Sequenzer (`sequence_T_xx_AX`)

Diese Bausteine schalten automatisch nach Ablauf der für den jeweiligen Schritt definierten Zeit weiter.

### Verfügbare Typen
- `sequence_T_04_AX`: 4 Schritte, zeitgesteuert.
- `sequence_T_04_loop_AX`: 4 Schritte, zyklisch.
- `sequence_T_05_AX`: 5 Schritte, zeitgesteuert.
- `sequence_T_05_loop_AX`: 5 Schritte, zyklisch.
- `sequence_T_08_AX`: 8 Schritte, zeitgesteuert.
- `sequence_T_08_loop_AX`: 8 Schritte, zyklisch.

---

## ⚙️ Pattern-Sequenzer (Nockenschaltwerke)

Die Pattern-Sequenzer (`sequence_Pattern_xx_AX`) ermöglichen es, für jeden Schritt ein individuelles Bitmuster (Pattern) für die Ausgänge zu definieren. Dies ist ideal für Anwendungen, bei denen in einem Schritt mehrere Aktoren gleichzeitig in bestimmten Mustern geschaltet werden müssen.

### Verfügbare Typen
- **[sequence_Pattern_04_04_loop_AX](../.lib/logiBUS-3.0.0/typelib/utils/sequence/pattern/sequence_Pattern_04_04_loop_AX.md)**: 4 Schritte, 4 Ausgänge, zyklisch.
- **[sequence_Pattern_08_08_loop_AX](../.lib/logiBUS-3.0.0/typelib/utils/sequence/pattern/sequence_Pattern_08_08_loop_AX.md)**: 8 Schritte, 8 Ausgänge, zyklisch.

### Funktionsweise
Jeder Zustand `S1` bis `Sx` hat einen zugehörigen Eingang `P_S1` bis `P_Sx` vom Typ `BYTE`. Die einzelnen Bits dieses Bytes steuern die Adapter-Ausgänge `Q1` bis `Qx`:
- Bit 0 -> Ausgang Q1
- Bit 1 -> Ausgang Q2
- ...und so weiter.

Beim Übergang in einen neuen Zustand wird das entsprechende Muster sofort an die Ausgänge angelegt.

---

## ⚙️ Reine Event-Sequenzer (`sequence_E_xx_AX`)

Im Gegensatz zur `ET`-Serie besitzen diese Bausteine **keine integrierte Zeitüberwachung**. Ein Weiterschalten erfolgt ausschließlich durch externe Ereignis-Signale.

### Verfügbare Typen
- `sequence_E_04_AX`: 4 Schritte.
- `sequence_E_04_loop_AX`: 4 Schritte, zyklisch.
- `sequence_E_05_AX`: 5 Schritte.
- `sequence_E_05_loop_AX`: 5 Schritte, zyklisch.
- `sequence_E_08_AX`: 8 Schritte.
- `sequence_E_08_loop_AX`: 8 Schritte, zyklisch.

---

## ⚙️ Spezialisierte Sequenz-Bausteine

Neben den universellen Schrittketten gibt es spezialisierte Bausteine für häufig vorkommende Aufgabenstellungen.

### Schiebersteuerung (`SchieberControl_AX`)
Dieser Baustein dient zur sequentiellen Ansteuerung von Schiebern oder Ventilen mit Endlagenrückmeldung. Er bündelt die Logik für das Öffnen/Schließen und die Überwachung der Laufzeit.

### Links-Rechts-Verteiler (`LinksRechts_AX`)
Spezialbaustein für Anwendungen wie z.B. Förderbänder oder Weichen, die zwischen zwei Richtungen oder Zuständen hin- und herschalten müssen, inklusive der notwendigen Verriegelungen und Umschaltpausen.

---

## 🔌 Schnittstellenbeschreibung (Beispiel AX)

| Anschluss | Typ | Beschreibung |
| :--- | :--- | :--- |
| **Plugs (Ausgänge)** | `adapter::types::unidirectional::AX` | Gebündelte Ausgänge für Daten und Events. |
| **START_S1** | `Event` | Startet die Sequenz im ersten Schritt. |
| **RESET** | `Event` | Setzt die Sequenz sofort auf den Initialzustand (START) zurück. |
| **STATE_NR** | `SINT` | Aktuelle Schrittnummer (0 = START, 1 = S1, ...). |
| **timeOut** | `adapter` | Adapter zur Anbindung eines Time-Out-Managements. |

---

## 🛠️ Zugehörige Übungen

- [Uebung_035a1_AX](Uebung_035a1_AX.md) (Nutzung von `sequence_Pattern_04_04_loop_AX`)
- [Uebung_039_AX](Uebung_039_AX.md) (Nutzung von `sequence_ET_05_AX`)
