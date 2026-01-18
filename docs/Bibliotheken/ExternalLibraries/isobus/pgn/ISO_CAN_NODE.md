# ISO_CAN_NODE

```{index} single: ISO_CAN_NODE
```

* * * * * * * * * *
## Einleitung
Die globale Konstantendatei `ISO_CAN_NODE` definiert eine Reihe von numerischen Konstanten zur Identifikation von CAN-Knoten (Controller Area Network) innerhalb eines 4diac-Projekts. Sie dient der Abstraktion und Vereinheitlichung von Knotenadressen, um die Lesbarkeit und Wartbarkeit von Applikationen zu erhöhen, die mit mehreren CAN-Bussen arbeiten.

## Schnittstellenstruktur
Dieses Element ist eine Sammlung globaler Konstanten und besitzt keine ereignis- oder datenflussgesteuerten Schnittstellen wie ein Funktionsblock.

### **Daten-Konstanten**
Die Datei definiert die folgenden Konstanten vom Typ `USINT` (Unsigned Short Integer):

| Name    | Typ   | Initialwert | Kommentar        |
| :------ | :---- | :---------- | :--------------- |
| `NODE1` | USINT | 0           | Kennung für CAN 1 |
| `NODE2` | USINT | 1           | Kennung für CAN 2 |
| `NODE3` | USINT | 2           | Kennung für CAN 3 |
| `NODE4` | USINT | 3           | Kennung für CAN 4 |
| `INVALID`| USINT | USINT#16#FF | Kennung für einen ungültigen oder nicht konfigurierten CAN-Knoten (dezimal: 255) |

## Funktionsweise
Die Konstanten werden zur Kompilierzeit in den Code eingefügt. Anstatt direkte numerische Werte (wie `0` oder `1`) in Funktionsblöcken zu verwenden, die CAN-Kommunikation steuern, können Entwickler die sprechenden Namen (`NODE1`, `NODE2`, etc.) nutzen. Dies macht den Code intuitiver verständlich und erleichtert zukünftige Änderungen, da die tatsächlichen Adressen zentral an einem Ort verwaltet werden.

Der Wert `INVALID` (255) stellt einen reservierten Wert dar, der typischerweise verwendet wird, um einen nicht initialisierten, fehlerhaften oder nicht existenten Knoten zu kennzeichnen.

## Technische Besonderheiten
*   **Paketzuordnung:** Die Konstanten sind dem Paket `isobus::pgn` zugeordnet, was auf eine Verwendung im Kontext des ISO-Bus (ISOBUS, Landtechnik) und Parameter Group Numbers (PGN) hindeutet.
*   **Datentyp:** Alle Konstanten sind vom Typ `USINT`, was einen Wertebereich von 0 bis 255 ermöglicht und für CAN-Knotenadressen üblich ist.
*   **Hexadezimale Notation:** Der Wert für `INVALID` wird in hexadezimaler Schreibweise (`16#FF`) definiert, was der dezimalen Zahl 255 entspricht.

## Zustandsübersicht
Da es sich um statische Konstanten handelt, existiert kein Zustandsautomat.

## Anwendungsszenarien
*   **Multi-CAN-Systeme:** In Steuerungen, die mit mehreren unabhängigen CAN-Bussen kommunizieren (z.B. ein Hauptbus und ein Antriebsbus), um die Busse eindeutig zu adressieren.
*   **ISOBUS-Anwendungen:** Zur Konfiguration von virtuellen Terminals (VT), Task-Controllern (TC) oder anderen Geräten in einem landtechnischen ISOBUS-Netzwerk.
*   **Fehlerbehandlung:** Die Konstante `INVALID` kann als Rückgabewert oder Initialwert in Funktionsblöcken dienen, um anzuzeigen, dass kein gültiger CAN-Knoten ausgewählt oder erkannt wurde.

## Vergleich mit ähnlichen Bausteinen
*   **Direkte Werte:** Der alternative Ansatz wäre die direkte Verwendung numerischer Literale (0, 1, 2, ...) im Code. Die Verwendung von `ISO_CAN_NODE` ist diesem Ansatz in puncto Codequalität und Wartbarkeit überlegen.
*   **Enumerations (ENUM):** In einigen Programmiersprachen oder FB-Typen könnten ähnliche Konstrukte als Enumeration definiert werden. Globale Konstanten sind in IEC 61499 ein einfaches und weit verbreitetes Mittel, um dieses Muster umzusetzen.

## Fazit
Die `ISO_CAN_NODE` Konstantendatei ist ein einfaches, aber wertvolles Hilfsmittel für die strukturierte Entwicklung von CAN-basierten Steuerungsapplikationen in 4diac. Sie fördert sauberen, selbsterklärenden Code und zentralisiert Konfigurationsdaten, was Fehler reduziert und Anpassungen erleichtert. Ihre Verwendung ist besonders in Projekten mit mehreren CAN-Knoten oder im ISOBUS-Umfeld empfehlenswert.
