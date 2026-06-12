# AD_TO_AULI


![AD_TO_AULI](./AD_TO_AULI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein AD_TO_AULI ist ein Composite-FB zur Konvertierung eines DWORD-Adapters (AD) in einen ULINT-Adapter (AULI). Er verwendet die IEC 61131-Konvertierungsfunktion F_DWORD_TO_ULINT und kapselt die Ereignis- und Datenverbindungen für eine einfache adapterbasierte Umwandlung.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine
### **Ereignis-Ausgänge**
Keine
### **Daten-Eingänge**
Keine
### **Daten-Ausgänge**
Keine
### **Adapter**
- **AD_IN** (Socket): Typ AD (DWORD), unidirektionaler Eingangsadapter für das DWORD.
- **AULI_OUT** (Plug): Typ AULI (ULINT), unidirektionaler Ausgangsadapter für das konvertierte ULINT.

## Funktionsweise
Der Baustein nimmt ein DWORD über den AD_IN-Adapter entgegen. Ein Ereignis am E1-Eingang von AD_IN triggert den REQ-Ereigniseingang des internen Konverters F_DWORD_TO_ULINT. Dieser konvertiert den Datenwert (AD_IN.D1) und signalisiert nach Abschluss über CNF. Das CNF-Ereignis löst dann das E1-Ereignis am AULI_OUT-Adapter aus, und der konvertierte Wert (ULINT) wird über AULI_OUT.D1 ausgegeben.

## Technische Besonderheiten
- Der Baustein ist als Composite realisiert und nutzt die Bibliothek `iec61131::conversion::F_DWORD_TO_ULINT`.
- Es werden keine direkten Ereignis- oder Dateneingänge/-ausgänge verwendet; die gesamte Kommunikation erfolgt ausschließlich über Adapter.
- Die Konvertierung erfolgt nach IEC 61499-Ereignissteuerung: Das Ausgangsereignis wird erst nach Abschluss der Konvertierung gesendet.

## Zustandsübersicht
Der Composite-Baustein selbst besitzt keine eigenen Zustände. Der integrierte Funktionsblock F_DWORD_TO_ULINT durchläuft folgende Zustände:
- **IDLE**: Warten auf ein REQ-Ereignis.
- **REQ**: Konvertierung wird durchgeführt.
- **CNF**: Konvertierung abgeschlossen, Ausgangsdaten werden aktualisiert.

## Anwendungsszenarien
- Umwandlung von Messwerten oder Steuerdaten, die als DWORD (32 Bit) vorliegen, in einen ULINT (64 Bit) Adapter für nachfolgende Verarbeitung.
- Einsatz in modularen Automatisierungssystemen, die auf Adapter-Schnittstellen basieren.
- Brücke zwischen Komponenten mit unterschiedlichen Adapter-Typen.

## Vergleich mit ähnlichen Bausteinen
- Direkte Typumwandlungs-FBs wie `F_DWORD_TO_ULINT` arbeiten auf Datenebene, während AD_TO_AULI die Adapter-Schnittstellen kapselt.
- Ähnliche Composite-Bausteine existieren für andere Datentyp-Kombinationen (z. B. DWORD_TO_LWORD), wobei hier speziell die unidirektionalen Adapter AD und AULI verwendet werden.

## Fazit
AD_TO_AULI bietet eine einfache und wiederverwendbare Lösung zur adapterbasierten Konvertierung von DWORD zu ULINT. Durch die Kapselung der Konvertierungslogik in einem Composite-FB wird die Wiederverwendbarkeit erhöht und die Netzwerkkomplexität reduziert.