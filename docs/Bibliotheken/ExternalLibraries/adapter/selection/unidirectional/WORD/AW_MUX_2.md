# AW_MUX_2


![AW_MUX_2](./AW_MUX_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AW_MUX_2** ist ein generischer Multiplexer für zwei Adaptereingänge. Er wählt anhand eines Indexwertes (`K`) einen der beiden Adapter (`IN1`, `IN2`) aus und leitet diesen auf den Ausgangsadapter (`OUT`) weiter. Der Baustein arbeitet ereignisgesteuert und eignet sich für die Umschaltung zwischen zwei unidirektionalen Adapterverbindungen des Typs „AW“.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Setzt den Index `K` und löst die Durchschaltung des gewählten Eingangs auf den Ausgang aus. |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Bestätigt die erfolgreiche Ausführung der Umschaltung gemäß dem aktuellen Index `K`. |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `K` | UINT | Index zur Auswahl des Eingangs: `0` → `IN1`, `1` → `IN2`. |

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Name | Richtung | Typ | Kommentar |
|------|----------|-----|-----------|
| `IN1` | Socket (Eingang) | `adapter::types::unidirectional::AW` | Erster Adaptereingang, aktiv bei `K = 0`. |
| `IN2` | Socket (Eingang) | `adapter::types::unidirectional::AW` | Zweiter Adaptereingang, aktiv bei `K = 1`. |
| `OUT` | Plug (Ausgang) | `adapter::types::unidirectional::AW` | Ausgangsadapter, der den gewählten Eingang weitergibt. |

## Funktionsweise

Der Funktionsblock führt bei jedem Ereignis an `REQ` folgende Schritte aus:

1. Auswerten des aktuellen Indexwertes `K`.
2. Verbinden des entsprechenden Socket-Adapters (`IN1` bei `K = 0` oder `IN2` bei `K = 1`) mit dem Plug `OUT`.
   - Bei Werten von `K`, die ungleich 0 oder 1 sind, wird kein Eingang durchgeschaltet (keine Aktion).
3. Abschließendes Senden des Bestätigungsereignisses `CNF`.

Der Adaptertyp `AW` ist als unidirektional definiert, sodass die Datenübertragung nur in einer Richtung (vom Socket zum Plug) erfolgt.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ (`GenericClassName = 'GEN_AW_MUX'`) deklariert. Er kann in verschiedenen Kontexten mit dem zugrunde liegenden Adaptertyp `AW` verwendet werden.
- **Keine Zustandsmaschine**: Der Baustein besitzt keine explizite Zustandslogik – die Umschaltung erfolgt rein ereignisgesteuert und sofortig.
- **Adapterorientiert**: Statt einzelner Datenpunkte werden ganze Adapterverbindungen geschaltet, was den Baustein für modulare, adapterbasierte Architekturen prädestiniert.

## Zustandsübersicht

Der FB verfügt über keinen internen Zustandsautomaten. Die Funktionalität beschränkt sich auf die direkte Reaktion auf das `REQ`-Ereignis. Daher existieren keine definierten Zustände außer dem impliziten **Ruhezustand** (Warten auf `REQ`).

## Anwendungsszenarien

- **Sensorumschaltung**: Auswahl zwischen zwei Messwertgebern (z. B. Temperatur von zwei verschiedenen Fühlern) über einen Index.
- **Konfigurationsumschaltung**: Wechsel zwischen zwei unterschiedlichen Datenquellen (z. B. zwei Parametriersätzen) durch Adapter-Multiplexing.
- **Test- und Diagnose**: Selektive Durchschaltung von Test- oder Normalbetrieb auf eine gemeinsame Ausgangsschnittstelle.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Merkmal |
|----------|---------|
| `MUX` (Standard-4diac) | Schaltet einzelne Datenwerte (z. B. INT, REAL) anhand eines Index. |
| `AW_MUX_2` | Schaltet komplette Adapterverbindungen (Typ `AW`). Geeignet für adapterbasierte Kommunikation, z. B. in OPC-UA oder Service-Interfaces. |
| `SELECT` | Wählt zwischen zwei Bool-Eingängen; hier dagegen Adapterauswahl mit einem ganzzahligen Index. |

Der `AW_MUX_2` füllt die Lücke zwischen reinen Daten-Multiplexern und vollständigen Protokoll-Umschaltern.

## Fazit

Der **AW_MUX_2** ist ein einfacher, aber leistungsfähiger Funktionsblock zur Adapterumschaltung in der 4diac-IDE. Durch die Verwendung des generischen Adaptertyps `AW` und die indexbasierte Auswahl eignet er sich für flexible Umschaltungen in modularen Automatisierungslösungen. Die fehlende Zustandsmaschine macht ihn ressourcenschonend und einfach einsetzbar, während die klare Ereignissteuerung eine zuverlässige Synchronisation ermöglicht.