# AQ_D_FF


![AQ_D_FF](./AQ_D_FF.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AQ_D_FF` realisiert ein Datenspeicherglied (D-Latch) auf Basis des Adapterkonzepts der IEC 61499. Er übernimmt einen eingehenden Datenwert bei einem eingehenden Ereignis und stellt diesen bis zum nächsten Ereignis am Ausgang bereit. Der Baustein kapselt die Latch-Funktionalität vollständig in einer Adapter-Schnittstelle und ermöglicht so eine modulare Integration in systemweit genutzte Daten- und Ereignispfade.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge vorhanden. Die Ereignissteuerung erfolgt ausschließlich über den Adapter `I`.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge vorhanden. Die Ereignisausgabe erfolgt ausschließlich über den Adapter `Q`.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden. Der zu latchende Datenwert wird über den Adapter `I` bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden. Der gelatchte Datenwert wird über den Adapter `Q` ausgegeben.

### **Adapter**
| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `I`     | Socket (Eingang) | `adapter::types::unidirectional::AQ` | Liefert den zu latchenden Datenwert sowie das auslösende Ereignis. |
| `Q`     | Plug (Ausgang) | `adapter::types::unidirectional::AQ` | Gibt den gelatchten Datenwert sowie ein Bestätigungsereignis aus. |

Der verwendete Adaptertyp `adapter::types::unidirectional::AQ` stellt eine unidirektionale Verbindung bereit: Vom Socket zum Plug werden jeweils ein Ereignis- und ein Datenkanal übertragen.

## Funktionsweise
Der `AQ_D_FF` arbeitet nach dem Prinzip eines flankengesteuerten D-Latches. Intern wird der Funktionsblock `iec61499::events::E_D_FF_ANY` verwendet:

- Sobald am Adapter `I` ein Ereignis ankommt, wird der aktuell anliegende Datenwert `D1` (aus dem Adapter `I`) übernommen.
- Der übernommene Wert wird am Adapter `Q` als `D1` ausgegeben, gleichzeitig wird das Ereignis `E1` am Ausgangsadapter ausgelöst.
- Zwischen zwei Ereignissen bleibt der Ausgangswert konstant. Bei jedem neuen Ereignis am Eingang wird der Ausgang auf den dann gültigen Eingangswert aktualisiert.

## Technische Besonderheiten
- **Reine Adapter-Schnittstelle**: Der Baustein besitzt keine direkten Ereignis- oder Daten-Ein-/Ausgänge. Die gesamte Kommunikation erfolgt über die Adapter `I` und `Q`.
- **Unidirektionale Datenübertragung**: Die Adapter sind vom Typ `adapter::types::unidirectional::AQ`, was bedeutet, dass Daten und Ereignisse nur vom Eingang zum Ausgang fließen. Eine Rückmeldung oder bidirektionale Kommunikation ist nicht vorgesehen.
- **Interne Realisierung**: Die Latch-Funktion wird durch den universellen FB `E_D_FF_ANY` aus der IEC 61499-Ereignisbibliothek implementiert, was eine robuste und standardkonforme Verarbeitung gewährleistet.
- **Keine Initialisierung**: Der Anfangszustand des gelatchten Werts ist undefiniert, bis das erste Ereignis am Eingang eintrifft.

## Zustandsübersicht
Der `AQ_D_FF` besitzt keinen expliziten Zustandsautomaten. Sein Verhalten lässt sich jedoch durch zwei logische Zustände beschreiben:

| Zustand | Beschreibung |
|---------|--------------|
| **Warten auf Ereignis** | Der Ausgang `Q` hält den zuletzt gelatchten Wert. Es liegt kein Ereignis an `I` an. |
| **Übernahme/Ausgabe** | Bei Eintreffen eines Ereignisses an `I` wird der neue Wert von `I` übernommen, an `Q` ausgegeben und ein Ereignis auf `E1` von `Q` generiert. Danach kehrt der Baustein in den Wartezustand zurück. |

## Anwendungsszenarien
- **Zwischenspeicherung von Sensorwerten**: Ein Messwert wird bei einem Trigger-Ereignis (z. B. Takt oder Abfrage) übernommen und steht dann für die weitere Verarbeitung bereit.
- **Synchronisation asynchroner Datenströme**: Wenn Daten asynchron ankommen, kann der `AQ_D_FF` den letzten gültigen Wert festhalten, bis ein nachgelagerter Prozess ihn abholt.
- **Ereignisgesteuerte Datenweitergabe**: Der Baustein kann als einfacher „Data-Holder“ in einem Adapter-basierten Kommunikationspfad verwendet werden, um Daten nur bei bestimmten Ereignissen weiterzuleiten.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Eigenschaften |
|----------|---------------|
| `E_D_FF` (direkte IOs) | Gleiche Latch-Funktionalität, aber mit separaten Ereignis- und Dateneingängen/-ausgängen. Keine Adapter. |
| `E_SR_FF` | Set/Reset-Flipflop mit zwei getrennten Eingangsereignissen. Hier kein Datenwert, sondern binäre Zustände. |
| `AQ_D_FF` | Ermöglicht die Einbettung der Latch-Funktion in bestehende Adapter-Schnittstellen, ohne zusätzliche Verdrahtung auf FB-Ebene. |

## Fazit
Der Funktionsblock `AQ_D_FF` bietet eine kompakte, adapterbasierte Realisierung eines D-Latches. Er integriert sich nahtlos in systemweit genutzte Adapterpfade und reduziert so den Verdrahtungsaufwand auf der FB-Ebene. Seine Funktionsweise ist einfach und zuverlässig, insbesondere für Anwendungen, bei denen ein Datenwert bei einem Ereignis übernommen und bis zum nächsten Ereignis gehalten werden muss.