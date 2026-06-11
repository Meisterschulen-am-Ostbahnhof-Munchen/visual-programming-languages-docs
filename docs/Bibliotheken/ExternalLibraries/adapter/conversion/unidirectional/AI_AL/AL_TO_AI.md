# AL_TO_AI


![AL_TO_AI](./AL_TO_AI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AL_TO_AI ist ein Composite-Baustein, der einen unidirektionalen AL-Adapter (LWORD) in einen unidirektionalen AI-Adapter (INT) umwandelt. Er dient als Schnittstellenkonverter für adapterbasierte Kommunikation und ermöglicht eine einfache Integration zwischen Komponenten, die unterschiedliche Datentypen verwenden. Die Konvertierung erfolgt intern mittels des standardisierten IEC 61131-3-Funktionsbausteins F_LWORD_TO_INT.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der FB besitzt keine expliziten Ereignis-Eingänge. Die Ereignissteuerung erfolgt indirekt über den Socket-Adapter **AL_IN**, der das Ereignis **E1** bereitstellt.

### **Ereignis-Ausgänge**
Der FB besitzt keine expliziten Ereignis-Ausgänge. Die Ereignissteuerung erfolgt indirekt über den Plug-Adapter **AI_OUT**, der das Ereignis **E1** bereitstellt.

### **Daten-Eingänge**
Der FB besitzt keine expliziten Daten-Eingänge. Die aufzunehmenden Daten werden über den Socket-Adapter **AL_IN** als LWORD zur Verfügung gestellt.

### **Daten-Ausgänge**
Der FB besitzt keine expliziten Daten-Ausgänge. Die konvertierten Daten werden über den Plug-Adapter **AI_OUT** als INT ausgegeben.

### **Adapter**
| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|-------------|
| **AL_IN** | Socket (Eingang) | `adapter::types::unidirectional::AL` | Liefert ein LWORD (über Daten-Port D1) sowie ein Ereignis (E1). |
| **AI_OUT** | Plug (Ausgang) | `adapter::types::unidirectional::AI` | Stellt ein INT (über Daten-Port D1) sowie ein Ereignis (E1) bereit. |

## Funktionsweise
Der FB arbeitet als transparenter Konverter zwischen den beiden Adaptern. Sobald am Socket **AL_IN** das Ereignis **E1** eintrifft, wird der interne Funktionsbaustein **F_LWORD_TO_INT** mit dem übergebenen LWORD-Wert (aus **AL_IN.D1**) getriggert. Der Konvertierungsbaustein wandelt den Wert in ein INT um und signalisiert die Fertigstellung über das Ereignis **CNF**. Dieses Ereignis wird direkt an den Plug **AI_OUT** weitergeleitet (E1), und das konvertierte INT (aus **F_LWORD_TO_INT.OUT**) wird auf **AI_OUT.D1** ausgegeben. Die gesamte Umwandlung erfolgt synchron innerhalb eines Ereignisdurchlaufs.

## Technische Besonderheiten
- **Composite-Architektur**: Der FB verwendet intern einen standardisierten IEC 61131-3-Funktionsbaustein (`F_LWORD_TO_INT`), der plattformunabhängig implementiert werden kann.
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangsadapter sind vom Typ `unidirectional`, d. h. sie unterstützen nur eine Daten- und Ereignisrichtung (vom Socket zum Plug).
- **Keine Eigenlogik**: Der FB enthält keine Zustandslogik oder Sequenzen; er fungiert ausschließlich als Koppler und Konverter.
- **Typumwandlung**: Die Konvertierung von LWORD (64 Bit) nach INT (16 Bit) kann je nach Wertebereich zu Datenverlusten führen (Abschneiden höherwertiger Bits). Dies muss im Anwendungskontext berücksichtigt werden.

## Zustandsübersicht
Der Composite-Baustein besitzt keine eigenen Zustände. Das Verhalten wird vollständig durch den internen **F_LWORD_TO_INT** bestimmt, der eine reine Funktion ohne Zustand ist. Die Ablaufsteuerung erfolgt ereignisgesteuert: Auf ein Eingangsereignis folgt unmittelbar ein Ausgangsereignis.

## Anwendungsszenarien
- **Adapter-Brücke**: Verbindung einer Komponente, die LWORD über einen AL-Adapter bereitstellt, mit einer Komponente, die INT über einen AI-Adapter erwartet.
- **Systemintegration**: Einsatz in heterogenen Automatisierungssystemen, wenn unterschiedliche Adaptertypen aufeinandertreffen.
- **Protokollanpassung**: Datenkonvertierung in einer serviceorientierten Architektur (z. B. 4diac) zur Anpassung von Schnittstellen aus verschiedenen IEC 61499- oder IEC 61131-Bibliotheken.

## Vergleich mit ähnlichen Bausteinen
- **AL_TO_AI** ist spezifisch für die Kombination unidirektionaler AL- und AI-Adapter. Andere Konverter wie `LWORD_TO_INT` arbeiten auf reiner Datenebene ohne Adapter-Kapselung.
- Im 4diac-Ökosystem gibt es weitere Adapter-Konverter (z. B. `AI_TO_AL`), die die umgekehrte Richtung abdecken. `AL_TO_AI` füllt die Lücke für die unidirektionale LWORD→INT-Umwandlung.
- Gegenüber einer direkten Verwendung von `F_LWORD_TO_INT` bietet der Composite-FB den Vorteil einer standardisierten Adapter-Schnittstelle, die eine einfache Plug-and-Play-Integration ermöglicht.

## Fazit
Der **AL_TO_AI**-Funktionsblock ist ein nützlicher, schlanker Konverter für den Wechsel zwischen unidirektionalen LWORD- und INT-Adaptern. Er kapselt die bewährte IEC 61131-3-Konvertierung in eine adaptergerechte Form und erleichtert so die Wiederverwendung und den Austausch von Komponenten in IEC 61499-basierten Systemen. Durch seine Ereignissteuerung fügt er sich nahtlos in ereignisgesteuerte Abläufe ein und erfordert keine zusätzliche Konfiguration.