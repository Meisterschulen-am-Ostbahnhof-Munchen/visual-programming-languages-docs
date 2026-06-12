# AIWS_MUX_3


![AIWS_MUX_3](./AIWS_MUX_3.svg)

* * * * * * * * * *
## Einleitung

Der Baustein **AIWS_MUX_3** ist ein generischer Multiplexer für den unidirektionalen Datentyp *AIWS*. Er wählt aus drei Eingangsadaptern (`IN1`, `IN2`, `IN3`) entsprechend eines übergebenen Index `K` einen aus und stellt diesen am Ausgangsadapter `OUT` bereit. Die Auswahl wird durch ein Ereignis `REQ` gestartet und mit `CNF` quittiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| `REQ`    | Löst die Auswahl des Index `K` aus. Verknüpft mit Variable `K`. |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| `CNF`    | Bestätigung der erfolgten Index-Auswahl. |

### **Daten-Eingänge**

| Name | Typ   | Kommentar |
|------|-------|-----------|
| `K`  | UINT  | Index des zu übernehmenden Eingangs (0 = IN1, 1 = IN2, 2 = IN3). |

### **Daten-Ausgänge**

Keine separaten Datenausgänge – die Übergabe erfolgt über den Adapter `OUT`.

### **Adapter**

| Typ | Bezeichnung | Richtung | Kommentar |
|-----|-------------|----------|-----------|
| `AIWS` (unidirectional) | `IN1` | Socket | Erster Eingangswert (Index 0). |
| `AIWS` (unidirectional) | `IN2` | Socket | Zweiter Eingangswert (Index 1). |
| `AIWS` (unidirectional) | `IN3` | Socket | Dritter Eingangswert (Index 2). |
| `AIWS` (unidirectional) | `OUT` | Plug   | Ausgangswert des selektierten Eingangs. |

## Funktionsweise

1. Der Baustein erwartet ein Ereignis `REQ`. Gleichzeitig muss der Daten-Eingang `K` einen gültigen Index (0, 1 oder 2) bereitstellen.
2. Nach dem Eintreffen von `REQ` wird der Wert von `K` ausgewertet:
   - `K = 0`: Der Datenstrom von `IN1` wird auf den Ausgang `OUT` durchgeschaltet.
   - `K = 1`: Der Datenstrom von `IN2` wird auf den Ausgang `OUT` durchgeschaltet.
   - `K = 2`: Der Datenstrom von `IN3` wird auf den Ausgang `OUT` durchgeschaltet.
   - Werte außerhalb des Bereichs (z. B. > 2) sind undefiniert – in einer konkreten Implementierung könnte der Baustein entweder nichts tun oder einen vordefinierten Fehlerzustand einnehmen.
3. Nach erfolgreicher Durchschaltung wird das Ereignis `CNF` gesendet.

## Technische Besonderheiten

- **Generischer Baustein**: Der Multiplexer ist vollständig generisch für den Adaptertyp `AIWS` ausgelegt. Dadurch kann er in unterschiedlichen Kontexten (z. B. analoge Eingänge, Sensordaten) wiederverwendet werden, solange der Adapter den gleichen unidirektionalen Vertrag erfüllt.
- **Adapterbasierte Kommunikation**: Die gesamte Datenübertragung zwischen Funktionsbausteinen erfolgt über Adapter, nicht über einzelne Variablen. Dies ermöglicht eine lose Kopplung und modulare Systemgestaltung.
- **Unidirektionale Schnittstelle**: Sowohl Eingangs- als auch Ausgangsadapter sind als unidirektional definiert – Daten fließen nur in eine Richtung (vom Socket zum Plug). Dies vereinfacht die Testbarkeit und vermeidet Rückkopplungen.
- **Ereignisgesteuert**: Die Umschaltung erfolgt nur auf explizite Anforderung (`REQ`). Ohne Ereignis bleiben die internen Verbindungen unverändert.

## Zustandsübersicht

Der Baustein besitzt ein einfaches Zustandsmodell, das in der internen Ablaufsteuerung (ECC) realisiert ist:

| Zustand | Beschreibung |
|---------|--------------|
| `IDLE`  | Warten auf ein `REQ`-Ereignis. |
| `SELECT`| Auswertung von `K` und Durchschaltung des entsprechenden Eingangs auf `OUT`. |
| `SEND`  | Aussenden von `CNF` und Rückkehr nach `IDLE`. |

Nach jedem erfolgreichen Durchlauf wird wieder der Ruhezustand `IDLE` erreicht.

## Anwendungsszenarien

- **Sensorauswahl**: Ein System besitzt mehrere analoge Sensoren (z. B. Temperatur, Druck, Feuchte). Über `K` kann abwechselnd ein Sensorwert an eine zentrale Verarbeitungseinheit übergeben werden.
- **Signalrouting**: In einer Steuerung werden drei verschiedene Quellen (z. B. alternative Messpfade oder Redundanzsignale) bereitgestellt. Der Multiplexer wählt je nach Betriebsmodus die aktive Quelle aus.
- **Test- und Diagnose**: Während des Betriebs kann auf einen fest definierten Testeingang umgeschaltet werden, um die Funktion des nachfolgenden Bausteins zu prüfen.

## Vergleich mit ähnlichen Bausteinen

- **Standard-MUX (z. B. IEC 61499 MUX)**: Ein herkömmlicher Multiplexer arbeitet meist mit elementaren Datentypen (BOOL, INT, REAL) und besitzt separate Daten-Eingänge. Der `AIWS_MUX_3` nutzt dagegen Adapter, wodurch auch komplexe, zusammengesetzte Datenobjekte (wie Strukturen oder ganze Messwerte mit Qualitätsflags) durchgeschaltet werden können.
- **Adapterbasierte Selektoren**: Andere Bausteine wie `AIWS_SELECT` wählen zwischen zwei Adaptern. `AIWS_MUX_3` erweitert dies auf drei Eingänge und einen festen Index-Parameter.
- **Generischer Multi-MUX**: Im Vergleich zu einem nicht-generischen Multiplexer erlaubt die generische Definition den Einsatz beliebig vieler Instanzen mit demselben Adaptertyp, ohne dass der Baustein für jede Datenart neu definiert werden muss.

## Fazit

Der **AIWS_MUX_3** ist ein flexibler und generischer Multiplexer, der speziell für den unidirektionalen Adaptertyp *AIWS* entwickelt wurde. Er ermöglicht die saubere, ereignisgesteuerte Auswahl aus bis zu drei Quellen und eignet sich besonders für modulare Automatisierungslösungen, bei denen Daten über Adapter gekapselt werden. Die einfache Schnittstelle (ein Index, ein Ereignis) und die klare Zustandslogik machen ihn leicht integrierbar und testbar.