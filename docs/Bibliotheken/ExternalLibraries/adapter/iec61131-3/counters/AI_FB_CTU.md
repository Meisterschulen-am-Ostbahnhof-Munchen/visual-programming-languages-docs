# AI_FB_CTU


![AI_FB_CTU](./AI_FB_CTU.svg)

* * * * * * * * * *
## Einleitung
Der **AI_FB_CTU** ist ein Aufwärtszähler (Up Counter) für Ganzzahlen (INT), der die IEC 61131-3 Funktionalität eines CTU (Counter Up) in einer adapterbasierten Bauform kapselt. Er ist speziell für die Verwendung in der 4diac-IDE konzipiert und erlaubt eine modulare Anbindung über unidirektionale Adapter-Schnittstellen. Der Baustein feuert bei jeder Aktualisierung seiner Eingänge (CU, R, PV) ein Bestätigungsereignis, wodurch er sich für zeitgesteuerte oder ereignisgesteuerte Zählaufgaben eignet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt ausschließlich über die Adapter-Sockets **CU**, **R** und **PV**. Jeder dieser Sockets liefert ein Ereignis (E1), das den internen Ablauf auslöst.

- **CU.E1** – Zählimpuls (Ereignis vom counting-up Adapter)
- **R.E1** – Rücksetzen (Ereignis vom Reset Adapter)
- **PV.E1** – Vorgabe des Preset-Werts (Ereignis vom Preset-Value Adapter)

### **Ereignis-Ausgänge**
- **CNF** (Typ: Event) – Bestätigungsereignis, das nach jeder erfolgreichen Verarbeitung aller drei möglichen Ereignisse ausgelöst wird.

Zusätzlich werden die Ausgabeadapter **Q** und **CV** mit demselben Ereignis bedient:
- **Q.E1** – Ereignis für den Ausgangsadapter (Zählerstand erreicht oder übersteigt den Preset-Wert)
- **CV.E1** – Ereignis für den aktuellen Zählwert

### **Daten-Eingänge**
Alle Dateneingänge werden über die Adapter-Sockets bereitgestellt:

| Adapter | Daten-Eingang | Typ | Beschreibung |
|---------|---------------|-----|--------------|
| CU.D1   | CU            | INT | Count Up – Zählimpuls (wird bei jedem Ereignis inkrementiert) |
| R.D1    | R             | INT | Reset – Wert auf den der Zähler zurückgesetzt wird (typischerweise 0) |
| PV.D1   | PV            | INT | Preset Value – Schwellwert, bei dessen Erreichen der Ausgang Q aktiv wird |

### **Daten-Ausgänge**
- **Q.D1** (über Adapter Q, Typ AX) – Ausgangssignal (BOOL), wird TRUE, wenn der Zählerstand ≥ PV ist.
- **CV.D1** (über Adapter CV, Typ AI) – Aktueller Zählerstand (INT).

### **Adapter**
| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| CU   | adapter::types::unidirectional::AX | Socket (Eingang) | Ereignis- und Datenadapter für den Zählimpuls |
| R    | adapter::types::unidirectional::AX | Socket (Eingang) | Ereignis- und Datenadapter für das Rücksetzen |
| PV   | adapter::types::unidirectional::AI | Socket (Eingang) | Datenadapter (nur Wert, kein Ereignis) für den Preset-Wert |
| Q    | adapter::types::unidirectional::AX | Plug (Ausgang) | Ereignis- und Datenadapter für den Zählerausgang |
| CV   | adapter::types::unidirectional::AI | Plug (Ausgang) | Datenadapter (nur Wert) für den aktuellen Zählerstand |

## Funktionsweise
Der **AI_FB_CTU** verwendet intern einen standardisierten IEC 61131-3 CTU-Baustein (`iec61131::counters::FB_CTU`). Bei jedem eingehenden Ereignis (CU.E1, R.E1 oder PV.E1) wird der interne CTU durch Aufruf seines REQ-Eingangs verarbeitet. Die Daten aus den Adaptern (CU.D1, R.D1, PV.D1) werden direkt an die entsprechenden Eingänge des internen CTU weitergeleitet.

Nach der Verarbeitung wird das Ergebnis (aktueller Zählerstand CV und Ausgang Q) an die Ausgabeadapter gesendet und gleichzeitig das Bestätigungsereignis CNF ausgelöst. Wichtig: **Der Baustein führt bei jedem beliebigen der drei Ereignisse einen vollständigen Durchlauf durch**, d.h. CU, R und PV werden stets gemeinsam ausgewertet. Dieses Verhalten kann zu unerwarteten Zählimpulsen führen, wenn nicht alle Eingänge gleichzeitig relevant sind. Für reine Änderungsauslösung empfiehlt sich die Verwendung eines AX_D_FF (D-Flipflop) als Filter.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle**: Alle Ein- und Ausgänge sind als Adapter realisiert, was eine flexible Verschaltung in Composite-FBs oder Subapplikationen ermöglicht.
- **Kapselung von IEC 61131-3**: Der Baustein verpackt die bewährte Zählerlogik aus der IEC 61131-3 in eine 4diac-konforme Komponente.
- **Simultane Triggerung**: Jedes Ereignis (CU, R, PV) führt zu einer vollständigen Neuberechnung – auch wenn nur ein Parameter geändert wurde.
- **Lizenz**: veröffentlicht unter der Eclipse Public License 2.0.

## Zustandsübersicht
Der interne Zustand wird durch den IEC 61131-3 CTU bestimmt:
- **CV** (aktueller Zählerstand) – Integer-Wert, der bei jedem CU-Ereignis inkrementiert wird (sofern kein Reset erfolgt).
- **Q** (Ausgang) – Boolescher Wert, der TRUE wird, sobald CV >= PV.
- Bei einem **Reset** (R) wird CV auf den Wert von R.D1 gesetzt (meist 0) und Q zurückgesetzt.
- Bei einem neuen **PV** wird lediglich der Schwellwert aktualisiert; Q kann sich sofort ändern, wenn CV >= neuer PV.

Der Baustein hat keine eigenen sequentiellen Zustände jenseits dieser Datenabhängigkeiten.

## Anwendungsszenarien
- **Produktionszählung**: Erfassung von Werkstücken auf einem Förderband (CU = Impulsgeber, PV = Chargengröße, Q = Chargenende).
- **Ereigniszähler**: Zählen von Sensorsignalen in Kombination mit zeitlicher Auswertung.
- **Batch-Prozesse**: Steuerung von Dosier- oder Abfüllvorgängen mit einstellbarem Sollwert (PV).
- **Modulare Automatisierung**: Einbettung in größere Funktionsbausteine über einheitliche Adapter-Schnittstellen (AX/AI).

## Vergleich mit ähnlichen Bausteinen
| Baustein | Eigenschaften |
|----------|---------------|
| **AI_FB_CTU** | Adapter-basiert, verwendet IEC 61131-3 CTU, löst bei jedem Eingang aus |
| **Standard CTU (IEC 61131)** | Eingänge als Events + Daten, kein Adapterkonzept, oft direkt an Hardware gebunden |
| **CTUD (Auf-/Abwärtszähler)** | Bietet zusätzlich Abwärtszählen, hat komplexere Schnittstelle |
| **AX_CTU** (hypothetisch) | Könnte optimierte Ereignisauslösung (nur bei Änderung) bieten |

Der **AI_FB_CTU** besticht durch seine einfache Adapter-Anbindung, erfordert aber ggf. einen externen Filter, um unnötige Aufrufe zu vermeiden.

## Fazit
Der **AI_FB_CTU** ist ein praktischer Zählerbaustein für die adapterbasierte Automatisierung mit 4diac. Er kombiniert die bewährte IEC 61131-3 Logik mit moderner, modularer Schnittstellentechnik. Seine einfache Struktur und klare Funktionsweise machen ihn zur ersten Wahl für alle Aufwärtszählaufgaben, bei denen eine lose Kopplung über Adapter gewünscht ist. Anwender sollten jedoch das Triggern auf jedes Ereignis beachten und bei Bedarf eine Differentialfilterung vorsehen.