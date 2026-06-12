# AS_MUX_3


![AS_MUX_3](./AS_MUX_3.svg)

* * * * * * * * * *
## Einleitung

Der **AS_MUX_3** ist ein generischer Multiplexer-Baustein gemäß IEC 61499-2. Er ermöglicht die Weiterleitung eines von drei Eingangssignalen über einen unidirektionalen **AS**-Adapter an einen gemeinsamen Ausgang. Die Auswahl des aktiven Eingangs erfolgt durch einen ganzzahligen Index `K` (UINT). Der Baustein eignet sich besonders für die flexible Umschaltung zwischen verschiedenen Signalquellen in Automatisierungssystemen, wie sie z. B. in der Agrartechnik vorkommen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar                        |
|------|-------|----------------------------------|
| REQ  | Event | Setzt den Index K und löst die Weiterleitung aus |

### **Ereignis-Ausgänge**

| Name | Typ   | Kommentar                                         |
|------|-------|---------------------------------------------------|
| CNF  | Event | Bestätigt die erfolgreiche Übernahme des Index K |

### **Daten-Eingänge**

| Name | Typ  | Kommentar                   |
|------|------|-----------------------------|
| K    | UINT | Auswahlindex (0, 1 oder 2) |

### **Daten-Ausgänge**

Keine direkten Datenausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über den Adapter **OUT**.

### **Adapter**

| Richtung | Name | Typ                               | Kommentar                              |
|----------|------|-----------------------------------|----------------------------------------|
| Plug     | OUT  | adapter::types::unidirectional::AS | Ausgang für den ausgewählten Eingang   |
| Socket   | IN1  | adapter::types::unidirectional::AS | Erster Eingang (K=0)                   |
| Socket   | IN2  | adapter::types::unidirectional::AS | Zweiter Eingang (K=1)                  |
| Socket   | IN3  | adapter::types::unidirectional::AS | Dritter Eingang (K=2)                  |

## Funktionsweise

Der Baustein arbeitet ereignisgesteuert. Bei einem **REQ**-Ereignis wird der aktuelle Wert des Daten-Eingangs `K` (0, 1 oder 2) gelesen. Anschließend wird die entsprechende Adapterverbindung vom Socket (`IN1`, `IN2` oder `IN3`) auf den Plug **OUT** geschaltet und die anliegenden Signale werden durchgereicht. Nach erfolgreicher Umschaltung wird das Ereignis **CNF** ausgegeben.

- Falls `K = 0` → OUT erhält die Signale von IN1.
- Falls `K = 1` → OUT erhält die Signale von IN2.
- Falls `K = 2` → OUT erhält die Signale von IN3.
- Werte außerhalb des Bereichs 0‑2 sind nicht definiert und führen zu undefiniertem Verhalten.

## Technische Besonderheiten

- **Adapter-basiert**: Der Baustein verwendet den unidirektionalen `adapter::types::unidirectional::AS`-Adapter. Dies ermöglicht eine flexible Kopplung mit anderen Bausteinen desselben Adaptertyps ohne feste Datenpfade.
- **Generische Auslegung**: Der **AS_MUX_3** ist als generischer FB deklariert (Attribute `eclipse4diac::core::GenericClassName = 'GEN_AS_MUX'`). Dadurch kann er in verschiedenen Ausführungen (z. B. unterschiedliche Anzahl von Eingängen) durch die IDE spezialisiert werden.
- **Einfache Erweiterbarkeit**: Das Konzept lässt sich auf beliebig viele Eingänge erweitern (z. B. AS_MUX_4, AS_MUX_5 usw.), ohne die grundlegende Funktionsweise zu ändern.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten im XML. Das Verhalten kann als **Ereignis-gesteuerter Funktionsblock** mit folgenden impliziten Zuständen beschrieben werden:

1. **Warten**: Kein REQ-Ereignis anstehend → Ausgang OUT bleibt unverändert.
2. **Auswahl**: REQ empfangen → Index K wird geprüft und der entsprechende Adapter-Socket auf den Plug geschaltet.
3. **Bestätigung**: Nach erfolgreicher Umschaltung wird CNF gesendet, danach Rückkehr in den Wartezustand.

## Anwendungsszenarien

- **Signalumschaltung** in der Feldsteuerung: Auswahl zwischen verschiedenen Sensoren (z. B. Temperatur, Feuchte, Druck) für eine Regelung.
- **Multiplexing von Datenströmen** in einer übergeordneten Steuerungslogik, bei der mehrere Quellen nacheinander abgefragt werden müssen.
- **Test- und Diagnosesysteme**: Umschaltung zwischen Normalbetrieb und Testsignalen.

## Vergleich mit ähnlichen Bausteinen

| Baustein    | Eingänge | Ausgang               | Besonderheit                              |
|-------------|----------|-----------------------|-------------------------------------------|
| AS_MUX_2    | 2        | 1 (unidirectional)    | Einfacherer Multiplexer                   |
| **AS_MUX_3**| 3        | 1                     | Dieser Baustein                           |
| AS_MUX_4    | 4        | 1                     | Erweiterte Auswahlmöglichkeiten           |
| SEL (Standard-61499) | 2 Daten-Eingänge | 1 Daten-Ausgang | Arbeitet auf einfachen Datentypen, nicht auf Adaptern |

Der **AS_MUX_3** hebt sich durch seine Adapter-Schnittstelle von klassischen SEL-Bausteinen ab, die nur einfache Variablen verarbeiten. Adapter ermöglichen den Austausch komplexer Datentypen und bieten eine typsichere Verbindung.

## Fazit

Der **AS_MUX_3** ist ein kompakter und effizienter Multiplexer-Baustein für drei unidirektionale **AS**-Signale. Seine klare Ereignissteuerung und die generische Auslegung machen ihn zu einem wertvollen Werkzeug in IEC‑61499‑basierten Automatisierungslösungen, insbesondere in der Agrartechnik, wo eine flexible Signalumschaltung gefordert ist. Durch den Verzicht auf Datenausgänge zugunsten eines Adapter-Plugs wird eine saubere Trennung von Daten- und Ereignispfaden gewährleistet.