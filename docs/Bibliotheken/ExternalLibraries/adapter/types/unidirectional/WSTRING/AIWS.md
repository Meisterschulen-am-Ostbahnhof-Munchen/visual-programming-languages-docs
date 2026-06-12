# AIWS


![AIWS](./AIWS.svg)

* * * * * * * * * *

## Einleitung

Der Adapter **AIWS** stellt eine unidirektionale Schnittstelle für die Übertragung genau eines Ereignisses (Event) und eines zugehörigen WSTRING-Datums bereit. Er definiert die Kommunikationsrichtung von einer Quelle zu einem Ziel, wobei das Ereignis immer von dem Datum begleitet wird. Der Adapter dient als Grundbaustein für lose gekoppelte, ereignisgesteuerte Datenflüsse in IEC 61499-Anwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| E1   | Event | Indication (or Request) |

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

| Name | Typ     | Kommentar                      |
|------|---------|--------------------------------|
| D1   | WSTRING | Indication (or Request) Data from Plug |

### **Adapter**

Der Adapter selbst ist als Schnittstellendefinition zu verstehen. Er besitzt keine weiteren internen Adapter.

## Funktionsweise

Der Adapter **AIWS** überträgt ein Ereignis **E1** zusammen mit einem WSTRING-Wert **D1** in einer festen Kopplung. Sobald die sendende Komponente das Ereignis auslöst, wird der aktuelle Wert von **D1** an die empfangende Seite übergeben. Die Richtung ist strikt von der Plug-Seite zur Socket-Seite (oder umgekehrt, je nach Verwendungszweck) – es findet keine Rückmeldung oder Bestätigung statt. Der Adapter definiert somit einen einfachen, unidirektionalen Datenkanal.

## Technische Besonderheiten

- **Unidirektionalität**: Es existiert nur eine Ereignis-Ausgangsseite, keine Eingänge. Dies erzwingt eine klare Flussrichtung.
- **Kompaktheit**: Genau ein Event mit einem einfachen Datentyp (WSTRING) minimiert die Schnittstellenkomplexität.
- **Keine Fehlerbehandlung**: Der Adapter bietet keine Mechanismen für Timeouts, Wiederholungen oder Fehlererkennung. Die Datenintegrität muss von den angeschlossenen Funktionsblöcken sichergestellt werden.
- **Standardkonform**: Erfüllt die IEC 61499-1 Spezifikation für Adaptertypen.

## Zustandsübersicht

Der Adapter selbst besitzt keinen internen Zustand. Er dient ausschließlich als Schnittstellendefinition und realisiert keine eigene Ablaufsteuerung. Die Zustandslogik liegt bei den verbundenen Funktionsblöcken.

## Anwendungsszenarien

- **Einbindung von Sensordaten**: Übermittlung eines Ereignisses mit einem Messwert (z. B. Statusmeldung oder Identifikation) als WSTRING an eine übergeordnete Steuerung.
- **Textbasierte Befehle**: Senden von Kommandos (z. B. „START“, „STOP“) als Ereignis mit Parameter.
- **Logging und Diagnose**: Ausgabe von beschreibenden Ereignissen mit Klartextinformationen in eine Protokollkomponente.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Ereignisse | Daten | Richtung | Besonderheit |
|----------|------------|-------|----------|--------------|
| **AIWS** | 1 Output   | 1 WSTRING | Unidirektional | Einfachster Adapter für WSTRING |
| **AI** (hypothetisch) | 1 Output | 1 ANY (generisch) | Unidirektional | Flexibler Datentyp, aber aufwendiger |
| **BIWS** (bidirektional) | 2 Events (in/out) | 2 WSTRING in beide Richtungen | Bidirektional | Erfordert Handshake |

Der **AIWS** sticht durch seine minimale Schnittstelle hervor und eignet sich besonders für einfache, klar definierte Punkt-zu-Punkt-Verbindungen, bei denen kein Rückkanal benötigt wird.

## Fazit

Der Adapter **AIWS** ist ein grundlegender und effizienter Baustein für die unidirektionale Übertragung eines Ereignisses mit einem WSTRING-Datum. Durch seine Einfachheit reduziert er die Kopplung zwischen Komponenten und erleichtert die modulare Gestaltung von Automatisierungslösungen nach IEC 61499. Er eignet sich ideal für Aufgaben, die eine schnelle und unkomplizierte ereignisgesteuerte Kommunikation erfordern.