# AIWS_DEMUX_5


![AIWS_DEMUX_5](./AIWS_DEMUX_5.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AIWS_DEMUX_5 ist ein generischer Demultiplexer für den Datentyp **AIWS**. Er verteilt einen eingehenden Datenstrom, der über einen unidirektionalen Adapter bereitgestellt wird, auf einen von fünf möglichen Ausgangsadaptern. Die Auswahl des Zielausgangs erfolgt über einen Index `K`, der bei einem Ereignis am Eingang `REQ` ausgewertet wird. Die Bestätigung der erfolgreichen Weiterleitung erfolgt über den Ereignisausgang `CNF`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
| :--- | :--- |
| REQ | Startet die Demultiplex-Operation. Der aktuelle Wert von `K` bestimmt, an welchen Ausgang der eingehende Datenwert weitergeleitet wird. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
| :--- | :--- |
| CNF | Bestätigt, dass die Demultiplex-Operation abgeschlossen ist und der Datenwert an den ausgewählten Ausgang gesendet wurde. |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
| :--- | :--- | :--- |
| K | UINT | Index des gewünschten Ausgangs (Wertebereich 1–5). |

### **Daten-Ausgänge**

Keine Datenausgänge vorhanden.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
| :--- | :--- | :--- | :--- |
| Socket (Eingang) | IN | adapter::types::unidirectional::AIWS | Der eingehende Datenwert, der demultiplext werden soll. |
| Plug (Ausgang 1) | OUT1 | adapter::types::unidirectional::AIWS | Zielausgang 1 für den eingehenden Datenwert (wenn `K = 1`). |
| Plug (Ausgang 2) | OUT2 | adapter::types::unidirectional::AIWS | Zielausgang 2 (wenn `K = 2`). |
| Plug (Ausgang 3) | OUT3 | adapter::types::unidirectional::AIWS | Zielausgang 3 (wenn `K = 3`). |
| Plug (Ausgang 4) | OUT4 | adapter::types::unidirectional::AIWS | Zielausgang 4 (wenn `K = 4`). |
| Plug (Ausgang 5) | OUT5 | adapter::types::unidirectional::AIWS | Zielausgang 5 (wenn `K = 5`). |

## Funktionsweise

1. Der FB wartet auf ein Ereignis am Eingang `REQ`.
2. Gleichzeitig wird der anliegende Index `K` (1–5) eingelesen.
3. Der aktuelle Wert, der über den Socket `IN` (Adapter) empfangen wird, wird auf den Plug `OUTx` weitergeleitet, dessen Nummer dem Wert von `K` entspricht.
4. Nach erfolgreicher Weiterleitung wird ein Ereignis am Ausgang `CNF` ausgegeben.
5. Falls der Wert von `K` außerhalb des gültigen Bereichs (1–5) liegt, wird das Ereignis inkonsistent behandelt (kein Ausgang geschrieben, `CNF` wird dennoch gesendet – dies ist abhängig von der konkreten Implementierung).

Die verwendeten Adapter sind unidirektional, d. h. die Daten fließen nur vom Socket zum Plug. Es findet keine Rückkopplung oder Quittierung über den Adapter statt.

## Technische Besonderheiten

- **Generischer FB**: Der Baustein trägt das Attribut `GenericClassName` und kann in einem generischen Kontext als Vorlage verwendet werden.
- **Adapterbasierte Kommunikation**: Statt direkter Datenports wird ein Adaptertyp (`unidirectional::AIWS`) genutzt, was eine flexible Kopplung mit anderen Bausteinen desselben Protokolls ermöglicht.
- **Keine Zustandsmaschine**: Die Aktion erfolgt ereignisgesteuert und ohne Zustandsbehaftung. Die Auswahl des Ausgangs und die Weiterleitung sind deterministisch.

## Zustandsübersicht

Der Funktionsblock besitzt keine explizite, im ECC definierte Zustandsmaschine. Die Operation wird **rein funktional** durchgeführt: Bei jedem `REQ`-Ereignis wird der Index ausgewertet und der Datenwert sofort an den entsprechenden Ausgang gesendet. Der FB bleibt nach dem `CNF`-Ereignis bereit für den nächsten Aufruf.

## Anwendungsszenarien

- **Protokolldemultiplexing**: Ein Datenstrom von einem Sensor (z. B. über einen Bus) soll je nach Konfiguration an verschiedene nachgelagerte Verarbeitungseinheiten verteilt werden.
- **Test- und Simulationsumgebungen**: Einspeisen eines einzelnen Datenpfades in mehrere parallele Prüfkanäle.
- **Steuerung von Mehrfachaktoren**: Ein analoger Sollwert wird je nach Index an verschiedene Stelleinheiten weitergegeben.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Typ | Auswahlkriterium |
| :--- | :--- | :--- |
| `AIWS_DEMUX_5` | Demultiplexer (1→5) | Index am Ereigniseingang |
| `AIWS_MUX_5` | Multiplexer (5→1) | Index zur Auswahl der Quelle |
| `AIWS_SWITCH` | Umschalter (1→1) | Binäre Entscheidung |

Der `AIWS_DEMUX_5` ist speziell für die gleichzeitige Bereitstellung von fünf unidirektionalen Ausgängen ausgelegt, während ein reiner Switch nur zwei Wege bietet. Im Gegensatz zum Multiplexer wird hier eine Eingangsquelle auf einen von vielen Ausgängen verteilt.

## Fazit

Der `AIWS_DEMUX_5` ist ein strukturierter, generischer Demultiplexer für den unidirektionalen AIWS-Adapterdatentyp. Er ermöglicht die flexible Aufteilung eines eingehenden Datenstroms auf bis zu fünf Ziele, gesteuert durch einen externen Index. Dank der Adaptertechnik und der einfachen ereignisgesteuerten Schnittstelle lässt er sich leicht in komplexe Automatisierungs- und Datenverarbeitungssysteme integrieren.