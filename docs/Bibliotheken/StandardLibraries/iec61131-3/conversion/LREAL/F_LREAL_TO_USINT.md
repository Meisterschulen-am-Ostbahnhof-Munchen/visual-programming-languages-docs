# F_LREAL_TO_USINT

```{index} single: F_LREAL_TO_USINT
```

<img width="1463" height="214" alt="F_LREAL_TO_USINT" src="https://github.com/user-attachments/assets/65089d2d-a285-4427-8a17-fbb9a66adf8b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LREAL_TO_USINT` dient der Konvertierung eines LREAL-Wertes (64-Bit Gleitkommazahl) in einen USINT-Wert (8-Bit vorzeichenlose Ganzzahl). Diese Konvertierung ist besonders nützlich, wenn Gleitkommazahlen in vorzeichenlose Ganzzahlen umgewandelt werden müssen, z.B. für die Steuerung von Hardware-Registern oder die Kommunikation mit Systemen, die nur Ganzzahlen verarbeiten können.

![F_LREAL_TO_USINT](F_LREAL_TO_USINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: LREAL (64-Bit Gleitkommazahl) – Der Eingabewert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: USINT (8-Bit vorzeichenlose Ganzzahl) – Das Ergebnis der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der Algorithmus `REQ` ausgeführt wird, sobald das Ereignis `REQ` eintrifft. Der Algorithmus wandelt den LREAL-Wert `IN` mit der Funktion `LREAL_TO_USINT` in einen USINT-Wert um und speichert das Ergebnis in `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung schneidet den Gleitkommawert auf einen 8-Bit vorzeichenlosen Integer zu. Es ist zu beachten, dass Werte außerhalb des Bereichs von 0 bis 255 zu unerwarteten Ergebnissen führen können (Überlauf/Unterlauf).
- Der Block ist als einfacher Funktionsblock (SimpleFB) implementiert und verwendet einen ST-Algorithmus für die Konvertierung.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von Sensorwerten (z.B. Temperatur, Spannung) in vorzeichenlose Ganzzahlen für die Ansteuerung von Hardware.
- Kommunikation mit Systemen, die nur Ganzzahlen verarbeiten können (z.B. ältere Steuerungen oder Protokolle).
- Datenreduktion, wenn eine hohe Präzision nicht erforderlich ist.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_REAL_TO_USINT` (Konvertierung von 32-Bit Gleitkommazahlen) bietet dieser Block eine höhere Eingangspräzision durch die Verwendung von 64-Bit Gleitkommazahlen.
- Ähnliche Blöcke wie `F_LREAL_TO_INT` oder `F_LREAL_TO_UINT` bieten Konvertierungen in andere Ganzzahltypen mit unterschiedlichen Wertebereichen.




## 🛠️ Zugehörige Übungen

* [Uebung_126b_sub](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_126b_sub.md)

## Fazit
Der `F_LREAL_TO_USINT`-Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Konvertierung von 64-Bit Gleitkommazahlen in 8-Bit vorzeichenlose Ganzzahlen. Er eignet sich besonders für Anwendungen, bei denen eine begrenzte Ausgabegröße erforderlich ist, jedoch sollte der Wertebereich des Eingangssignals beachtet werden, um Überläufe zu vermeiden.