# AB_SPLIT_5


![AB_SPLIT_5](./AB_SPLIT_5.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AB_SPLIT_5` dient dazu, einen unidirektionalen AB-Adapter-Eingang (Socket) auf fünf identische AB-Adapter-Ausgänge (Plugs) zu verteilen. Es handelt sich um einen generischen Baustein, der für die Signalverteilung in Automatisierungssystemen konzipiert ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine. Die Datenübertragung erfolgt ausschließlich über die Adapter-Schnittstellen.

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** (Eingang) | `IN` | `adapter::types::unidirectional::AB` | Unidirektionaler AB-Adapter, der das Eingangssignal bereitstellt. |
| **Plug** (Ausgang) | `OUT1` | `adapter::types::unidirectional::AB` | Erster unidirektionaler AB-Adapter-Ausgang. |
| **Plug** (Ausgang) | `OUT2` | `adapter::types::unidirectional::AB` | Zweiter unidirektionaler AB-Adapter-Ausgang. |
| **Plug** (Ausgang) | `OUT3` | `adapter::types::unidirectional::AB` | Dritter unidirektionaler AB-Adapter-Ausgang. |
| **Plug** (Ausgang) | `OUT4` | `adapter::types::unidirectional::AB` | Vierter unidirektionaler AB-Adapter-Ausgang. |
| **Plug** (Ausgang) | `OUT5` | `adapter::types::unidirectional::AB` | Fünfter unidirektionaler AB-Adapter-Ausgang. |

## Funktionsweise

Der Baustein empfängt über den Socket `IN` ein unidirektionales AB-Signal. Dieses Signal wird ohne Änderung an alle fünf Plugs (`OUT1` bis `OUT5`) weitergeleitet. Dadurch entstehen fünf identische Kopien des Eingangssignals, die parallel an verschiedene nachfolgende Bausteine oder Systeme angeschlossen werden können.

Da der Baustein keine Ereignis- oder Dateneingänge besitzt, erfolgt die gesamte Kommunikation rein über die Adapter-Schnittstellen. Die Verteilung geschieht statisch und ohne Verzögerung oder Pufferung.

## Technische Besonderheiten

- **Generischer Baustein**: `AB_SPLIT_5` verwendet den generischen Klassennamen `GEN_AB_SPLIT` und ermöglicht eine typsichere Instanziierung in der 4diac-IDE.
- **Unidirektionalität**: Alle beteiligten Adapter sind vom Typ `unidirectional::AB`, d. h. die Daten fließen nur in eine Richtung (vom Socket zu den Plugs).
- **Keine Zustandslogik**: Der Baustein besitzt kein internes Zustandsdiagramm oder Ereignisverarbeitung – er ist rein strukturell und führt keine Transformation der Daten durch.

## Zustandsübersicht

Es existiert kein Zustandsautomat. Der Baustein arbeitet kontinuierlich und gibt das empfangene Signal permanent an alle fünf Ausgänge weiter.

## Anwendungsszenarien

- **Signalverteilung in Feldbussystemen**: Wenn ein Sensorwert oder Steuersignal (als AB-Adapter) an mehrere Aktoren oder Steuerungen gesendet werden muss.
- **Multiplexing in modularen Maschinen**: Verteilung eines zentralen AB-Signals an verschiedene Module einer Anlage.
- **Test und Simulation**: Gleichzeitiges Anschließen mehrerer Überwachungs- oder Logging-Einheiten an eine Datenquelle.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Ausgänge | Besonderheit |
|----------|-----------------|--------------|
| `AB_SPLIT_2` | 2 | Einfache 1:2-Verteilung |
| `AB_SPLIT_3` | 3 | 1:3-Verteilung |
| `AB_SPLIT_5` | 5 | 1:5-Verteilung (dieser Baustein) |
| `AB_SPLIT_N` (generisch) | parametrierbar | Individuelle Anzahl über GenericClassName |

Gegenüber einem parametrierbaren Split-Baustein bietet `AB_SPLIT_5` eine feste, aber einfache und typsichere Lösung ohne zusätzliche Konfigurationsaufwände.

## Fazit

`AB_SPLIT_5` ist ein schlanker, spezialisierter Funktionsbaustein für die 1:5-Verteilung unidirektionaler AB-Adapter-Signale. Dank seiner generischen Implementierung und der klaren Schnittstellenstruktur eignet er sich ideal für den modularen Aufbau von Automatisierungssystemen, in denen ein Signal mehrfach benötigt wird.