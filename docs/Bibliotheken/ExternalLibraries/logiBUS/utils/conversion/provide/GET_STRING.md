# GET_STRING


![GET_STRING](./GET_STRING.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `GET_STRING` dient dazu, einen Stringwert aus einer InOut-Variable auszulesen und als gepufferten Ausgang bereitzustellen. Er wird typischerweise verwendet, um den aktuellen Wert einer externen Variablen zu einem bestimmten Zeitpunkt zu erfassen und für die Weiterverarbeitung bereitzustellen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ      | Event    | Normaler Ausführungsanforderung. Löst das Einlesen der InOut-Variablen aus. |

### **Ereignis-Ausgänge**
| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF      | Event    | Bestätigung der Ausführung. Wird gesendet, nachdem der Wert gelesen und an den Ausgang übergeben wurde. |

### **Daten-Eingänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| IN   | STRING   | InOut-Variable, die als Quelle dient. Ihr aktueller Wert wird bei REQ gelesen und gepuffert. |

### **Daten-Ausgänge**
| Name | Datentyp | Kommentar |
|------|----------|-----------|
| OUT  | STRING   | Gepufferter Ausgabewert. Enthält den zum Zeitpunkt des letzten REQ gelesenen String von IN. |

### **Adapter**
Keine.

## Funktionsweise
Der Funktionsblock verfügt über einen Zustand `REQ`. Ein eingehendes Ereignis an `REQ` führt den Algorithmus aus, der den Wert der InOut-Variablen `IN` direkt in den Ausgang `OUT` kopiert. Anschließend wird das Ereignis `CNF` gesendet. Die InOut-Variable `IN` wird dabei nicht verändert, sondern nur gelesen. Der gepufferte Wert bleibt solange erhalten, bis ein weiterer `REQ` einen neuen Wert einliest.

## Technische Besonderheiten
- Die Variable `IN` ist als **InOut** deklariert, was bedeutet, dass sie als Referenz übergeben wird (Pass-by-Reference). Dies ermöglicht einen direkten Zugriff auf den Speicher der übergebenen Stringvariablen, ohne den Wert vorher in eine lokale Kopie zu übernehmen.
- Der Baustein ist auf den Datentyp `STRING` spezialisiert. Für andere Datentypen sind entsprechende Varianten (z. B. `GET_ANY`) erforderlich.
- Es werden keine initialen Werte gesetzt. Der Ausgang `OUT` ist nach dem ersten Zyklus undefiniert, solange kein `REQ` empfangen wurde.

## Zustandsübersicht
Der Baustein besitzt einen einzigen Zustand:

| Zustandsname | Beschreibung |
|--------------|--------------|
| REQ          | Wartet auf ein Ereignis an `REQ`. Führt den Algorithmus aus (kopiert `IN` → `OUT`) und sendet `CNF`. |

Es gibt keine Start- oder Endzustände; der Baustein verharrt nach jedem Durchlauf wieder im Zustand `REQ`.

## Anwendungsszenarien
- **Zwischenspeicherung**: Ein Stringwert einer externen Quelle (z. B. eines Datenbausteins) wird abgetastet und für eine nachfolgende Verarbeitung zwischengespeichert, ohne die Quelle zu beeinflussen.
- **Protokollierung**: Momentaufnahme eines sich ändernden Strings zu bestimmten Ereigniszeitpunkten.
- **Synchronisation**: Bereitstellung eines konsistenten Wertes für mehrere nachgeschaltete Bausteine, wenn die Quelle von mehreren Stellen gleichzeitig gelesen werden soll.

## Vergleich mit ähnlichen Bausteinen
- **MOVE / ASSIGN**: Einfache Zuweisungsbausteine für beliebige Typen, oft ohne explizite Ereignissteuerung. `GET_STRING` ist dagegen speziell auf `STRING` ausgelegt und nutzt eine InOut-Schnittstelle.
- **GET_ANY**: Ein generischer Baustein für beliebige Datentypen. `GET_STRING` ist typsicher und vermeidet Parameterisierungsaufwand für das Einlesen von Strings.
- **READ_REF**: Ebenfalls ein Baustein zur Referenzübergabe, aber häufig als Funktionsbaustein ohne Ereignissteuerung realisiert. `GET_STRING` integriert die Ereignissteuerung und eignet sich daher für ablauforientierte Steuerungen.

## Fazit
`GET_STRING` ist ein einfacher, aber spezialisierter Funktionsbaustein für die gepufferte Übernahme eines Stringwerts aus einer InOut-Variablen. Durch die Ereignissteuerung lässt er sich präzise in zeitkritischen Abläufen einsetzen. Die Verwendung einer InOut-Schnittstelle spart Speicher und Rechenzeit, da keine Wertkopie auf der Aufruferseite nötig ist. Für die meisten Anwendungen, in denen Strings abgetastet werden müssen, stellt dieser Baustein eine saubere und ressourcenschonende Lösung dar.