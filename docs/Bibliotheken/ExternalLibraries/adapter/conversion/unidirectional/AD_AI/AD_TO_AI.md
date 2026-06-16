# AD_TO_AI


![AD_TO_AI](./AD_TO_AI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AD_TO_AI** dient als Konverter zwischen zwei unterschiedlichen Adapterschnittstellen: Er wandelt einen **AD-Adapter (DWORD)** in einen **AI-Adapter (INT)** um. Der Baustein wird als Composite FB realisiert und nutzt intern die IEC 61131‑3 Funktion `F_DWORD_TO_INT`, um die eigentliche Typumwandlung durchzuführen. Ziel ist es, die Integration von Komponenten zu erleichtern, die auf verschiedenen Datentypen basieren, und dabei die ereignisgesteuerte Datenweitergabe innerhalb der 4diac-IDE zu gewährleisten.

## Schnittstellenstruktur

### **Ereignis‑Eingänge**
Der FB besitzt keine direkten Ereignis‑Eingänge auf oberster Ebene. Die Ereignissteuerung erfolgt über die angeschlossenen Adapter:
- **AD_IN.E1** (Ereignis des Socket‑Adapters) – löst die Konvertierung aus.

### **Ereignis‑Ausgänge**
Auch diese werden ausschließlich über die Adapter bereitgestellt:
- **AI_OUT.E1** (Ereignis des Plug‑Adapters) – signalisiert die Fertigstellung der konvertierten Daten.

### **Daten‑Eingänge**
- **AD_IN.D1** (DWORD) – Der ursprüngliche Datenwert, der vom AD‑Adapter geliefert wird.

### **Daten‑Ausgänge**
- **AI_OUT.D1** (INT) – Der konvertierte Wert, der über den AI‑Adapter nach außen gegeben wird.

### **Adapter**

| Adaptertyp | Richtung | Typ | Beschreibung |
|-----------|----------|-----|--------------|
| Socket | Eingang | `adapter::types::unidirectional::AD` | Empfängt einen DWORD‑Wert (über Ereignis E1 und Daten D1). |
| Plug | Ausgang | `adapter::types::unidirectional::AI` | Stellt den konvertierten INT‑Wert bereit (Ereignis E1, Daten D1). |

## Funktionsweise

Der Baustein arbeitet ereignisgesteuert:

1. Ein Ereignis am Socket **AD_IN.E1** triggert die interne Instanz `Convert` (Typ `F_DWORD_TO_INT`) über deren Ereigniseingang **REQ**.
2. Gleichzeitig wird der Datenwert **AD_IN.D1** (DWORD) an den Dateneingang **IN** von `Convert` übergeben.
3. Die Funktion `F_DWORD_TO_INT` führt die Typumwandlung von DWORD nach INT durch.
4. Nach Abschluss der Berechnung sendet `Convert` ein Ereignis an ihrem Ausgang **CNF**, welches mit dem Plug‑Ereignis **AI_OUT.E1** verbunden ist.
5. Parallel dazu wird der konvertierte INT‑Wert vom Ausgang **OUT** von `Convert` an den Datenausgang **AI_OUT.D1** weitergeleitet.

Somit wird nach jedem eingehenden Ereignis am Socket automatisch ein konvertierter Datenwert auf dem Plug bereitgestellt.

## Technische Besonderheiten

- **Komposition:** Der FB ist ein reiner Composite‑Baustein – er enthält keine eigene Logik, sondern delegiert die Umwandlung an den Standardbaustein `F_DWORD_TO_INT` aus der IEC‑61131‑Bibliothek.
- **Datentypen:** DWORD ist ein 32‑Bit‑Wert, INT dagegen ein 16‑Bit‑Integer (vorzeichenbehaftet). Bei der Konvertierung können Datenverluste auftreten, wenn der DWORD‑Wert außerhalb des INT‑Bereichs (−32768 … 32767) liegt oder nicht in diesen Bereich passt. Der Anwender muss dies bei der Verwendung beachten.
- **Adapter‑Kopplung:** Die Verbindung zwischen Socket und Plug erfolgt ausschließlich über die inneren Ereignis‑ und Datenflüsse. Die Adapter selbst sind vom Typ `unidirectional`, d. h. sie übertragen Daten nur in eine Richtung.
- **Paketstruktur:** Der Baustein wird im Paket `adapter::conversion::unidirectional` bereitgestellt und importiert die Konvertierungsfunktion aus `iec61131::conversion`.

## Zustandsübersicht

Da es sich um einen Composite‑FB ohne eigene Zustandsmaschine handelt, gibt es keine expliziten Zustände. Der Baustein verhält sich wie ein transparenter Konverter:  
- **Idle:** Wartet auf ein Ereignis am Socket.  
- **Processing:** Nach Ereigniseingang wird die Konvertierung gestartet; in dieser Phase sind keine weiteren Ereignisse aktiv.  
- **Done:** Nach der Konvertierung wird das Ausgangsereignis ausgegeben; der Baustein kehrt in den Idle‑Zustand zurück.

Der interne FB `F_DWORD_TO_INT` besitzt eine eigene, vom System definierte Zustandslogik, die jedoch durch die Kapselung im Composite‑FB nicht sichtbar ist.

## Anwendungsszenarien

- **Integration unterschiedlicher Adaptertypen:** Ein Sensor liefert Daten als DWORD über einen AD‑Adapter, nachgeschaltete Logik erwartet jedoch INT‑Werte über einen AI‑Adapter. Der Baustein übernimmt die Typumwandlung nahtlos.
- **Heterogene Systemarchitekturen:** In Anlagen, in denen verschiedene Komponenten unterschiedliche Datentypen verwenden, ermöglicht `AD_TO_AI` eine einfache und standardisierte Anbindung.
- **Prototyping und Migration:** Beim Wechsel von einer DWORD‑basierten Datenverarbeitung auf INT‑basierte Komponenten kann der Baustein als temporärer oder dauerhafter Konverter eingesetzt werden.

## Vergleich mit ähnlichen Bausteinen

Es existieren weitere Konverter‑Bausteine wie `AD_TO_AI`, `AI_TO_AD`, `INT_TO_DWORD` usw. Der vorliegende Baustein fokussiert speziell auf die Adapterebene und arbeitet vollständig ereignisgesteuert. Im Gegensatz zu einfachen Daten‑Konvertierungs‑FBs (z. B. `F_DWORD_TO_INT`) bietet er eine vorgefertigte Adapterschnittstelle, die eine direkte Kopplung an Adapter‑orientierte Architekturen ermöglicht, ohne dass zusätzliche Verbindungen von Hand gezeichnet werden müssen.

Andere ähnliche Composite‑Bausteine unterscheiden sich hauptsächlich in der Richtung (z. B. `AI_TO_AD` für die Rückwandlung) oder in den verwendeten Datentypen.

## Fazit

Der Composite‑FB **AD_TO_AI** ist ein nützliches Werkzeug zur Typanpassung zwischen DWORD‑ und INT‑Adaptern. Er kapselt die Konvertierungslogik in einer sauberen, ereignisgesteuerten Schnittstelle und erleichtert so die Wiederverwendbarkeit und Integration in bestehende 4diac‑Projekte. Seine einfache Struktur und die Verwendung eines bewährten Standardbausteins machen ihn zuverlässig und leicht verständlich. Anwender sollten jedoch stets die Grenzen des INT‑Datentyps im Auge behalten, um unbeabsichtigte Datenverluste zu vermeiden.