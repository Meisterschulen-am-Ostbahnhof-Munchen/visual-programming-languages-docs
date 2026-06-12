# UDINT_AUI_LE


![UDINT_AUI_LE](./UDINT_AUI_LE.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **UDINT_AUI_LE** realisiert einen Vergleich zweier Werte auf „kleiner oder gleich“ (less or equal). Er ist als Standard-Vergleichsfunktion nach IEC 61131-3 klassifiziert und speziell für die Verwendung mit Adapter-Schnittstellen konzipiert. Der Baustein kapselt einen internen `F_LE`-Vergleichsbaustein und stellt dessen Funktionalität über einen unidirektionalen Eingangsadapter (Socket) und einen unidirektionalen Ausgangsadapter (Plug) bereit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `REQ` | Event | Service Request – löst den Vergleich aus |

### **Ereignis-Ausgänge**

Der FB besitzt keine eigenständigen Ereignis-Ausgänge. Das Ergebnisereignis wird über den Ausgangsadapter `OUT.E1` signalisiert.

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| `IN1` | ANY_ELEMENTARY | Erster Vergleichswert (beliebiger elementarer Datentyp) |

### **Daten-Ausgänge**

Der FB besitzt keine eigenständigen Daten-Ausgänge. Das Ergebnis (Boolean) wird über den Ausgangsadapter `OUT.D1` bereitgestellt.

### **Adapter**

| Adapter | Typ | Richtung | Kommentar |
|---------|-----|----------|-----------|
| `IN2` | `adapter::types::unidirectional::AUI` | Socket (Eingang) | Zweiter Vergleichswert, wird über den Adapter als Datenpunkt `D1` und Ereignis `E1` bereitgestellt |
| `OUT` | `adapter::types::unidirectional::AX` | Plug (Ausgang) | Gibt das Vergleichsergebnis als Boolean (`D1`) und ein Bestätigungsereignis (`E1`) aus |

## Funktionsweise

Der Funktionsblock führt einen Vergleich `IN1 <= IN2` durch. Der Vergleich wird entweder durch ein Ereignis am Eingang `REQ` oder durch ein eingehendes Ereignis des Adapters `IN2.E1` (z. B. nach Aktualisierung des Wertes) ausgelöst. Der interne Baustein `F_LE` (Typ `iec61131::comparison::F_LE`) vergleicht die beiden Werte und setzt das Ergebnis auf `OUT.D1`. Gleichzeitig wird über den Ereignisausgang `OUT.E1` signalisiert, dass ein neues Ergebnis vorliegt.

Die Logik entspricht einer ODER-Verknüpfung der beiden Triggerquellen – sowohl der explizite Aufruf über `REQ` als auch die implizite Aktualisierung des Eingangsadapters lösen den Vergleich aus. Dies ermöglicht eine flexible Steuerung des Vergleichsablaufs.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Statt direkter Ein-/Ausgangsvariablen werden Adapter (Socket `IN2`, Plug `OUT`) verwendet. Dadurch ist der FB besonders für den Einsatz in modularen und wiederverwendbaren Komponenten geeignet.
- **Duale Triggerung**: Der Vergleich wird sowohl durch das Ereignis `REQ` als auch durch das Ereignis des Eingangsadapters gestartet. Dies verhindert Datenverluste und vereinfacht die Anbindung an kontinuierlich aktualisierte Quellen.
- **ANY_ELEMENTARY für IN1**: Der erste Eingang akzeptiert beliebige elementare Datentypen (z. B. INT, REAL, UDINT), wodurch der Baustein universell einsetzbar ist.
- **Keine eigenen Ereignis- oder Datenausgänge**: Die gesamte Kommunikation nach außen erfolgt ausschließlich über die Adapter, was die Kapselung verbessert.

## Zustandsübersicht

Der FB hat keinen expliziten Zustandsautomaten, sein Verhalten ist rein funktional:

1. **Idle**: Warten auf ein Triggersignal (entweder `REQ` oder `IN2.E1`).
2. **Vergleich**: Der interne `F_LE`-Baustein wird ausgeführt, sobald ein Trigger eintrifft.
3. **Ausgabe**: Das Ergebnis (`True` bei `IN1 <= IN2`, sonst `False`) wird auf `OUT.D1` gesetzt und das Ereignis `OUT.E1` ausgelöst.
4. Rückkehr zu **Idle**.

## Anwendungsszenarien

- **Grenzwertüberwachung**: Der aktuelle Messwert wird über `IN1` (z. B. als `REAL`) eingegeben, der Grenzwert über den Adapter `IN2` von einer übergeordneten Steuerung. Das Ausgangssignal `OUT.D1` gibt an, ob der Grenzwert unterschritten oder erreicht wird.
- **Vergleich in modularen Systemen**: In einer verteilten Automatisierungsanwendung können verschiedene FB-Typen über Adapter kommunizieren. Dieser Baustein dient als standardisierte Vergleichskomponente mit einheitlicher Schnittstelle.
- **Datengesteuerte Logik**: Die automatische Triggerung über `IN2.E1` ermöglicht eine reaktive Ausführung, sobald sich der zweite Vergleichswert ändert – ohne zyklischen Polling-Aufwand.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum direkten `F_LE`-Baustein aus der IEC‑61131‑3-Bibliothek, der standardmäßige Ein-/Ausgänge verwendet, bietet `UDINT_AUI_LE` eine auf Adapter basierende Kapselung. Dadurch wird die Integration in hierarchische FB-Netzwerke und die Wiederverwendbarkeit in unterschiedlichen Kontexten erleichtert. Die duale Triggerung (über `REQ` und Adapterereignis) ist eine Erweiterung der rein ereignisgesteuerten `F_LE`-Funktion und erhöht die Flexibilität.

## Fazit

Der FB `UDINT_AUI_LE` ist eine leistungsfähige und flexible Komponente für Vergleichsoperationen in der Automatisierungstechnik. Durch die Verwendung von unidirektionalen Adaptern wird eine klare und standardisierte Schnittstelle erreicht, die sich besonders für modulare und verteilte Architekturen eignet. Die Kombination aus explizitem Trigger und automatischer Aktualisierung über den Eingangsadapter macht den FB vielseitig einsetzbar und robust gegenüber Datenänderungen.