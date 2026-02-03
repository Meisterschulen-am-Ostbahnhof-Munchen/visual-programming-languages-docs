# AND_2_BOOL

```{index} single: AND_2_BOOL
```

<img width="1383" height="250" alt="image" src="https://github.com/user-attachments/assets/10df4f18-5ed8-46f2-aaae-c0c787c2731e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AND_2_BOOL` ist ein Standardbaustein zur Berechnung der logischen UND-Verknüpfung (Konjunktion) zweier boolescher Eingangswerte. Er folgt dem IEC 61131-3-Standard für grundlegende boolesche Funktionen und ist für den Einsatz in der 4diac-IDE konzipiert. Der Baustein wartet auf ein Auslöseereignis, führt die Operation aus und signalisiert die Beendigung der Berechnung mit einem Bestätigungsereignis.

![AND_2_BOOL](AND_2_BOOL.svg)

## Schnittstellenstruktur
Die Schnittstelle des `AND_2_BOOL`-Funktionsblocks ist einfach und übersichtlich aufgebaut und besteht aus einem Ereigniseingang, einem Ereignisausgang sowie den zugehörigen Datenverbindungen.

### **Ereignis-Eingänge**
*   **REQ (Normal Execution Request):** Dieses Ereignis löst die Ausführung des Funktionsblocks aus. Bei seinem Eintreffen werden die aktuellen Werte an den Daten-Eingängen `IN1` und `IN2` gelesen und die UND-Operation berechnet.

### **Ereignis-Ausgänge**
*   **CNF (Execution Confirmation):** Dieses Ereignis wird nach Abschluss der Berechnung erzeugt. Es signalisiert, dass das Ergebnis an den Daten-Ausgang `OUT` ausgegeben wurde und nun gültig ist.

### **Daten-Eingänge**
*   **IN1 (AND input 1):** Erster boolescher Operand (Typ: `BOOL`).
*   **IN2 (AND input 2):** Zweiter boolescher Operand (Typ: `BOOL`).

### **Daten-Ausgänge**
*   **OUT (AND result):** Ergebnis der logischen UND-Verknüpfung von `IN1` und `IN2` (Typ: `BOOL`). Der Ausgangswert ist `TRUE` (1), wenn sowohl `IN1` als auch `IN2` den Wert `TRUE` haben. In allen anderen Fällen ist der Ausgang `FALSE` (0).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Die Funktionsweise des `AND_2_BOOL`-Blocks ist deterministisch und folgt der klassischen booleschen Logik:
1.  **Auslösung:** Das Eintreffen des Ereignisses `REQ` startet die Ausführung.
2.  **Eingabe lesen:** Die aktuellen Werte der Daten-Eingänge `IN1` und `IN2` werden abgefragt.
3.  **Berechnung:** Es wird die logische UND-Operation `OUT := IN1 AND IN2` durchgeführt.
4.  **Ausgabe:** Das berechnete Ergebnis wird an den Daten-Ausgang `OUT` geschrieben.
5.  **Bestätigung:** Unmittelbar nach der Ausgabe wird das Bestätigungsereignis `CNF` erzeugt, um nachgelagerte Blöcke über die Verfügbarkeit des neuen Ergebnisses zu informieren.

Die Operation kann durch folgende Wahrheitstabelle beschrieben werden:

| IN1 | IN2 | OUT (IN1 AND IN2) |
|:---:|:---:|:-----------------:|
|  0  |  0  |         0         |
|  0  |  1  |         0         |
|  1  |  0  |         0         |
|  1  |  1  |         1         |

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als Instanz eines generischen UND-Bausteins (`GEN_AND`) implementiert, der für verschiedene Datentypen spezialisiert werden kann. In dieser konkreten Instanz ist er auf den Datentyp `BOOL` festgelegt.
*   **Ereignisgesteuert:** Wie für 4diac-Funktionsblöcke typisch, ist die Ausführung strikt ereignisgesteuert. Eine Änderung der Eingangswerte allein löst keine Berechnung aus; diese erfolgt erst beim Eintreffen des `REQ`-Ereignisses.
*   **Einfache Latenz:** Die Ausführungszeit ist vernachlässigbar, sodass das `CNF`-Ereignis praktisch unmittelbar auf das `REQ`-Ereignis folgt.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand im Sinne eines Speichers für vorherige Werte. Er ist ein rein kombinatorischer Baustein, dessen Ausgang ausschließlich von den aktuellen Eingangswerten bei Auslösung abhängt. Sein "Zustand" ist daher immer "wartend auf REQ" oder "in Ausführung", wobei die Ausführungsphase sehr kurz ist.

## Anwendungsszenarien
Der `AND_2_BOOL`-Block ist ein fundamentaler Baustein in der Steuerungs- und Automatisierungstechnik. Typische Anwendungen sind:
*   **Sicherheitsbedingungen:** Verknüpfung mehrerer Sicherheitssignale (z.B. "Schutztür geschlossen" UND "Not-Aus nicht gedrückt"), um eine Maschinenfreigabe zu erzeugen.
*   **Zweihand-Bedienung:** Sicherstellung, dass zwei Taster gleichzeitig gedrückt werden müssen, um einen gefährlichen Vorgang zu starten.
*   **Verkettung von Schaltbedingungen:** Kombination mehrerer Sensor- oder Schalterzustände, um ein Aktor-Signal zu steuern (z.B. "Material vorhanden" UND "Position erreicht" -> Greifer schließen).
*   **Maskierung von Signalen:** Gezieltes Durchschalten oder Sperren eines Signals (`DATA`) durch ein Freigabesignal (`ENABLE`) mittels `OUT := DATA AND ENABLE`.

## Vergleich mit ähnlichen Bausteinen
*   **`AND_n` (generisch):** Der generische `GEN_AND`-Baustein kann für mehr als zwei Eingänge und andere Datentypen (z.B. `WORD`, `DWORD`) konfiguriert werden. `AND_2_BOOL` ist eine spezifische, auf zwei boolesche Eingänge festgelegte Instanz davon, die einfacher und direkter in booleschen Logikschaltungen eingesetzt werden kann. Siehe: [AND_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_2.md)
*   **`OR_2_BOOL` / `XOR_2_BOOL`:** Diese Blöcke implementieren andere grundlegende boolesche Operationen (ODER bzw. exklusives ODER). Sie besitzen die identische ereignisgesteuerte Schnittstelle (`REQ`/`CNF`), führen aber eine andere logische Verknüpfung der Eingänge `IN1` und `IN2` durch.
*   **Kombinatorische Logik in SFC/ST:** Die UND-Funktion könnte auch direkt in Structured Text (ST) mit dem `&`- oder `AND`-Operator codiert werden. Der Vorteil des `AND_2_BOOL`-FB liegt in der standardisierten, wiederverwendbaren und grafisch verknüpfbaren Form innerhalb des 4diac-Funktionsbaustein-Netzwerks (FBN).




## Zugehörige Übungen

* [Uebung_002a4](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_002a4.md)
* [Uebung_002b3](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_002b3.md)
* [Uebung_006a3](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_006a3.md)

## Fazit
Der `AND_2_BOOL`-Funktionsblock ist ein essentieller, zuverlässiger und einfach zu verwendender Grundbaustein für die Implementierung boolescher Logik in 4diac-basierten Steuerungsanwendungen. Seine klare, ereignisgesteuerte Schnittstelle und die deterministische Funktionsweise machen ihn zum idealen Baustein für Sicherheitsverknüpfungen, Steuerungsbedingungen und allgemeine logische Operationen. Für reine boolesche Zweier-Verknüpfungen ist er die erste Wahl.