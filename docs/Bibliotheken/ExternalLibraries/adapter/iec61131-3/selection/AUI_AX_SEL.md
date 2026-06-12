# AUI_AX_SEL


![AUI_AX_SEL](./AUI_AX_SEL.svg)

* * * * * * * * * *

## Einleitung
Der AUI_AX_SEL ist ein binärer Selektionsbaustein, der über einen Adapteranschluss gesteuert wird. Er wählt zwischen zwei Daten-Eingangswerten (IN0 und IN1) basierend auf einem Auswahlsignal aus und gibt den ausgewählten Wert am Daten-Ausgang OUT aus. Die Verarbeitung erfolgt ereignisgesteuert über den Adapter.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **EI0** (Event): Setzt den Daten-Eingang IN0. Der Datenwert IN0 wird bei diesem Ereignis aktualisiert.
- **EI1** (Event): Setzt den Daten-Eingang IN1.

### **Ereignis-Ausgänge**
- **CNF** (Event): Bestätigung, dass die Auswahl durchgeführt und der Ausgang OUT aktualisiert wurde.

### **Daten-Eingänge**
- **IN0** (UINT): Erster wählbarer Eingangswert.
- **IN1** (UINT): Zweiter wählbarer Eingangswert.

### **Daten-Ausgänge**
- **OUT** (UINT): Ausgewählter Wert – entweder IN0 oder IN1, abhängig vom Auswahlsignal.

### **Adapter**
- **G** (AX): Adapteranschluss für die Auswahlsteuerung. Er liefert ein Ereignis (E1) und ein Datensignal (D1), das als Auswahlkriterium dient. Typischerweise ist D1 ein BOOL-Wert: 0 wählt IN0, 1 wählt IN1.

## Funktionsweise
Der Baustein besitzt zwei Ereigniseingänge EI0 und EI1, die unabhängig voneinander die Daten-Eingänge IN0 und IN1 setzen. Die eigentliche Selektion wird jedoch nicht durch diese Ereignisse ausgelöst. Stattdessen triggert das vom Adapter G eingehende Ereignis (G.E1) die interne Verarbeitung. Bei jedem Ereignis am Adapter wird der interne Funktionsblock F_SEL (IEC 61131) aktiviert, der anhand des Adapter-Datensignals (G.D1) entscheidet, ob OUT den Wert von IN0 oder IN1 erhält. Nach erfolgreicher Berechnung wird der Ausgangs-Ereignis CNF gesendet.

## Technische Besonderheiten
- **Adapterbasierte Steuerung:** Die Auswahlbedingung wird nicht über einen separaten Dateneingang, sondern über einen Adapter realisiert. Dies ermöglicht eine flexible Kopplung mit anderen Bausteinen, die das AX-Protokoll unterstützen.
- **Asynchrone Aktualisierung:** Die Eingänge IN0 und IN1 können unabhängig von der Auswahl aktualisiert werden. Die Selektion erfolgt erst beim Eintreffen des Adapter-Ereignisses, sodass die Werte zum Zeitpunkt der Verarbeitung aktuell sind.
- **Kein interner Zustand:** Der Baustein speichert keine Zustände außer den aktuellen Werten der Eingänge.

## Zustandsübersicht
Der AUI_AX_SEL besitzt keinen expliziten Zustandsautomaten. Die Funktionalität ist rein ereignisgesteuert und kombinatorisch: Die Ausgabe wird bei jedem Adapter-Ereignis neu berechnet.

## Anwendungsszenarien
- **Sensordatenumschaltung:** Auswahl zwischen zwei verschiedenen Sensormesswerten, gesteuert durch ein externes Umschaltsignal (z. B. von einer SPS).
- **Parameterauswahl:** Dynamische Auswahl zwischen zwei Konfigurationswerten (z. B. Sollwerten) abhängig von einem Betriebsmodus.
- **Redundanzumschaltung:** Automatische Umschaltung auf einen Ersatzwert, falls ein Signal ausfällt (in Kombination mit entsprechenden Überwachungsbausteinen).

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einem Standard-Multiplexer (z. B. MUX) bietet AUI_AX_SEL eine ereignisgesteuerte Schnittstelle mit Adapteranschluss. Während MUX oft einen direkten Auswahleingang (BOOL) besitzt, erlaubt AUI_AX_SEL eine lose Kopplung über Adapter, was die Wiederverwendbarkeit und Modularität erhöht. Der interne F_SEL-Baustein entspricht der IEC 61131-Logik für binäre Auswahl.

## Fazit
Der AUI_AX_SEL ist ein nützlicher Baustein für binäre Selektionsaufgaben in IEC 61499-Umgebungen, der durch seine Adapterschnittstelle eine flexible Integration ermöglicht. Er eignet sich besonders für Szenarien, in denen das Auswahlsignal von externen Komponenten bereitgestellt wird und eine asynchrone Aktualisierung der Eingänge gewünscht ist.