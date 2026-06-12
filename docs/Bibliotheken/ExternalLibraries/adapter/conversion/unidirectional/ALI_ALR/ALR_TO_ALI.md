# ALR_TO_ALI


![ALR_TO_ALI](./ALR_TO_ALI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **ALR_TO_ALI** ist ein Composite-Baustein, der eine Adapter-Konvertierung von **ALR (LREAL)** nach **ALI (LINT)** realisiert. Er ermöglicht die einfache und strukturierte Integration einer LREAL-basierten Adapter-Schnittstelle in eine LINT-basierte Umgebung, ohne dass die Konvertierungslogik selbst implementiert werden muss. Der Baustein ist für den Einsatz in IEC 61499 basierten Industriesteuerungen konzipiert und nutzt den internen Funktionbaustein `F_LREAL_TO_LINT` nach IEC 61131-3.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keine expliziten Ereignis-Eingänge. Das auslösende Ereignis wird über den eingehenden Adapter **ALR_IN** (Typ `adapter::types::unidirectional::ALR`) bereitgestellt:

- **ALR_IN.E1** – Eingangsereignis, das die Konvertierung startet.

### **Ereignis-Ausgänge**
Der FB besitzt keine expliziten Ereignis-Ausgänge. Das Bestätigungsereignis wird über den ausgehenden Adapter **ALI_OUT** (Typ `adapter::types::unidirectional::ALI`) bereitgestellt:

- **ALI_OUT.E1** – Ausgangsereignis, das die Fertigstellung der Konvertierung signalisiert.

### **Daten-Eingänge**
Der FB besitzt keinen expliziten Daten-Eingang. Der Eingangswert wird über den Adapter **ALR_IN** zur Verfügung gestellt:

- **ALR_IN.D1** – Wert vom Typ LREAL, der in LINT konvertiert werden soll.

### **Daten-Ausgänge**
Der FB besitzt keinen expliziten Daten-Ausgang. Das Ergebnis wird über den Adapter **ALI_OUT** ausgegeben:

- **ALI_OUT.D1** – konvertierter Wert vom Typ LINT.

### **Adapter**
| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | ALR_IN | `adapter::types::unidirectional::ALR` | Unidirektionaler Adapter für LREAL-Daten und Ereignisse. Enthält Ereignis-Port E1 und Daten-Port D1 (LREAL). |
| Plug (Ausgang) | ALI_OUT | `adapter::types::unidirectional::ALI` | Unidirektionaler Adapter für LINT-Daten und Ereignisse. Enthält Ereignis-Port E1 und Daten-Port D1 (LINT). |

## Funktionsweise
Der FB arbeitet als reiner „Wrapper“ für die Typkonvertierung von LREAL nach LINT. Das Ablaufdiagramm ist wie folgt:

1. Ein Ereignis (E1) auf dem Eingangsadapter **ALR_IN** triggert den internen Baustein **Convert** (Typ `iec61131::conversion::F_LREAL_TO_LINT`).
2. Der Datenwert von **ALR_IN.D1** (LREAL) wird an den Eingang **Convert.IN** übergeben.
3. Der interne Baustein führt die Konvertierung durch und liefert das Ergebnis an **Convert.OUT**.
4. Das Ereignis am Ausgang **Convert.CNF** wird an **ALI_OUT.E1** weitergeleitet, sodass der ausgehende Adapter die fertige Konvertierung signalisiert.
5. Der konvertierte LINT-Wert steht an **ALI_OUT.D1** zur Verfügung.

Die Aufrufsteuerung erfolgt über die Ereignisverkettung (E1 → REQ → CNF → E1), sodass die Konvertierung blockierend innerhalb eines Ausführungszyklus erfolgt.

## Technische Besonderheiten
- **Composite-Struktur**: Der Baustein ist als Composite (Netzwerk) realisiert und nutzt intern den Standardbaustein `F_LREAL_TO_LINT` aus der IEC 61131-3-Bibliothek.
- **Adapterkapselung**: Durch die Adaptertechnik können die konkreten LREAL- und LINT-Signale über standardisierte Schnittstellen (ALR, ALI) angebunden werden, was eine hohe Wiederverwendbarkeit und Austauschbarkeit ermöglicht.
- **Lizenz**: Der Quelltext steht unter der Eclipse Public License 2.0 (EPL-2.0).
- **Version**: 1.0, veröffentlicht am 17.02.2026 durch HR Agrartechnik GmbH, Autor: Franz Höpfinger.
- **Paketstruktur**: `adapter::conversion::unidirectional`.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten, da er als Netzwerk von einem einzigen internen FB realisiert wird. Das Verhalten ist rein ereignisgesteuert:

- **Idle**: Warten auf ein Ereignis am Eingangsadapter (ALR_IN.E1).
- **Processing**: Nach Eintreffen des Ereignisses wird der interne Konvertierungsbaustein aktiviert.
- **Done**: Nach Abschluss (CNF) wird das Ausgangsereignis (ALI_OUT.E1) gesetzt und der Baustein kehrt in den Idle-Zustand zurück.

Ein expliziter Fehlerzustand existiert nicht, da der Konvertierungsbaustein `F_LREAL_TO_LINT` keine Fehlerbehandlung vorsieht.

## Anwendungsszenarien
- **Migration**: Austausch eines ALI-basierten (LINT) Systems gegen ein ALR-basiertes (LREAL) System oder umgekehrt, ohne Änderung der übergeordneten Logik.
- **Adapter-Brücke**: Wenn eine Komponente nur LREAL-Werte liefert, der nachfolgende Adapter aber LINT erwartet, kann dieser FB dazwischen geschaltet werden.
- **Standardisierte Konvertierung**: In Bibliotheken oder Frameworks, die eine einheitliche Umsetzung von Typkonvertierungen über Adapter fordern.

## Vergleich mit ähnlichen Bausteinen
In der IEC 61499- und IEC 61131-Welt existieren zahlreiche Konvertierungsbausteine:

- **F_LREAL_TO_LINT** (direkt): Einzelner Baustein, der einen einfachen Wert konvertiert, aber keine Adapter-Schnittstelle bietet.
- **ALR_TO_ALI** (dieser FB): Kapselt den direkten Baustein in eine Adapter-Struktur, sodass die Anbindung über einheitliche Adapter-Ports erfolgt.
- **Weitere Typkonvertierungen**: Ähnlich aufgebaute Bausteine für z.B. REAL → DINT oder LREAL → DWORD können nach demselben Muster erstellt werden.

Der entscheidende Vorteil von **ALR_TO_ALI** ist die Wiederverwendbarkeit im Adapterkontext und die saubere Trennung von Ereignis und Daten.

## Fazit
Der Funktionsbaustein **ALR_TO_ALI** ist ein nützlicher Composite-Baustein, der eine saubere und standardisierte Adapterkonvertierung von LREAL nach LINT ermöglicht. Er erbt die Robustheit des IEC 61131-3-Konvertierungsbausteins und integriert ihn nahtlos in die adapterbasierte Kommunikationsstruktur. Durch seine offene Lizenz und die klare Schnittstelle eignet er sich gut für den Einsatz in modularen Automatisierungslösungen.