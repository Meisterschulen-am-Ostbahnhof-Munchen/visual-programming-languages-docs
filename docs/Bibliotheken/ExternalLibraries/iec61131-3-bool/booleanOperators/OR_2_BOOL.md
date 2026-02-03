# OR_2_BOOL

```{index} single: OR_2_BOOL
```

<img width="1568" height="281" alt="image" src="https://github.com/user-attachments/assets/8ebdc4b4-c155-45d6-81bb-875ba03dc816" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `OR_2_BOOL` führt eine logische ODER-Verknüpfung (Disjunktion) auf zwei boolesche Eingangswerte aus. Es handelt sich um einen generischen Baustein, der gemäß der IEC 61131-3 Norm für Standard-Boolesche Funktionen klassifiziert ist. Der Block wartet auf eine Ausführungsanforderung, berechnet das Ergebnis und signalisiert dessen Verfügbarkeit.

![OR_2_BOOL](OR_2_BOOL.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ** (Normal Execution Request): Dieses Ereignis löst die Ausführung des Funktionsblocks aus. Bei seinem Eintreffen werden die an den Daten-Eingängen `IN1` und `IN2` anliegenden Werte gelesen und die ODER-Operation durchgeführt.

### **Ereignis-Ausgänge**
*   **CNF** (Execution Confirmation): Dieses Ereignis wird nach Abschluss der Berechnung erzeugt. Es signalisiert, dass das Ergebnis an den Daten-Ausgang `OUT` ausgegeben wurde und gültig ist.

### **Daten-Eingänge**
*   **IN1** (BOOL): Erster Operand für die ODER-Operation.
*   **IN2** (BOOL): Zweiter Operand für die ODER-Operation.

### **Daten-Ausgänge**
*   **OUT** (BOOL): Ergebnis der logischen ODER-Verknüpfung von `IN1` und `IN2`. Der Ausgangswert ist `TRUE`, wenn mindestens einer der beiden Eingänge `TRUE` ist. Andernfalls ist er `FALSE`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Die Funktionsweise ist ereignisgesteuert und folgt einem einfachen Anforderungs-Bestätigungs-Zyklus:
1.  Das Eintreffen des Ereignisses `REQ` startet die Ausführung.
2.  Die aktuellen Werte der Daten-Eingänge `IN1` und `IN2` werden abgefragt.
3.  Die logische ODER-Verknüpfung `OUT := IN1 OR IN2` wird berechnet.
4.  Das Ergebnis wird an den Daten-Ausgang `OUT` gelegt.
5.  Das Ereignis `CNF` wird erzeugt, um den Abschluss der Operation anzuzeigen.

Die Wahrheitstabelle der Operation lautet:

| IN1 | IN2 | OUT (IN1 OR IN2) |
|:---:|:---:|:----------------:|
| 0   | 0   | 0                |
| 0   | 1   | 1                |
| 1   | 0   | 1                |
| 1   | 1   | 1                |

## Technische Besonderheiten
*   **Generischer Baustein:** Der Block ist als generischer Baustein (`GEN_OR`) gekennzeichnet, was bedeutet, dass er als Basis für die Ableitung ähnlicher Bausteine mit anderen Datentypen dienen kann.
*   **Einfache Laufzeit:** Die Ausführungszeit ist konstant und sehr kurz, da es sich um eine einfache logische Operation handelt.
*   **Kein interner Zustand:** Der Block ist zustandslos (kombinatorisch). Das Ergebnis hängt ausschließlich von den aktuellen Eingangswerten zum Zeitpunkt der `REQ`-Anforderung ab.

## Zustandsübersicht
Der Funktionsblock besitzt keinen persistenten internen Zustand. Sein Verhalten ist rein kombinatorisch und wird vollständig durch die Schnittstellenereignisse und -daten beschrieben.

## Anwendungsszenarien
*   **Logische Verknüpfungen in Steuerungslogik:** Kombination von zwei Bedingungen, bei der eine Aktion ausgeführt werden soll, wenn mindestens eine der Bedingungen erfüllt ist (z.B. "Motor starten, wenn Taster gedrückt ODER Fernbedienungssignal empfangen wird").
*   **Fehleraggregation:** Zusammenfassung mehrerer Fehlersignale zu einem gemeinsamen Fehlerstatus. Liegt mindestens ein Fehler vor (`TRUE`), wird der Gesamtfehlerstatus aktiviert.
*   **Freigabelogik:** Erzeugen einer Freigabe, wenn eine von mehreren möglichen Quellen aktiv ist.
*   **Grundbaustein in komplexeren logischen Schaltungen:** Als Teil von UND-ODER-Verknüpfungen (SOP - Sum of Products) zur Realisierung von Schaltfunktionen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **AND_2_BOOL:** Führt eine logische UND-Verknüpfung durch. Das Ergebnis ist nur dann `TRUE`, wenn **beide** Eingänge `TRUE` sind.
*   **XOR_2_BOOL:** Führt eine exklusive ODER-Verknüpfung (Antivalenz) durch. Das Ergebnis ist `TRUE`, wenn genau **ein** Eingang `TRUE` ist.
*   **NOT_BOOL:** Führt eine logische NICHT-Verknüpfung (Negation) auf einem einzelnen Eingang durch.
*   **OR_n_BOOL:** Ein generischer ODER-Baustein, der eine variable Anzahl von Eingängen (n) verknüpfen kann, während `OR_2_BOOL` genau zwei feste Eingänge besitzt. Siehe: [OR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_2.md)






## 🛠️ Zugehörige Übungen

* [Uebung_002b3](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_002b3.md)
* [Uebung_160](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_160.md)
* [Uebung_160b](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_160b.md)
* [Uebung_160b2](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_160b2.md)

## Fazit
Der `OR_2_BOOL` ist ein fundamentaler, zuverlässiger und einfach zu verwendender Funktionsblock zur Realisierung der grundlegenden logischen ODER-Funktion in 4diac-IDE Applikationen. Seine ereignisgesteuerte, zustandslose Architektur macht ihn vorhersehbar und gut in den Datenfluss von IEC 61499-Systemen integrierbar. Er ist ein unverzichtbarer Baustein für die Implementierung von Steuerungslogik und Bedingungsauswertungen.