# ALR_TO_AUDI


![ALR_TO_AUDI](./ALR_TO_AUDI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock ALR_TO_AUDI ist ein zusammengesetzter Baustein (Composite FB), der einen **ALR-Adapter** (LREAL) in einen **AUDI-Adapter** (UDINT) umwandelt. Er dient als Schnittstelle zwischen einer analogen LREAL-Quelle und einer digitalen UDINT-Senke in unidirektionalen Kommunikationspfaden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `ALR_IN.E1` – Ereigniseingang des ALR-Adapters; löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- `AUDI_OUT.E1` – Ereignisausgang des AUDI-Adapters; signalisiert die Fertigstellung der Konvertierung.

### **Daten-Eingänge**
- `ALR_IN.D1` – LREAL-Eingangswert, der in einen UDINT-Wert umgewandelt wird.

### **Daten-Ausgänge**
- `AUDI_OUT.D1` – UDINT-Ausgangswert, Ergebnis der Konvertierung.

### **Adapter**
- **Socket** `ALR_IN` vom Typ `adapter::types::unidirectional::ALR` – Eingangsschnittstelle für LREAL-Werte mit Ereignis.
- **Plug** `AUDI_OUT` vom Typ `adapter::types::unidirectional::AUDI` – Ausgangsschnittstelle für UDINT-Werte mit Ereignis.

## Funktionsweise

Der Baustein nutzt intern den Konvertierungs-FB `iec61131::conversion::F_LREAL_TO_UDINT`. Der Ablauf ist wie folgt:

1. Ein Ereignis auf `ALR_IN.E1` wird an den Eingang `REQ` des internen Konverters weitergeleitet.
2. Gleichzeitig wird der Datenwert von `ALR_IN.D1` an den Eingang `IN` des Konverters übergeben.
3. Nach erfolgreicher Wandlung sendet der Konverter ein Bestätigungsereignis (`CNF`) an `AUDI_OUT.E1`.
4. Der konvertierte UDINT-Wert steht am Ausgang `OUT` des Konverters und wird an `AUDI_OUT.D1` weitergegeben.

Somit erfolgt die Umwandlung streng ereignisgesteuert und datensynchron.

## Technische Besonderheiten

- **Adapterbasierte Kapselung** – Daten und Ereignisse werden über standardisierte Adapter vom Typ `unidirectional` ausgetauscht, was eine saubere Trennung von Schnittstellen und Implementierung ermöglicht.
- **Unidirektionale Kommunikation** – Der Baustein unterstützt nur eine Datenflussrichtung (LREAL → UDINT). Rückmeldungen oder Fehlerstatus sind nicht vorgesehen.
- **Typumwandlung** – Die Konvertierung von LREAL (64-Bit-Gleitkomma) nach UDINT (32-Bit-Ganzzahl ohne Vorzeichen) kann zu Rundungs- oder Überlaufverlusten führen, wird aber gemäß IEC 61131-Standard durchgeführt.

## Zustandsübersicht

Der ALR_TO_AUDI besitzt keine eigene interne Zustandsmaschine. Sein Verhalten wird vollständig durch den enthaltenen Funktionsblock `F_LREAL_TO_UDINT` bestimmt, der als einfache, ereignisgesteuerte Wandlungsinstanz arbeitet.

## Anwendungsszenarien

- **Analog-Digital-Wandlung in der Agrarsteuerung** – Umwandlung von LREAL-Sensorwerten (z. B. Druck, Füllstand) in ganzzahlige UDINT-Werte für Anzeigen oder digitale Regelkreise.
- **Schnittstellenanpassung** – Verbindung von Komponenten, die auf unterschiedliche Adapter-Typen setzen (z. B. ALR aus einem Messmodul und AUDI in einer Steuerung).
- **Protokollumsetzung** – Einfache Konvertierung innerhalb von Adapterketten, ohne eigene Logik implementieren zu müssen.

## Vergleich mit ähnlichen Bausteinen

- **LREAL_TO_DINT** – Wandelt in einen vorzeichenbehafteten 32-Bit-Integer. ALR_TO_AUDI nutzt dagegen die vorzeichenlose Variante UDINT.
- **REAL_TO_UDINT** – Arbeitet mit 32-Bit-Gleitkomma statt 64-Bit-LREAL, entsprechend geringere Genauigkeit.
- **LREAL_TO_LWORD** – Konvertiert in einen 64-Bit-Integer, jedoch mit anderem Adapter-Typ (LWORD statt UDINT).

Der ALR_TO_AUDI ist speziell auf die unidirektionale Adapter-Kopplung mit den genannten Typen ausgelegt.

## Fazit

Der ALR_TO_AUDI ist ein spezialisierter, aber dennoch einfacher Baustein zur Konvertierung von LREAL- in UDINT-Werte über Adapterschnittstellen. Dank seiner klaren Struktur und der Nutzung eines standardisierten IEC-Konverters lässt er sich leicht in bestehende 4diac-Projekte integrieren und trägt zur Interoperabilität unterschiedlicher Adapter-Typen bei.