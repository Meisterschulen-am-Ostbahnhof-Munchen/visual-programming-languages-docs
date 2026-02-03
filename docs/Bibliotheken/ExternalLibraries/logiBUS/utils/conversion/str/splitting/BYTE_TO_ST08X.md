# BYTE_TO_ST08X

```{index} single: BYTE_TO_ST08X
```

<img width="1225" height="244" alt="image" src="https://github.com/user-attachments/assets/aaadee66-4701-4548-a8a5-c07d4936e97d" />

* * * * * * * * * *
## Einleitung
Dieser Funktionsblock (FB) dient dazu, einen einzelnen Byte-Wert in eine Struktur von acht einzelnen BOOL-Werten aufzuschlüsseln. Jedes Bit des Eingangsbytes wird dabei einem separaten Bool-Feld in der Ausgangsstruktur zugewiesen, was die Handhabung bitweiser Informationen vereinfacht.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Ein Ereigniseingang, der die Ausführung des Funktionsblocks triggert. Er ist mit dem Dateneingang `IN` assoziiert.

### **Ereignis-Ausgänge**
*   **CNF**: Ein Ereignisausgang, der signalisiert, dass die Konvertierung abgeschlossen ist. Er ist mit dem Datenausgang `OUT` assoziiert.

### **Daten-Eingänge**
*   **IN**: Typ `BYTE`. Dies ist der Byte-Wert, dessen acht Bits in einzelne Boolesche Werte aufgeteilt werden sollen.

### **Daten-Ausgänge**
*   **OUT**: Typ `logiBUS::utils::conversion::types::ST08X`. Dies ist eine Struktur, die acht BOOL-Werte (benannt X_00 bis X_07) enthält. Jedes dieser Felder repräsentiert ein Bit des Eingangsbytes.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der `BYTE_TO_ST08X` Funktionsblock konvertiert ein einzelnes 8-Bit-Byte in eine vordefinierte Struktur `ST08X`, die acht separate BOOL-Variablen enthält.

Bei einem `REQ`-Ereignis wird der Wert des `IN`-Bytes gelesen. Anschließend wird jedes Bit des `IN`-Bytes dem entsprechenden BOOL-Feld in der `OUT`-Struktur zugewiesen:
*   `OUT.X_00` wird Bit 0 von `IN` zugewiesen.
*   `OUT.X_01` wird Bit 1 von `IN` zugewiesen.
*   ...
*   `OUT.X_07` wird Bit 7 von `IN` zugewiesen.

Nach der Zuweisung wird ein `CNF`-Ereignis ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
*   **Direkte Bit-Extraktion:** Die Konvertierung erfolgt durch eine direkte Zuweisung der einzelnen Bits des Bytes (z.B. `IN.0`) zu den BOOL-Feldern der Zielstruktur (z.B. `OUT.X_00`).
*   **Verwendung von `ST08X`:** Der Funktionsblock nutzt die spezifische Datentyp-Struktur `logiBUS::utils::conversion::types::ST08X`, die explizit für die Aufnahme von acht Booleschen Werten vorgesehen ist. Diese Struktur muss im System bekannt sein.
*   **Ereignisgesteuert:** Die Operation wird durch ein Eingangserreignis `REQ` ausgelöst und signalisiert ihren Abschluss durch ein Ausgangsereignis `CNF`. Dies gewährleistet eine kontrollierte Datenflusssteuerung im 4diac-System.

## Zustandsübersicht
Dieser Funktionsblock ist ein reiner Datenkonverter ohne interne Zustände. Seine Funktion ist deterministisch und hängt ausschließlich von den Eingangswerten und dem auslösenden Ereignis ab.

## Anwendungsszenarien
*   **Hardware-Interfacing:** Wenn von externen Geräten (z.B. über Feldbusse wie Modbus, CANopen) ein Byte empfangen wird, das den Zustand von acht diskreten digitalen Eingängen oder Ausgängen darstellt, kann dieser FB verwendet werden, um die einzelnen Zustände für die Weiterverarbeitung im Steuerungsprogramm zu isolieren.
*   **Protokoll-Parsing:** Zerlegung von Status-Bytes in Kommunikationsprotokollen, bei denen jedes Bit eine spezifische Flag oder einen Zustand anzeigt.
*   **Logische Verknüpfungen:** Vorbereitung von Daten für logische Operationen, die einzelne BOOL-Werte erfordern.
*   **Visualisierung:** Darstellung einzelner Bits eines Byte-Wertes auf einer Benutzeroberfläche.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Standard-Funktionsblöcke in 4diac bieten oft allgemeine Typumwandlungen (z.B. `BYTE_TO_INT`). Dieser Baustein ist jedoch spezialisiert auf die Zerlegung eines Bytes in eine strukturierte Gruppe von Booleschen Werten (`ST08X`), was ihn von generischen Konvertern unterscheidet. Es gibt keine direkte Entsprechung in der Standardbibliothek für diese spezifische Strukturkonvertierung. Andere Ansätze könnten darin bestehen, Bitmasken und logische Operationen (AND, SHIFT) mit mehreren einzelnen Konvertierungsbausteinen zu verwenden, was jedoch zu einer komplexeren und weniger übersichtlichen Implementierung führen würde. Dieser Baustein bietet eine direkte und elegante Lösung für die genannte Aufgabe.

## Fazit
Der `BYTE_TO_ST08X` Funktionsblock ist ein nützliches Werkzeug zur effizienten und übersichtlichen Zerlegung eines Byte-Wertes in acht individuelle Boolesche Zustände, die in einer `ST08X`-Struktur organisiert sind. Er vereinfacht die Handhabung bitweiser Informationen, insbesondere im Bereich der E/A-Verarbeitung und Protokollanalyse, indem er eine klare und ereignisgesteuerte Schnittstelle bietet.