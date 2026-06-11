# AUDI_TO_ADI


![AUDI_TO_ADI](./AUDI_TO_ADI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_TO_ADI** ist ein Composite-Baustein, der einen unidirektionalen AUDI‑Adapter (UDINT) in einen ADI‑Adapter (DINT) umwandelt. Er dient als Brücke zwischen Komponenten, die unterschiedliche Datentypen über Adapter-Schnittstellen verwenden. Die Konvertierung erfolgt durch den inneren Baustein `iec61131::conversion::F_UDINT_TO_DINT`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| AUDI_IN.E1 | EVENT | Ereignis-Eingang über den AUDI‑Adapter; löst die Konvertierung aus |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| ADI_OUT.E1 | EVENT | Ereignis-Ausgang über den ADI‑Adapter; signalisiert abgeschlossene Konvertierung |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| AUDI_IN.D1 | UDINT | Unsignierter 32‑Bit‑Wert, der in einen vorzeichenbehafteten DINT gewandelt wird |

### **Daten-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| ADI_OUT.D1 | DINT | Konvertierter vorzeichenbehafteter 32‑Bit‑Wert |

### **Adapter**
| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| AUDI_IN | adaper::types::unidirectional::AUDI | Socket (Eingang) | UDINT‑Adapter-Schnittstelle |
| ADI_OUT | adaper::types::unidirectional::ADI | Plug (Ausgang) | DINT‑Adapter-Schnittstelle |

## Funktionsweise
Der Baustein empfängt über den Socket `AUDI_IN` einen UDINT‑Wert zusammen mit einem Ereignis am Eingang `E1`. Dieses Ereignis löst die Konvertierung des anliegenden UDINT‑Wertes in einen DINT‑Wert aus. Die Konvertierung wird intern durch den Funktionsbaustein `F_UDINT_TO_DINT` realisiert. Nach erfolgreicher Wandlung wird der konvertierte DINT‑Wert über den Plug `ADI_OUT` bereitgestellt und ein Ereignis am Ausgang `E1` ausgesendet.

## Technische Besonderheiten
- Der Baustein ist ein Composite‑FB und enthält keinen eigenen Algorithmus – die gesamte Logik wird an den eingebetteten `F_UDINT_TO_DINT` delegiert.
- Die Konvertierung folgt der IEC‑61131‑3‑Definition von `UDINT_TO_DINT`, d. h. Werte außerhalb des DINT‑Bereichs (−2 147 483 648 … 2 147 483 647) werden auf den nächstliegenden gültigen Wert begrenzt (Clamping).
- Die Ereignisweiterleitung erfolgt streng kausal: erst nach Abschluss der Konvertierung wird der Ausgangs‑Event aktiviert.

## Zustandsübersicht
Der Baustein besitzt keine eigenen internen Zustände. Sein Verhalten ist rein reaktiv:  
Auf ein Ereignis am Eingang folgt stets ein Ereignis am Ausgang – sofern die Daten gültig sind. Eine dedizierte Zustandsmaschine existiert nicht.

## Anwendungsszenarien
- Anbindung eines UDINT‑liefernden Sensors (z. B. Zähler oder Positionswert) an einen Aktor, der einen DINT‑Adapter erwartet.
- Integration von SPS‑Komponenten, die unterschiedliche Adapter‑Datentypen verwenden, ohne dass der Anwender die Konvertierung manuell programmieren muss.
- Einheitliche Adapter‑Schnittstelle in einer Steuerungsarchitektur, die teilweise mit signierten und teils mit unsignierten Werten arbeitet.

## Vergleich mit ähnlichen Bausteinen
- **DINT_TO_AUDI**: Führt die umgekehrte Konvertierung (DINT → UDINT) durch.
- **F_UDINT_TO_DINT**: Direkte Verwendung des Konvertierungs‑FBs ohne Adapter‑Kapselung.  
  Der vorliegende Baustein kapselt die Datentypwandlung in einen Adapter‑Kontext und vereinfacht so die Verschaltung von Komponenten, die auf Adapter‑Schnittstellen angewiesen sind.

## Fazit
**AUDI_TO_ADI** bietet eine saubere, kompakte Lösung zur Umwandlung von UDINT‑Adapter‑Daten in DINT‑Adapter‑Daten. Durch die Verwendung eines standardisierten Konvertierungs‑FBs ist die Funktion zuverlässig und leicht nachvollziehbar. Der Composite‑Ansatz reduziert die Komplexität im übergeordneten System und erleichtert die Wiederverwendbarkeit der Adapter‑Logik.