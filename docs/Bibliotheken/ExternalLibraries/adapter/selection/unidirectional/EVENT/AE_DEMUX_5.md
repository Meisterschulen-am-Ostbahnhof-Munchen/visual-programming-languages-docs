# AE_DEMUX_5


![AE_DEMUX_5](./AE_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AE_DEMUX_5** ist ein generischer AE-Demultiplexer, der ein eingehendes AE-Signal über den Socket **IN** abhängig von einem ausgewählten Index auf einen von fünf Ausgangsadaptern (OUT1 … OUT5) leitet. Er ermöglicht so die gezielte Verteilung eines Datenstroms auf verschiedene Pfade.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **REQ** | Auslöser zum Setzen des Index **K** und Auswahl des Ausgangs. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **CNF** | Bestätigt die erfolgreiche Verarbeitung von **REQ**. |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| **K**    | UINT  | Indexwert zur Auswahl des Ausgangs (gültige Werte: 1 … 5). |

### **Daten-Ausgänge**
Keine Datenausgänge vorhanden.

### **Adapter**

| Rolle | Name | Typ                        | Beschreibung |
|-------|------|----------------------------|--------------|
| Socket| **IN** | `adapter::types::unidirectional::AE` | Eingangssignal, das demultiplext wird. |
| Plug  | **OUT1** | `adapter::types::unidirectional::AE` | Ausgang 1 |
| Plug  | **OUT2** | `adapter::types::unidirectional::AE` | Ausgang 2 |
| Plug  | **OUT3** | `adapter::types::unidirectional::AE` | Ausgang 3 |
| Plug  | **OUT4** | `adapter::types::unidirectional::AE` | Ausgang 4 |
| Plug  | **OUT5** | `adapter::types::unidirectional::AE` | Ausgang 5 |

## Funktionsweise
1. Am Ereigniseingang **REQ** wird ein Index **K** (1 … 5) übergeben.
2. Das am Socket **IN** anliegende AE-Signal wird auf den Plug **OUTx** (x = K) geschaltet.
3. Nach erfolgreichem Schalten wird der Ereignisausgang **CNF** ausgegeben.
   - Bei ungültigem Index (< 1 oder > 5) erfolgt keine Umschaltung; **CNF** bleibt aus.

## Technische Besonderheiten
- **Generischer Baustein**: Die Klasse kann unter dem Namen `GEN_AE_DEMUX` instanziiert werden, wobei die Anzahl der Ausgänge über den Symbolnamen (hier 5) festgelegt wird.
- **Adapter-basiert**: Anstelle fester Datenports werden AE‑Adapter verwendet, was eine flexible Kopplung mit anderen Bausteinen ermöglicht.
- **TypHash**: Über ein Attribut wird ein Typ‑Hash für die Laufzeitidentifikation bereitgestellt.
- **Kein eigener Zustandsautomat**: Die Funktionalität ist rein ereignisgesteuert ohne interne Zustände.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten. Er arbeitet ereignisgesteuert in einem Schritt pro **REQ**‑Aufruf. Ein impliziter Ruhezustand wird durch das Warten auf das nächste Ereignis dargestellt.

## Anwendungsszenarien
- **Signalverteilung**: Weitergabe eines AE‑Signals (z. B. Sensorwert, Steuerbefehl) an verschiedene Aktoren oder Unterfunktionen.
- **Kanalwahl**: Auswahl eines von fünf Ausgangskanälen, z. B. in Mehrfachventil‑ oder Multiplexer‑Anwendungen.
- **Routingschalter**: Dynamische Umschaltung des Zielpfads innerhalb einer Steuerung.

## Vergleich mit ähnlichen Bausteinen
- **AE_DEMUX_2 / AE_DEMUX_10**: Entsprechende Varianten mit zwei oder zehn Ausgängen – gleiche Logik, andere Kanalzahl.
- **AE_MUX_X**: Multiplexer (mehrere Eingänge, ein Ausgang) – die inverse Funktion.
- Im Vergleich zu einem spezialisierten Selektionsbaustein auf Datenebene (z. B. `SELECT_INT`) arbeitet dieser Baustein auf Adapterebene und überträgt den gesamten AE‑Kontext.

## Fazit
Der **AE_DEMUX_5** bietet eine einfache, aber effektive Möglichkeit, ein AE‑Signal basierend auf einem Index auf einen von fünf Ausgängen zu leiten. Durch die generische Implementierung und die Verwendung von Adaptern eignet er sich besonders für modulare Steuerungsapplikationen, die eine flexible, nachträgliche Erweiterung der Kanalzahl erlauben.