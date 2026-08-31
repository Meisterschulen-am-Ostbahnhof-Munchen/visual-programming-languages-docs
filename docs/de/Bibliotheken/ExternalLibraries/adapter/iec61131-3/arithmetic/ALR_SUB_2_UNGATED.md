# ALR_SUB_2_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`ALR_SUB_2`](ALR_SUB_2.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.


![ALR_SUB_2_UNGATED](./ALR_SUB_2_UNGATED.svg)

*(Kein Bild verfügbar)*

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ALR_SUB_2_UNGATED` ist ein generischer Baustein zur Durchführung von mathematischen Subtraktionen innerhalb einer IEC 61499-Entwicklungsumgebung (wie 4diac IDE). Anstatt direkte Daten- und Ereignispins zu nutzen, basiert dieser Baustein auf einer adaptergesteuerten Architektur. Dies ermöglicht eine strukturierte und saubere Kapselung von Signalen und vereinfacht die Verdrahtung in komplexen Steuerungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Baustein besitzt keine direkten Ereignis-Eingänge. Die Steuerung und Triggerung erfolgt über die angeschlossenen Adapter.*

### **Ereignis-Ausgänge**

*Dieser Baustein besitzt keine direkten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

- **IN1** (Typ: `adapter::types::unidirectional::ALR`):
  Der erste Eingangswert (Minuend) der Subtraktion. Über diesen Adapter werden sowohl der Wert als auch das auslösende Ereignis empfangen.
- **IN2** (Typ: `adapter::types::unidirectional::ALR`):
  Der zweite Eingangswert (Subtrahend), der vom ersten Wert abgezogen werden soll.

#### **Plugs (Ausgangs-Adapter)**

- **OUT** (Typ: `adapter::types::unidirectional::ALR`):
  Das Ergebnis der Subtraktion (Differenz). Dieser Adapter gibt das berechnete Ergebnis mitsamt dem zugehörigen Ausgangsereignis aus.

## Funktionsweise

Die interne Logik des Bausteins berechnet die Differenz aus den beiden über die Sockets bereitgestellten Werten. Die mathematische Formel lautet:

$$\text{OUT} = \text{IN1} - \text{IN2}$$

Sobald sich die Werte an den Eingangs-Adaptern ändern oder ein entsprechendes Trigger-Ereignis an `IN1` oder `IN2` empfangen wird, führt der Baustein die Berechnung aus und aktualisiert den Wert am Ausgangs-Plug `OUT`, gefolgt von einem Ausgangsereignis.

## Technische Besonderheiten

- **Generisches Verhalten**: Der Baustein ist als generischer Typ (`GEN_ALR_SUB`) definiert. Er ist somit nicht starr auf einen Datentyp (wie z. B. nur `REAL` oder nur `INT`) festgelegt, sondern passt sich flexibel an die im Adapter `ALR` definierten Datentypen an.
- **Unidirektionale Adapter**: Durch die Verwendung von unidirektionalen Adaptern (`unidirectional::ALR`) wird der Datenfluss klar in eine Richtung gelenkt, was die Systemstabilität erhöht und unnötigen Kommunikations-Overhead minimiert.

## Zustandsübersicht

Da es sich bei `ALR_SUB_2_UNGATED` um einen rein mathematischen, datenflussorientierten Funktionsbaustein handelt, besitzt er keinen internen Zustandsautomaten (ECC - Execution Control Chart). Die Abarbeitung erfolgt rein ereignis- und datengesteuert.

## Anwendungsszenarien

- **Regelungstechnik (Berechnung der Regelabweichung)**:
  Ermittlung der Differenz zwischen einem Sollwert (Führungsgröße an `IN1`) und einem Istwert (Regelgröße an `IN2`), um die Regelabweichung am Ausgang `OUT` für einen nachgelagerten PID-Regler bereitzustellen.
- **Differenzmessungen**:
  Berechnung von physikalischen Differenzwerten, beispielsweise zur Ermittlung des Druckabfalls über einem Filter (Druck vor dem Filter an `IN1` minus Druck nach dem Filter an `IN2`).
- **Offset-Korrektur**:
  Abzug eines konstanten oder variablen Korrekturwertes von einem analogen Rohsignal.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu klassischen IEC 61131-3 Subtraktionsbausteinen (wie z. B. `SUB`), die mit Standard-Datentypen und direkten Pins arbeiten, bietet der `ALR_SUB_2_UNGATED` durch die Kapselung in Adaptern erhebliche Vorteile bei der Übersichtlichkeit des Programmcodes. Komplexe Signaladern (Daten + Ereignis) werden in einer einzigen Adapterverbindung gebündelt.

Gegenüber bidirektionalen Berechnungsbausteinen zeichnet sich der `ALR_SUB_2_UNGATED` durch eine deterministische, rückwirkungsfreie Signalverarbeitung aus.

- **[`ALR_SUB_2`](ALR_SUB_2.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `ALR_SUB_2_UNGATED` ist ein effizienter und flexibel einsetzbarer Standardbaustein für arithmetische Berechnungen in modernen, serviceorientierten Steuerungssystemen. Durch die Nutzung der Adapter-Technologie unterstützt er ein modulares und wartungsfreundliches Softwaredesign nach dem IEC 61499-Standard.
