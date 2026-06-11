# AX_TO_ADI


![AX_TO_ADI](./AX_TO_ADI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AX_TO_ADI** ist ein zusammengesetzter Baustein (Composite FB), der einen AX-Adapter mit boolescher Schnittstelle (BOOL) in einen ADI-Adapter mit ganzzahliger Schnittstelle (DINT) umwandelt. Er dient als Konverter zwischen unidirektionalen Adaptern und ermöglicht die nahtlose Integration von binären Signalen in Systeme, die integerbasierte Adapter verwenden.

## Schnittstellenstruktur
Da es sich um einen Composite FB handelt, werden alle Ein- und Ausgänge über die enthaltenen Adapter realisiert. Die folgende Aufstellung zeigt die logischen Schnittstellen.

### **Ereignis-Eingänge**
Der Baustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den **AX_IN** Adapter:
- **E1** (BOOT): Ereigniseingang des AX-Adapter, der die Datenkonvertierung auslöst.

### **Ereignis-Ausgänge**
Der Baustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt über den **ADI_OUT** Adapter:
- **E1** (CNF): Ereignisausgang des ADI-Adapter, signalisiert die Fertigstellung der Konvertierung.

### **Daten-Eingänge**
Der Baustein besitzt keine direkten Daten-Eingänge. Die Datenaufnahme erfolgt über den **AX_IN** Adapter:
- **D1** (BOOL): Boolescher Eingangswert, der in einen DINT-Wert umgewandelt wird.

### **Daten-Ausgänge**
Der Baustein besitzt keine direkten Daten-Ausgänge. Die Datenausgabe erfolgt über den **ADI_OUT** Adapter:
- **D1** (DINT): Konvertierter ganzzahliger Ausgangswert (0 bei FALSE, 1 bei TRUE).

### **Adapter**
- **AX_IN** (Socket): Empfängt einen AX-Adapter (Typ: `adapter::types::unidirectional::AX`) mit einem booleschen Daten- und Ereignisknal.
- **ADI_OUT** (Plug): Stellt einen ADI-Adapter (Typ: `adapter::types::unidirectional::ADI`) mit einem DINT-Daten- und Ereignisknal zur Verfügung.

## Funktionsweise
Der Baustein nutzt intern den IEC 61131-3 Konverter `F_BOOL_TO_DINT`. Sobald am **AX_IN.E1** ein Ereignis eintrifft, wird der aktuelle Wert von **AX_IN.D1** ausgelesen und dem Konverter übergeben. Der Konverter setzt bei FALSE den Wert 0 und bei TRUE den Wert 1. Nach Abschluss der Konvertierung wird der Ergebniswert an **ADI_OUT.D1** weitergegeben und gleichzeitig ein Ereignis an **ADI_OUT.E1** gesendet.

Die Ereigniskette ist damit vollständig durchgeschliffen:  
`AX_IN.E1` → Konvertierung → `ADI_OUT.E1`.

## Technische Besonderheiten
- **Reine Datenkonvertierung:** Der Baustein führt keine Zustandslogik oder zeitliche Verzögerung durch – jede Ereignisaktivierung am Eingang erzeugt sofort eine Ausgabe.
- **Verwendung von IEC 61131-Bibliotheken:** Die Konvertierung basiert auf dem standardisierten Funktionsbaustein `F_BOOL_TO_DINT` aus der IEC 61131-Konvertierungsbibliothek.
- **Unidirektionale Adapter:** Sowohl AX als auch ADI sind unidirektionale Adapter, d.h. sie unterstützen nur eine Richtung (hier Eingang bzw. Ausgang). Dies vereinfacht die Datenflusssteuerung.
- **Composite FB ohne eigenen Zustand:** Als Composite FB besitzt der Baustein keinen internen Zustandsautomaten; die gesamte Logik wird durch den enthaltenen Funktionsbaustein realisiert.

## Zustandsübersicht
Als Composite FB hat **AX_TO_ADI** keinen eigenen Zustandsautomaten. Das Verhalten wird ausschließlich vom eingebetteten `F_BOOL_TO_DINT` bestimmt, der keine zustandsabhängige Logik besitzt. Die Ausgabe ist stets eine direkte Funktion des Eingangs zum Zeitpunkt der Ereignisaktivierung.

## Anwendungsszenarien
- **Umwandlung von Binärsignalen:** Wenn ein Sensor oder Schalter ein boolesches Signal über einen AX-Adapter liefert, das in einem System mit ADI-Adaptern (DINT) weiterverarbeitet werden soll.
- **Gateway-Funktion:** Verbindung zwischen Teilsystemen, die unterschiedliche Adaptertypen verwenden, ohne die zugrundeliegende Logik zu ändern.
- **Test und Simulation:** Erzeugung eines definierten DINT-Werts aus einem booleschen Eingang für Testzwecke.

## Vergleich mit ähnlichen Bausteinen
- **AX_TO_ADI (dieser FB):** Konvertiert BOOL → DINT über Adapter.
- **ADI_TO_AX (hypothetisch):** Würde DINT → BOOL konvertieren, z.B. durch Vergleich mit Null oder Schwellwert.
- **Direkter Befehl F_BOOL_TO_DINT:** Dieser Baustein ist eine gekapselte Version, die speziell für die Arbeit mit unidirektionalen Adaptern ausgelegt ist. Im Gegensatz zum Basisbaustein sind die Adapter-Schnittstellen bereits integriert.

## Fazit
**AX_TO_ADI** ist ein einfacher, aber nützlicher Konverterbaustein, der boolesche Adaptersignale in integerbasierte Adaptersignale überführt. Er erweitert die Interoperabilität zwischen verschiedenen Komponenten eines Systems und ermöglicht eine saubere Trennung von Daten- und Ereignisflüssen. Aufgrund seiner geringen Komplexität ist er schnell einsetzbar und gut in größere Composite FB-Ketten integrierbar.