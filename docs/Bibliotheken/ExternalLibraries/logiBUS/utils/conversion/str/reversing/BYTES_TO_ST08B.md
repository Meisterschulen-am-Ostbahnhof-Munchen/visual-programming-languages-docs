# BYTES_TO_ST08B

```{index} single: BYTES_TO_ST08B
```

<img width="1047" height="423" alt="image" src="https://github.com/user-attachments/assets/d2c1b827-1e6e-4e74-b89f-c8b60ae0824f" />

* * * * * * * * * *
## Einleitung
Dieser Funktionsbaustein dient dazu, acht individuelle BYTE-Werte zu einer einzigen 8-BYTE-Struktur vom Typ `ST08B` zusammenzuführen. Er ermöglicht eine geordnete Überführung von diskreten Byte-Werten in ein strukturiertes Datenformat.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ** (Typ: `Event`)
    *   Verbindet die Aktivierung des Bausteins mit den Daten-Eingängen: `IN_00`, `IN_01`, `IN_02`, `IN_03`, `IN_04`, `IN_05`, `IN_06`, `IN_07`.
    *   Löst die Konvertierung der Eingangs-BYTES in die `ST08B`-Struktur aus.

### **Ereignis-Ausgänge**
*   **CNF** (Typ: `Event`)
    *   Wird nach erfolgreicher Konvertierung ausgelöst.
    *   Signalisiert die Verfügbarkeit des konvertierten Werts am Daten-Ausgang `OUT`.

### **Daten-Eingänge**
*   **IN_00** (Typ: `BYTE`)
    *   Kommentar: BYTE 00
*   **IN_01** (Typ: `BYTE`)
    *   Kommentar: BYTE 01
*   **IN_02** (Typ: `BYTE`)
    *   Kommentar: BYTE 02
*   **IN_03** (Typ: `BYTE`)
    *   Kommentar: BYTE 03
*   **IN_04** (Typ: `BYTE`)
    *   Kommentar: BYTE 04
*   **IN_05** (Typ: `BYTE`)
    *   Kommentar: BYTE 05
*   **IN_06** (Typ: `BYTE`)
    *   Kommentar: BYTE 06
*   **IN_07** (Typ: `BYTE`)
    *   Kommentar: BYTE 07

### **Daten-Ausgänge**
*   **OUT** (Typ: `logiBUS::utils::conversion::types::ST08B`)
    *   Kommentar: ST08B Output
    *   Gibt die aus den acht Eingangs-Bytes erstellte 8-Byte-Struktur aus.

### **Adapter**
Dieser Funktionsbaustein verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Bei Empfang eines `REQ`-Ereignisses weist der Baustein die Werte der acht Daten-Eingänge `IN_00` bis `IN_07` direkt den entsprechenden Feldern (`B_00` bis `B_07`) der Ausgangsstruktur `OUT` zu. Nach Abschluss dieser Zuweisung wird ein `CNF`-Ereignis ausgelöst, welches signalisiert, dass die `OUT`-Struktur mit den neuen Werten aktualisiert wurde und zur Weiterverarbeitung bereitsteht.

## Technische Besonderheiten
Der Funktionsbaustein verwendet den benutzerdefinierten Datentyp `logiBUS::utils::conversion::types::ST08B` als Ausgangsformat. Dieser Typ muss im System definiert sein, damit der Baustein korrekt funktioniert. Die Zuordnung der Bytes erfolgt positionsgenau: `IN_00` wird zu `OUT.B_00`, `IN_01` zu `OUT.B_01` und so weiter.

## Zustandsübersicht
Der `BYTES_TO_ST08B`-Baustein ist ein rein kombinatorischer Funktionsbaustein. Er besitzt keine internen Zustände, die über längere Zeit gespeichert werden. Jede Ausführung durch ein `REQ`-Ereignis verarbeitet die aktuellen Eingangswerte unabhängig von früheren Ausführungen und produziert ein entsprechendes Ausgangsergebnis.

## Anwendungsszenarien
*   **Datenpaket-Assemblierung:** Zusammenfügen von einzelnen Byte-Komponenten zu einem fest definierten Datenpaket, z.B. für die Kommunikation über serielle Schnittstellen oder Netzwerke.
*   **Interfacing mit Protokollen:** Anpassung von Daten an Kommunikationsprotokolle, die spezifische 8-Byte-Strukturen erwarten.
*   **Datentyp-Konvertierung:** Umwandlung von Raw-Byte-Daten in einen höherwertigen, strukturierten Datentyp zur besseren Handhabung und Lesbarkeit innerhalb der Applikation.
*   **Hardware-Anbindung:** Wenn Daten von Sensoren oder Aktoren byteweise gelesen werden und zu einer festen Struktur aggregiert werden müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu allgemeinen Typumwandlungs- oder Array-Manipulationsbausteinen bietet `BYTES_TO_ST08B` eine spezialisierte Lösung für die Umwandlung von genau acht Bytes in eine vordefinierte `ST08B`-Struktur. Dies eliminiert die Notwendigkeit manueller Indizierung oder Schleifen und vereinfacht die Handhabung für diesen spezifischen Anwendungsfall. Andere Bausteine könnten flexibler sein (z.B. eine variable Anzahl von Bytes verarbeiten), aber dieser Baustein ist für seine feste Größe optimiert.

## Fazit
Der Funktionsbaustein `BYTES_TO_ST08B` ist ein nützliches Werkzeug, um acht einzelne Byte-Eingänge in eine definierte 8-Byte-Struktur `ST08B` zu konvertieren. Er trägt zur Modularisierung und Vereinfachung von Steuerungsprogrammen bei, insbesondere wenn es darum geht, diskrete Bytedaten für strukturierte Kommunikationsaufgaben oder interne Datenverarbeitung vorzubereiten. Seine direkte und ereignisgesteuerte Arbeitsweise macht ihn zuverlässig und einfach zu integrieren.