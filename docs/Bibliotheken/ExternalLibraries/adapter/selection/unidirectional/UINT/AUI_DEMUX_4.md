# AUI_DEMUX_4


![AUI_DEMUX_4](./AUI_DEMUX_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUI_DEMUX_4` ist ein generischer AUI‑Demultiplexer für vier Ausgangspfade. Er leitet die über den Eingangsadapter `IN` ankommenden AUI‑Signale an einen der vier Ausgangsadapter (`OUT1`–`OUT4`) weiter, der durch den Index `K` ausgewählt wird. Der Baustein arbeitet nach dem Prinzip der ereignisgesteuerten Umschaltung und eignet sich für flexible Datenverteilung in industriellen Steuerungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar                                    |
|------|-------|----------------------------------------------|
| REQ  | Event | Set Index K; löst die Weiterleitung aus      |

Der Eingang `REQ` triggert die Verarbeitung: Der aktuelle Wert von `K` wird ausgelesen und das an `IN` anliegende Signal wird an den entsprechenden Ausgangsadapter weitergeleitet.

### **Ereignis-Ausgänge**

| Name | Typ   | Kommentar                                    |
|------|-------|----------------------------------------------|
| CNF  | Event | Bestätigung der Indexübernahme               |

Nach erfolgreicher Demultiplexierung wird das Ereignis `CNF` gesendet.

### **Daten-Eingänge**

| Name | Typ   | Kommentar                      |
|------|-------|--------------------------------|
| K    | UINT  | Index des Zielausgangs (1..4)  |

Der Wertebereich für `K` ist nicht im XML festgelegt, üblich sind jedoch Werte von 1 bis 4 (entsprechend den vier Ausgängen). Werte außerhalb dieses Bereichs führen zu keinem definierten Verhalten (können z. B. ignoriert werden oder einen Fehler auslösen – je nach Implementierung).

### **Daten-Ausgänge**

Keine Datenausgänge vorhanden. Die Signalweiterleitung erfolgt ausschließlich über die Adapter.

### **Adapter**

| Name | Typ                                                      | Richtung | Kommentar                           |
|------|----------------------------------------------------------|----------|-------------------------------------|
| IN   | `adapter::types::unidirectional::AUI`                    | Socket   | Eingangssignal (Quelle)             |
| OUT1 | `adapter::types::unidirectional::AUI`                    | Plug     | Zielausgang 1                       |
| OUT2 | `adapter::types::unidirectional::AUI`                    | Plug     | Zielausgang 2                       |
| OUT3 | `adapter::types::unidirectional::AUI`                    | Plug     | Zielausgang 3                       |
| OUT4 | `adapter::types::unidirectional::AUI`                    | Plug     | Zielausgang 4                       |

Alle Adapter sind vom gleichen Typ `AUI` (unidirektional). Der Eingangsadapter `IN` ist als Socket, die vier Ausgangsadapter sind als Plugs ausgeführt. Damit kann der Baustein in eine Adapterverbindung eingefügt werden, die typischerweise von einem AUI‑Sender zu einem AUI‑Empfänger aufgebaut ist.

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis am Eingang `REQ`.
2. Beim Eintreffen von `REQ` wird der aktuelle Wert des Index `K` ausgelesen.
3. Das am Socket `IN` anliegende AUI‑Signal wird auf den Plug `OUT1` ... `OUT4` umgeschaltet – je nachdem, welcher Index (1‑4) in `K` steht.
4. Nach erfolgreicher Umschaltung wird das Ereignis `CNF` ausgegeben, um der aufrufenden Instanz die Verarbeitung zu bestätigen.

Die Signale selbst werden über die Adapter transportiert; der Demultiplexer beeinflusst nur die Verbindungslogik, nicht den Inhalt der AUI‑Daten.

## Technische Besonderheiten

- **Generischer Typ**: Der FB ist als generisch deklariert (`GenericClassName = 'GEN_AUI_DEMUX'`). Dadurch kann er in Projekten mit unterschiedlichen Adaptertypen wiederverwendet werden, sofern die Schnittstellen entsprechend angepasst werden.
- **Unidirektionale Adapter**: Die Adapter sind unidirektional ausgelegt. Eine bidirektionale Kommunikation ist nicht vorgesehen.
- **Keine Pufferung**: Die Umschaltung erfolgt ereignisgetrieben. Es werden keine internen Zwischenspeicher für die AUI‑Signale vorgehalten.
- **Gültigkeitsbereich von K**: Der Index `K` sollte vor dem Auslösen von `REQ` gesetzt werden. Mehrfachaufrufe mit demselben Index führen zu wiederholter Weiterleitung ohne Fehler.

## Zustandsübersicht

Der FB hat einen impliziten Zustand:

- **Idle**: Warten auf `REQ`.
- **Processing**: Verarbeitung von `REQ`. Nach Abschluss wird automatisch zurück in den Idle‑Zustand gewechselt, und `CNF` wird ausgegeben.

Es gibt keine zusätzlichen Fehlerzustände. Ein ungültiger Index (z. B. 0 oder >4) kann je nach Implementierung ignoriert oder als Fehler behandelt werden – dies ist im XML nicht spezifiziert.

## Anwendungsszenarien

- **Signalverteilung**: Ein AUI‑Sender liefert Daten, die wahlweise an vier verschiedene Empfänger (z. B. Aktoren, Subsysteme) weitergeleitet werden müssen.
- **Umschaltung von Steuerbefehlen**: In einer Maschinensteuerung kann ein Taktgeber über den Demultiplexer verschiedene Module nacheinander aktivieren.
- **Test- und Simulationsumgebungen**: Der FB kann genutzt werden, um Testsignale gezielt an einzelne Komponenten zu leiten.

## Vergleich mit ähnlichen Bausteinen

- **AUI_DEMUX_2** o. Ä.: Demultiplexer mit nur zwei Ausgängen – für kleinere Verteilungen optimiert.
- **AUI_MUX_4**: Multiplexer, der mehrere Eingänge auf einen Ausgang zusammenführt – die umgekehrte Funktionalität.
- **AUI_ROUTER**: Komplexerer Baustein mit Adressierung und häufig mehreren Ports – erfordert oft eine Konfigurationstabelle.

Der `AUI_DEMUX_4` ist ein einfacher, klar definierter Baustein ohne Overhead und eignet sich besonders für feste, vorab bekannte Verteilungen mit maximal vier Pfaden.

## Fazit

Der Funktionsblock `AUI_DEMUX_4` stellt eine einfache und effiziente Lösung zur Signalführung in AUI‑basierten Steuerungen dar. Dank seiner generischen Auslegung und der klaren Schnittstellen lässt er sich unkompliziert in vorhandene Systeme integrieren. Die ereignisgesteuerte Indexumschaltung erlaubt eine schnelle Reaktion auf Änderungen der Zieladresse. Für viele Anwendungen, bei denen eine dynamische Verteilung auf bis zu vier Ausgänge erforderlich ist, bietet dieser Baustein eine robuste Grundlage.