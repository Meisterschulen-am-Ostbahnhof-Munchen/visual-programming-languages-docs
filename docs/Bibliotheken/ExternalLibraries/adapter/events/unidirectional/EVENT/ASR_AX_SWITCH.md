# ASR_AX_SWITCH


![ASR_AX_SWITCH](./ASR_AX_SWITCH.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ASR_AX_SWITCH** dient als Demultiplexer für asynchrone Set/Reset-Ereignisse (ASR). Er leitet ein eingehendes SET- oder RESET-Ereignis basierend auf dem Zustand eines binären Steuereingangs **G** wahlweise an einen von zwei Ausgängen (**EO0** oder **EO1**) weiter. Der Baustein ermöglicht eine bedarfsgerechte Verteilung von Steuersignalen in Automatisierungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine klassischen Ereignis-Eingänge über *EventInputs* – die Ereignisse werden über den **Socket-Adapter `EI`** vom Typ `ASR` empfangen. Dieser Adapter stellt die beiden Ereignisse `SET` und `RESET` bereit.

### **Ereignis-Ausgänge**

Die Ereignis-Ausgänge werden über die **Plug-Adapter `EO0`** und **`EO1`** (beide Typ `ASR`) bereitgestellt. Jeder dieser Adapter verfügt über die Ausgänge `SET` und `RESET`:

| Adapter | Ereignis | Beschreibung |
|---------|----------|--------------|
| `EO0.SET` | SET | Wird ausgelöst, wenn ein `EI.SET`-Ereignis eintrifft und `G.D1 == 0` |
| `EO0.RESET` | RESET | Wird ausgelöst, wenn ein `EI.RESET`-Ereignis eintrifft und `G.D1 == 0` |
| `EO1.SET` | SET | Wird ausgelöst, wenn ein `EI.SET`-Ereignis eintrifft und `G.D1 == 1` |
| `EO1.RESET` | RESET | Wird ausgelöst, wenn ein `EI.RESET`-Ereignis eintrifft und `G.D1 == 1` |

### **Daten-Eingänge**

Der FB verfügt über keine separaten Daten-Eingänge. Die Steuergröße **G** wird über den **Socket-Adapter `G`** vom Typ `AX` bezogen – das logische Signal liegt am Datenausgang `D1` des Adapters an.

### **Daten-Ausgänge**

Es sind keine expliziten Daten-Ausgänge vorhanden. Steuerinformationen werden ausschließlich über die Ereignisausgänge der ASR-Adapter übertragen.

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
|------|----------|-----|--------------|
| `EI` | Socket (Eingang) | `adapter::types::unidirectional::ASR` | Empfängt die zu verteilenden SET-/RESET-Ereignisse |
| `G` | Socket (Eingang) | `adapter::types::unidirectional::AX` | Liefert das binäre Umschaltsignal über `D1` (0 → Kanal 0, 1 → Kanal 1) |
| `EO0` | Plug (Ausgang) | `adapter::types::unidirectional::ASR` | Ausgang für Kanal 0 (bei `G.D1 = 0`) |
| `EO1` | Plug (Ausgang) | `adapter::types::unidirectional::ASR` | Ausgang für Kanal 1 (bei `G.D1 = 1`) |

## Funktionsweise

Der FB arbeitet ereignisgesteuert. Nach dem Start befindet er sich im Zustand **START** und wartet auf eingehende Ereignisse über den `EI`-Adapter:

- **`EI.SET`** und **`EI.RESET`** werden nur dann verarbeitet, wenn gleichzeitig über den `G`-Adapter ein gültiger binärer Wert an `G.D1` anliegt.
- Die Bedingung für die Transition lautet:
  - `EI.SET[NOT G.D1]` → **G0_SET** → Ausgabe `EO0.SET`
  - `EI.SET[G.D1]` → **G1_SET** → Ausgabe `EO1.SET`
  - `EI.RESET[NOT G.D1]` → **G0_RESET** → Ausgabe `EO0.RESET`
  - `EI.RESET[G.D1]` → **G1_RESET** → Ausgabe `EO1.RESET`
- Nach dem Auslösen des Ausgangsereignisses kehrt der FB sofort in den **START**-Zustand zurück (unbedingte Transition mit `1`).
- Zusätzlich existiert eine Transition von **START** nach **START** bei **`G.E1`** – dies erlaubt eine asynchrone Aktualisierung des Steuersignals ohne sofortige Ereignisweitergabe (dient z.B. der Synchronisation oder Initialisierung).

Die Verarbeitung erfolgt deterministisch ohne Zwischenspeicherung der Ereignisse.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation**: Der FB verwendet ausschließlich Adapter (Sockets/Plugs) für Ereignis- und Datenaustausch – dies ermöglicht eine flexible Kopplung in der 4diac-IDE.
- **Keine Zustandsspeicherung**: Die Auswahl des Zielkanals erfolgt rein kombinatorisch zum Zeitpunkt des eingehenden Ereignisses. Es wird kein interner Zustand gehalten.
- **Volle Synchronität**: Nach jedem Ausgabeereignis kehrt der FB wieder in den Grundzustand zurück – es können keine Ereignisse gestapelt werden.
- **Eingebettete Lizenz**: Der Code ist unter der Eclipse Public License 2.0 veröffentlicht.

## Zustandsübersicht

| Zustand | Beschreibung | Aktion |
|---------|--------------|--------|
| **START** | Warte auf eingehendes SET/RESET-Ereignis | – |
| **G0_SET** | `EI.SET` bei `G.D1=0` empfangen | `EO0.SET` ausgeben |
| **G1_SET** | `EI.SET` bei `G.D1=1` empfangen | `EO1.SET` ausgeben |
| **G0_RESET** | `EI.RESET` bei `G.D1=0` empfangen | `EO0.RESET` ausgeben |
| **G1_RESET** | `EI.RESET` bei `G.D1=1` empfangen | `EO1.RESET` ausgeben |

Die Zustandsübergänge erfolgen nach dem ECC-Schema: Bedingung führt von START in den Aktionszustand, von dort ohne weitere Bedingung sofort zurück zu START.

## Anwendungsszenarien

- **Kanalumschaltung**: In einer modularen Steuerung soll ein zentraler Set-/Reset-Befehl je nach Betriebsmodus an verschiedene Aktoren (z.B. Ventile, Motoren) weitergeleitet werden.
- **Sicherheitslogik**: Abhängig von einem Freigabesignal (`G`) werden Resets nur an den aktiven Kanal geleitet.
- **Redundanzsteuerung**: Das Signal `G` wählt zwischen Haupt- und Ersatzkanal aus.
- **Sequenzielle Prozesse**: Mehrere Bearbeitungsstationen werden durch Umlegen von `G` nacheinander angesteuert.

## Vergleich mit ähnlichen Bausteinen

| Eigenschaft | ASR_AX_SWITCH | Einfacher Event-Multiplexer (z.B. SELECT) |
|-------------|---------------|--------------------------------------------|
| Ereignistyp | SET/RESET (ASR-Adapter) | Beliebige Einzelereignisse |
| Steuerung | Binär über AX-Adapter (mit `D1`) | Boolescher Dateneingang |
| Ausgangstyp | Zwei ASR-Adapter | Je nach Typ Einzelereignis oder mehrere |
| Zustandsbehaftet | Nein (keine Speicherung) | Meist zustandslos |
| Adapter-Schnittstelle | Ja | Oft direkt über Event-/Data-Ports |

Der ASR_AX_SWITCH ist speziell für asynchrone Set/Reset-Signale optimiert und integriert sich nahtlos in die ASR-Adapter-Welt der 4diac-Bibliothek. Gegenüber generischen Multiplexern entfällt die Notwendigkeit, die Adapter-Ereignisse manuell zu extrahieren.

## Fazit

Der **ASR_AX_SWITCH** ist ein kompakter, effizienter Demultiplexer für die gerichtete Weiterleitung von ASR-Steuerereignissen. Durch die adapterbasierte Schnittstelle und die klare Entscheidungslogik eignet er sich hervorragend für modulare Automatisierungsprojekte, bei denen ein einzelnes Steuersignal wahlweise auf verschiedene Pfade geschaltet werden muss. Die einfache Zustandsmaschine garantiert schnelle, deterministische Reaktionszeiten ohne Seiteneffekte.