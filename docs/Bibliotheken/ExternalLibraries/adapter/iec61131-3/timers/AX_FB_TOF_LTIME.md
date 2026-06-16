# AX_FB_TOF_LTIME


![AX_FB_TOF_LTIME](./AX_FB_TOF_LTIME.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AX_FB_TOF_LTIME** realisiert einen Standard-Timer für die Ausschaltverzögerung (Off-Delay) nach IEC 61131-3. Er ist speziell für den Einsatz mit einem AX-Adapter ausgelegt und verwendet dabei einen internen Timerbaustein sowie ein D-Flipflop, um das Zeitverhalten präzise abzubilden. Die Zeitbasis arbeitet mit dem Datentyp `LTIME`, wodurch eine hohe zeitliche Auflösung erreicht wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| `REQ` | Normaler Ausführungsauftrag (nicht auslösend) – startet bzw. aktualisiert die Timerberechnung. Der zugehörige Daten-Eingang ist `PT`. |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| `CNF` | Bestätigung der Ausführung – signalisiert den Abschluss einer Timeraktualisierung. Der zugehörige Daten-Ausgang ist `ET`. |

### **Daten-Eingänge**

| Variable | Typ | Kommentar |
|----------|-----|-----------|
| `PT` | `LTIME` | Prozesszeit – die gewünschte Ausschaltverzögerungsdauer. |

### **Daten-Ausgänge**

| Variable | Typ | Kommentar |
|----------|-----|-----------|
| `ET` | `LTIME` | Verstrichene Zeit – die bereits abgelaufene Zeit seit Start der Verzögerung. |

### **Adapter**

| Richtung | Adaptertyp | Kommentar |
|----------|------------|-----------|
| **Socket** `IN` | `adapter::types::unidirectional::AX` | Eingangsadapter – nimmt das binäre Steuersignal entgegen (z. B. über Ereignis `E1` und Daten `D1`). |
| **Plug** `Q` | `adapter::types::unidirectional::AX` | Ausgangsadapter – gibt das zeitverzögerte Ausgangssignal weiter (über Ereignis `E1` und Daten `D1`). |

## Funktionsweise
Der Baustein verhält sich wie eine klassische Ausschaltverzögerung (TOF):

- Solange der Eingang `IN` (über den Adapter) **TRUE** ist, ist der Ausgang `Q` ebenfalls **TRUE** und die verstrichene Zeit `ET` wird auf Null gesetzt.
- Sobald `IN` von **TRUE** auf **FALSE** wechselt, startet die Zeitmessung. Der Ausgang `Q` bleibt für die Dauer der vorgegebenen Zeit `PT` **TRUE** und fällt erst danach auf **FALSE**.
- Wird `IN` vor Ablauf der Verzögerungszeit wieder **TRUE**, wird der Timer zurückgesetzt und `Q` bleibt **TRUE**.

Die ereignisgesteuerte Verarbeitung erfolgt wie folgt:
1. Das Ereignis `REQ` (entweder direkt oder vom Adaptereingang `IN.E1`) triggert den internen Timer `FB_TOF_LTIME`.
2. Der Timer berechnet die verstrichene Zeit und gibt bei Abschluss das Ereignis `CNF` aus.
3. Dieses `CNF` taktet das D‑Flipflop `E_D_FF`, das den aktuellen Timer‑Ausgang (`Q` des Timers) speichert und auf den Ausgangsadapter `Q.D1` durchschaltet.
4. Gleichzeitig wird das `CNF`-Ereignis an den Ausgangsadapter `Q.E1` weitergeleitet, so dass der nachgeschaltete Adapter über die Änderung informiert wird.

Die Variable `ET` wird direkt vom Timer übernommen und zeigt jederzeit die aktuell abgelaufene Verzögerungszeit an.

## Technische Besonderheiten
- **Hohe Zeitauflösung** durch Verwendung von `LTIME` (Long Time) gemäß IEC 61131-3.
- **Adapter-basierte Ein‑/Ausgabe** über den unidirektionalen `AX`-Adapter ermöglicht eine lose Kopplung zwischen verschiedenen Ressourcen (z. B. zwischen Anwendung und E/A‑Treiber).
- **Standardkonformität** nach IEC 61131-3 – das Verhalten entspricht exakt dem eines TOF‑Timers.
- **Interne Struktur**: Der Baustein kombiniert einen reinen Timer (`FB_TOF_LTIME`) mit einem flankengetriggerten D‑Flipflop, um das Ausschaltverzögerungsverhalten zu realisieren.

## Zustandsübersicht

| Zustand | Eingang `IN` | Ausgang `Q` | Verstrichene Zeit `ET` |
|---------|--------------|-------------|------------------------|
| Inaktiv / Bereit | TRUE | TRUE | 0 (Null) |
| Verzögerung läuft | FALSE → TRUE‑Rückkehr möglich | TRUE | 0 … PT |
| Verzögerung abgelaufen | FALSE | FALSE | PT (konstant) |

Ein erneuter Wechsel von `IN` auf **TRUE** setzt den Timer zurück und führt sofort wieder in den Zustand „Inaktiv / Bereit“. Ein Wechsel auf **FALSE** startet die Verzögerung von Neuem.

## Anwendungsszenarien
- **Nachlaufsteuerung** von Lüftern, Pumpen oder Förderbändern nach dem Abschalten eines Signals.
- **Entprellung** von Signalen: ein kurzzeitiger Pegelwechsel wird durch die Verzögerung ausgefiltert.
- **Schutzzeiten** beim Schalten von induktiven Lasten: das Ausschalten wird um eine definierte Zeit verzögert.
- **Zeitgesteuerte Logik** in Produktionsanlagen, bei der ein Ausgang für eine bestimmte Dauer nach dem Eingangsereignis aktiv bleiben soll.

## Vergleich mit ähnlichen Bausteinen
- **TON (Einschaltverzögerung)**: Der Ausgang wird erst nach einer Verzögerung nach dem Einschalten aktiv. – TOF verzögert das Ausschalten.
- **TP (Impuls)**: Der Ausgang gibt einen Impuls vorgegebener Länge, unabhängig von der Dauer des Eingangssignals. – TOF reagiert nur auf die fallende Flanke.
- **RTRIG / FTRIG (Flankenerkennung)**: Erkennen Signalwechsel, ohne Zeitkomponente. – TOF kombiniert Flankenerkennung mit Zeitsteuerung.

## Fazit
Der `AX_FB_TOF_LTIME` ist ein leistungsfähiger, standardisierter Funktionsblock für zeitkritische Ausschaltverzögerungen in der Automatisierungstechnik. Durch die Verwendung des AX-Adapters lässt er sich flexibel in verteilte Systeme einbinden, während die interne Kombination aus Timer und Flipflop ein präzises und reproduzierbares Zeitverhalten gewährleistet. Er eignet sich besonders für Anwendungen, die eine genaue Zeitbasis und eine modulare Schnittstelle erfordern.