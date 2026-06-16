# AL_DEMUX_2


![AL_DEMUX_2](./AL_DEMUX_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AL_DEMUX_2** ist ein generischer AL-Demultiplexer. Er leitet einen über einen Adapter-Socket eingehenden Datenstrom wahlweise an einen von zwei Adapter-Plugs weiter. Die Auswahl des Ausgangs erfolgt über einen Index-Parameter, der durch ein Ereignis gesetzt und aktiviert wird. Der Baustein ist für den Einsatz in automatisierten Systemen konzipiert, bei denen Datenpfad-Umschaltungen auf Basis diskreter Steuersignale erforderlich sind.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Datenparameter | Beschreibung |
|----------|----------------|--------------|
| `REQ` | `K` | Setzt den Index `K` und startet die Weiterleitung des aktuellen Werts vom Eingang an den entsprechenden Ausgang. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF` | Bestätigt die erfolgreiche Umschaltung und Weiterleitung des Wertes. |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `K` | `UINT` | Index zur Auswahl des Ausgangs (0 → OUT1, 1 → OUT2). |

### **Daten-Ausgänge**
Keine eigenen Datenausgänge. Die Datenweitergabe erfolgt ausschließlich über die Adapter-Plugs.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket   | `IN` | `adapter::types::unidirectional::AL` | Eingangsadapter, der den zu demultiplexenden Wert bereitstellt. |
| Plug     | `OUT1` | `adapter::types::unidirectional::AL` | Erster Ausgang (aktiv bei K = 0). |
| Plug     | `OUT2` | `adapter::types::unidirectional::AL` | Zweiter Ausgang (aktiv bei K = 1). |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
1. Im Ruhezustand wartet er auf das Ereignis `REQ`.
2. Bei Eintreffen von `REQ` wird der an `K` anliegende Wert ausgelesen.
3. Der aktuelle Wert des Eingangsadapter `IN` wird auf den durch `K` bestimmten Ausgangsadapter (`OUT1` bei K=0, `OUT2` bei K=1) kopiert.
4. Nach erfolgreicher Weiterleitung wird das Bestätigungsereignis `CNF` gesendet.

Handelt es sich bei `K` um einen Wert außerhalb des gültigen Bereichs (≥2), erfolgt keine Weiterleitung und es wird kein `CNF` ausgelöst (oder das Verhalten ist anwendungsspezifisch).

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AL_DEMUX`) deklariert und kann für verschiedene AL-Adapter-Varianten wiederverwendet werden.
- **Unidirektionale Adapter**: Alle verwendeten Adapter sind vom Typ `unidirectional::AL`, was bedeutet, dass Daten nur in eine Richtung fließen (vom Socket zum Plug). Dies vereinfacht die Kopplung und reduziert potentielle Nebenwirkungen.
- **Keine Zustandsmaschine in der XML**: Die Logik wird implizit durch die Ereignisverarbeitung realisiert; eine explizite ECC existiert nicht, was die Implementierung schlank hält.

## Zustandsübersicht
Eine formale Zustandsmaschine ist nicht definiert. Der Baustein verhält sich wie folgt:
- **Idle**: Warten auf `REQ`.
- **Processing**: Nach Eintreffen von `REQ` wird die Weiterleitung durchgeführt.
- **Done**: Nach erfolgreicher Weiterleitung wird `CNF` ausgegeben und der Baustein kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- **Aktuatorenselektion**: In einer Maschinensteuerung kann ein analoger oder digitaler Wert (z.B. Drehzahlvorgabe) wahlweise an zwei verschiedene Motortreiber weitergeleitet werden.
- **Datenpfadumschaltung**: In einem Messsystem, bei dem ein Sensorwert abwechselnd an zwei Auswertemodule übergeben werden muss.
- **Ressourcensparen**: Statt zwei paralleler Kommunikationskanäle kann ein Demultiplexer verwendet werden, um Hardware-Schnittstellen zu teilen.

## Vergleich mit ähnlichen Bausteinen
- **AL_MUX_2** (Multiplexer): Führt mehrere Quellen auf einen Ausgang zusammen – das Gegenstück zum Demultiplexer.
- **SIMPLE_SELECT**: Einfache Weiche auf Basis eines Booleschen Signals. AL_DEMUX_2 arbeitet dagegen mit einem ganzzahligen Index und AL-Adapter-Schnittstellen.
- **Standard-Demultiplexer in Bibliotheken**: Viele IEC-61499-Bibliotheken bieten Demultiplexer mit mehr als zwei Ausgängen (z.B. `DEMUX_4`), die jedoch oft nur einfache Datentypen und keine Adapter verwenden. Der AL_DEMUX_2 ist speziell für Adapter-basierte Anwendungen optimiert.

## Fazit
Der Funktionsbaustein **AL_DEMUX_2** stellt eine kompakte, generische Lösung zur Datenweiterleitung an zwei Adapterausgänge dar. Durch die ereignisgesteuerte Auswahl per Index eignet er sich besonders für zeitgesteuerte oder sequenzielle Umschaltvorgänge in Automatisierungssystemen. Die Verwendung von AL-Adaptern gewährleistet eine einfache Integration in bestehende Adapter-basierte Architekturen.