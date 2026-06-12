# AQ_MUX_4


![AQ_MUX_4](./AQ_MUX_4.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AQ_MUX_4` dient als Multiplexer für Adapter vom Typ `AQ`. Er wählt aus vier verfügbaren Adapter-Eingängen (IN1–IN4) einen aus und leitet dessen Signal an den Adapter-Ausgang OUT weiter. Die Auswahl erfolgt anhand eines numerischen Indexes `K`, der über den Ereignis-Eingang `REQ` gesetzt wird. Der Block ist als generischer Funktionsblock deklariert und kann in der Entwicklungsumgebung bei Bedarf an die Anzahl der Eingänge angepasst werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar                       |
|------|-------|---------------------------------|
| REQ  | Event | Setzt den Index `K` und löst die Umschaltung aus. |

### **Ereignis-Ausgänge**

| Name | Typ   | Kommentar                              |
|------|-------|----------------------------------------|
| CNF  | Event | Bestätigung der Umschaltung (Quittung). |

### **Daten-Eingänge**

| Name | Typ  | Kommentar                     |
|------|------|-------------------------------|
| K    | UINT | Index des gewünschten Eingangs (0–3). |

### **Daten-Ausgänge**

Keine eigenen Datenausgänge – die Ausgabe erfolgt über den Adapter-Ausgang `OUT`.

### **Adapter**

| Richtung | Name | Typ                                          | Kommentar                                                     |
|----------|------|----------------------------------------------|---------------------------------------------------------------|
| Plug     | OUT  | `adapter::types::unidirectional::AQ`         | Ausgang: Signal des ausgewählten Eingangs (IN1–IN4).          |
| Socket   | IN1  | `adapter::types::unidirectional::AQ`         | Erster Eingang (wird für K=0 aktiv).                         |
| Socket   | IN2  | `adapter::types::unidirectional::AQ`         | Zweiter Eingang (wird für K=1 aktiv).                        |
| Socket   | IN3  | `adapter::types::unidirectional::AQ`         | Dritter Eingang (wird für K=2 aktiv).                        |
| Socket   | IN4  | `adapter::types::unidirectional::AQ`         | Vierter Eingang (wird für K=3 aktiv).                        |

Alle Adapter sind vom Typ `adapter::types::unidirectional::AQ` – ein unidirektionaler Adapter für analoge Ausgabewerte (z. B. Spannungs- oder Stromsignale).

## Funktionsweise

Der `AQ_MUX_4` arbeitet ereignisgesteuert:

1. Ein Ereignis am Eingang `REQ` triggert die Verarbeitung.
2. Der aktuelle Wert des Daten-Eingangs `K` wird ausgelesen.
3. Je nach Wert von `K` (0, 1, 2 oder 3) wird der entsprechende Adapter-Eingang auf den Adapter-Ausgang `OUT` umgeschaltet:
   - `K = 0` → OUT erhält die Daten von IN1
   - `K = 1` → OUT erhält die Daten von IN2
   - `K = 2` → OUT erhält die Daten von IN3
   - `K = 3` → OUT erhält die Daten von IN4
4. Nach erfolgreicher Umschaltung wird das Bestätigungsereignis `CNF` gesendet.

Wird ein Index außerhalb des gültigen Bereichs (0–3) übergeben, so ist das Verhalten undefiniert – typischerweise wird kein Eingang aktiviert oder es erfolgt eine unbeabsichtigte Weiterleitung.

## Technische Besonderheiten

- **Generischer Funktionsblock**: Der `AQ_MUX_4` ist als generischer Block (`GenericClassName = 'GEN_AQ_MUX'`) definiert. In der 4diac-IDE kann er daher als Vorlage für Multiplexer mit anderer Anzahl von Eingängen (z. B. 2, 8) verwendet werden, ohne die interne Logik neu erstellen zu müssen.
- **Adapterbasierte Schnittstelle**: Anders als klassische Multiplexer mit Datentypen wie `INT` oder `REAL` arbeitet dieser Block mit Adaptern, sodass ganze Signalpakete (z. B. Werte, Qualitätsflags) übertragen werden können.
- **Keine Bereichsprüfung**: Die Gültigkeit von `K` wird nicht geprüft. Bei einer Fehlbedienung (Wert > 3) ist das Systemverhalten nicht festgelegt – dies muss in der Applikation durch geeignete Maßnahmen abgefangen werden.
- **Keine Zustandsspeicherung**: Der Block hat keinen internen Zustand außer der aktuellen Verbindung. Jedes `REQ`-Ereignis führt sofort zur Neukonfiguration.

## Zustandsübersicht

Der `AQ_MUX_4` besitzt keine explizite Zustandsmaschine (State Machine). Der Ablauf lässt sich als einfache Transaktion beschreiben:

```
IDLE → [REQ] → Auswerten von K → Verbindung umschalten → [CNF] → IDLE
```

Die Zeitspanne zwischen `REQ` und `CNF` ist rein durch die Ausführungszeit der umgebenden Steuerung bestimmt.

## Anwendungsszenarien

- **Umschaltung zwischen mehreren analogen Sollwerten** in einer Maschinensteuerung (z. B. Landwirtschaft, Antriebstechnik).
- **Betriebsartenauswahl** für Aktoren, bei denen unterschiedliche Signalquellen (Handbetrieb, Automatik, Notbetrieb) aktiv geschaltet werden müssen.
- **Redundanzumschaltung** zwischen mehreren analogen Mess- oder Steuersignalen.

## Vergleich mit ähnlichen Bausteinen

| Baustein    | Schnittstelle                       | Anzahl Eingänge | Besonderheit                                     |
|-------------|-------------------------------------|-----------------|--------------------------------------------------|
| `AQ_MUX_4`  | Adapter (unidirektional, `AQ`)      | 4               | Generisch, für analoge Ausgangssignale optimiert |
| `MUX`       | Datentypen (z. B. `ANY`)            | parametrierbar  | Standard-Multiplexer aus IEC 61499-Bibliotheken  |
| `SEL`       | Datentypen (zwei Eingänge)          | 2               | Einfache Auswahl zwischen zwei Werten            |

Der `AQ_MUX_4` hebt sich durch die Verwendung von Adaptern ab, die es erlauben, komplexe Signale über eine einzige Verbindung zu transportieren, und durch seine generische Basis, die eine einfache Wiederverwendung in verschiedenen Ausbaustufen ermöglicht.

## Fazit

Der `AQ_MUX_4` ist ein praktischer Baustein zur dynamischen Auswahl eines analogen Ausgangssignals aus bis zu vier Quellen. Seine adapterbasierte Schnittstelle macht ihn besonders geeignet für modulare Steuerungsarchitekturen, in denen Signale nicht nur als einzelne Werte, sondern als strukturierte Datenpakete ausgetauscht werden. Die generische Deklaration erleichtert zudem die Anpassung an abweichende Anforderungen.