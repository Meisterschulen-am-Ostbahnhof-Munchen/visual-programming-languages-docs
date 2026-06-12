# AUI_TO_AD


![AUI_TO_AD](./AUI_TO_AD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUI_TO_AD** ist ein zusammengesetzter Baustein (Composite FB), der eine Umwandlung eines AUI-Adapters (UINT-Datentyp) in einen AD-Adapter (DWORD-Datentyp) realisiert. Er dient als unidirektionale Konvertierungsschnittstelle innerhalb einer IEC 61499-basierten Steuerungsanwendung. Der Baustein ist als Kapselung des Standardkonverters `F_UINT_TO_DWORD` aus der Bibliothek `iec61131::conversion` implementiert und ermöglicht eine adapterbasierte Datenweitergabe.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Beschreibung |
|------|--------------|
| AUI_IN.E1 | Ereignis vom AUI-Adapter, das die Konvertierung auslöst. |

### **Ereignis-Ausgänge**

| Name | Beschreibung |
|------|--------------|
| AD_OUT.E1 | Ereignis zum AD-Adapter, das die Verfügbarkeit des konvertierten Wertes signalisiert. |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| AUI_IN.D1 | UINT | Eingangswert vom AUI-Adapter, der in einen DWORD-Wert umgewandelt wird. |

### **Daten-Ausgänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| AD_OUT.D1 | DWORD | Ausgangswert, der den konvertierten DWORD-Wert an den AD-Adapter weitergibt. |

### **Adapter**

| Typ | Name | Rolle |
|-----|------|-------|
| `adapter::types::unidirectional::AUI` | AUI_IN | Socket – Eingangsadapter für den UINT-Wert und das zugehörige Ereignis. |
| `adapter::types::unidirectional::AD` | AD_OUT | Plug – Ausgangsadapter für den konvertierten DWORD-Wert und das Bestätigungsereignis. |

## Funktionsweise

Der Baustein **AUI_TO_AD** arbeitet als Kapselung des Funktionsbausteins `F_UINT_TO_DWORD`. Sobald ein Ereignis am Ereigniseingang `AUI_IN.E1` eintrifft, wird der angeschlossene interne Konverter `Convert` aufgerufen. Dieser Konverter liest den Wert vom Dateneingang `AUI_IN.D1` (Typ UINT) und wandelt ihn in einen DWORD-Wert um. Das Ergebnis wird am Datenausgang `AD_OUT.D1` bereitgestellt. Gleichzeitig wird nach erfolgreicher Konvertierung ein Ereignis am Ausgang `AD_OUT.E1` erzeugt, welches dem nachgeschalteten AD-Adapter die Fertigstellung signalisiert.

Die Umwandlung erfolgt nach der IEC 61131-3 Norm für die Funktion `UINT_TO_DWORD`. Der Wertebereich des UINT-Eingangs (0 bis 65535) wird auf den unteren 16 Bit des DWORD-Ausgangs abgebildet; die oberen 16 Bit werden mit Null aufgefüllt.

## Technische Besonderheiten

- Der Baustein ist als Composite FB realisiert und enthält keine eigene Zustandsautomaten (ECC). Das Verhalten wird vollständig durch den integrierten Konverter `F_UINT_TO_DWORD` bestimmt.
- Die Verbindung zwischen den Adaptern und dem internen Konverter erfolgt über Ereignis- und Datenverbindungen.
- Der Baustein ist für den unidirektionalen Datentransfer konzipiert – es gibt keine Rückwärtskonvertierung von AD zu AUI.
- Die Paketangabe (`packageName`) lautet `adapter::conversion::unidirectional`, was auf eine klare Strukturierung der Konvertierungsadapter hindeutet.

## Zustandsübersicht

Als Composite FB besitzt **AUI_TO_AD** keine eigene Zustandsmaschine. Der Funktionsablauf ist rein ereignisgesteuert: Ein Ereignis am Eingang löst die Umwandlung aus, nach deren Abschluss ein Ereignis am Ausgang generiert wird. Zwischen diesen Ereignissen gibt es keine internen Zustände.

## Anwendungsszenarien

- **Datenintegration**: Ein AUI-Adapter liefert einen UINT-Wert (z. B. aus einem Sensormodul), der in einem System benötigt wird, das ausschließlich DWORD-Adressen (z. B. über einen AD-Adapter) verarbeitet.
- **Protokollanpassung**: Wenn vorhandene Komponenten mit unterschiedlichen Datentypen arbeiten, kann dieser Baustein als einfacher Konverter zwischen den Adapterschnittstellen eingesetzt werden.
- **Modularisierung**: Innerhalb einer 4diac-Applikation können so standardisierte Konvertierungsbausteine als Adapter zusammengefasst werden, um die Wiederverwendbarkeit zu erhöhen.

## Vergleich mit ähnlichen Bausteinen

Es existieren vergleichbare Konvertierungsbausteine für andere Datentypen, z. B. `WORD_TO_DWORD`, `BYTE_TO_DWORD` oder generische `TO_DWORD`-Funktionen. Der Besonderheit von **AUI_TO_AD** liegt in der Kapselung der Adapterprotokolle: Statt einer direkten Datenverbindung werden die Werte über Adapter bereitgestellt, was eine lose Kopplung zwischen den Komponenten ermöglicht. Im Gegensatz zu einem direkten Aufruf von `F_UINT_TO_DWORD` in einer Applikation bietet dieser FB eine standardisierte, wiederverwendbare Schnittstelle auf Adapterebene.

## Fazit

Der Baustein **AUI_TO_AD** bietet eine saubere, auf Adapter basierende Lösung zur Umwandlung von UINT- in DWORD-Werte. Er ist einfach zu verwenden, erfordert keine eigene Programmierung und fügt sich nahtlos in die 4diac-Welt mit Ereignis- und Adapternetzwerken ein. Durch die Kapselung des Standardkonverters bleibt die Funktionalität robust und normkonform. Der Baustein eignet sich besonders für Anwendungen, bei denen unterschiedliche Adaptertypen harmonisiert werden müssen.