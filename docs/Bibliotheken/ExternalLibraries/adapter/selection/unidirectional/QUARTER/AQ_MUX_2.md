# AQ_MUX_2


![AQ_MUX_2](./AQ_MUX_2.svg)

* * * * * * * * * *
## Einleitung
Der **AQ_MUX_2** ist ein generischer 2‑Kanal‑Multiplexer für analoge Ausgangswerte, realisiert als IEC‑61499‑Funktionsblock. Er wählt basierend auf einem Index `K` einen der beiden analogen Eingangsadapter (`IN1`, `IN2`) aus und leitet dessen Signal an den Ausgangsadapter (`OUT`) weiter. Der Baustein eignet sich für Anwendungen, bei denen zwischen zwei Signalquellen umgeschaltet werden muss, z. B. zur Ansteuerung eines Aktors mit unterschiedlichen Sollwerten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **REQ**  | Mit diesem Ereignis wird die Umschaltung des Multipexers ausgelöst. Der aktuelle Wert von `K` bestimmt, welcher Eingang zum Ausgang durchgeschaltet wird. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **CNF**  | Bestätigt die erfolgreiche Ausführung der durch `REQ` angeforderten Auswahl. |

### **Daten-Eingänge**

| Name | Typ   | Beschreibung |
|------|-------|--------------|
| **K** | UINT  | Index für die Auswahl des Eingangs. Gültige Werte: `0` → IN1, `1` → IN2. Werte außerhalb dieses Bereichs sind undefiniert. |

### **Daten-Ausgänge**
Der Baustein besitzt keine eigenständigen Datenausgänge; die Ausgangsdaten werden über den Adapter `OUT` bereitgestellt.

### **Adapter**

| Rolle | Name | Typ (Adapter) | Beschreibung |
|-------|------|---------------|--------------|
| Plug  | **OUT**  | `adapter::types::unidirectional::AQ` | Ausgewählter analoger Ausgangswert. |
| Socket | **IN1** | `adapter::types::unidirectional::AQ` | Erster Eingang (Index 0). |
| Socket | **IN2** | `adapter::types::unidirectional::AQ` | Zweiter Eingang (Index 1). |

Alle Adapter sind vom gleichen Typ, einem unidirektionalen Analog‑Ausgangs‑Adapter.

## Funktionsweise
Der **AQ_MUX_2** arbeitet ereignisgesteuert:
1. Ein **REQ**‑Ereignis signalisiert eine neue Anforderung.
2. Der aktuelle Wert von `K` wird ausgewertet:
   - Bei `K = 0` wird der Wert des Adapters **IN1** an **OUT** weitergegeben.
   - Bei `K = 1` wird der Wert des Adapters **IN2** an **OUT** weitergegeben.
3. Nach erfolgreicher Umschaltung wird ein **CNF**‑Ereignis ausgegeben.

Die Auswahl erfolgt sofort bei Eintreffen des `REQ`‑Ereignisses. Es gibt keine Zwischenspeicherung; die Ausgangsdaten entsprechen dem aktuellen Zustand des gewählten Eingangsadapters.

## Technische Besonderheiten
- **Adapter‑basierte Schnittstelle**: Sowohl Eingänge als auch Ausgang verwenden einheitliche Adapter vom Typ `adapter::types::unidirectional::AQ`, was eine modulare und wiederverwendbare Verkabelung in der Applikation ermöglicht.
- **Generischer Aufbau**: Der Baustein ist als generischer FB (`GEN_AQ_MUX`) deklariert und kann je nach Zielplattform spezifisch instanziiert werden.
- **Lizenz**: Verfügbar unter der Eclipse Public License 2.0 (EPL‑2.0).
- **Entwickelt von**: HR Agrartechnik GmbH (Version 1.0, 2026‑05‑28).

## Zustandsübersicht
Der FB besitzt keine explizit modellierte Zustandsmaschine (ECC). Das interne Verhalten lässt sich als einfacher, ereignisgesteuerter Ablauf beschreiben:

```
IDLE → [REQ empfangen] → Auswahl durchführen → [CNF senden] → IDLE
```

Nach der Verarbeitung kehrt der Baustein sofort in den Bereitschaftszustand zurück und erwartet das nächste `REQ`‑Ereignis.

## Anwendungsszenarien
- **Umschaltung zwischen zwei Sollwerten**: In einer Maschinensteuerung kann zwischen zwei vorgegebenen analogen Stellgrößen (z. B. Geschwindigkeit, Position) gewählt werden.
- **Redundanzumschaltung**: Wenn ein Sensor oder Signalgeber ausfällt, wird automatisch oder manuell auf einen Ersatzeingang umgeschaltet.
- **Betriebsarten‑Auswahl**: Je nach Betriebsmodus (z. B. Automatik/Handbetrieb) wird ein anderer Analogwert an den Aktor weitergeleitet.

## Vergleich mit ähnlichen Bausteinen
Im IEC‑61499‑Standard existieren verschiedene Multiplexer‑Funktionsblöcke (z. B. `SEL`, `MUX`). Der **AQ_MUX_2** unterscheidet sich durch:
- **Adapter‑Schnittstelle**: Statt einzelner Daten‑Ein‑/Ausgänge arbeitet er mit Adaptern, was die Kapselung komplexerer Datentypen ermöglicht.
- **Spezialisierung auf analoge Ausgänge**: Der Adaptertyp `AQ` ist für analoge Ausgangssignale optimiert (z. B. 0‑10 V, 4‑20 mA).
- **Einfachheit**: Nur zwei Kanäle (gegenüber `MUX` mit mehreren Eingängen), was die Übersichtlichkeit erhöht.

## Fazit
Der **AQ_MUX_2** ist ein praktischer, generischer Multiplexer‑Baustein für analoge Ausgangswerte. Seine adapterbasierte Schnittstelle erleichtert die Integration in bestehende 4diac‑Applikationen und macht ihn besonders für modulare Steuerungslösungen geeignet. Dank der transparenten Umschaltlogik und der klaren Ereignissteuerung ist er zuverlässig und leicht verständlich.