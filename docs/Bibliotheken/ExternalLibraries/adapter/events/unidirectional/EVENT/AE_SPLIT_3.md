# AE_SPLIT_3


![AE_SPLIT_3](./AE_SPLIT_3.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AE_SPLIT_3** dient dazu, einen eingehenden Adapter-Datenstrom (vom Typ `AE`) auf drei identische Ausgänge zu verteilen. Er ist als generischer Baustein ausgeführt und ermöglicht die flexible Verwendung unterschiedlicher Adaptertypen durch Konfiguration zur Designzeit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Sockel (Eingang) | IN | `adapter::types::unidirectional::AE` | Eingehender Adapter-Datenstrom, der auf die drei Ausgänge verteilt wird. |
| Stecker (Ausgang) | OUT1 | `adapter::types::unidirectional::AE` | Erster Ausgang – erhält die gleichen Daten wie der Eingang. |
| Stecker (Ausgang) | OUT2 | `adapter::types::unidirectional::AE` | Zweiter Ausgang – erhält die gleichen Daten wie der Eingang. |
| Stecker (Ausgang) | OUT3 | `adapter::types::unidirectional::AE` | Dritter Ausgang – erhält die gleichen Daten wie der Eingang. |

## Funktionsweise

Der Baustein akzeptiert über den Socket `IN` einen unidirektionalen Adapter-Datenstrom vom Typ `AE`. Jedes ankommende Datenpaket oder Ereignis wird ohne Veränderung an alle drei Adapter-Plugs (`OUT1`, `OUT2`, `OUT3`) weitergeleitet. Es findet keine Verarbeitung oder Aufbereitung der Daten statt – der FB fungiert als reiner **Signalverteiler** für Adapterverbindungen.

Dank der generischen Auslegung (`eclipse4diac::core::GenericClassName = 'GEN_AE_SPLIT'`) kann der konkrete Adaptertyp (z. B. ein benutzerdefinierter AE-Subtyp) zur Entwurfszeit für `IN`, `OUT1`–`OUT3` festgelegt werden. Zur Laufzeit sind alle Instanzen identisch typisiert.

## Technische Besonderheiten

- **Generischer Baustein** – der Adaptertyp wird erst bei der Instanziierung im Projekt festgelegt, was Wiederverwendbarkeit und Typ-Sicherheit erhöht.
- **Unidirektionale Kommunikation** – Daten fließen nur vom Eingang zu den Ausgängen; Rückwärtskommunikation ist nicht vorgesehen.
- **Lizenz** – Der Baustein steht unter der **Eclipse Public License 2.0 (EPL-2.0)**, die eine freie Nutzung, Modifikation und Weitergabe erlaubt.
- Keine ereignis- oder datenbasierten Ein-/Ausgänge – die gesamte Kommunikation erfolgt ausschließlich über die Adapterschnittstellen.

## Zustandsübersicht

Der Funktionsblock besitzt kein internes Zustandsdiagramm (ECC). Er arbeitet **kombinatorisch**: Jede Änderung am Eingang wird sofort und ohne Verzögerung an alle Ausgänge weitergegeben.

## Anwendungsszenarien

- **Signalvervielfältigung** – Ein von einem Sensor bereitgestellter Adapter-Datenstrom (z. B. `AE_Temperature`) soll parallel an drei verschiedene Auswerteeinheiten gesendet werden.
- **Aufteilung von Ereignisadaptern** – In Automatisierungssystemen, die auf Adapter-basierte Kommunikation setzen, können so mehrere Empfänger bedient werden.
- **Test- und Simulationsumgebungen** – Ein Datenstrom wird auf mehrere Überwachungs- oder Protokollierungsmodule verteilt.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Ausgänge | Besonderheit |
|----------|-----------------|--------------|
| `AE_SPLIT_2` | 2 | Verteilt auf zwei Ausgänge. |
| `AE_SPLIT_3` | 3 | Verteilt auf drei Ausgänge (vorliegender FB). |
| `AE_SPLIT_N` (hypothetisch) | variabel | Flexible Anzahl über Parameter – erfordert höheren Konfigurationsaufwand. |

Gemeinsam ist allen Varianten, dass sie lediglich auf Adapterebene arbeiten und keine Datenmanipulation vornehmen.

## Fazit

Der **AE_SPLIT_3** ist ein einfacher und dennoch unverzichtbarer Funktionsblock zur Vervielfältigung von Adapterverbindungen in der 4diac-IDE. Seine generische Ausführung und die klare, unidirektionale Struktur machen ihn zu einem wartungsfreundlichen Werkzeug für die Signalverteilung ohne zusätzliche Logik. Durch die EPL-2.0-Lizenz kann er in eigenen Projekten ohne Einschränkungen eingesetzt werden.