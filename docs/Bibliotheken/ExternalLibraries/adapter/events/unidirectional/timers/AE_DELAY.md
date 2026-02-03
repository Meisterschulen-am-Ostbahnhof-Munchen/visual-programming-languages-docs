# AE_DELAY

![AE_DELAY](AE_DELAY.png)


![AE_DELAY](.././AE_DELAY.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AE_DELAY** ist ein Wrapper für den Standard-IEC-61499-Baustein `E_DELAY`, der speziell für die Verwendung mit **Event-Adaptern (AE)** konzipiert wurde. Er ermöglicht die verzögerte Weiterleitung von Ereignissen innerhalb einer adapterbasierten Architektur. Anstatt herkömmlicher Ereignis-Pins verwendet dieser Baustein Adapter-Sockets und -Plugs, um Start- und Stopp-Signale zu empfangen und das verzögerte Ereignis auszugeben.

## Schnittstellenstruktur

Der Baustein kapselt die Funktionalität eines Einschaltverzögerungs-Timers (On-Delay Timer) in Adapter-Schnittstellen.

### **Ereignis-Eingänge**

| Name | Kommentar |
| :--- | :--- |
| **REQ** | Dient zur Aktualisierung des Zeitwerts am Dateneingang `DT`. |

### **Ereignis-Ausgänge**

Dieser Baustein verfügt über keine direkten Ereignis-Ausgänge auf der Hauptebene. Alle Ausgangsereignisse werden über den Adapter `EO` geleitet.

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
| :--- | :--- | :--- |
| **DT** | TIME | **Delay Time**: Die Zeitdauer, um die das Eingangsereignis verzögert werden soll. |

### **Daten-Ausgänge**

Dieser Baustein verfügt über keine Daten-Ausgänge.

### **Adapter**

| Name | Typ | Art | Kommentar |
| :--- | :--- | :--- | :--- |
| **START** | adapter::types::unidirectional::AE | Socket (Eingang) | Startet die Zeitverzögerung (löst intern `START` aus). |
| **STOP** | adapter::types::unidirectional::AE | Socket (Eingang) | Stoppt/bricht die Zeitverzögerung ab (löst intern `STOP` aus). |
| **EO** | adapter::types::unidirectional::AE | Plug (Ausgang) | **Event Output**: Gibt das Ereignis nach Ablauf der Zeit `DT` aus. |

## Funktionsweise

Der **AE_DELAY** Baustein agiert als Brücke zwischen der Adapter-Welt und dem klassischen `E_DELAY` Timer:

1.  **Initialisierung:** Über den Dateneingang `DT` wird die gewünschte Verzögerungszeit festgelegt. Dies kann über das Ereignis `REQ` aktualisiert werden.
2.  **Starten des Timers:** Trifft ein Ereignis (üblicherweise `E1`) am Adapter-Socket **START** ein, wird dieses intern an den `START`-Eingang des eingebetteten `E_DELAY` Bausteins weitergeleitet. Der Timer beginnt zu laufen.
3.  **Ablauf der Zeit:** Sobald die Zeit `DT` verstrichen ist, generiert der interne Timer ein Ereignis. Dieses wird an den Adapter-Plug **EO** (Ereignis `E1`) weitergeleitet.
4.  **Abbrechen:** Trifft ein Ereignis am Adapter-Socket **STOP** ein, wird der laufende Timer sofort unterbrochen und zurückgesetzt. Es wird kein Ereignis am Ausgang `EO` generiert.

## Technische Besonderheiten

*   **Paket-Zugehörigkeit:** Der Baustein ist Teil des Pakets `adapter::events::unidirectional::timers`.
*   **Kapselung:** Er enthält eine Instanz von `iec61499::events::E_DELAY`.
*   **Adapter-Typ:** Verwendet den unidirektionalen Ereignis-Adapter `AE` (`adapter::types::unidirectional::AE`), der typischerweise ein einzelnes Ereignis (`E1`) transportiert.

## Zustandsübersicht

Der Baustein selbst besitzt keine explizite Zustandsmaschine (ECC), da es sich um ein zusammengesetztes Netzwerk (Composite FB) handelt. Das Verhalten wird vollständig durch den internen `E_DELAY` bestimmt:

*   **Idle:** Warten auf ein Ereignis am `START`-Adapter.
*   **Timing:** Nach Empfang eines Signals an `START` läuft die Zeit `DT`.
*   **Triggered:** Nach Ablauf von `DT` wird das Signal an `EO` gesendet und der Baustein kehrt in den Idle-Zustand zurück.
*   **Reset:** Ein Signal an `STOP` während der Phase *Timing* setzt den Baustein sofort in den Idle-Zustand zurück.

## Anwendungsszenarien

*   **Adapter-basierte Steuerungen:** Ideal für Systeme, die stark auf Adapter-Verbindungen setzen, um den "Spaghetti-Code" von Einzelverbindungen zu reduzieren.
*   **Verzögerte Signalketten:** Einfügen von Wartezeiten in einer Ereigniskette, die logisch durch Adapter gruppiert ist.
*   **Prozesssteuerung:** Verzögertes Starten von Aggregaten oder Prozessen, die über standardisierte AE-Schnittstellen angesteuert werden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Baustein | Unterschied |
| :--- | :--- |
| **E_DELAY** | Der Standard-Baustein mit direkten Event-Pins (START, STOP, EO). **AE_DELAY** ist der Wrapper hierfür. |
| **E_CYCLE** | Erzeugt periodische Ereignisse, während **AE_DELAY** ein Ereignis nur einmalig verzögert weiterleitet. |
| **AE_SPLIT** | Dient zum Aufteilen von Adapter-Ereignissen, bietet aber keine Zeitverzögerung. |

## Fazit

Der **AE_DELAY** ist ein unverzichtbarer Hilfsbaustein für Entwickler, die die Vorteile von 4diac-Adaptern (reduzierte Verbindungskomplexität, klare Schnittstellendefinitionen) nutzen möchten, ohne auf grundlegende Zeitfunktionen wie Verzögerungen verzichten zu müssen. Er integriert den bewährten `E_DELAY` nahtlos in moderne, adapterbasierte Applikationsdesigns.