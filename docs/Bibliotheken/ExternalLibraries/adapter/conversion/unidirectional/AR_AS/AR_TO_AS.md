# AR_TO_AS


![AR_TO_AS](./AR_TO_AS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AR_TO_AS** ist ein Composite-Baustein, der einen **REAL-Adapter** (AR) in einen **SINT-Adapter** (AS) umwandelt. Er ermöglicht die einfache und standardisierte Konvertierung zwischen den Adaptertypen und kapselt die dafür notwendige Logik in einem wiederverwendbaren Baustein.

## Schnittstellenstruktur
Der FB besitzt keine separaten Ereignis- oder Datenports der IEC 61499-Ebene. Die gesamte Kommunikation erfolgt über die integrierten Adapter. Die nachfolgende Tabelle beschreibt die verfügbaren Adapter.

### **Ereignis-Eingänge**
Keine eigenen Ereignis-Eingänge vorhanden. Ereignisse werden über den **AS_OUT‑Adapter** empfangen (siehe Adapter).

### **Ereignis-Ausgänge**
Keine eigenen Ereignis-Ausgänge vorhanden. Ereignisse werden über den **AR_IN‑Adapter** gesendet (siehe Adapter).

### **Daten-Eingänge**
Keine eigenen Daten-Eingänge vorhanden. Daten werden über den **AS_OUT‑Adapter** empfangen (siehe Adapter).

### **Daten-Ausgänge**
Keine eigenen Daten-Ausgänge vorhanden. Daten werden über den **AR_IN‑Adapter** gesendet (siehe Adapter).

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `AR_IN` | `adapter::types::unidirectional::AR` | Socket (eingehend) | Unidirektionaler REAL‑Adapter. Liefert einen REAL‑Wert (D1) und ein zugehöriges Ereignis (E1). |
| `AS_OUT` | `adapter::types::unidirectional::AS` | Plug (ausgehend) | Unidirektionaler SINT‑Adapter. Empfängt einen SINT‑Wert (D1) und ein zugehöriges Ereignis (E1). |

## Funktionsweise
Der Baustein realisiert die Konvertierung wie folgt:
1. Ein eingehendes Ereignis auf **AR_IN.E1** triggert den internen Konvertierungsbaustein **F_REAL_TO_SINT**.
2. Der mit dem Ereignis verbundene REAL‑Wert von **AR_IN.D1** wird an den Eingang `IN` des Konvertierungsbausteins weitergeleitet.
3. **F_REAL_TO_SINT** wandelt den REAL‑Wert in einen SINT‑Wert um und legt das Ergebnis an seinem Ausgang `OUT` an.
4. Nach Abschluss der Konvertierung wird ein Ereignis über **AS_OUT.E1** gesendet, zusammen mit dem konvertierten SINT‑Wert auf **AS_OUT.D1**.

Es findet eine synchrone 1:1‑Umsetzung statt – jede eingehende REAL‑Anforderung erzeugt genau eine ausgehende SINT‑Antwort.

## Technische Besonderheiten
- **Wiederverwendbarkeit**: Der Baustein basiert auf dem Standard‑FB `F_REAL_TO_SINT` aus der IEC 61131‑Bibliothek. Dadurch ist die Konvertierungslogik normgerecht und auf vielen Plattformen verfügbar.
- **Adapter‑Schnittstelle**: Die Verwendung von Adaptern erlaubt eine lose Kopplung zwischen Funktionsblöcken und erleichtert den Austausch oder die Erweiterung der Schnittstelle.
- **Wertebereich**: Bei der Konvertierung von REAL (ca. ±3,4∙10³⁸) nach SINT (−128 … 127) kann es zu Wertebereichsüberschreitungen kommen. Der interne FB `F_REAL_TO_SINT` verhält sich dabei gemäß der IEC 61131‑Definition (Überlauf oder Verwendung des sättigenden Verhaltens). Der Anwender sollte die Eingangswerte entsprechend begrenzen.

## Zustandsübersicht
Der **AR_TO_AS** besitzt keinen eigenen Zustandsautomaten. Da es sich um einen reinen Composite‑Baustein handelt, der nur die Verbindung zwischen dem eingehenden und dem ausgehenden Adapter herstellt, gibt es kein internes Zustandsverhalten. Der Baustein arbeitet kombinatorisch auf Ereignisebene.

## Anwendungsszenarien
- **Integration von REAL‑basierten Bausteinen in SINT‑Umgebungen**: Wenn eine Komponente einen REAL‑Adapter bereitstellt, der nachfolgende Funktionsblock jedoch einen SINT‑Adapter erwartet, kann **AR_TO_AS** als vermittelnder Adapter eingesetzt werden.
- **Typsichere Konvertierung in modularen Steuerungen**: Durch die Verwendung von Adaptern bleibt die Typisierung erhalten, und die Konvertierung ist explizit sichtbar im Netzwerk.
- **Erweiterung von Bibliotheken**: Der Baustein kann als Teil einer Adapter‑Konvertierungsbibliothek verwendet werden, um den Datenaustausch zwischen unterschiedlichen numerischen Auflösungen zu standardisieren.

## Vergleich mit ähnlichen Bausteinen
Es existieren analoge Konvertierungs‑Adapter, z. B.:
- **AR_TO_INT** – REAL → INT
- **AR_TO_UDINT** – REAL → UDINT
- **AR_TO_LREAL** – REAL → LREAL

Gemeinsam ist allen die Verwendung des entsprechenden IEC 61131‑Konvertierungsbausteins im Inneren. Der Unterschied liegt im Zieltyp und der Adapter‑Definition. **AR_TO_AS** ist speziell für die Konvertierung in den schmalen, vorzeichenbehafteten 8‑Bit‑SINT‑Typ ausgelegt.

## Fazit
Der **AR_TO_AS** ist ein einfacher, aber effektiver Composite‑Baustein zur Umwandlung eines REAL‑Adapters in einen SINT‑Adapter. Er kapselt die Konvertierungslogik sauber und ermöglicht eine typsichere, ereignisgesteuerte Kommunikation zwischen Funktionsblöcken mit unterschiedlichen numerischen Schnittstellen. Dank der Verwendung von Standard‑Bibliotheken ist er zuverlässig und plattformunabhängig einsetzbar.