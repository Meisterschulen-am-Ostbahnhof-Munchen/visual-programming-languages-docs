# AX_TO_AD


![AX_TO_AD](./AX_TO_AD.svg)

* * * * * * * * * *
## Einleitung
Der Composite FB `AX_TO_AD` dient der Konvertierung eines Bool-Adapters (AX) in einen DWORD-Adapter (AD). Er leitet Ereignis- und Datensignale vom Eingangsadapter direkt an den Ausgangsadapter weiter und wandelt implizit den Datentyp von BOOL nach DWORD um.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den Socket `AX_IN`.

### **Ereignis-Ausgänge**
Es existieren keine direkten Ereignis-Ausgänge. Die Ereignisweitergabe erfolgt über den Plug `AD_OUT`.

### **Daten-Eingänge**
Es sind keine direkten Daten-Eingänge vorhanden. Die Datenaufnahme erfolgt über den Socket `AX_IN`.

### **Daten-Ausgänge**
Es gibt keine direkten Daten-Ausgänge. Die Datenausgabe wird über den Plug `AD_OUT` realisiert.

### **Adapter**
- **AX_IN** (Socket): Adapter vom Typ `adapter::types::unidirectional::AX`. Stellt ein BOOL-Signal (D1) und ein Trigger-Ereignis (E1) bereit.
- **AD_OUT** (Plug): Adapter vom Typ `adapter::types::unidirectional::AD`. Erwartet ein DWORD-Signal (D1) und ein Trigger-Ereignis (E1).

## Funktionsweise
Der FB verknüpft den Eingangsadapter `AX_IN` direkt mit dem Ausgangsadapter `AD_OUT`:

- **Ereignispfad**: Das Ereignis von `AX_IN.E1` wird unverändert an `AD_OUT.E1` weitergeleitet.
- **Datenpfad**: Der boolesche Wert von `AX_IN.D1` wird auf `AD_OUT.D1` übertragen. Dabei erfolgt eine implizite Typkonvertierung: `TRUE` wird zu `1` (DWORD), `FALSE` zu `0` (DWORD).

Der Baustein selbst enthält keine eigene Logik oder Zustandsautomaten – er fungiert als reiner Durchreiche-Konverter zwischen den beiden Adaptertypen.

## Technische Besonderheiten
- **Composite FB**: Die Implementierung besteht ausschließlich aus einer Verdrahtung im FBNetzwerk, ohne zusätzliche Algorithmen.
- **Implizite Datentypkonvertierung**: Der BOOL-Wert wird automatisch in einen DWORD-Wert umgewandelt (Bits 0..31: 0 oder 1).
- **Unidirektionale Adapter**: Sowohl Ein- als auch Ausgang verwenden unidirektionale Adapter, die nur eine Daten- und eine Ereignisverbindung unterstützen.

## Zustandsübersicht
Der `AX_TO_AD` FB besitzt keinen eigenen internen Zustand. Sein Verhalten ist rein reaktiv: Ein eintreffendes Ereignis am Eingang wird sofort an den Ausgang weitergegeben, optional begleitet von der aktualisierten Datensignatur.

## Anwendungsszenarien
- Integration eines digitalen Sensors (z.B. Schalter, Lichtschranke) in ein System, das einen DWORD-Adapter für die Datenaufnahme erwartet.
- Schrittweise Migration einer Anwendung von BOOL-basierten zu DWORD-basierten Adapter-Schnittstellen.
- Prototypische Verbindung zwischen unterschiedlichen Bibliotheken oder Komponenten mit inkompatiblen Adaptertypen.

## Vergleich mit ähnlichen Bausteinen
- **BOOL_TO_DWORD** (Funktionsbaustein): Führt die reine Datentypkonvertierung durch, jedoch ohne Adapter-Kapselung.
- **AX_TO_AD** spezialisiert auf die Adapter-Schnittstellen und eignet sich daher besonders für den Austausch zwischen verschiedenen Kommunikationsmustern in 4diac.
- Ähnliche Bausteine existieren für andere Typkombinationen, z. B. `INT_TO_REAL_AD` oder `WORD_TO_BOOL_AD`.

## Fazit
Der `AX_TO_AD` FB bietet eine einfache und saubere Möglichkeit, einen BOOL-Adapter in einen DWORD-Adapter umzuwandeln, ohne dass der Anwender selbst Konvertierungslogik schreiben muss. Er eignet sich ideal für die Kopplung unterschiedlicher Adapter-Welten in 4diac-Projekten.