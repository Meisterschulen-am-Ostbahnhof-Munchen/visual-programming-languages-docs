# BYTES_TO_ARR08B

```{index} single: BYTES_TO_ARR08B
```

<img width="1102" height="362" alt="image" src="https://github.com/user-attachments/assets/a1d78d97-bc58-4056-8fa5-6127a949d1fc" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BYTES_TO_ARR08B` dient der Konvertierung von acht einzelnen `BYTE`-Werten in ein Array vom Typ `BYTE` mit acht Elementen. Er ist Teil einer Sammlung von Hilfsfunktionen für Datenkonvertierungen und Array-Operationen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Dieses Ereignis löst die Verarbeitung des Funktionsblocks aus. Bei seinem Eintreffen werden die Werte an den Daten-Eingängen gelesen und in das Ausgabe-Array geschrieben.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses Ereignis wird nach erfolgreicher Verarbeitung und Zuweisung der Werte zum Ausgabe-Array generiert. Es signalisiert die Verfügbarkeit des Ergebnisses.

### **Daten-Eingänge**
*   **IN_00** (`BYTE`): Wert für das Array-Element an Index 0.
*   **IN_01** (`BYTE`): Wert für das Array-Element an Index 1.
*   **IN_02** (`BYTE`): Wert für das Array-Element an Index 2.
*   **IN_03** (`BYTE`): Wert für das Array-Element an Index 3.
*   **IN_04** (`BYTE`): Wert für das Array-Element an Index 4.
*   **IN_05** (`BYTE`): Wert für das Array-Element an Index 5.
*   **IN_06** (`BYTE`): Wert für das Array-Element an Index 6.
*   **IN_07** (`BYTE`): Wert für das Array-Element an Index 7.

### **Daten-Ausgänge**
*   **OUT** (`ARRAY[0..7] OF BYTE`): Das resultierende Byte-Array. Die Indizes 0 bis 7 enthalten nacheinander die Werte von `IN_00` bis `IN_07`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung durch das `REQ`-Ereignis kopiert der Block die Werte der acht `BYTE`-Eingänge direkt in die entsprechenden Positionen des Ausgabe-Arrays `OUT`. Die Zuordnung ist sequenziell: `IN_00` → `OUT[0]`, `IN_01` → `OUT[1]`, usw. bis `IN_07` → `OUT[7]`. Unmittelbar nach dieser Zuweisung wird das `CNF`-Ereignis ausgelöst.

Die interne Implementierung erfolgt in Structured Text (ST) und besteht aus einer einfachen Reihe von Zuweisungen.

## Technische Besonderheiten
*   **Deterministische Laufzeit:** Die Operation hat eine konstante und sehr kurze Ausführungszeit, da sie nur aus direkten Zuweisungen besteht.
*   **Keine Pufferung:** Es findet keine Zwischenspeicherung der Eingangswerte statt. Die Verarbeitung erfolgt ausschließlich bei Eintreffen eines `REQ`-Ereignisses.
*   **Feste Größe:** Der Block ist spezifisch für die Kombination von genau acht Bytes ausgelegt.

## Zustandsübersicht
Der Funktionsblock ist zustandslos (stateless). Jeder `REQ`-Aufruf ist unabhängig von vorherigen Aufrufen und verarbeitet ausschließlich die aktuell anliegenden Eingangswerte.

## Anwendungsszenarien
*   **Datenaggregation:** Zusammenfassen einzelner Byte-Werte (z.B. aus verschiedenen Quellen oder Sensoren) zu einem kompakten Array für die Weiterverarbeitung oder Übertragung.
*   **Protokoll- und Schnittstellenanpassung:** Vorbereitung von Datenstrukturen für Kommunikationsprotokolle oder Funktionsblöcke, die ein Byte-Array anstelle einzelner Bytes erwarten.
*   **Datenumstrukturierung:** Konvertierung zwischen verschiedenen Darstellungsformen von Daten innerhalb einer Steuerungsanwendung.

## Vergleich mit ähnlichen Bausteinen
*   **`CONCAT`-Blöcke:** Allgemeine Blöcke zum Verketten von Strings sind nicht direkt vergleichbar, da sie auf den Datentyp `STRING` ausgelegt sind.
*   **Manuelle Zuweisung in ST:** Die Funktionalität könnte direkt in einem ST-Programm durch Zuweisungen realisiert werden. Der Funktionsblock kapselt diese Logik jedoch für eine bessere Wiederverwendbarkeit, Lesbarkeit und Wartbarkeit innerhalb von FBD-/LD-Diagrammen.
*   **Individuelle Array-Bausteine:** Im Gegensatz zu universellen Array-Bausteinen, die über Indexeingänge verfügen, ist `BYTES_TO_ARR08B` für eine spezifische, feste Aufgabe optimiert und daher einfacher und schneller in der Anwendung.


## Zugehörige Übungen

* [Uebung_126b_sub](../../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_126b_sub.md)
* [Uebung_12x_sub](../../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_12x_sub.md)

## Fazit
Der `BYTES_TO_ARR08B` ist ein spezialisierter und effizienter Hilfsbaustein für eine häufige Aufgabe in der Datenmanipulation. Er bietet eine klare, ereignisgesteuerte Schnittstelle und erspart dem Anwender die wiederholte manuelle Implementierung der Array-Zuordnung. Seine Stärke liegt in der Einfachheit und Eindeutigkeit für den konkreten Anwendungsfall der Kombination von acht Bytes.