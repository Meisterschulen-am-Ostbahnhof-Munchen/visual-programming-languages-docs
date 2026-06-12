# AI_TO_AB


![AI_TO_AB](./AI_TO_AB.svg)

* * * * * * * * * *
## Einleitung

Der Composite FB `AI_TO_AB` dient der Umwandlung eines **INT**-Werts, der über einen unidirektionalen **AI**-Adapter bereitgestellt wird, in einen **BYTE**-Wert und der Weiterleitung über einen unidirektionalen **AB**-Adapter. Die eigentliche Konvertierung erfolgt durch den intern genutzten FB `F_INT_TO_BYTE`. Der Baustein ist Teil einer Adapter-Konvertierungsbibliothek und ermöglicht die nahtlose Integration von Komponenten mit unterschiedlichen Datentypen in IEC-61499-Systemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine eigenständigen Ereignis-Eingänge. Die ereignisgesteuerte Kommunikation erfolgt über den AI_IN-Adapter (siehe Adapter).

### **Ereignis-Ausgänge**
Keine eigenständigen Ereignis-Ausgänge. Die ereignisgesteuerte Ausgabe erfolgt über den AB_OUT-Adapter (siehe Adapter).

### **Daten-Eingänge**
Keine eigenständigen Daten-Eingänge. Der zu konvertierende INT-Wert wird über den AI_IN-Adapter bereitgestellt.

### **Daten-Ausgänge**
Keine eigenständigen Daten-Ausgänge. Der konvertierte BYTE-Wert wird über den AB_OUT-Adapter ausgegeben.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | `AI_IN` | `adapter::types::unidirectional::AI` | Stellt den INT-Eingangswert (D1) sowie das auslösende Ereignis (E1) bereit. |
| Plug (Ausgang)  | `AB_OUT` | `adapter::types::unidirectional::AB` | Gibt den konvertierten BYTE-Wert (D1) sowie das zugehörige Ereignis (E1) aus. |

## Funktionsweise

Der FB `AI_TO_AB` arbeitet als reiner Datenkonverter auf Basis einer Ereignissteuerung:

1. Am **AI_IN**-Adapter wird ein Ereignis **E1** empfangen.
2. Dieses Ereignis triggert den internen FB `Convert` vom Typ `F_INT_TO_BYTE` über dessen **REQ**-Eingang.
3. Gleichzeitig wird der INT-Datenwert von `AI_IN.D1` an den **IN**-Eingang von `Convert` weitergeleitet.
4. Nach Abschluss der Konvertierung erzeugt `Convert` ein Bestätigungsereignis (**CNF**).
5. Dieses Ereignis wird an **AB_OUT.E1** gesendet, und der konvertierte BYTE-Wert (`Convert.OUT`) wird an **AB_OUT.D1** übergeben.

Somit wird jeder eingehende INT-Wert durch ein Ereignis synchron in einen BYTE-Wert umgesetzt und über den Ausgangsadapter bereitgestellt.

## Technische Besonderheiten

- **Composite FB:** Der Baustein kapselt die Logik in einem Netzwerk aus einem einzelnen Konvertierungs-FB. Er ist selbst kein elementarer Baustein, sondern nutzt die Wiederverwendung von `F_INT_TO_BYTE`.
- **Adapterbasierte Schnittstelle:** Ereignisse und Daten werden ausschließlich über unidirektionale Adapter übertragen, wodurch eine lose Kopplung zwischen Quell- und Zielkomponenten erreicht wird.
- **Typkonvertierung:** Die eigentliche Umwandlung `INT -> BYTE` folgt der IEC 61131-3 Konvention (z.B. Wertebereich <0,255>; bei Überschreitung erfolgt ein Overflow). Dies ist abhängig von der Implementierung des verwendeten `F_INT_TO_BYTE`-Bausteins.
- **Keine interne Zustandsmaschine:** Der FB ist rein kombinatorisch mit ereignisgesteuerter Ausführung.

## Zustandsübersicht

Da es sich um einen Composite FB handelt, besitzt `AI_TO_AB` keinen eigenen Zustandsautomaten. Der interne FB `F_INT_TO_BYTE` kann je nach Implementierung einen einfachen Zustandsautomaten (IDLE, EXECUTING) haben, der jedoch im Rahmen dieses Bausteins nicht sichtbar ist. Die Daten- und Ereignisflüsse sind deterministisch und werden durch das Zusammenspiel der Verbindungen gesteuert.

## Anwendungsszenarien

- **Sensoranbindung:** Ein Sensor liefert INT-Werte, die von einer Steuerungseinheit als BYTE verarbeitet werden müssen (z.B. für einfache Ein-/Ausgabe-Karten).
- **Datenformatkonvertierung** in heterogenen IEC-61499-Systemen, um Komponenten mit unterschiedlichen Adaptertypen zu verbinden.
- **Adapter-Übersetzung** in Bibliotheken, die auf unidirektionale Kommunikation ausgelegt sind, z.B. bei der Verwendung von Feldbusprotokollen, die BYTE-orientierte Daten erwarten.

## Vergleich mit ähnlichen Bausteinen

- **Direkte Konverter (z.B. `F_INT_TO_BYTE`):** Diese arbeiten auf Datenportebene und benötigen eine explizite Eventsteuerung. `AI_TO_AB` kapselt dies in einer adapterbasierten Schnittstelle.
- **Weitere Adapterkonverter:** Denkbar sind Bausteine wie `AI_TO_AW` (INT nach WORD) oder `AB_TO_AI` (BYTE nach INT). `AI_TO_AB` ist speziell auf die Kombination der beiden unidirektionalen Adapter `AI` und `AB` zugeschnitten.
- **Composite-Konverter vs. elementare Konverter:** Composite-FBs bieten eine höhere Abstraktion und Wiederverwendbarkeit, während elementare FBs mehr Kontrolle über die interne Logik erlauben.

## Fazit

Der Composite FB `AI_TO_AB` stellt eine effiziente, adapterbasierte Lösung zur Konvertierung von INT- zu BYTE-Werten dar. Er vereinfacht die Integration von Komponenten mit unterschiedlichen Datentypen in IEC-61499-Anwendungen, indem er die Konvertierungslogik in einer standardisierten, wiederverwendbaren Schnittstelle kapselt. Die ereignisgesteuerte Ausführung und die Nutzung eines etablierten Konvertierungsbausteins gewährleisten eine zuverlässige und deterministische Datenverarbeitung.