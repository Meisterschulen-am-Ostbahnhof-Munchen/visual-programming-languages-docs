# ST08B_TO_ARR08B

```{index} single: ST08B_TO_ARR08B
```

<img width="1352" height="215" alt="image" src="https://github.com/user-attachments/assets/2ae15254-1c8f-40ed-9f4b-d611666ba335" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ST08B_TO_ARR08B` dient der Konvertierung eines 8-Byte-Strukturdatentyps (`ST08B`) in ein 8-Byte-Array. Diese Umwandlung ermöglicht die einfache Anpassung von strukturierten Daten an Schnittstellen oder Protokolle, die eine sequentielle Anordnung von Bytes erfordern.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Ein Ereignis-Eingang, der die Ausführung der Konvertierung auslöst. Dieses Ereignis ist mit dem Daten-Eingang `IN` verknüpft, um sicherzustellen, dass die Konvertierung mit den aktuellen Eingangsdaten erfolgt.

### **Ereignis-Ausgänge**
*   **CNF**: Ein Ereignis-Ausgang, der signalisiert, dass die Konvertierung erfolgreich abgeschlossen wurde und die Ausgabe `OUT` aktualisiert ist. Dieses Ereignis ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
*   **IN**: Ein Daten-Eingang vom Typ `logiBUS::utils::conversion::types::ST08B`. Dieser Eingang erwartet eine Struktur, die aus 8 Bytes besteht (z.B. `B_00` bis `B_07`).

### **Daten-Ausgänge**
*   **OUT**: Ein Daten-Ausgang vom Typ `BYTE` als Array mit der Größe `0..7`. Dieses Array enthält die 8 Bytes, die aus der Eingangsstruktur konvertiert wurden.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Die Funktionsweise des `ST08B_TO_ARR08B` ist direkt und unkompliziert. Beim Empfang eines `REQ`-Ereignisses werden die einzelnen Byte-Elemente der Eingangsstruktur `IN` direkt den entsprechenden Elementen des Ausgangsarrays `OUT` zugewiesen. Jedes Element `B_xx` der Struktur `IN` wird dem Element `OUT[xx]` des Arrays zugewiesen.
Konkret erfolgt die Zuweisung wie folgt:
*   `OUT[0]` wird `IN.B_00` zugewiesen.
*   `OUT[1]` wird `IN.B_01` zugewiesen.
*   ...
*   `OUT[7]` wird `IN.B_07` zugewiesen.
Nach Abschluss dieser Zuweisungen wird das `CNF`-Ereignis ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
*   **Datentypen:** Der Funktionsblock arbeitet mit einem spezifischen benutzerdefinierten Strukturtyp `ST08B` und einem Standard `BYTE`-Array.
*   **Direkte Zuordnung:** Es findet keine komplexe Logik, Transformation oder Berechnung statt, sondern eine direkte 1:1-Zuordnung der Bytes.
*   **Transparenz:** Die Implementierung in ST (Strukturierter Text) ist klar und leicht nachvollziehbar, was eine hohe Transparenz der Funktion gewährleistet.

## Zustandsübersicht
Der Funktionsblock `ST08B_TO_ARR08B` ist ein reiner Datenkonvertierungsbaustein ohne internen Zustand im Sinne einer Zustandsmaschine. Er führt seine Operation deterministisch bei jedem `REQ`-Ereignis aus und liefert ein Ergebnis basierend auf den aktuellen Eingabedaten.

## Anwendungsszenarien
*   **Datenvorbereitung für Kommunikation:** Um strukturierte Daten für serielle Kommunikationsprotokolle (z.B. Modbus RTU, SPI, I2C), Ethernet-Frames oder andere byteorientierte Schnittstellen vorzubereiten.
*   **Anbindung externer Geräte:** Wenn externe Geräte oder Bibliotheken Daten als reines Byte-Array erwarten, kann dieser Baustein interne strukturierte Daten passend umwandeln.
*   **Typumwandlung und Interoperabilität:** Verbesserung der Kompatibilität zwischen verschiedenen Teilen einer Anwendung oder zwischen verschiedenen Systemen, die unterschiedliche Datenrepräsentationen verwenden.
*   **Archivierung und Logging:** Speicherung von strukturierten Daten in einem generischen Byte-Format für Archivierungs- oder Logging-Zwecke.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konvertierungsbausteinen zeichnet sich `ST08B_TO_ARR08B` durch seine Spezialisierung auf die Umwandlung einer 8-Byte-Struktur in ein 8-Byte-Array aus. Allgemeine Typumwandlungsfunktionen könnten komplexer sein und mehr Konfigurationsmöglichkeiten bieten, während dieser Baustein eine hochoptimierte und spezifische Aufgabe erfüllt. Bausteine für die Array-zu-Struktur-Konvertierung (z.B. `ARR08B_TO_ST08B`) wären die Umkehrfunktion dieses Bausteins.

## Fazit
Der `ST08B_TO_ARR08B` ist ein einfacher, aber effektiver Funktionsblock zur Konvertierung einer 8-Byte-Struktur in ein 8-Byte-Array. Er bietet eine zuverlässige Lösung für Szenarien, in denen eine direkte und transparente Anpassung von strukturierten Daten an byteorientierte Schnittstellen oder Formate erforderlich ist. Seine klare Funktionalität und Implementierung machen ihn zu einem wertvollen Werkzeug in der 4diac-Entwicklungsumgebung.
