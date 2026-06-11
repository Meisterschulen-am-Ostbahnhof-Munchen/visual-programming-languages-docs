# AUS_TO_AS


![AUS_TO_AS](./AUS_TO_AS.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AUS_TO_AS** ist ein zusammengesetzter Baustein (Composite FB) zur Umwandlung eines unidirektionalen AUS-Adapters (basierend auf dem Datentyp USINT) in einen unidirektionalen AS-Adapter (basierend auf dem Datentyp SINT). Er dient als standardisierte Schnittstelle zwischen Komponenten, die unterschiedliche vorzeichenlose/vorzeichenbehaftete Ganzzahl-Typen verwenden.

## Schnittstellenstruktur
Der FB verfügt über keine direkten Ereignis- oder Dateneingänge/-ausgänge, sondern ausschließlich über zwei Adapter-Schnittstellen:

### **Ereignis-Eingänge**
Keine direkt sichtbaren Ereigniseingänge. Die Ereignissteuerung erfolgt über den Socket-Adapter `AUS_IN`.

### **Ereignis-Ausgänge**
Keine direkt sichtbaren Ereignisausgänge. Die Ereignisrückmeldung erfolgt über den Plug-Adapter `AS_OUT`.

### **Daten-Eingänge**
Keine direkt sichtbaren Dateneingänge. Die Daten werden über den Socket-Adapter `AUS_IN` bereitgestellt.

### **Daten-Ausgänge**
Keine direkt sichtbaren Datenausgänge. Die Daten werden über den Plug-Adapter `AS_OUT` ausgegeben.

### **Adapter**
| Name     | Typ                                           | Richtung | Kommentar                     |
|----------|-----------------------------------------------|----------|-------------------------------|
| `AUS_IN` | `adapter::types::unidirectional::AUS` (Socket) | Eingang  | USINT-Adapter-Eingang         |
| `AS_OUT` | `adapter::types::unidirectional::AS` (Plug)  | Ausgang  | SINT-Adapter-Ausgang          |

Die Schnittstelle der Adapter selbst enthält:
- `AUS_IN.E1` (Event), `AUS_IN.D1` (USINT)
- `AS_OUT.E1` (Event), `AS_OUT.D1` (SINT)

## Funktionsweise
Der FB ist als Composite implementiert und enthält einen internen Funktionsblock `Convert` vom Typ `iec61131::conversion::F_USINT_TO_SINT`, der die eigentliche Wertekonvertierung durchführt.

1. **Datenerfassung:** Ein anliegender USINT-Wert wird über den Socket `AUS_IN.D1` bereitgestellt.
2. **Triggerung:** Ein Ereignis am Ausgang `AUS_IN.E1` löst den Eingang `REQ` des Konvertierungsbausteins aus.
3. **Konvertierung:** Der interne FB `F_USINT_TO_SINT` wandelt den USINT-Wert in einen entsprechenden SINT-Wert um (Wertebereich 0..255 → -128..127; bei Überschreitung erfolgt eine Bereichsbegrenzung gemäß IEC 61131).
4. **Rückmeldung:** Nach Abschluss der Konvertierung signalisiert der interne FB über seinen Ausgang `CNF` ein Ereignis an den Plug `AS_OUT.E1`.
5. **Datenweitergabe:** Der konvertierte SINT-Wert wird über `AS_OUT.D1` an den angeschlossenen Plug ausgegeben.

Die Verbindungen im FBNetzwerk sind:
- Ereignis: `AUS_IN.E1` → `Convert.REQ`
- Ereignis: `Convert.CNF` → `AS_OUT.E1`
- Daten: `AUS_IN.D1` → `Convert.IN`
- Daten: `Convert.OUT` → `AS_OUT.D1`

## Technische Besonderheiten
- **Adapterbasiert:** Der Baustein fungiert als reiner Adapter-Konverter und kann nahtlos in bestehende adapterorientierte Systeme integriert werden.
- **Composite-Struktur:** Die Umwandlung erfolgt durch einen internen, standardisierten IEC-61131-Konverter, was eine zuverlässige und zertifizierte Konvertierung gewährleistet.
- **Unidirektionale Schnittstelle:** Die Daten- und Ereignisflüsse sind strikt von Eingang zu Ausgang gerichtet.
- **Kein expliziter Zustandsautomat:** Die Steuerung erfolgt rein ereignisgesteuert über die Adapter-Ereignisse. Es gibt keine internen Zustände.

## Zustandsübersicht
Der FB besitzt keinen sichtbaren Zustandsautomaten. Er verhält sich wie ein transparentes Gateway, das bei jedem Ereignis am Eingang die Umwandlung auslöst und das Ergebnis am Ausgang bereitstellt.

## Anwendungsszenarien
- **Integration von Komponenten** mit unterschiedlichen Datentypen, z. B. wenn ein Sensor USINT-Daten liefert, ein nachfolgender Regler aber SINT-Werte erwartet.
- **Adapter-Konvertierung** in modularen Steuerungssystemen, die auf unidirektionalen Adaptern basieren (z. B. nach IEC 61499).
- **Sicherheitskritische Systeme**, in denen die genaue Typumwandlung (ohne Überlauf) essenziell ist – der interne FB `F_USINT_TO_SINT` ist spezifikationskonform.

## Vergleich mit ähnlichen Bausteinen
- **Einfache Konverter wie `F_USINT_TO_SINT`:** Wandeln nur skalare Werte, verwenden aber keine Adapter. `AUS_TO_AS` kapselt diese Konvertierung in einem adapterbasierten Baustein.
- **`INT_TO_DINT`-Adapter:** Andere Typkonvertierungen (z. B. INT nach DINT) folgen demselben Muster, unterscheiden sich jedoch in der Bitbreite und Vorzeichenbehandlung.
- **Bidirektionale Adapter:** Im Gegensatz zu bidirektionalen Varianten ist dieser FB nur für einen Datenfluss ausgelegt, was die Komplexität reduziert.

## Fazit
Der **AUS_TO_AS**-Funktionsblock bietet eine saubere, adapterbasierte Lösung zur Konvertierung von USINT- nach SINT-Werten. Dank seiner Composite-Struktur und der Nutzung eines standardisierten IEC-61131-Konverters ist er wartungsfreundlich, zuverlässig und leicht in industrielle Steuerungsnetzwerke integrierbar. Er eignet sich besonders für Systeme, die auf unidirektionale Adapter setzen und eine explizite Typumwandlung benötigen.