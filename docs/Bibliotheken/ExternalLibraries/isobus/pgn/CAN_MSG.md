# CAN_MSG

```{index} single: CAN_MSG
```

* * * * * * * * * *
## Einleitung
Der Datentyp `CAN_MSG` ist eine strukturierte Typdefinition (Struct) zur Repräsentation eines klassischen CAN-Nachrichtenrahmens (ohne Transportprotokoll, TP). Er dient als Container für die wesentlichen Attribute einer CAN-Nachricht, einschließlich Priorität, Nutzdatenlänge und dem eigentlichen Datenpuffer. Dieser Typ ist für den Einsatz in Funktionsblöcken vorgesehen, die CAN-Kommunikation in einem IEC 61499-System implementieren.

## Schnittstellenstruktur
Da es sich bei `CAN_MSG` um einen Datentyp und nicht um einen Funktionsblock handelt, existieren keine Ereignis- oder Adapterschnittstellen. Die Struktur wird ausschließlich über ihre Datenmember definiert.

### **Daten-Eingänge**
*(Nicht anwendbar – Datentyp)*

### **Daten-Ausgänge**
*(Nicht anwendbar – Datentyp)*

### **Ereignis-Eingänge**
*(Nicht anwendbar – Datentyp)*

### **Ereignis-Ausgänge**
*(Nicht anwendbar – Datentyp)*

### **Adapter**
*(Nicht anwendbar – Datentyp)*

## Funktionsweise
Der `CAN_MSG`-Typ ist eine passive Datenstruktur. Er kapselt die für eine CAN-Nachricht relevanten Informationen:
1.  **Priorität (`u8Priority`)**: Definiert die Arbitrierungspriorität auf dem CAN-Bus. Ein niedrigerer numerischer Wert entspricht einer höheren Priorität.
2.  **Datenlänge (`u16DaSize`)**: Gibt die tatsächliche Anzahl der genutzten Bytes im Datenpuffer an (0 bis 8).
3.  **Datenpuffer (`data`)**: Ein Array von 8 Bytes, das die Nutzdaten der Nachricht speichert. Nicht genutzte Bytes sind mit einem Standardwert initialisiert.

Diese Struktur kann als Eingabe- oder Ausgabedatentyp für Funktionsblöcke verwendet werden, die CAN-Nachrichten senden, empfangen, verarbeiten oder loggen.

## Technische Besonderheiten
*   **Feste Puffergröße**: Das Datenarray ist statisch auf eine Länge von 8 Bytes dimensioniert, was der maximalen Nutzdatenlänge eines klassischen CAN-Frames entspricht.
*   **Initialisierung**: Das Datenarray wird standardmäßig mit dem Hexadezimalwert `16#FF` (dezimal 255) in allen 8 Positionen vorbelegt. Die Datenlänge `u16DaSize` ist standardmäßig `0`, und die Priorität `u8Priority` ist standardmäßig `7` (niedrigste Priorität).
*   **Typensicherheit**: Die Verwendung eines strukturierten Typs anstelle einzelner Variablen erhöht die Wartbarkeit und Klarheit in der Funktionsblock-Verbindungsansicht.

## Zustandsübersicht
*(Nicht anwendbar – Datentyp besitzt kein Verhalten oder Zustandsautomaten.)*

## Anwendungsszenarien
Der `CAN_MSG`-Typ ist grundlegend für:
*   **CAN-Sender-FBs**: Ein FB, der einen `CAN_MSG`-Typ als Eingang erhält und dessen Inhalt als physikalischen CAN-Frame auf den Bus sendet.
*   **CAN-Empfänger-FBs**: Ein FB, der empfangene CAN-Frames in eine Variable vom Typ `CAN_MSG` packt und an nachgelagerte Logik weiterreicht.
*   **Nachrichten-Konstruktion**: FBs, die aus einzelnen Werten (z.B. aus Sensor-FBs) eine gültige `CAN_MSG`-Struktur für die spätere Übertragung aufbauen.
*   **Nachrichten-Filterung/Verarbeitung**: FBs, die eingehende `CAN_MSG`-Strukturen basierend auf Priorität, Dateninhalt oder Länge analysieren und verarbeiten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Als Datentyp ist `CAN_MSG` mit anderen strukturierten Typen in 4diac vergleichbar, die Kommunikationsprotokolle abbilden (z.B. `UDP_PACKET`, `MODBUS_MSG`). Sein spezifisches Merkmal ist die enge Abbildung auf die Hardware-Eigenschaften des CAN-Bus-Protokolls (Priorität, 8-Byte-Limit). Im Gegensatz zu einem TP-basierten Nachrichtentyp (z.B. für ISO 11783 oder CANopen) fehlen hier Felder für Paketierung, Sequenznummern oder spezifische Protokollkopfzeilen.

## Fazit
Der `CAN_MSG`-Datentyp stellt eine essentielle und gut strukturierte Grundlage für die Implementierung von CAN-Bus-Kommunikation in 4diac-basierten Steuerungssystemen dar. Durch die Bündelung von Priorität, Länge und Daten in einem einzigen Typ wird die Handhabung von CAN-Nachrichten in Funktionsblock-Netzwerken deutlich vereinfacht und standardisiert. Seine Verwendung ist für alle Anwendungen empfohlen, die den direkten Zugriff auf CAN-Frames erfordern.