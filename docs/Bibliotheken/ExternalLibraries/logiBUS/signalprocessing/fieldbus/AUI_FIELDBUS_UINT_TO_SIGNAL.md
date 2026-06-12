# AUI_FIELDBUS_UINT_TO_SIGNAL


![AUI_FIELDBUS_UINT_TO_SIGNAL](./AUI_FIELDBUS_UINT_TO_SIGNAL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUI_FIELDBUS_UINT_TO_SIGNAL** dient der Weiterleitung eines als `UINT` kodierten Feldbussignals an einen nachgeschalteten AUI‑Adapter, sofern das Signal als gültig erkannt wurde. Er stellt zusätzlich einen separaten Gültigkeitsindikator (`VALID`) bereit. Der Baustein kapselt einen Datenumsetzer und ein flankengesteuertes D‑Flip‑Flop, das das Gültigkeitssignal bis zum nächsten Ereignis zwischenspeichert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Funktionsblock besitzt keine separaten Ereignis-Eingänge. Alle ereignisgesteuerten Abläufe werden über den **Adapter‑Socket `IN`** abgewickelt.

### **Ereignis-Ausgänge**

Der Funktionsblock besitzt keine separaten Ereignis-Ausgänge. Ereignisse werden über die **Adapter‑Plugs `OUT` und `VALID`** ausgegeben.

### **Daten-Eingänge**

Der Funktionsblock besitzt keine separaten Daten-Eingänge. Der Eingangswert wird über den **Adapter‑Socket `IN`** als Daten‑Signal `D1` bereitgestellt.

### **Daten-Ausgänge**

Der Funktionsblock besitzt keine separaten Daten-Ausgänge. Ausgangsdaten werden über die **Adapter‑Plugs `OUT` und `VALID`** als Daten‑Signale `D1` übertragen.

### **Adapter**

| Bezeichnung | Typ                   | Richtung | Beschreibung                                                                 |
|-------------|-----------------------|----------|-----------------------------------------------------------------------------|
| `IN`        | AUI (unidirectional)  | Socket   | Empfängt das rohe Feldbussignal als `UINT`. Stellt Ereignis `E1` und Daten `D1` bereit. |
| `OUT`       | AUI (unidirectional)  | Plug     | Gibt das gefilterte Signal als `UINT` aus. Ereignis `E1` signalisiert anliegende Daten. |
| `VALID`     | AX (unidirectional)   | Plug     | Liefert ein Gültigkeitssignal (`TRUE`/`FALSE`) über `D1`; Ereignis `E1` zeigt Aktualisierung an. |

## Funktionsweise

1. Ein externes Ereignis am **Socket `IN`** (über dessen Ereignis‑Eingang `E1`) triggert den Ablauf.
2. Der eingehende Datenwert (`IN.D1`) wird durch den internen FB `FIELDBUS_UINT_TO_SIGNAL` verarbeitet. Dies erzeugt einen Ausgangswert (`OUT`) sowie ein Gültigkeitsflag (`VALID`).
3. Der verarbeitete Wert wird sofort an den **Plug `OUT`** (Daten‑Signal `D1`) weitergegeben und ein Ereignis an `OUT.E1` ausgelöst.
4. Gleichzeitig wird das Gültigkeitsflag des internen FB in das **D‑Flip‑Flop `E_D_FF`** übernommen (getaktet durch dasselbe Ereignis).
5. Der Ausgang des Flip‑Flops (`Q`) wird an den **Plug `VALID`** (Daten‑Signal `D1`) gelegt; gleichzeitig wird ein Ereignis an `VALID.E1` gesendet.
6. Der Zustand des Gültigkeitssignals bleibt bis zum nächsten Verarbeitungszyklus erhalten.

## Technische Besonderheiten

- Der Baustein ist als **Composite FB** realisiert; seine Funktionalität setzt sich aus zwei internen FBs zusammen:  
  - `FIELDBUS_UINT_TO_SIGNAL` (Datenumsetzer)  
  - `E_D_FF` (flankengesteuertes D‑Flip‑Flop)
- Die Gültigkeitsanzeige ist **ereignisgetaktet** und wird über ein Flip‑Flop zwischengespeichert. Dadurch ist sie auch dann stabil, wenn das Eingangssignal für mehrere Zyklen ausbleibt.
- Die Signal‑ und Gültigkeitsausgabe erfolgen **quasi‑parallel** (beide über dasselbe Ereignis des internen FB).
- Die Schnittstellen sind ausschließlich als **Adapter** definiert, was eine modulare Einbindung in Feldbussysteme erleichtert.

## Zustandsübersicht

Der FB selbst besitzt keine explizite Zustandsmaschine. Sein Verhalten kann jedoch durch die interne Logik beschrieben werden:

| Zustand                | Beschreibung                                                                 |
|------------------------|-----------------------------------------------------------------------------|
| **Idle**               | Kein Eingangsereignis; die Ausgänge `OUT` und `VALID` behalten ihre letzten Werte. |
| **Processing**         | Ein Ereignis an `IN.E1` startet die Verarbeitung. |
| **Output**             | Nach Abschluss werden `OUT.D1` und `VALID.D1` aktualisiert und die Ereignisse an `OUT.E1` und `VALID.E1` gesendet. |
| **Hold**               | Der Gültigkeitswert wird im Flip‑Flop gehalten, bis das nächste Ereignis eintrifft. |

## Anwendungsszenarien

- **Feldbus‑Schnittstelle**: Ein von einem Feldbus stammender `UINT`‑Wert soll in ein standardisiertes AUI‑Signal umgewandelt und nur bei Datenintegrität weitergereicht werden.
- **Gültigkeitsgeprüfte Weiterleitung**: Anwendungen, bei denen das Ausgangssignal erst dann als gültig betrachtet werden soll, wenn eine interne Validierung (z. B. CRC‑Prüfung) erfolgreich war.
- **Einkanal‑Signalaufbereitung**: Der Baustein kann in sicherheitsgerichteten Ketten eingesetzt werden, um das Ergebnis einer Plausibilitätsprüfung separat zu signalisieren.

## Vergleich mit ähnlichen Bausteinen

| Baustein                       | Unterschied / Gemeinsamkeit                                                 |
|--------------------------------|-----------------------------------------------------------------------------|
| `FIELDBUS_UINT_TO_SIGNAL`      | Enthält nur die reine Datenumsetzung ohne Gültigkeits‑Zwischenspeicher.     |
| `AUI_SIGNAL_FILTER`            | Filtert Signale, bietet aber keine explizite Gültigkeitsanzeige.            |
| `E_D_FF`                       | Reines Flip‑Flop ohne Datenumsetzung – hier als Hilfsbaustein genutzt.      |

Der vorliegende FB kombiniert die Umsetzung mit einer **ereignisgesteuerten Gültigkeitshaltung**, was ihn für sequenzielle Feldbusprotokolle besonders geeignet macht.

## Fazit

Der Funktionsblock `AUI_FIELDBUS_UINT_TO_SIGNAL` ist ein kompakter, adapterbasierter Baustein zur geprüften Signalweiterleitung in Feldbussystemen. Durch die interne Kopplung von Datenumsetzung und flankengesteuerter Gültigkeitsanzeige bietet er eine robuste und nachvollziehbare Schnittstelle für die industrielle Automatisierung. Die Verwendung von Adaptern ermöglicht eine einfache Integration in bestehende 4diac‑Netzwerke.