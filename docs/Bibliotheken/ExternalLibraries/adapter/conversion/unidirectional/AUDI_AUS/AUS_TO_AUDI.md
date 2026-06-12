# AUS_TO_AUDI


![AUS_TO_AUDI](./AUS_TO_AUDI.svg)

* * * * * * * * * *

## Einleitung

Der Composite-Funktionsblock **AUS_TO_AUDI** dient der Umwandlung eines unidirektionalen Adapters vom Typ **AUS** (basierend auf USINT-Werten) in einen Adapter vom Typ **AUDI** (basierend auf UDINT-Werten). Er wird eingesetzt, um Daten zwischen zwei verschiedenen Adapter-Schnittstellen zu übersetzen, ohne dass die zugrunde liegende Datenlogik verändert wird. Der Baustein ist als reine Durchreich-Komponente realisiert, die Ereignisse und Daten direkt von der Eingangs- zur Ausgangsseite weiterleitet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine eigenen Ereignis-Eingänge. Ereignisse werden über den angeschlossenen **Socket-Adapter** `AUS_IN` bereitgestellt.

### **Ereignis-Ausgänge**

Der Baustein besitzt keine eigenen Ereignis-Ausgänge. Ereignisse werden über den angeschlossenen **Plug-Adapter** `AUDI_OUT` weitergegeben.

### **Daten-Eingänge**

Der Baustein besitzt keine eigenen Daten-Eingänge. Daten werden über den **Socket-Adapter** `AUS_IN` entgegengenommen.

### **Daten-Ausgänge**

Der Baustein besitzt keine eigenen Daten-Ausgänge. Daten werden über den **Plug-Adapter** `AUDI_OUT` ausgegeben.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AUS` | `AUS_IN` | Socket (Eingang) | Unidirektionaler Adapter, der Daten im USINT-Format (8 Bit) sowie ein Ereignis bereitstellt. |
| `adapter::types::unidirectional::AUDI` | `AUDI_OUT` | Plug (Ausgang) | Unidirektionaler Adapter, der Daten im UDINT-Format (32 Bit) sowie ein Ereignis erwartet. |

Der interne Netzwerkaufbau verbindet das Ereignis `E1` und den Datenwert `D1` des Eingangsadapters direkt mit den gleichnamigen Schnittstellen des Ausgangsadapters.

## Funktionsweise

Der Funktionsblock arbeitet als reine Durchreiche. Sobald am Socket `AUS_IN` das Ereignis `E1` eintritt, wird dieses unverzögert an den Plug `AUDI_OUT` als Ereignis `E1` weitergeleitet. Gleichzeitig wird der Datenwert `D1` (USINT) des Eingangsadapters auf den Datenwert `D1` (UDINT) des Ausgangsadapters übertragen. Eine Typumwandlung von USINT nach UDINT findet dabei implizit durch die Datenverbindung statt (Aufweitung von 8 Bit auf 32 Bit). Es erfolgt keine Validierung oder Wertebereichsprüfung.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Der Baustein besitzt keine klassischen Ein-/Ausgangsvariablen, sondern verwendet ausschließlich die standardisierten Adapter-Typen `AUS` und `AUDI` aus dem Paket `adapter::types::unidirectional`.
- **Einfache Durchleitung**: Die Ereignis- und Datenverbindungen sind direkt und ohne zusätzliche Logik ausgeführt.
- **Typaufweitung**: Die Konvertierung von USINT (0–255) nach UDINT (0–4294967295) erfolgt verlustfrei, da der gesamte USINT-Wertebereich in den UDINT-Bereich abbildbar ist.
- **Keine Zustandsspeicherung**: Der Baustein ist zustandslos; jede Verarbeitung erfolgt in derselben Ausführungsinstanz.

## Zustandsübersicht

Der Funktionsblock besitzt keinen internen Zustandsautomaten. Die Funktionalität beschränkt sich auf eine direkte 1:1-Verbindung zwischen Eingangs- und Ausgangsadapter. Eine Zustandsbeschreibung ist daher nicht erforderlich.

## Anwendungsszenarien

- **Adapterbrücke**: Einsatz in Systemen, die den AUS-Adapter (z. B. für einfache Byte-Werte) verwenden, aber eine AUDI-Schnittstelle (z. B. für 32‑Bit-Zähler oder Adressen) erwarten.
- **Protokollumsetzung**: Verwendung innerhalb von Composite-FBs, um zwischen unterschiedlichen Adapterversionen einer Gerätefamilie zu vermitteln.
- **Datenaufbereitung**: Vorbereitung von USINT-Daten für Bausteine, die ausschließlich UDINT-Eingänge akzeptieren.

## Vergleich mit ähnlichen Bausteinen

- **INT_TO_DINT**: Ein Standard-FB zur Konvertierung von INTEGER-Typen, jedoch mit eigenständigen Ein-/Ausgangs-Variablen. `AUS_TO_AUDI` arbeitet hingegen auf Adapterebene und ist für die Einbettung in adapterbasierte Architekturen optimiert.
- **AUS_TO_AUDI (einfach)**: Alternative Realisierungen könnten zusätzliche Überlaufprüfungen oder Filterfunktionen enthalten; dieser FB beschränkt sich auf die reine Durchleitung.

## Fazit

`AUS_TO_AUDI` ist ein kompakter, spezialisierter Composite-Funktionsblock zur verlustfreien Umwandlung zwischen den unidirektionalen Adaptern AUS (USINT) und AUDI (UDINT). Dank der direkten Durchleitung von Ereignis und Daten ohne Zusatzlogik eignet er sich ideal als Baustein in adapterbasierten Steuerungsnetzwerken, bei denen eine einfache Typanpassung auf der Kommunikationsebene erforderlich ist.