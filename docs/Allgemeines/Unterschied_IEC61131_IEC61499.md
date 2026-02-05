# ⚖️ Unterschied zwischen IEC 61131-3 und IEC 61499

Die Normen **IEC 61131-3** und **IEC 61499** definieren beide Standards für die Programmierung von industriellen Steuerungssystemen, verfolgen jedoch unterschiedliche Ansätze in Bezug auf Architektur und Ausführung.

## 1. Architekturmodell

### IEC 61131-3: Zentrale Steuerung
Die IEC 61131-3 wurde primär für **speicherprogrammierbare Steuerungen (SPS)** entwickelt. Das Modell geht von einer zentralen Recheneinheit aus, die ein Programm ausführt.
*   **Struktur:** Konfiguration -> Ressource -> Task -> Programm -> Funktionsbausteine/Funktionen.
*   **Fokus:** Ein einzelnes Gerät steuert einen Prozess.

### IEC 61499: Verteilte Systeme
Die IEC 61499 erweitert die Konzepte der IEC 61131-3 für **verteilte Systeme**. Eine Applikation kann auf mehrere Geräte (Devices) und Ressourcen verteilt werden, ohne dass die Funktionalität neu programmiert werden muss.
*   **Struktur:** System -> Gerät -> Ressource -> Applikation -> Funktionsbausteine.
*   **Fokus:** Funktionale Einheiten (Software-Bausteine) kommunizieren über Ereignisse und Daten, unabhängig davon, auf welcher Hardware sie laufen.

## 2. Ausführungsmodell

Der wohl wichtigste Unterschied liegt in der Art und Weise, wie Code ausgeführt wird.

### IEC 61131-3: Zyklisch (Scan-basiert)
In der klassischen SPS-Welt folgt die Ausführung meist einem starren Zyklus:
1.  **Eingänge lesen:** Alle physikalischen Eingänge werden in das Prozessabbild eingelesen.
2.  **Programm ausführen:** Der Code wird von oben nach unten (oder nach Task-Priorität) abgearbeitet.
3.  **Ausgänge schreiben:** Die berechneten Werte werden auf die physikalischen Ausgänge geschrieben.

Dieser Zyklus wiederholt sich ständig (z. B. alle 10 ms). Ein Funktionsbaustein wird in jedem Zyklus aufgerufen, unabhängig davon, ob sich seine Eingangsdaten geändert haben.

### IEC 61499: Ereignisgesteuert (Event-driven)
Die Ausführung in IEC 61499 basiert auf **Ereignissen (Events)**.
*   Ein Funktionsbaustein tut **nichts**, solange kein Ereignis an einem seiner Ereignis-Eingänge (Event Inputs) eintrifft.
*   Wenn ein Ereignis eintrifft (z. B. `REQ` für Request), wird der Baustein "geweckt".
*   Die **Ausführungssteuerung (ECC)** entscheidet dann, welche Algorithmen ausgeführt und welche Ausgangs-Ereignisse (z. B. `CNF` für Confirmation) gefeuert werden.
*   Es gibt keinen globalen Zyklus; die Ausführungskette wird durch den Fluss von Ereignissen bestimmt.

## 3. Funktionsbausteine im Vergleich

| Merkmal | IEC 61131-3 FB | IEC 61499 FB |
| :--- | :--- | :--- |
| **Schnittstelle** | Nur Daten (VAR_INPUT, VAR_OUTPUT) | Ereignisse (Events) und Daten |
| **Ausführung** | Wird durch den Aufruf im Programm (Zyklus) getriggert | Wird durch eingehende Ereignisse getriggert |
| **Interne Logik** | Code-Rumpf (in ST, KOP, FBS, etc.) | Explizite Zustandsmaschine (**ECC**) oder verschaltetes Netzwerk |
| **Datensynchronisation**| Implizit (beim Aufruf) | Explizit durch **WITH-Qualifier** (verbindet Daten mit Ereignissen) |

## Zusammenfassung

*   Nutzen Sie **IEC 61131-3**, wenn Sie eine einzelne SPS programmieren und eine zyklische, deterministische Abarbeitung benötigen.
*   Nutzen Sie **IEC 61499**, wenn Sie verteilte Systeme entwerfen, komponentenbasierte Softwarekapselung benötigen oder ereignisgesteuerte Prozesse abbilden wollen.
