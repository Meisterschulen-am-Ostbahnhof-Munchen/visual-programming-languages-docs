# AI_MUX_2


![AI_MUX_2](./AI_MUX_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AI_MUX_2** ist ein generischer Analog-Eingangs-Multiplexer. Er wählt aus zwei analogen Signaleingängen (IN1 und IN2) einen anhand eines Index **K** aus und stellt das ausgewählte Signal an seinem Ausgang **OUT** zur Verfügung. Der Baustein wird über ein Ereignis gesteuert und arbeitet nach dem 61499-2 Standard.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar                         | Mit Daten |
|------|-------|-----------------------------------|-----------|
| REQ  | Event | Anforderung zur Auswahl von Index K | K         |

### **Ereignis-Ausgänge**

| Name | Typ   | Kommentar                                   |
|------|-------|---------------------------------------------|
| CNF  | Event | Bestätigung der ausgeführten Index-Auswahl  |

### **Daten-Eingänge**

| Name | Typ  | Kommentar         |
|------|------|-------------------|
| K    | UINT | Index (0 oder 1)  |

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Typ   | Richtung | Name | Kommentar                                          | Adaptertyp                                          |
|-------|----------|------|----------------------------------------------------|-----------------------------------------------------|
| Plug  | Ausgang  | OUT  | Ausgangssignal, abhängig von K: IN1 bei K=0, IN2 bei K=1 | adapter::types::unidirectional::AI                 |
| Socket| Eingang  | IN1  | Erster analoger Eingang (K=0)                      | adapter::types::unidirectional::AI                 |
| Socket| Eingang  | IN2  | Zweiter analoger Eingang (K=1)                     | adapter::types::unidirectional::AI                 |

Die verwendeten Adapter sind unidirektional (Sender/Empfänger) und spezifisch für analoge Eingangssignale (Typ `adapter::types::unidirectional::AI`).

## Funktionsweise

1. Der Baustein wartet auf ein **REQ**-Ereignis.
2. Beim Eintreten des Ereignisses wird der Wert des Daten-Eingangs **K** ausgelesen.
3. Ist **K = 0**, wird der Adapter-Socket **IN1** auf den Adapter-Plug **OUT** durchgeschaltet.
   Ist **K = 1**, wird **IN2** auf **OUT** durchgeschaltet.
   Bei anderen Werten von **K** ist das Verhalten nicht spezifiziert (typischerweise werden nur die Werte 0 und 1 unterstützt).
4. Nach erfolgreicher Durchschaltung wird das **CNF**-Ereignis ausgegeben.

Die Schaltlogik erfolgt synchron zum REQ-Ereignis. Es gibt keine Verzögerung oder Pufferung.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AI_MUX`) deklariert und kann durch Typparameter an verschiedene Umgebungen angepasst werden.
- **Adapterbasierte Schnittstelle**: Die analogen Signale werden nicht über direkte Ein-/Ausgangsvariablen, sondern über Adapter übertragen. Dies ermöglicht eine flexible Kopplung mit anderen Bausteinen, die denselben Adaptertyp verwenden.
- **Keine Zustandsmaschine**: Der FB besitzt keinen ECC (Execution Control Chart) und keine internen Zustände. Die Verarbeitung ist rein ereignisgesteuert und erfolgt in einem Schritt.
- **Unidirektionale Adapter**: Die Adapter sind als unidirektional definiert, d.h. der Datenfluss ist fest von den Sockets (IN1, IN2) zum Plug (OUT) gerichtet.

## Zustandsübersicht

Der FB besitzt **keine expliziten Zustände**. Die Funktionsweise ist kombinatorisch mit einer ereignisgesteuerten Auslösung:

- **Startzustand**: Warten auf REQ.
- **Nach REQ**: Sofortige Auswahl gemäß K und Ausgabe von CNF.

Es gibt keine internen Variablen, die einen Zustand speichern.

## Anwendungsszenarien

- **Sensorumschaltung**: Auswahl zwischen zwei analogen Sensoren (z.B. Temperatur, Druck) in einer Steuerung, je nach Betriebsmodus.
- **Test- / Messsystem**: Umschaltung zwischen einem Messsignal und einem Referenzsignal zur Kalibrierung.
- **Redundanz**: Wechsel auf ein zweites analoges Signal bei Ausfall des ersten (Ansteuerung über externen Index).

## Vergleich mit ähnlichen Bausteinen

| Baustein | Merkmale |
|----------|----------|
| **AI_MUX_2** | Multiplexer für zwei analoge Eingänge, adapterbasiert, generisch. |
| **DEMUX_AI** | Verteilt ein analoges Signal auf mehrere Ausgänge (Demultiplexer). |
| **SEL** (Standard IEC 61499) | Auswahl zwischen mehreren Dateneingängen über einen Index, meist für elementare Datentypen und ohne Adapter. |

Der **AI_MUX_2** ist speziell für analoge (AI-)Signale über Adapter ausgelegt und daher in komplexen Automatisierungssystemen, die auf Adapter-Kommunikation setzen, besser integrierbar als ein standardisierter SEL-Baustein.

## Fazit

Der **AI_MUX_2** ist ein einfacher, aber effektiver Funktionsblock zur ereignisgesteuerten Umschaltung zwischen zwei analogen Signalen. Er nutzt das Adapterkonzept der 61499-2-Norm, um eine saubere Trennung von Daten- und Ereignisflüssen zu gewährleisten. Durch seinen generischen Aufbau kann er leicht an kundenspezifische Anforderungen angepasst werden. Der FB eignet sich besonders für modulare Steuerungsarchitekturen, in denen analoge Signalpfadumschaltungen benötigt werden.