# AUI_MUL_3


![AUI_MUL_3](./AUI_MUL_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUI_MUL_3` dient der mathematischen Multiplikation von drei Eingangswerten. Es handelt sich um einen generischen Funktionsbaustein (Generic FB), der auf der übergeordneten Klasse `GEN_AUI_MUL` basiert. Die Besonderheit dieses Bausteins liegt in der Verwendung von unidirektionalen Adaptern des Typs `AUI` (Adapter Unidirectional Interface), welche sowohl die Daten als auch die dazugehörigen Ereignisse kapseln. Dies sorgt für eine übersichtliche und modulare Strukturierung innerhalb von 4diac-Anwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*Dieser Funktionsbaustein besitzt keine direkten, dedizierten Ereignis-Eingänge. Die Ereignissteuerung wird vollständig über die angeschlossenen Adapter abgewickelt.*

### **Ereignis-Ausgänge**

*Dieser Funktionsbaustein besitzt keine direkten, dedizierten Ereignis-Ausgänge. Die Ereignisweiterleitung erfolgt über den Ausgangs-Adapter.*

### **Daten-Eingänge**

*Es sind keine direkten Daten-Eingänge vorhanden. Die Datenübergabe erfolgt über die Eingangs-Adapter.*

### **Daten-Ausgänge**

*Es sind keine direkten Daten-Ausgänge vorhanden. Die Datenausgabe erfolgt über den Ausgangs-Adapter.*

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**

- **IN1** (Typ: `adapter::types::unidirectional::AUI`): Erster Multiplikand.
- **IN2** (Typ: `adapter::types::unidirectional::AUI`): Zweiter Multiplikand.
- **IN3** (Typ: `adapter::types::unidirectional::AUI`): Dritter Multiplikand.

#### **Plugs (Ausgangs-Schnittstelle)**

- **OUT** (Typ: `adapter::types::unidirectional::AUI`): Ergebnis der Multiplikation ($OUT = IN1 \cdot IN2 \cdot IN3$).

---

## Funktionsweise

Sobald an einem der Eingangs-Adapter (`IN1`, `IN2` oder `IN3`) ein neues Ereignis signalisiert wird, liest der Funktionsbaustein die aktuellen Werte der drei Eingänge aus.
Es wird die arithmetische Multiplikation berechnet:

$$\text{Ergebnis} = \text{Wert}(IN1) \cdot \text{Wert}(IN2) \cdot \text{Wert}(IN3)$$

Das Ergebnis wird an den Ausgangs-Adapter `OUT` übergeben, und ein entsprechendes Ausgangsereignis wird über diesen Adapter getriggert, um nachfolgende Bausteine über die Aktualisierung zu informieren.

Da der Baustein als generisch (`GEN_AUI_MUL`) deklariert ist, passt er sich flexibel an die Datentypen der verbundenen Adapter an (z. B. `INT`, `REAL`, `LREAL`), solange diese vom genutzten Adaptertyp unterstützt werden.

---

## Technische Besonderheiten

- **Generischer Typ:** Durch die Definition als generischer Baustein kann er flexibel für verschiedene numerische Datentypen eingesetzt werden, ohne dass für jeden Typ ein eigener Baustein erstellt werden muss.
- **Kapselung durch Adapter:** Die Verwendung der unidirektionalen `AUI`-Adapter reduziert die Anzahl der sichtbaren Verbindungslinien im 4diac-Editor signifikant, da Daten und Trigger-Ereignisse in einer einzigen Verbindung gebündelt sind.

---

## Zustandsübersicht

Der Baustein arbeitet rein ereignisgesteuert:

1. **Wartezustand:** Der Baustein wartet auf ein Trigger-Ereignis an einem der Sockets (`IN1`, `IN2`, `IN3`).
2. **Berechnung:** Nach dem Eintreffen eines Ereignisses werden die Daten ausgelesen und multipliziert.
3. **Ausgabe:** Das Ergebnis wird an den Plug `OUT` angelegt, das Sende-Ereignis des Plugs wird ausgelöst, und der Baustein kehrt in den Wartezustand zurück.

---

## Anwendungsszenarien

- **Volumenberechnung:** Berechnung eines dreidimensionalen Volumens (Länge $\cdot$ Breite $\cdot$ Höhe) in Förder- oder Abfüllanlagen.
- **Mehrstufige Skalierung:** Multiplikation eines Sensor-Rohwertes mit einem Kalibrierungsfaktor und einem zusätzlichen Umrechnungsfaktor (z. B. für Maßeinheiten).
- **Leistungsberechnungen:** Berechnung von physikalischen Größen im dreiphasigen System oder unter Einbezug von Wirkungsgraden.

---

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem klassischen, nicht-generischen IEC 61131-3 `MUL`-Standardbaustein bietet der `AUI_MUL_3`:

- **Weniger Kaskadierung:** Standard-Multiplizierer besitzen oft nur zwei Eingänge. Um drei Werte zu multiplizieren, müssten zwei Bausteine kaskadiert werden. `AUI_MUL_3` erledigt dies in einem Schritt.
- **Bessere Übersicht:** Während klassische Bausteine getrennte Event- und Datenleitungen benötigen, vereinfacht das hier genutzte Adapterkonzept das visuelle Applikationsdesign in der 4diac-IDE erheblich.

---

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der `AUI_MUL_3` ist ein hocheffizienter und wiederverwendbarer Funktionsbaustein für arithmetische Berechnungen. Durch die Kombination aus generischer Datenverarbeitung und moderner Adapter-Technologie eignet er sich ideal für saubere, übersichtliche und wartbare Steuerungsarchitekturen in IEC 61499-Umgebungen.
