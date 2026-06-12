# AR_ADD_3


![AR_ADD_3](./AR_ADD_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AR_ADD_3` dient der Berechnung einer arithmetischen Addition von drei Werten. Es handelt sich um einen generischen Baustein (generic FB) gemäß IEC 61499-2, der über Adapter-Schnittstellen arbeitet. Der Block ist so konzipiert, dass er in Verbindung mit dem Adapter `adapter::types::unidirectional::AR` der Bibliothek `adapter::iec61131::arithmetic` eingesetzt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine direkten Dateneingänge. Die Eingabewerte werden über Adapter-Schnittstellen bereitgestellt.

### **Daten-Ausgänge**

Keine direkten Datenausgänge. Das Ergebnis wird über einen Adapter-Ausgang bereitgestellt.

### **Adapter**

| Richtung  | Name | Typ                                 | Kommentar       |
|-----------|------|--------------------------------------|-----------------|
| Sockets   | IN1  | `adapter::types::unidirectional::AR` | ADD input 1     |
| Sockets   | IN2  | `adapter::types::unidirectional::AR` | ADD input 2     |
| Sockets   | IN3  | `adapter::types::unidirectional::AR` | ADD input 3     |
| Plugs     | OUT  | `adapter::types::unidirectional::AR` | ADD result      |

## Funktionsweise

Der Baustein addiert die drei über die Adapter-Sockets `IN1`, `IN2` und `IN3` eingehenden Werte und stellt das Ergebnis über den Adapter-Plug `OUT` bereit. Die genaue Semantik der Addition (z. B. unterstützte Datentypen, Überlaufverhalten) wird durch die Implementierung des verwendeten Adapter-Typs `AR` festgelegt. Der Baustein ist generisch, d. h. er kann für verschiedene Datentypen parametrisiert werden (z. B. durch Type-Hash oder generischen Klassennamen).

## Technische Besonderheiten

- **Generischer Baustein:** Die tatsächliche Datentypbehandlung wird über das Attribut `eclipse4diac::core::GenericClassName` (Wert: `'GEN_AR_ADD'`) und `eclipse4diac::core::TypeHash` gesteuert.
- **Adapterbasierte Kommunikation:** Der Baustein verwendet ausschließlich Adapter (`adapter::types::unidirectional::AR`) für Ein- und Ausgabe. Dies ermöglicht eine lose Kopplung und Wiederverwendbarkeit in unterschiedlichen Kontexten.
- **Lizenz:** Unter der Eclipse Public License 2.0 (EPL-2.0) veröffentlicht.
- **Kompatibilität:** Entwickelt für die 4diac-IDE und die Eclipse 4diac Laufzeitumgebung.

## Zustandsübersicht

Der Baustein besitzt kein explizites Zustandsdiagramm (ECC). Es handelt sich um eine rein kombinatorische Funktion: Die Ausgabe ist jederzeit die Summe der drei Eingänge. Es sind keine internen Zustände oder zeitlichen Abhängigkeiten vorhanden.

## Anwendungsszenarien

- **Mehrfachaddition in Steuerungssystemen:** Wenn drei analoge oder digitale Werte (z. B. Sensordaten, Sollwerte) aufsummiert werden müssen.
- **Generische Bibliotheksbausteine:** Einsatz in wiederverwendbaren Funktionsbaustein-Bibliotheken, bei denen die Datentypen zur Konfigurationszeit festgelegt werden.
- **Adapterbasierte Architekturen:** In Systemen, die auf standardisierte Adapter-Schnittstellen setzen, um eine flexible Verkettung von Funktionen zu ermöglichen.

## Vergleich mit ähnlichen Bausteinen

**AR_ADD_2 / AR_ADD_4 etc.:** Diese Bausteine unterscheiden sich lediglich in der Anzahl der Eingänge (zwei bzw. vier). `AR_ADD_3` ist speziell für die Addition von genau drei Werten optimiert. Der generische Ansatz erlaubt es, alle diese Varianten bei Bedarf durch Parametrisierung eines gemeinsamen Basistyps zu realisieren.

## Fazit

`AR_ADD_3` ist ein übersichtlicher, generischer Funktionsblock für die Addition dreier Werte unter Verwendung von Adaptern. Durch die Abstraktion über generische Attribute und Adapter eignet er sich gut für IEC-61499-Anwendungen, die eine flexible und wiederverwendbare Signalverarbeitung erfordern.