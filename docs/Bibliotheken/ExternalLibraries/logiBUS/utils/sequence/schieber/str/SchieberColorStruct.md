# SchieberColorStruct

```{index} single: SchieberColorStruct
```

* * * * * * * * * *
## Einleitung
Der Datentyp `SchieberColorStruct` ist eine strukturierte Datenstruktur, die zur Verwaltung von Farbwerten für verschiedene Zustände eines Schiebers (z. B. eines Ventils, einer Klappe oder eines Verschlusses) dient. Er definiert eine konsistente Farbkodierung für die visuelle Darstellung der Zustände `Unbekannt`, `Geschlossen`, `Öffnend`, `Geöffnet` und `Schließend` in einer Benutzeroberfläche oder Anzeige.

## Schnittstellenstruktur
Der Datentyp ist eine Struktur (`STRUCT`) und enthält keine Ereignisse oder Adapter. Seine Schnittstelle besteht ausschließlich aus Daten-Elementen.

### **Daten-Eingänge**
Diese Struktur besitzt keine Ereignis-Eingänge im herkömmlichen Sinne, da es sich um einen Datentyp handelt. Die folgenden Elemente sind die Mitgliedsvariablen der Struktur, die bei der Instanziierung beschrieben oder mit Werten belegt werden können.

### **Daten-Ausgänge**
Diese Struktur besitzt keine Ereignis-Ausgänge. Die Mitgliedsvariablen stellen die gespeicherten Daten dar.

### **Daten-Elemente (Struktur-Mitglieder)**
| Name     | Datentyp | Kommentar                          | Initialwert       |
| :------- | :------- | :--------------------------------- | :---------------- |
| `Unknown`| `USINT`  | u8Colour for Unknown State         | `COLOR_WHITE`     |
| `Closed` | `USINT`  | u8Colour for Closed State          | `COLOR_WHITE`     |
| `Opening`| `USINT`  | u8Colour for Opening State         | `COLOR_WHITE`     |
| `Opened` | `USINT`  | u8Colour for Opened State          | `COLOR_WHITE`     |
| `Closing`| `USINT`  | u8Colour for Closing State         | `COLOR_WHITE`     |

### **Adapter**
Diese Datenstruktur verwendet keine Adapter.

## Funktionsweise
Die `SchieberColorStruct` ist ein reiner Datentyp. Sie dient als Container, um fünf verschiedene Farbwerte (jeweils als 8-Bit-unsigned integer, `USINT`) für die fünf definierten Schieber-Zustände zu gruppieren. Durch die Verwendung dieser Struktur kann ein Funktionsblock oder eine Anwendung eine einzige, konsistente Variable übergeben oder speichern, die alle für die Darstellung benötigten Farben enthält. Die Initialwerte aller Mitglieder sind auf die Konstante `COLOR_WHITE` gesetzt, die aus dem importierten Paket `isobus::UT::Q::const::colours` stammt.

## Technische Besonderheiten
*   **Importierte Konstante:** Die Struktur ist von der extern definierten Konstante `COLOR_WHITE` abhängig, die über den Compiler-Import `isobus::UT::Q::const::colours::COLOR_WHITE` bereitgestellt wird. Dies stellt sicher, dass ein projektweiter, einheitlicher Weißton verwendet wird.
*   **Typensicherheit:** Die Verwendung eines strukturierten Typs anstelle von fünf einzelnen Variablen erhöht die Lesbarkeit und Wartbarkeit des Codes und verringert die Fehleranfälligkeit.
*   **Hash-Attribut:** Die Struktur enthält das Attribut `eclipse4diac::core::TypeHash` mit einem leeren Wert. Dies wird vom 4diac-System für die Typidentifikation und -verwaltung genutzt.

## Zustandsübersicht
Da es sich um einen statischen Datentyp handelt, besitzt die `SchieberColorStruct` selbst keinen Zustandsautomaten. Sie kodiert vielmehr die Darstellungsattribute für die Zustände eines anderen, übergeordneten Elements (z. B. eines `Schieber`-Funktionsblocks).

## Anwendungsszenarien
*   **Visualisierung in HMIs:** Übergabe der Farbkonfiguration an Visualisierungskomponenten, um den Zustand eines Schiebers farblich korrekt anzuzeigen (z. B. Rot für "Schließend", Grün für "Geöffnet").
*   **Konfiguration von Funktionsblöcken:** Ein Funktionsblock, der einen physischen Schieber steuert, kann eine Instanz dieses Typs als konfigurierbaren Eingang besitzen, um benutzerdefinierte Farben für die Zustandsrückmeldung zu ermöglichen.
*   **Datenkapselung:** Bündelung aller zustandsbezogenen Farbinformationen in einem einzigen Parameter, der zwischen verschiedenen Softwaremodulen (z. B. Steuerung und Visualisierung) ausgetauscht werden kann.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken (FBs) wie `E_SR` oder `E_D_FF`, die eine Logik implementieren, ist `SchieberColorStruct` ein reiner **Datentyp** (STRUCT). Ähnliche strukturierte Typen könnten z. B. `MotorConfigStruct` (für Konfigurationsdaten) oder `AxisPositionStruct` (für mehrdimensionale Positionen) sein. Seine spezifische Aufgabe ist die Definition eines Farbschemas für eine vordefinierte Menge von Zuständen.

## Fazit
Die `SchieberColorStruct` ist ein einfacher, aber nützlicher strukturierter Datentyp, der die Verwaltung und den Austausch von Farbwerten für die Zustandsdarstellung eines Schiebers standardisiert. Sie fördert saubere Schnittstellen, erleichtert die Wiederverwendung und trägt durch die Verwendung initialer Standardwerte und importierter Konstanten zur Konsistenz innerhalb eines Projekts bei.
