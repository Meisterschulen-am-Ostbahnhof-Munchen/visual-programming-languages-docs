# AI_TO_ADI


![AI_TO_ADI](./AI_TO_ADI.svg)

* * * * * * * * * *
## Einleitung

Der Baustein AI_TO_ADI ist ein Composite-Funktionsblock, der einen AI-Adapter (Integer-Werte, Typ INT) in einen ADI-Adapter (Double-Integer-Werte, Typ DINT) umwandelt. Er dient als Brücke zwischen Komponenten, die unterschiedliche Adapter-Schnittstellen verwenden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine eigenen Ereignis-Eingänge. Das Ereignis wird über den eingehenden Adapter AI_IN bereitgestellt:

- **AI_IN.E1** (Ereignis): Auslöser für die Weiterleitung des Datenwerts und des Ereignisses an den Ausgang.

### **Ereignis-Ausgänge**

Der FB besitzt keine eigenen Ereignis-Ausgänge. Das Ereignis wird über den ausgehenden Adapter ADI_OUT ausgegeben:

- **ADI_OUT.E1** (Ereignis): Wird nach erfolgreicher Datenweitergabe ausgelöst.

### **Daten-Eingänge**

Der FB besitzt keine eigenen Daten-Eingänge. Die Daten werden über den eingehenden Adapter AI_IN bereitgestellt:

- **AI_IN.D1** (INT): Der umzuwandelnde Integer-Wert.

### **Daten-Ausgänge**

Der FB besitzt keine eigenen Daten-Ausgänge. Die Daten werden über den ausgehenden Adapter ADI_OUT ausgegeben:

- **ADI_OUT.D1** (DINT): Der konvertierte Double-Integer-Wert.

### **Adapter**

| Name    | Richtung | Typ                         | Beschreibung                         |
|---------|----------|-----------------------------|--------------------------------------|
| AI_IN   | Socket   | adapter::types::unidirectional::AI | Eingangsadapter für Integer-Werte (INT) |
| ADI_OUT | Plug     | adapter::types::unidirectional::ADI | Ausgangsadapter für Double-Integer-Werte (DINT) |

## Funktionsweise

Der Baustein arbeitet als reine Weiterleitung: Sobald am eingehenden Adapter `AI_IN` das Ereignis `E1` anliegt, wird der aktuelle Wert von `AI_IN.D1` gelesen und unverändert an `ADI_OUT.D1` weitergegeben. Anschließend wird das Ereignis `E1` am ausgehenden Adapter `ADI_OUT` ausgelöst. Die Typkonvertierung von `INT` nach `DINT` erfolgt automatisch durch die Adapterbindung; es wird keine explizite Konvertierungslogik benötigt.

## Technische Besonderheiten

- **Implizite Typkonvertierung:** Der FB führt die Umwandlung von 16‑Bit Integer (INT) auf 32‑Bit Double Integer (DINT) ohne Datenverlust durch, da der Ziel-Datentyp größer ist.
- **Composite-Implementierung:** Der Baustein ist als Composite-FB realisiert, d.h. er enthält ein internes Netzwerk, das die beiden Adapter direkt miteinander verbindet. Er kann wie ein primitiver FB in Steuerungsprojekten eingesetzt werden.
- **Unidirektionale Kommunikation:** Beide Adapter sind unidirektional ausgelegt – die Daten fließen nur vom Eingang zum Ausgang.
- **Keine Latenz oder Pufferung:** Die Weiterleitung erfolgt ereignisgesteuert und ohne zusätzliche Verzögerung.

## Zustandsübersicht

Der AI_TO_ADI besitzt keinen internen Zustandsautomaten (ECC). Er verhält sich passiv und leitet jedes eingehende Ereignis und die zugehörigen Daten sofort weiter. Es gibt keine internen Zustände, Wartezeiten oder Speicherung von Werten.

## Anwendungsszenarien

- **Adapter-Brücke:** Wenn ein Sensormodul einen AI-Adapter (INT) bereitstellt, ein nachfolgendes Verarbeitungsmodul jedoch einen ADI-Adapter (DINT) erwartet, kann der AI_TO_ADI zwischengeschaltet werden.
- **Systemintegration:** In heterogenen Automatisierungssystemen, in denen unterschiedliche Datentypen für Adapter-Schnittstellen verwendet werden, ermöglicht dieser Baustein eine einfache Anpassung ohne Änderung der ursprünglichen Komponenten.
- **Prototyping:** Schnelle Kopplung von Funktionsbausteinen aus verschiedenen Bibliotheken, die auf unterschiedlichen Adaptertypen basieren.

## Vergleich mit ähnlichen Bausteinen

| Baustein        | Typkonvertierung | Schnittstelle                       | Anwendungsfall                     |
|-----------------|------------------|-------------------------------------|------------------------------------|
| AI_TO_ADI       | INT -> DINT      | Adapter (Socket/Plug)               | Brücke zwischen adapterbasierten Komponenten |
| INT_TO_DINT     | INT -> DINT      | Direkte Eingänge/Ausgänge (z.B. DI1, DO1) | Einfache Datenkonvertierung ohne Adapter |
| CONV_ANY_TO_ANY | Generisch        | Flexible Ein-/Ausgänge              | Universelle Konvertierung (oft aufwändiger) |

Während Bausteine wie `INT_TO_DINT` eine direkte Datenkonvertierung mit eigenen Ein- und Ausgängen bieten, integriert der AI_TO_ADI die Konvertierung nahtlos in eine Adapter-basierte Architektur und erleichtert so die Wiederverwendung vorhandener Adapterdefinitionen.

## Fazit

Der AI_TO_ADI ist ein einfacher, aber wertvoller Funktionsblock für die Umwandlung von Integer- auf Double-Integer-Adapter-Schnittstellen. Durch seine Composite-Struktur und die implizite Typkonvertierung lässt er sich ohne zusätzliche Programmierlogik in adapterbasierte Steuerungssysteme einfügen und vereinfacht die Integration von Komponenten mit unterschiedlichen Datenbreiten.