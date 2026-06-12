# AL_MUX_2


![AL_MUX_2](./AL_MUX_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AL_MUX_2** ist ein generischer Multiplexer für unidirektionale AL‑ (Action‑Link) Adapterschnittstellen. Er wählt anhand eines ganzzahligen Index `K` einen von zwei eingehenden Adaptern (`IN1` oder `IN2`) aus und leitet dessen Daten über den Ausgangsadapter `OUT` weiter. Die Umschaltung erfolgt synchron zum Ereignis `REQ`. Der Baustein ist als generischer Typ (`GEN_AL_MUX`) ausgeführt und kann daher für verschiedene AL‑Adapterimplementierungen verwendet werden.

## Schnittstellenstruktur

### Ereignis-Eingänge

| Ereignis | Kommentar |
|----------|-----------|
| `REQ`    | Startet die Umschaltung bzw. Weiterleitung entsprechend des aktuellen Index `K`. |

### Ereignis-Ausgänge

| Ereignis | Kommentar |
|----------|-----------|
| `CNF`    | Bestätigt die erfolgreiche Bearbeitung des `REQ`-Ereignisses. |

### Daten-Eingänge

| Daten | Typ  | Kommentar |
|-------|------|-----------|
| `K`   | UINT | Index zur Auswahl des Eingangs (0 = `IN1`, 1 = `IN2`). |

### Daten-Ausgänge

Keine eigenen Datenausgänge; die Ausgangsdaten werden über den Adapter `OUT` bereitgestellt.

### Adapter

| Adapter | Richtung | Typ | Kommentar |
|---------|----------|-----|-----------|
| `OUT`   | Plug     | `adapter::types::unidirectional::AL` | Ausgangsadapter (liefert die Daten des ausgewählten Eingangs). |
| `IN1`   | Socket   | `adapter::types::unidirectional::AL` | Erster Eingangsadapter – aktiv für `K = 0`. |
| `IN2`   | Socket   | `adapter::types::unidirectional::AL` | Zweiter Eingangsadapter – aktiv für `K = 1`. |

## Funktionsweise

1. Der Baustein erwartet an den Sockets `IN1` und `IN2` zwei unidirektionale AL‑Adapter, die kontinuierlich Daten führen können.
2. Mit dem Ereignis `REQ` wird der aktuelle Wert des Index `K` ausgewertet:
   - Ist `K = 0`, wird die Verbindung von `IN1` nach `OUT` durchgeschaltet.
   - Ist `K = 1`, wird die Verbindung von `IN2` nach `OUT` durchgeschaltet.
   - Für andere Werte von `K` ist das Verhalten nicht definiert (typischerweise bleibt der letzte gültige Zustand erhalten oder es wird keine Verbindung hergestellt).
3. Nach erfolgreicher Umschaltung wird das Ereignis `CNF` gesendet.

Der Baustein arbeitet **synchrone**: Ein neues `REQ`-Ereignis führt sofort zur erneuten Auswertung von `K` und zur entsprechenden Umschaltung.

## Technische Besonderheiten

- **Generischer Baustein**: Der Typ `AL_MUX_2` ist als generisch markiert (`eclipse4diac::core::GenericClassName = 'GEN_AL_MUX'`). Damit kann er in verschiedenen Ausprägungen für unterschiedliche AL‑Adapter‑Typen verwendet werden – der konkrete Adaptertyp wird erst bei der Instanziierung festgelegt.
- **Unidirektionale AL‑Adapter**: Die verwendeten Adapter sind vom Typ `adapter::types::unidirectional::AL`. Diese übertragen Daten nur in eine Richtung (vom Socket zum Plug). Eine bidirektionale Kommunikation oder Quittierungsmechanismen sind nicht vorgesehen.
- **Keine Zustandsmaschine**: Der Baustein besitzt keine explizite ECC (Execution Control Chart) – die Funktionalität beschränkt sich auf eine einfache, sofortige Umschaltung des Datenflusses beim Eintreffen von `REQ`.

## Zustandsübersicht

Da der Baustein keine eigenen internen Zustände besitzt, kann sein Verhalten als **kombinatorisch** mit einem Auslöser beschrieben werden:

- **Idle**: Warten auf `REQ`.
- **Umschalten**: Beim Eintreffen von `REQ` wird `K` gelesen und die entsprechende Verbindung aktiviert. Danach wird `CNF` gesendet und der Baustein kehrt in den Idle‑Zustand zurück.

Eine detaillierte Zustandsmaschine wird vom Hersteller nicht bereitgestellt.

## Anwendungsszenarien

- **Auswahl eines AL‑Signalpfads**: In Steuerungssystemen, bei denen zwei verschiedene AL‑Quellen (z. B. Sensordaten, Positionswerte) zur Verfügung stehen und je nach Betriebsmodus eine davon an die nachfolgende Logik weitergegeben werden soll.
- **Umschaltung zwischen redundanten Pfaden**: Wenn ein primäres AL‑Signal ausfällt, kann über einen Index auf ein Backup‑Signal umgeschaltet werden.
- **Parametrierbare Signalquellen**: Durch externe Steuerung (z. B. aus einem übergeordneten Baustein) kann dynamisch zwischen zwei AL‑Eingängen gewählt werden.

## Vergleich mit ähnlichen Bausteinen

- **AL_MUX_2 vs. MUX_2 (Standard‑Datentypen)**: Während klassische Multiplexer (z. B. `MUX_2` für `INT`, `REAL`, `BOOL`) einzelne Datenwerte weiterleiten, arbeitet `AL_MUX_2` auf Adapterebene. Es wird nicht nur ein einzelner Wert, sondern die gesamte Adapter‑Schnittstelle (mehrere Signale) durchgeschaltet.
- **AL_MUX_2 vs. AL_MUX_4**: Ein Multiplexer mit vier Eingängen existiert ggf. als Erweiterung, benötigt dann aber einen größeren Indexbereich (z. B. `K = 0..3`).
- **AL_MUX_2 vs. generischer `GEN_AL_MUX`**: Der vorliegende Baustein ist eine konkrete Instanz des generischen Musters mit zwei Eingängen. Andere Instanzen könnten z. B. `AL_MUX_4` oder `AL_MUX_8` sein.

## Fazit

Der **AL_MUX_2** ist ein einfacher, aber flexibler Multiplexer für unidirektionale AL‑Adapter. Seine generische Natur erlaubt den Einsatz in vielen Anwendungen, bei denen zwischen zwei Adapter‑Signalen umgeschaltet werden muss. Die saubere Trennung von Ereignis‑ und Datenpfad sowie die Bestätigung über `CNF` machen ihn zu einem verlässlichen Baustein in IEC 61499‑basierten Automatisierungssystemen.