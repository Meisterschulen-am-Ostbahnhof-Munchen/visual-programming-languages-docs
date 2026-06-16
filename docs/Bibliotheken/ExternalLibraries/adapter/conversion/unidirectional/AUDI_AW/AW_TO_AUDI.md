# AW_TO_AUDI


![AW_TO_AUDI](./AW_TO_AUDI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AW_TO_AUDI` ist ein Composite-Baustein, der einen über einen WORD-Adapter (`AW`) eingehenden Datenwert in einen UDINT-Wert konvertiert und über einen UDINT-Adapter (`AUDI`) ausgibt. Die Konvertierung erfolgt mittels des intern genutzten Bausteins `F_WORD_TO_UDINT` aus der IEC‑61131‑Bibliothek. Der FB kapselt die Adapter‑Schnittstellen und ermöglicht eine saubere Trennung zwischen verschiedenen Datenformaten in einem System.

## Schnittstellenstruktur
### **Ereignis‑Eingänge**
- **AW_IN.E1** (über Socket `AW_IN`): Auslöser für die Konvertierung. Ein eingehendes Ereignis startet die Umwandlung des aktuellen WORD‑Werts.

- **Eigene Ereignis‑Eingänge**: Keine – der FB empfängt Ereignisse ausschließlich über den Adapter `AW_IN`.

### **Ereignis‑Ausgänge**
- **AUDI_OUT.E1** (über Plug `AUDI_OUT`): Quittierung nach erfolgter Konvertierung. Das ausgehende Ereignis signalisiert, dass ein neuer UDINT‑Wert am Datenausgang anliegt.

- **Eigene Ereignis‑Ausgänge**: Keine – der FB gibt Ereignisse ausschließlich über den Adapter `AUDI_OUT` weiter.

### **Daten‑Eingänge**
- **AW_IN.D1** (über Socket `AW_IN`): Der zu konvertierende WORD‑Wert (16‑Bit).

- **Eigene Daten‑Eingänge**: Keine.

### **Daten‑Ausgänge**
- **AUDI_OUT.D1** (über Plug `AUDI_OUT`): Der konvertierte UDINT‑Wert (32‑Bit, vorzeichenlos).

- **Eigene Daten‑Ausgänge**: Keine.

### **Adapter**
- **Socket `AW_IN`**: Erwartet eine Instanz des Adapter‑Typs `adapter::types::unidirectional::AW`. Dieser Adapter stellt die ereignis‑ und datenseitige Schnittstelle für den WORD‑Eingang bereit.

- **Plug `AUDI_OUT`**: Stellt eine Instanz des Adapter‑Typs `adapter::types::unidirectional::AUDI` bereit. Dieser Adapter gibt die ereignis‑ und datenseitige Schnittstelle für den UDINT‑Ausgang nach außen.

## Funktionsweise
1. Der FB wartet auf ein Ereignis an **AW_IN.E1**.
2. Mit dem Ereignis wird der aktuelle Wert von **AW_IN.D1** (WORD) an den eingebetteten Funktionsblock `F_WORD_TO_UDINT` übergeben.
3. Der `F_WORD_TO_UDINT` führt die Konvertierung durch und legt das Ergebnis (UDINT) an seinem Ausgang `OUT` an.
4. Sobald die Konvertierung abgeschlossen ist, wird ein Ereignis über `Convert.CNF` an **AUDI_OUT.E1** gesendet und der konvertierte Wert über **AUDI_OUT.D1** ausgegeben.

Datenfluss und Ereignissteuerung sind synchron: Jedes eingehende Ereignis erzeugt genau ein ausgehendes Ereignis mit dem aktualisierten Datenwert.

## Technische Besonderheiten
- **Composite‑FB**: Der Baustein ist ausschließlich aus einem internen Netzwerk zusammengesetzt und besitzt keine eigene Zustandslogik.
- **Adapter‑Kapselung**: Die gesamte Kommunikation erfolgt über die standardisierten unidirektionalen Adapter `AW` und `AUDI`. Dadurch kann der FB in beliebige Systeme integriert werden, die diese Adapter‑Schnittstellen unterstützen.
- **Wiederverwendung**: Die intern verwendete Konvertierungsfunktion `F_WORD_TO_UDINT` ist Teil der IEC‑61131‑Bibliothek und gewährleistet eine standardkonforme Typumwandlung.
- **Keine Nebenwirkungen**: Der FB führt keinerlei Zustandsänderungen oder Seiteneffekte außerhalb der eigentlichen Konvertierung durch.

## Zustandsübersicht
Der FB `AW_TO_AUDI` besitzt keinen eigenen Zustandsautomaten. Die Ablaufsteuerung wird durch den internen Baustein `F_WORD_TO_UDINT` realisiert, der ein einfaches REQ/CNF‑Verhalten aufweist:
- **Warten** (vor REQ): Kein Ereignis an `AW_IN.E1` → keine Aktion.
- **Verarbeitung** (nach REQ, vor CNF): Die Konvertierung läuft; der Ausgang wird nicht aktualisiert.
- **Fertig** (nach CNF): Neuer Wert liegt an `AUDI_OUT.D1` an und ein Ereignis an `AUDI_OUT.E1` wird gesendet.

Der Gesamt‑FB spiegelt dieses Verhalten nach außen wider.

## Anwendungsszenarien
- **Integration von Subsystemen mit unterschiedlichen Datentypen**: Ein Sensor liefert seine Werte als WORD (z.B. 16‑Bit‑Zähler) über einen AW‑Adapter, während ein Steuerungsteil UDINT‑Werte (32‑Bit) über einen AUDI‑Adapter erwartet.
- **Schnittstellenanpassung in modularen Automatisierungssystemen**: Nutzung in einer Komponente, die Adapter‑basiert kommuniziert, aber die eigentliche Datenkonvertierung von WORD nach UDINT benötigt.
- **Bildung von Konvertierungskaskaden**: Zusammen mit anderen Bausteinen, die z.B. DINT‑ oder REAL‑Adapter verwenden, können beliebige Datenformat‑Anpassungen aufgebaut werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eingangsadapter | Ausgangsadapter | Konvertierung | Bemerkung |
|----------|-----------------|-----------------|---------------|-----------|
| `AW_TO_AUDI` | `AW` (WORD) | `AUDI` (UDINT) | WORD → UDINT | Composite, kapselt `F_WORD_TO_UDINT` |
| Direkte Nutzung von `F_WORD_TO_UDINT` | Keine Adapter | Kein Adapter | WORD → UDINT | Standard‑Funktionsbaustein ohne Adapter‑Schnittstellen |
| `AW_TO_ADINT` (hypothetisch) | `AW` (WORD) | `ADINT` (DINT) | WORD → DINT | analoge Konvertierung mit Vorzeichen |

Der `AW_TO_AUDI` unterscheidet sich von der direkten Nutzung der Konvertierungsfunktion durch die Integration von Adaptern, was ihn für adapterbasierte Systeme sofort einsetzbar macht.

## Fazit
Der Funktionsblock `AW_TO_AUDI` bietet eine einfache und saubere Möglichkeit, zwischen zwei unidirektionalen Adaptern der Typen WORD und UDINT zu konvertieren. Durch die Kapselung der IEC‑Konvertierungsfunktion und die klare Schnittstellendefinition erhöht er die Wiederverwendbarkeit und erleichtert die Integration in bestehende Adapter‑Architekturen. Er ist ideal für Anwendungen, in denen unterschiedliche Datenbreiten oder Formate über standardisierte Adapter ausgetauscht werden müssen.