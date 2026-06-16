# AD_TO_AR


![AD_TO_AR](./AD_TO_AR.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AD_TO_AR** ist ein Composite-Baustein zur Umwandlung eines DWORD-Werts aus einem unidirektionalen AD-Adapter (Socket) in einen REAL-Wert, der über einen AR-Adapter (Plug) ausgegeben wird. Er kapselt die Konvertierungslogik und ermöglicht so eine einfache Adapter-basierte Datenübertragung zwischen unterschiedlichen Datentypen.

## Schnittstellenstruktur
Der Baustein besitzt keine direkten (einzelnen) Ereignis- oder Daten-Ein-/Ausgänge. Die gesamte Kommunikation erfolgt über zwei Adapter-Schnittstellen:

### **Ereignis-Eingänge**
- *Keine direkten Ereignis-Eingänge* – die Ereignissteuerung erfolgt über den eingehenden Adapter.

### **Ereignis-Ausgänge**
- *Keine direkten Ereignis-Ausgänge* – die Ereignisausgabe erfolgt über den ausgehenden Adapter.

### **Daten-Eingänge**
- *Keine direkten Daten-Eingänge* – die Datenaufnahme erfolgt über den eingehenden Adapter.

### **Daten-Ausgänge**
- *Keine direkten Daten-Ausgänge* – die Datenausgabe erfolgt über den ausgehenden Adapter.

### **Adapter**

| Name   | Typ                                       | Richtung | Beschreibung                                                                 |
|--------|--------------------------------------------|----------|-----------------------------------------------------------------------------|
| AD_IN  | `adapter::types::unidirectional::AD`      | Socket   | Empfängt ein Ereignis (E1) und einen DWORD-Wert (D1) zur Konvertierung.    |
| AR_OUT | `adapter::types::unidirectional::AR`      | Plug     | Sendet ein Ereignis (E1) mit dem konvertierten REAL-Wert (D1) aus.         |

## Funktionsweise
Der Baustein arbeitet als ereignisgesteuerte Pipeline:

1. Ein eingehendes Ereignis am Socket **AD_IN.E1** triggert die Konvertierung.
2. Der Datenwert **AD_IN.D1** (DWORD) wird an den internen Funktionsblock `F_DWORD_TO_REAL` übergeben.
3. Nach erfolgreicher Konvertierung signalisiert der interne Baustein ein Ausgangsereignis (**CNF**).
4. Dieses Ereignis wird an den Plug **AR_OUT.E1** weitergeleitet und zeitgleich der konvertierte REAL-Wert über **AR_OUT.D1** ausgegeben.

Die Wertumwandlung erfolgt gemäß der IEC-61131-Standardfunktion `DWORD_TO_REAL`.

## Technische Besonderheiten
- **Composite-Baustein**: Die Konvertierungslogik ist vollständig in einem internen Netzwerk aus einem einzigen Funktionsblock realisiert.
- **Typkonvertierung über Adapter**: Der Baustein ermöglicht die Anbindung von Komponenten, die ausschließlich über Adapter-Schnittstellen kommunizieren, ohne dass zusätzliche manuelle Konvertierungen notwendig sind.
- **Standardkonformität**: Verwendet die IEC-61131-Bibliotheksfunktion `F_DWORD_TO_REAL`, dadurch portabel und gut getestet.
- **Unidirektionale Adapter**: Sowohl Eingangs- als auch Ausgangsadapter sind als unidirektional ausgeführt, d.h. es findet nur eine Datenflussrichtung statt.

## Zustandsübersicht
Der Baustein besitzt keinen eigenen Zustandsautomaten. Die Verarbeitung erfolgt streng kausal: Ein Ereignis am Eingang löst sofort die Konvertierung und Ausgabe aus. Es gibt keine Verzögerungen oder Zwischenzustände.

## Anwendungsszenarien
- **Adapter-Brücke**: Verbindung einer Komponente, die DWORD über Adapter liefert (z. B. aus einem binären Sensorwert), mit einer Komponente, die REAL über Adapter erwartet (z. B. eine Steuerung mit Fließkommaberechnung).
- **Wertumwandlung in Adapter-Netzwerken**: Wenn in einer 4diac-IDE-Anwendung Adapter unterschiedlicher Datentypen aufeinandertreffen, kann dieser FB als einfacher Konverter dienen.
- **Datenvorbereitung**: Vor der Weiterverarbeitung in Analyse- oder Visualisierungsblöcken, die REAL-Werte benötigen.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Konvertierungsbausteine existieren für andere Datentypen, z. B.:
- `WORD_TO_REAL` oder `INT_TO_REAL` – direkt als Einzelfunktionsblöcke,
- `AD_TO_AR` – als Composite mit Adapter-Schnittstelle.

Der Vorteil des `AD_TO_AR` liegt in der nahtlosen Integration in adapterbasierte Architekturen, während reine IEC-61131-Bausteine oft manuelle Verbindungen erfordern.

## Fazit
Der **AD_TO_AR**-Baustein bietet eine kompakte und standardkonforme Lösung zur Umwandlung von DWORD- in REAL-Werte über Adapter-Schnittstellen. Durch die Kapselung als Composite erhöht er die Wiederverwendbarkeit und vereinfacht den Entwurf von adapterbasierten Automatisierungslösungen.