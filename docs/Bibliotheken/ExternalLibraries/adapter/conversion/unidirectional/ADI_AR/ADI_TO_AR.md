# ADI_TO_AR


![ADI_TO_AR](./ADI_TO_AR.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ADI_TO_AR** ist ein Composite-Baustein, der einen DINT-Adapter (ADI) in einen REAL-Adapter (AR) umwandelt. Er dient als Vermittler zwischen Komponenten, die über unidirektionale Adapter kommunizieren, und führt dabei eine Datentypkonvertierung von Ganzzahl (DINT) auf Gleitkommazahl (REAL) durch.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- Keine direkt sichtbaren Ereignis-Eingänge. Die Ereignissteuerung erfolgt indirekt über den Adapter **ADI_IN** (Ereignis E1).

### **Ereignis-Ausgänge**
- Keine direkt sichtbaren Ereignis-Ausgänge. Die Ereignissignalisierung erfolgt indirekt über den Adapter **AR_OUT** (Ereignis E1).

### **Daten-Eingänge**
- Keine direkt sichtbaren Daten-Eingänge. Der Eingabedatenwert wird über den Adapter **ADI_IN** (Datenpunkt D1 vom Typ DINT) bereitgestellt.

### **Daten-Ausgänge**
- Keine direkt sichtbaren Daten-Ausgänge. Der Ausgabedatenwert wird über den Adapter **AR_OUT** (Datenpunkt D1 vom Typ REAL) ausgegeben.

### **Adapter**

| Adapter | Rolle | Typ | Beschreibung |
|---------|-------|-----|--------------|
| ADI_IN | Socket | adapter::types::unidirectional::ADI | Unidirektionaler DINT-Adapter als Eingangsschnittstelle. |
| AR_OUT | Plug | adapter::types::unidirectional::AR | Unidirektionaler REAL-Adapter als Ausgangsschnittstelle. |

## Funktionsweise
Der Baustein enthält intern einen einzelnen Funktionsbaustein `F_DINT_TO_REAL` aus der IEC 61131-3 Standardbibliothek. Die Ablaufsteuerung erfolgt rein ereignisgesteuert:

1. Ein Ereignis am Eingangsadapter **ADI_IN.E1** triggert den Eingang **REQ** des internen Konvertierungsbausteins.
2. Der Datenwert **ADI_IN.D1** (DINT) wird an den Eingang **IN** des Konverters übergeben.
3. Bei Abschluss der Konvertierung signalisiert der Ausgang **CNF** des Konverters ein Ereignis.
4. Dieses Ereignis wird an den Ausgangsadapter **AR_OUT.E1** weitergeleitet.
5. Gleichzeitig wird der konvertierte REAL-Wert (Ausgang **OUT**) an den Datenpunkt **AR_OUT.D1** übergeben.

Der gesamte Vorgang erfolgt synchron und ohne Zwischenspeicherung – jede erfolgreiche Konvertierung löst sofort ein Ausgangsereignis aus.

## Technische Besonderheiten
- **Typkonvertierung nach IEC 61131-3**: Der interne Baustein `F_DINT_TO_REAL` garantiert eine standardkonforme Umwandlung von 32-Bit-Ganzzahlen in Gleitkommazahlen (einfache Genauigkeit).
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangsadapter sind unidirektional ausgelegt. Eine Rückwärtskommunikation ist nicht vorgesehen, was die Implementierung vereinfacht und den Datenfluss eindeutig festlegt.
- **Composite-Struktur**: Der Baustein besteht aus einem Netzwerk, das vollständig im FB selbst gekapselt ist. Er eignet sich daher besonders gut für modulare, wiederverwendbare Schnittstellen.
- **Keine Zustände**: Es existiert kein Zustandsautomat – die Funktionalität ist rein kombinatorisch mit einem ereignisgesteuerten Trigger.

## Zustandsübersicht
Der Baustein besitzt keine eigene Zustandsmaschine. Der Ablauf lässt sich als einfacher Schritt beschreiben:

| Schritt | Aktion |
|---------|--------|
| 1 | Warten auf Ereignis an **ADI_IN.E1** |
| 2 | Konvertierung des Datenwerts von DINT nach REAL |
| 3 | Ausgabe des konvertierten Werts an **AR_OUT.D1** und Ereignis an **AR_OUT.E1** |
| 4 | Rückkehr zu Schritt 1 |

## Anwendungsszenarien
- **Sensorintegration**: Ein Sensor liefert ganzzahlige Messwerte (z. B. Drehzahl, Zählerstand) über einen ADI-Adapter. Für eine nachgelagerte Regelung oder Visualisierung, die REAL-Werte erwartet, wird dieser Baustein als Konverter eingesetzt.
- **Schnittstellenanpassung**: In heterogenen Steuerungssystemen, in denen verschiedene Komponenten unterschiedliche Datentypen verwenden, ermöglicht der Baustein eine nahtlose Integration ohne Änderung der vorhandenen Adapterdefinitionen.
- **Typsichere Datenverarbeitung**: Durch die explizite Konvertierung werden Laufzeitfehler vermieden, die bei impliziten Typumwandlungen in IEC 61499 auftreten können.

## Vergleich mit ähnlichen Bausteinen
- **F_DINT_TO_REAL**: Ein direkter Aufruf dieses Standardbausteins würde denselben Zweck erfüllen, erfordert jedoch eine manuelle Verschaltung von Ereignis- und Datenverbindungen. Der Adapter-basierte Ansatz vereinfacht die Wiederverwendung und verbessert die Lesbarkeit des Netzwerks.
- **ADI_TO_AR** im Gegensatz zu anderen Konvertierungsbausteinen (z. B. REAL_TO_DINT): Dieser Baustein ist speziell für die unidirektionale Adapter-Kommunikation ausgelegt und bietet keine weiteren Konvertierungsrichtungen an.
- **Composite-Bausteine ohne Adapter**: Andere Implementierungen nutzen direkte Daten- und Ereignis-Ports, was die Flexibilität beim Austausch von Komponenten einschränkt. Die Adapter-Schnittstelle erlaubt ein einfaches Plug-and-Play in vordefinierten Architekturen.

## Fazit
Der **ADI_TO_AR**-Funktionsblock stellt eine elegante und standardkonforme Lösung zur Umwandlung von DINT- in REAL-Werte dar, die vollständig in die Adapter-basierte Kommunikationsstruktur der IEC 61499 eingebettet ist. Durch die Kapselung des Konvertierungsvorgangs in einem wiederverwendbaren Composite-Baustein wird die Entwicklung modularer, typsicherer und gut dokumentierter Automatisierungssysteme unterstützt.