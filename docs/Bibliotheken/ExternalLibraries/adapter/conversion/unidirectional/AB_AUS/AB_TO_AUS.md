# AB_TO_AUS


![AB_TO_AUS](./AB_TO_AUS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AB_TO_AUS** ist ein Composite-Baustein, der eine unidirektionale Konvertierung von Daten vom **AB-Adapter** (BYTE) zum **AUS-Adapter** (USINT) vornimmt. Er kapselt die notwendige Typumwandlung und Ereignisweitergabe und ermöglicht so die nahtlose Integration von Komponenten, die auf unterschiedlichen Datentypen basieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt auf oberster Ebene keine separaten Ereignis-Eingänge. Das auslösende Ereignis wird über den Socket-Adapter **AB_IN** bereitgestellt (dort als `E1` verfügbar).

### **Ereignis-Ausgänge**

Es gibt keine direkten Ereignis-Ausgänge auf der Ebene des Composite-FBs. Das resultierende Ereignis wird über den Plug-Adapter **AUS_OUT** (dort als `E1`) ausgegeben.

### **Daten-Eingänge**

Auf oberster Ebene sind keine Daten-Eingänge definiert. Die Eingangsdaten (BYTE) werden über den Socket-Adapter **AB_IN** (dort als `D1`) entgegengenommen.

### **Daten-Ausgänge**

Es existieren keine direkten Daten-Ausgänge. Die konvertierten Daten (USINT) werden über den Plug-Adapter **AUS_OUT** (dort als `D1`) bereitgestellt.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| Socket | **AB_IN** | Eingang | Unidirektionaler Adapter vom Typ `adapter::types::unidirectional::AB`. Liefert ein BYTE (`D1`) sowie ein Ereignis (`E1`). |
| Plug | **AUS_OUT** | Ausgang | Unidirektionaler Adapter vom Typ `adapter::types::unidirectional::AUS`. Stellt ein USINT (`D1`) sowie ein Ereignis (`E1`) zur Verfügung. |

## Funktionsweise

1. Ein Ereignis an `AB_IN.E1` löst die Verarbeitung aus.  
2. Der Wert von `AB_IN.D1` (BYTE) wird an den internen Konverter **F_BYTE_TO_USINT** übergeben.  
3. Der Konverter wandelt das BYTE in einen USINT-Wert um.  
4. Das Ergebnis wird auf `AUS_OUT.D1` (USINT) ausgegeben.  
5. Gleichzeitig wird ein Ereignis auf `AUS_OUT.E1` erzeugt, um die nachfolgende Verarbeitung zu signalisieren.

Die gesamte Konvertierung erfolgt ereignisgesteuert und in einem Schritt.

## Technische Besonderheiten

- **Unidirektionale Adapterkopplung**: Der FB verbindet zwei unidirektionale Adapter (AB → AUS) und stellt sicher, dass die Datenflussrichtung klar definiert ist.  
- **Wiederverwendbare IEC-Konvertierung**: Intern wird der standardisierte Baustein `iec61131::conversion::F_BYTE_TO_USINT` verwendet.  
- **Composite-Architektur**: Die Konvertierungslogik ist gekapselt und kann leicht in andere Projekte eingebunden oder durch alternative Konverter ersetzt werden.  
- **Kein interner Zustand**: Der FB besitzt keinen eigenen Zustandsautomaten; er leitet Ereignisse und Daten direkt weiter.

## Zustandsübersicht

Der **AB_TO_AUS**-Baustein besitzt keinen eigenen Zustandsautomaten. Die Funktionsweise entspricht einer reinen, ereignisgesteuerten Datenumsetzung. Der interne Konverter `F_BYTE_TO_USINT` arbeitet ebenfalls ohne Zustandspeicherung.

## Anwendungsszenarien

- **Systemintegration**: Verbindung eines Geräts, das Messwerte als BYTE über den AB-Adapter bereitstellt, mit einer Steuerung, die USINT-Daten über den AUS-Adapter erwartet.  
- **Protokollanpassung**: Umwandlung von BYTE-kodierten Befehlen in USINT-kodierte Werte für die Weiterverarbeitung in Bibliotheken, die ausschließlich USINT unterstützen.  
- **Modulare Wiederverwendung**: Kapselung der Konvertierung als eigenständigen Baustein, um die Übersichtlichkeit in großen Automatisierungsprojekten zu erhöhen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung |
|----------|--------------|
| **F_BYTE_TO_USINT** | Einfacher IEC-Konverter ohne Adapteranbindung. Muss manuell mit Ereignis- und Datenverbindungen verdrahtet werden. |
| **AB_TO_AUS** | Composite-FB, der die gesamte Adapterkonvertierung inklusive Ereignisweitergabe kapselt und dadurch eine saubere, abstrahierte Schnittstelle bietet. |
| **AUS_TO_AB** (hypothetisch) | Reverse-Conversion von USINT zu BYTE – spiegelbildliche Funktionalität für die Gegenrichtung. |

Der **AB_TO_AUS** hebt sich durch seine einfache Handhabung und die direkte Adapterkompatibilität hervor.

## Fazit

Der **AB_TO_AUS**-Funktionsblock bietet eine elegante und standardisierte Möglichkeit, BYTE-Daten aus einem AB-Adapter in USINT-Daten für einen AUS-Adapter umzuwandeln. Durch die Kapselung der Konvertierungslogik in einem Composite-Baustein wird die Wiederverwendbarkeit gefördert und die Systemintegration vereinfacht. Er eignet sich besonders für modulare Automatisierungslösungen auf Basis von IEC 61499.