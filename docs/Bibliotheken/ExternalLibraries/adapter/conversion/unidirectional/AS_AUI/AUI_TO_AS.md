# AUI_TO_AS


![AUI_TO_AS](./AUI_TO_AS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUI_TO_AS` ist ein Composite Baustein, der die Konvertierung eines **AUI (UINT)**-Adapters in einen **AS (SINT)**-Adapter ermöglicht.  
Er kapselt die notwendige Signal- und Datenumwandlung in einer wiederverwendbaren Einheit und stellt die konvertierten Werte über einen einheitlichen Adapterausgang bereit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der Baustein besitzt auf seiner obersten Ebene **keine direkten Ereignis-Eingänge**.  
Das auslösende Ereignis wird über den Socket `AUI_IN` (Adapter `adapter::types::unidirectional::AUI`) bereitgestellt. Dieses Ereignis (bezeichnet als `E1`) startet die Konvertierung intern.

### **Ereignis-Ausgänge**
Auf der obersten Ebene sind **keine direkten Ereignis-Ausgänge** vorhanden.  
Das Abschlussereignis der Konvertierung wird über den Plug `AS_OUT` (Adapter `adapter::types::unidirectional::AS`) als Ereignis `E1` nach außen gegeben.

### **Daten-Eingänge**
Es existieren **keine direkten Daten-Eingänge**.  
Die Eingangsdaten (Datentyp `UINT`) werden über den Socket `AUI_IN` (Kanal `D1`) in den Baustein eingespeist.

### **Daten-Ausgänge**
Auch **keine direkten Daten-Ausgänge** sind vorhanden.  
Die konvertierten Daten (Datentyp `SINT`) verlassen den Baustein über den Plug `AS_OUT` (Kanal `D1`).

### **Adapter**

| Richtung | Name   | Typ                                    | Beschreibung                     |
|----------|--------|----------------------------------------|----------------------------------|
| Socket   | AUI_IN | `adapter::types::unidirectional::AUI` | Eingangsadapter (UINT-Daten)     |
| Plug     | AS_OUT | `adapter::types::unidirectional::AS`  | Ausgangsadapter (SINT-Daten)     |

## Funktionsweise

Der Baustein arbeitet als reine Kapselung eines Konvertierungsvorgangs:

1. Ein eingehendes Ereignis über `AUI_IN.E1` triggert den internen Funktionsblock `Convert` (vom Typ `iec61131::conversion::F_UINT_TO_SINT`).
2. Gleichzeitig wird der Datenwert von `AUI_IN.D1` (Typ `UINT`) an den Eingang `Convert.IN` weitergeleitet.
3. Nach Ausführung der Umwandlung sendet `Convert.CNF` ein Ereignis an `AS_OUT.E1`.
4. Der konvertierte Wert (`SINT`) wird von `Convert.OUT` auf `AS_OUT.D1` übertragen.

Dadurch wird eine durchgängige, ereignisgesteuerte Konvertierung von einem UINT-Adapter zu einem SINT-Adapter realisiert, ohne dass der Anwender die Konvertierungsdetails selbst implementieren muss.

## Technische Besonderheiten

- **Composite-Baustein:** Alle Verbindungen sind innerhalb eines Netzwerks gekapselt. Die interne Logik bleibt für die aufrufende Umgebung verborgen.
- **Verwendung der Standard-Konvertierungsfunktion:** Die eigentliche Umwandlung erfolgt durch den IEC-61131-Baustein `F_UINT_TO_SINT`. Dieser ist extern referenziert und wird als Bibliotheksbaustein importiert.
- **Unidirektionale Adapter:** Sowohl Ein- als auch Ausgangsadapter sind unidirektional ausgelegt, d.h. die Daten fließen nur in eine Richtung (vom Eingang zum Ausgang).
- **Keine eigenen Zustände:** Da es sich um einen Composite-Baustein handelt, existiert kein eigenes ECC (Execution Control Chart). Das Verhalten ergibt sich ausschließlich aus den internen Verbindungen.

## Zustandsübersicht

Der Baustein besitzt **keinen eigenen Zustandsautomaten**.  
Seine Funktionsweise ist rein datenfluss- und ereignisgesteuert durch die Vernetzung der enthaltenen Elemente. Es gibt keine definierten Zustände wie IDLE, BUSY oder ERROR.

## Anwendungsszenarien

- **Adapter-Brückenbildung:** Wenn in einer Anwendung Adapter mit unterschiedlichen Datentypen (z.B. AUI mit `UINT` und AS mit `SINT`) aufeinandertreffen, kann dieser Baustein als Konverter zwischen den Adapter-Schnittstellen eingesetzt werden.
- **Systemintegration:** In heterogenen Steuerungssystemen, in denen Komponenten unterschiedliche Datentypen verwenden, erleichtert der Baustein die Integration ohne manuelle Typkonvertierung.
- **Wiederverwendung:** Der Composite-Baustein kann mehrfach in verschiedenen Projekten oder Netzwerken eingebunden werden, um immer die gleiche Konvertierungslogik bereitzustellen.

## Vergleich mit ähnlichen Bausteinen

- **Andere Konvertierungs-Adapter:** Es existieren ähnliche Bausteine wie `SINT_TO_UINT_AS` oder generische Typkonverter. Der Unterschied liegt in der spezifischen Typkombination (UINT → SINT) und der Nutzung von Adaptern statt direkter Ereignis-/Daten-Eingänge.
- **Direkte Konvertierung ohne Adapter:** Statt eines Adapter-basierten Bausteins könnte man auch die Funktion `F_UINT_TO_SINT` direkt verwenden und die Adapter-Schnittstellen separat verdrahten. Der Composite-Baustein vereinfacht dies durch Kapselung.

## Fazit

Der Funktionsblock `AUI_TO_AS` bietet eine einfache, gekapselte Lösung zur Umwandlung eines unidirektionalen UINT-Adapters in einen SINT-Adapter. Durch die Nutzung einer standardisierten IEC-61131-Konvertierungsfunktion und die klare Ereignissteuerung fügt er sich nahtlos in 4diac-IDE-Projekte ein. Er eignet sich besonders für Szenarien, in denen Adapter unterschiedlicher Datentypen verbunden werden müssen, ohne dass der Anwender die Konvertierungslogik selbst implementieren muss.