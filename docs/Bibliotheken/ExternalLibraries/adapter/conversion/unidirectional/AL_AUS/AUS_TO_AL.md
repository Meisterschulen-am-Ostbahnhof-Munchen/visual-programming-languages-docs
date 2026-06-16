# AUS_TO_AL


![AUS_TO_AL](./AUS_TO_AL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUS_TO_AL** ist ein zusammengesetzter Baustein (Composite FB), der einen unidirektionalen **AUS**-Adapter (USINT-Datentyp) in einen unidirektionalen **AL**-Adapter (LWORD-Datentyp) umwandelt. Er dient als Brücke zwischen unterschiedlichen Datenformaten in einer 4diac-IDE-Umgebung, wobei die Konvertierung intern durch den IEC‑61131‑FB `F_USINT_TO_LWORD` realisiert wird. Der Baustein erleichtert die Integration von Komponenten, die auf verschiedenen Adaptertypen basieren.

## Schnittstellenstruktur
Da es sich um einen Composite FB handelt, werden alle E/A-Signale über die beiden Adapter bereitgestellt. Der FB selbst besitzt keine eigenständigen Ereignis- oder Dateneingänge/-ausgänge.

### **Ereignis-Eingänge**
- Keine eigenständigen Ereignis-Eingänge.

### **Ereignis-Ausgänge**
- Keine eigenständigen Ereignis-Ausgänge.

### **Daten-Eingänge**
- Keine eigenständigen Daten-Eingänge.

### **Daten-Ausgänge**
- Keine eigenständigen Daten-Ausgänge.

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
|-------------|-----|----------|--------------|
| **AUS_IN** | `adapter::types::unidirectional::AUS` | Socket (Eingang) | Empfängt den USINT-Wert sowie das zugehörige Ereignis. Der Adapter stellt intern einen Ereignis-Eingang `E1` und einen Daten-Eingang `D1` (USINT) bereit. |
| **AL_OUT** | `adapter::types::unidirectional::AL` | Plug (Ausgang) | Gibt den konvertierten LWORD-Wert aus. Der Adapter stellt intern einen Ereignis-Ausgang `E1` und einen Daten-Ausgang `D1` (LWORD) bereit. |

## Funktionsweise
1. Der Socket **AUS_IN** empfängt ein Ereignis an seinem internen Eingang `E1` und den zugehörigen USINT-Wert an `D1`.
2. Dieses Ereignis wird intern an den **REQ**-Eingang des Konvertierungs-FBs `F_USINT_TO_LWORD` weitergeleitet; der USINT-Wert wird an dessen **IN**-Eingang gelegt.
3. Der FB `F_USINT_TO_LWORD` führt die Umwandlung von USINT (8‑Bit vorzeichenlos) zu LWORD (64‑Bit vorzeichenlos) durch.
4. Nach Abschluss der Konvertierung wird am **CNF**-Ausgang von `F_USINT_TO_LWORD` ein Ereignis erzeugt, das an den internen Ereignis-Eingang des **AL_OUT**-Adapters (`E1`) gesendet wird. Gleichzeitig wird der konvertierte LWORD-Wert an den Daten-Ausgang `D1` des Adapters gelegt.
5. Der übergeordnete Baustein kann anschließend den LWORD-Wert über den Plug **AL_OUT** abgreifen und das Ereignis nutzen.

Die gesamte Abfolge ist streng kausal: Die Konvertierung wird nur dann ausgelöst, wenn am **AUS_IN** ein Ereignis eintrifft.

## Technische Besonderheiten
- **Composite FB**: Der Baustein kapselt die Konvertierungslogik in einem wiederverwendbaren Adapter-Paar.
- **Verwendete Bibliothek**: Die eigentliche Typumwandlung erfolgt durch `iec61131::conversion::F_USINT_TO_LWORD` aus der IEC‑61131‑Standardbibliothek.
- **Kein Zustand**: Der Baustein ist rein kombinatorisch mit ereignisgesteuerter Ausführung; er speichert keine internen Zustände.
- **Adapter‑Unidirektionalität**: Sowohl AUS als auch AL sind als unidirektionale Adapter definiert, d.h. die Daten fließen nur in eine Richtung (Eingang → Ausgang).

## Zustandsübersicht
Der Baustein besitzt kein eigenständiges Zustandsdiagramm. Sein Verhalten ist ausschließlich durch die Ereignis-/Datenflüsse des eingebetteten FBs `F_USINT_TO_LWORD` bestimmt:
- **Idle**: Warten auf ein Ereignis am **AUS_IN**.
- **Konvertierung aktiv**: Sobald ein Ereignis eintrifft, wird die Umwandlung durchgeführt. Nach Abschluss wird das Ausgangsereignis generiert und der Baustein kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- **Datenformat‑Anpassung**: Ein Sensor oder eine Steuerung liefert Daten als USINT‑Wert (z.B. Zählerstände), doch die nachgelagerte Komponente erwartet LWORD (z.B. für große Datenbereiche oder Zeitstempel).
- **Adapter‑Brücken**: Wenn in einer 4diac-Anwendung Komponenten mit unterschiedlichen Adaptertypen verbunden werden müssen, ermöglicht dieser FB eine saubere, typensichere Umwandlung.
- **Unterstützung von Legacy‑Systemen**: Altanlagen, die USINT‑Daten ausgeben, können über diesen Baustein in moderne LWORD‑Schnittstellen integriert werden.

## Vergleich mit ähnlichen Bausteinen
- **F_USINT_TO_LWORD**: Ein reiner Funktionsbaustein (Basic FB) ohne Adapter-Kapselung. Er kann direkt in einem Netzwerk verwendet werden, erfordert aber die manuelle Verkabelung von Ereignissen und Daten.
- **AUS_TO_AL**: Bietet eine höhere Abstraktionsebene durch die Verwendung von Adaptern. Dadurch wird die Wiederverwendbarkeit und Austauschbarkeit von Komponenten verbessert, da die Adapter-Schnittstellen standardisiert sind.
- **Andere Typkonverter** (z.B. `INT_TO_DWORD`): Ähnliche Logik, jedoch für andere Datentypen; der vorliegende Baustein füllt die spezifische Lücke zwischen USINT und LWORD.

## Fazit
Der **AUS_TO_AL**-Funktionsblock ist ein praktischer Composite‑FB zur Umwandlung von USINT‑ in LWORD‑Daten, verpackt in ein adapterbasiertes Interface. Er nutzt die bewährte IEC‑61131‑Konvertierung und erlaubt eine saubere Integration in modulare 4diac‑Anwendungen. Durch die Adapter‑Kapselung bleibt die Schnittstelle klar definiert und der Baustein kann einfach in bestehende Kommunikationsstrukturen eingebunden werden.