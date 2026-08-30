# AI_MUL_2


![AI_MUL_2](./AI_MUL_2.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AI_MUL_2` ist ein generischer arithmetischer Funktionsbaustein für die 4diac-IDE, der der Norm IEC 61131-3 entspricht. Seine Hauptaufgabe ist die Multiplikation von zwei Eingangswerten, die über unidirektionale Adapter bereitgestellt werden. Das Ergebnis dieser Multiplikation wird ebenfalls über einen unidirektionalen Adapter ausgegeben.

Durch die Verwendung von Adaptern anstelle von klassischen diskreten Ein- und Ausgängen wird die Komplexität der Verkabelung im Steuerungsentwurf erheblich reduziert, da zusammengehörige Daten und Ereignisse in einer einzigen Verbindung gebündelt werden.

## Schnittstellenstruktur

Die Schnittstelle dieses Funktionsbausteins basiert vollständig auf Adaptern. Es gibt keine direkten, klassischen Ereignis- oder Datenein- und -ausgänge auf der Bausteinoberfläche.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden (die Steuerung erfolgt über die Adapter).*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden (die Steuerung erfolgt über die Adapter).*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

| Name | Typ | Richtung (Modus) | Beschreibung |
| :--- | :--- | :--- | :--- |
| **IN1** | `adapter::types::unidirectional::AI` | Socket (Eingang) | Erster Eingangswert (Multiplikand) für die arithmetische Operation. |
| **IN2** | `adapter::types::unidirectional::AI` | Socket (Eingang) | Zweiter Eingangswert (Multiplikator) für die arithmetische Operation. |
| **OUT** | `adapter::types::unidirectional::AI` | Plug (Ausgang) | Ausgang für das berechnete Produkt der beiden Eingangswerte. |

## Funktionsweise

Der Funktionsbaustein realisiert die mathematische Multiplikation:

$$\text{OUT} = \text{IN1} \times \text{IN2}$$

Da der Baustein als generischer Funktionsbaustein (`GEN_AI_MUL`) definiert ist, kann er je nach Instanziierung und Typisierung der verwendeten Adapter unterschiedliche numerische Datentypen (z. B. `REAL`, `LREAL`, `INT` etc.) verarbeiten.

Sobald über die Eingangs-Adapter (`IN1` und/oder `IN2`) ein Aktualisierungsereignis empfangen wird, führt der Baustein intern die Multiplikation aus und signalisiert die Aktualisierung des Ergebnisses über den Ausgangs-Adapter `OUT`.

## Technische Besonderheiten

- **Generische Implementierung:** Der Baustein nutzt die Klasse `GEN_AI_MUL`. Dies ermöglicht eine hohe Flexibilität, da der konkrete Datentyp erst bei der Verwendung im System bestimmt wird.
- **Unidirektionale Adapter:** Die Schnittstellen nutzen den Typ `adapter::types::unidirectional::AI`. Das bedeutet, dass der Informationsfluss strikt in eine Richtung verläuft, was die Systemstabilität und die Performance erhöht.
- **Kapselung:** Durch das Fehlen einzelner Signal-Pins bleibt das Anwendungsdiagramm auch bei vielen mathematischen Operationen übersichtlich und aufgeräumt.

## Zustandsübersicht

Der Baustein verhält sich im Wesentlichen zustandslos (analogen Charakter aufweisend):
- **Initialisierung / Ruhezustand:** Der Baustein wartet auf eingehende Werte über die Adapter `IN1` und `IN2`.
- **Berechnung:** Bei Eintreffen eines neuen Wertes oder Triggersignals an den Sockets wird das Produkt neu berechnet.
- **Ausgabe:** Das Ergebnis wird unmittelbar an den Plug `OUT` übergeben und ein entsprechendes Ausgangsereignis im Adapter getriggert.

## Anwendungsszenarien

- **Skalierung von Sensorwerten:** Multiplikation eines analogen Rohwertes (z. B. von einem Stromeingang 4–20 mA) mit einem Skalierungsfaktor zur Umrechnung in eine physikalische Größe.
- **Berechnung physikalischer Größen:** Berechnung von Leistung ($P = U \times I$) aus gemessener Spannung und Stromstärke, sofern diese über entsprechende Adapterstrukturen geliefert werden.
- **Verstärkungsglieder in Regelkreisen:** Einsatz als proportionaler Verstärkungsfaktor (P-Glied) in einer softwarebasierten Regelung.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zum Standard-IEC-61131-3-Baustein `MUL` entfällt beim `AI_MUL_2` die manuelle Verdrahtung von Trigger-Ereignissen (wie `REQ` und `CNF`) sowie der einzelnen Daten-Pins. Während ein klassischer `MUL`-Baustein für jede Verbindung separate Linien für Daten und Events benötigt, bündelt der `AI_MUL_2` diese über die `AI`-Adapter. Dies eignet sich besonders für fortgeschrittene, objektorientierte oder modularisierte Softwarearchitekturen in 4diac.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AI_MUL_2` ist ein spezialisierter, aber durch seine generische Natur dennoch flexibler Baustein zur Multiplikation zweier Werte über Adapterverbindungen. Er eignet sich hervorragend für saubere, übersichtliche Steuerungsarchitekturen, bei denen analoge Signale standardisiert über unidirektionale Adapter übertragen und verarbeitet werden sollen.
