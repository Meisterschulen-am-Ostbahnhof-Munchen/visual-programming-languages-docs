# AR_D_FF_HYS


![AR_D_FF_HYS](./AR_D_FF_HYS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AR_D_FF_HYS** realisiert ein Data-Latch (D-)Flipflop mit Hysterese. Er dient zur stabilen Erfassung und Weitergabe eines analogen (realen) Wertes, wobei ein Hystereseband unerwünschtes Flattern am Ausgang unterdrückt. Der Baustein ist für den Einsatz in der industriellen Signalverarbeitung konzipiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INIT | EInit | Initialisiert den Baustein und setzt das Hystereseband. |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INITO | EInit | Bestätigt die erfolgreiche Initialisierung. |

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| HYSTERESIS | REAL | Größe des Hysteresebands. |

### **Daten-Ausgänge**

*(keine direkten Datenausgänge; der latente Wert wird über den Adapter Q ausgegeben)*

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
|-------------|-----|----------|--------------|
| I | adapter::types::unidirectional::AR | Socket (Eingang) | Empfängt den zu latchten Wert (Triggerevent auf E1, Daten auf D1). |
| Q | adapter::types::unidirectional::AR | Plug (Ausgang) | Gibt den gelatchten Wert aus (Ereignis auf E1, Daten auf D1). |

## Funktionsweise

Der Baustein enthält intern einen Sub-FB `E_D_FF_ANY_HYS` aus der Bibliothek `logiBUS::signalprocessing::hysteresis`.

- Bei jedem steigenden Flanke auf dem Ereigniseingang `I.E1` wird der aktuelle Datenwert von `I.D1` übernommen.
- Der übernommene Wert wird jedoch erst dann auf `Q.D1` weitergegeben, wenn er sich um mehr als die eingestellte Hysterese (`HYSTERESIS`) vom zuletzt ausgegebenen Wert unterscheidet.
- Das Ereignis `I.E1` wird synchron als `Q.E1` weitergereicht, um den Empfänger über einen neuen Wert zu informieren.
- Die Initialisierung (`INIT`) setzt das Hystereseband und bestätigt sofort mit `INITO`. Eine Änderung von `HYSTERESIS` während des Betriebs ist nicht vorgesehen; die Hysterese wird nur beim INIT-Ereignis übernommen.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Sowohl der Eingang als auch der Ausgang verwenden den generischen Adapter `adapter::types::unidirectional::AR`, der es erlaubt, den Baustein flexibel in vorhandene Adapterketten einzubinden.
- **Hysterese-Funktion**: Unterdrückt Rauschen und Oszillationen an Schwellwerten und sorgt für einen sauberen, stabilen Ausgang.
- **EPL 2.0**: Der Baustein ist unter der Eclipse Public License 2.0 lizenziert und kann frei verwendet und modifiziert werden.
- **Interne Implementierung**: Die eigentliche Hystereselogik wird von einem spezialisierten Subbaustein (`E_D_FF_ANY_HYS`) ausgeführt, was Wartbarkeit und Wiederverwendbarkeit verbessert.

## Zustandsübersicht

Der Baustein besitzt einen impliziten Speicherzustand für den zuletzt ausgegebenen Wert. Da es sich um ein D-Flipflop mit Hysterese handelt, kann man drei logische Bereiche unterscheiden:

- **Eingang ≥ (Ausgang + Hysterese/2)** → Ausgang wird auf den neuen Eingang gesetzt.
- **Eingang ≤ (Ausgang − Hysterese/2)** → Ausgang wird auf den neuen Eingang gesetzt.
- **Wert innerhalb des Hysteresebands** → Ausgang bleibt unverändert (Historie).

Explizite Zustandsautomaten sind nicht vorhanden; der Baustein arbeit rein ereignisgesteuert.

## Anwendungsszenarien

- **Signalglättung**: Entfernen von hochfrequentem Rauschen aus analogen Messwerten.
- **Schwellwertschalter**: Definierte Ein- und Ausschaltpunkte für binäre Entscheidungen (z. B. Temperaturregelung).
- **Flankenerkennung mit Hysterese**: Zuverlässige Erkennung von steigenden oder fallenden Flanken eines analogen Signals.
- **Pegelanpassung**: Stabiles Nachführen eines Ausgangswerts an einen schwankenden Eingang.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft |
|----------|-------------|
| **AR_D_FF** (ohne Hysterese) | Übernimmt jeden neuen Wert sofort; empfindlich gegen Rauschen. |
| **AR_D_FF_HYS** (dieser FB) | Verwendet ein Hystereseband zur Unterdrückung von Flimmern. |
| **Schmitt-Trigger** | Realisiert eine ähnliche Hysterese, aber meist für binäre (boolesche) Signale. Dieser Baustein arbeitet mit analogen (REAL) Werten. |

## Fazit

Der **AR_D_FF_HYS** ist ein robuster, adapterbasierter Funktionsbaustein für die zuverlässige Weitergabe analoger Werte mit einstellbarer Hysterese. Er eignet sich besonders für Anwendungen, in denen Störungen auf der Signalleitung auftreten oder ein definiertes Schaltverhalten erforderlich ist. Die einfache Initialisierung und die klare Schnittstellenstruktur erleichtern die Integration in automatisierungstechnische Systeme.