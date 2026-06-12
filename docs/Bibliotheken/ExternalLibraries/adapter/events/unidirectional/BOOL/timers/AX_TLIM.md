# AX_TLIM


![AX_TLIM](./AX_TLIM.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AX_TLIM** ist ein zeitbegrenzender Timer (Time-Limiting) gemäß IEC 61499-2. Er überwacht ein boolesches Eingangssignal, das über einen unidirektionalen **AX-Adapter** bereitgestellt wird. Solange das Signal aktiv (TRUE) ist, bleibt der Ausgang ebenfalls aktiv – jedoch maximal für eine vorgegebene Zeit. Überschreitet die Aktivierungsdauer den Grenzwert, wird der Ausgang zurückgesetzt (Timeout). Ein separater Ereigniseingang erlaubt das Voreinstellen der Zeitbegrenzung, ohne eine neue Ausführung auszulösen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Typ    | Beschreibung                                                 |
|-------|--------|--------------------------------------------------------------|
| `EIPT`| Event  | Setzt die Zeitbegrenzung `PT` neu (löst keine Ausführung aus)|

### **Ereignis-Ausgänge**

Der Funktionsblock besitzt keine direkten Ereignis-Ausgänge. Stattdessen werden das Ausgangsereignis und der Ausgangswert über den **Adapter `Q`** bereitgestellt (siehe Abschnitt Adapter).

### **Daten-Eingänge**

| Name | Typ    | Beschreibung                             |
|------|--------|------------------------------------------|
| `PT` | `TIME` | Zeitbegrenzung (Preset Time) für den Timer|

### **Daten-Ausgänge**

Direkte Daten-Ausgänge sind nicht vorhanden. Der aktuelle Zustand des Timers wird über den **Adapter `Q`** ausgegeben.

### **Adapter**

| Name | Typ       | Richtung | Beschreibung                                                                  |
|------|-----------|----------|-------------------------------------------------------------------------------|
| `IN` | `AX`      | Socket   | Eingangsadapter: empfängt (über Ereignis `E1` und Datum `D1`) den zu überwachenden booleschen Wert |
| `Q`  | `AX`      | Plug     | Ausgangsadapter: sendet (über Ereignis `E1` und Datum `D1`) den Timer-Zustand (`TRUE` = aktiv, `FALSE` = inaktiv oder Timeout) |

> Anmerkung: Der Adaptertyp `AX` ist ein unidirektionaler Standardadapter, bestehend aus einem Ereignis (`E1`) und einem booleschen Datum (`D1`).

## Funktionsweise

1. **Initialzustand** – Die Ausgangsvariable `Q.D1` ist `FALSE`, der Timer läuft nicht.
2. **Aktivierung** – Sobald der Eingangsadapter `IN` ein Ereignis (`E1`) mit dem Datum `TRUE` liefert, wird sofort `Q.D1` auf `TRUE` gesetzt und ein interner Timer gestartet.
3. **Zeitüberwachung** – Der Timer zählt die Zeit, die `IN.D1` auf `TRUE` bleibt. Der Timer verwendet den zuletzt via `EIPT` gesetzten Wert `PT`.
   - *Fall A:* `IN.D1` wird vor Ablauf von `PT` wieder `FALSE` → dann wird `Q.D1` sofort auf `FALSE` gesetzt.
   - *Fall B:* `IN.D1` bleibt länger als `PT` auf `TRUE` → nach Ablauf von `PT` wird `Q.D1` auf `FALSE` gesetzt (Timeout).
4. **Ereignisausgabe** – Jede Änderung von `Q.D1` wird über den Ausgangsadapter `Q.E1` signalisiert.
5. **Voreinstellung** – Das Ereignis `EIPT` setzt die Zeitbegrenzung `PT` neu, ohne die aktuelle Timer-Ausführung zu beeinflussen. Erst die nächste Aktivierung des Timers (durch `IN.E1` mit `TRUE`) verwendet den neuen Wert.

## Technische Besonderheiten

- Der Baustein ist als **Composite-FB** realisiert; intern nutzt er den Standard-FB `E_TLIM` (aus `iec61499::events::timers`). Die zugrunde liegende Logik ist identisch, jedoch wird die Schnittstelle über unidirektionale **AX-Adapter** bereitgestellt.
- Die Verwendung eines Adapter-Sockets (`IN`) und eines Adapter-Plugs (`Q`) ermöglicht eine saubere Trennung von Ereignis- und Datenkommunikation und vereinfacht die Anbindung an andere Bausteine mit kompatiblen Adaptern.
- Der Timer wird **flankengesteuert** ausgelöst: Nur eine steigende Flanke auf `IN.D1` startet einen neuen Timer-Lauf. Ein erneutes Ereignis auf `IN.E1` mit `TRUE` während eines laufenden Timers setzt den Timer nicht zurück (es sei denn, der Wert geht kurz auf `FALSE` und wieder auf `TRUE`).

## Zustandsübersicht

Der Funktionsblock durchläuft folgende logische Zustände (nicht als explizite Zustandsmaschine im XML abgebildet):

| Zustand         | Bedingung `IN.D1` | Ausgang `Q.D1` | Timer läuft | Beschreibung                                                |
|-----------------|-------------------|----------------|-------------|-------------------------------------------------------------|
| **Inaktiv**     | `FALSE`           | `FALSE`        | nein        | Warten auf Aktivierung                                      |
| **Aktiv**       | `TRUE`            | `TRUE`         | ja          | Timer zählt, Ausgang aktiv                                  |
| **Timeout**     | `TRUE`            | `FALSE`        | nein        | Zeitüberschreitung, Timer abgelaufen, Ausgang inaktiv       |
| **Rückkehr**    | `FALSE`           | `FALSE`        | nein        | Eingang geht vor Timeout zurück, Ausgang sofort inaktiv     |

Ein Wechsel von **Aktiv** nach **Timeout** erfolgt, wenn die verbleibende Timer-Zeit null erreicht. Ein Wechsel von **Aktiv** nach **Rückkehr** erfolgt, wenn `IN.D1` vor Ablauf des Timers auf `FALSE` wechselt.

## Anwendungsszenarien

- **Überwachung von Aktoren** – z. B. Prüfung, ob ein Ventil nicht länger als erlaubt geöffnet bleibt.
- **Sicherheitsfunktionen** – Abschaltung eines Signals nach einer maximalen Einschaltdauer.
- **Zeitbasierte Plausibilitätsprüfung** – Erkennung eines hängenden Sensors, der dauerhaft `TRUE` meldet.
- **Steuerung von Blink- oder Impulsfolgen** – der Timer kann als einfacher Monoflop mit Timeout verwendet werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein  | Beschreibung                                                                 | Unterschied zu AX_TLIM                                             |
|-----------|-------------------------------------------------------------------------------|---------------------------------------------------------------------|
| `E_TLIM`  | Standard-Timer (IEC 61499-2), direkte Ereignis- und Datenschnittstellen       | AX_TLIM kapselt `E_TLIM` und bietet eine Adapter-basierte Schnittstelle (`AX`), die in bestimmten Architekturen leichter einzubinden ist. |
| `E_DELAY` | Verzögerungsbaustein (Ansprechverzögerung, Rückfallverzögerung)               | `E_DELAY` verzögert Signaländerungen, während AX_TLIM eine maximale Aktivierungsdauer erzwingt. |
| `E_SR`    | Set-Reset-Flipflop                                                            | AX_TLIM setzt den Ausgang nicht zurück, solange der Eingang aktiv ist (außer durch Timeout). `E_SR` reagiert auf separate Set/Reset-Ereignisse. |

## Fazit

Der **AX_TLIM** Funktionsblock bietet eine kompakte, adapterbasierte Lösung für zeitbegrenzte Überwachung boolescher Signale. Durch die Kapselung des Standard-`E_TLIM` und die Nutzung unidirektionaler AX-Adapter lässt er sich flexibel in IEC 61499-Systeme einbinden, insbesondere wenn Kommunikationspfade über Adapter gekapselt werden sollen. Die Funktionsweise ist intuitiv: Solange der Eingang aktiv ist, bleibt der Ausgang aktiv – maximal für die konfigurierbare Zeit `PT`. Dies macht den Baustein ideal für Sicherheits- und Überwachungsaufgaben in der Automatisierungstechnik.