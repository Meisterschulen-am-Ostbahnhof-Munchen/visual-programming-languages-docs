# AUDI_ADD_2


![AUDI_ADD_2](./AUDI_ADD_2.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_ADD_2** führt eine arithmetische Addition zweier Eingangswerte durch und stellt das Ergebnis am Ausgang bereit. Der Baustein ist generisch ausgelegt und arbeitet über eine einheitliche Adapter-Schnittstelle vom Typ `AUDI`. Dadurch kann er für unterschiedliche Datentypen (z. B. Ganzzahlen, Gleitkommazahlen) eingesetzt werden, ohne dass der FB selbst angepasst werden muss.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Typ | Richtung | Name | Kommentar |
|-----|----------|------|-----------|
| `adapter::types::unidirectional::AUDI` | Socket (Eingang) | **IN1** | ADD input 1 |
| `adapter::types::unidirectional::AUDI` | Socket (Eingang) | **IN2** | ADD input 2 |
| `adapter::types::unidirectional::AUDI` | Plug (Ausgang) | **OUT** | ADD result |

Die drei Adapter sind alle vom gleichen Typ `AUDI`. Dieser Adaptertyp kapselt den eigentlichen Datenwert (z. B. einen numerischen Wert) und ermöglicht die unidirektionale Übertragung vom Socket zum Plug. Die Addition erfolgt zwischen den Werten von `IN1` und `IN2`; das Ergebnis wird an `OUT` bereitgestellt.

## Funktionsweise
Der FB **AUDI_ADD_2** besitzt keine klassischen Daten-Eingänge oder Ereignisse. Stattdessen kommuniziert er ausschließlich über Adapter. Sobald beide Eingangsadapter (`IN1` und `IN2`) gültige Werte enthalten, wird intern die Summe `IN1 + IN2` berechnet und der resultierende Wert über den Ausgangsadapter `OUT` ausgegeben.

Der Baustein ist generisch: Der tatsächlich verwendete Datentyp wird durch die Konfiguration des Adapters und die generischen Attribute (`GenericClassName`, `TypeHash`) bestimmt. Dies erlaubt den Einsatz mit verschiedenen numerischen Typen (z. B. `INT`, `REAL`, `LREAL`), ohne dass der FB selbst mehrfach instanziiert werden muss.

## Technische Besonderheiten
- **Reine Adapter-Schnittstelle**: Keine Ereignisse oder direkten Datenein-/ausgänge – die gesamte Kommunikation erfolgt über Adapter.
- **Generische Ausführung**: Durch die Attribute `eclipse4diac::core::GenericClassName` und `eclipse4diac::core::TypeHash` kann der FB zur Laufzeit auf unterschiedliche Datentypen spezialisiert werden.
- **Unidirektionale Adapter**: Die verwendeten Adapter vom Typ `AUDI` sind unidirektional, d. h. sie übertragen Werte nur in eine Richtung (Socket → Plug).
- **Keine Zustandsautomatik**: Der FB enthält kein ECC (Execution Control Chart) und arbeitet ereignislos; die Berechnung erfolgt sofort bei Vorliegen der Eingangswerte.

## Zustandsübersicht
Der **AUDI_ADD_2** besitzt keine Zustände (kein ECC). Die Addition wird unverzögert bei gültigen Eingangswerten durchgeführt.

## Anwendungsszenarien
- **Arithmetische Verarbeitung in adapterbasierten Systemen**: Wenn eine Architektur konsequent auf Adapter setzt, bietet dieser FB eine saubere Möglichkeit, zwei Zahlenwerte zu addieren.
- **Generische Berechnungen**: Dank der generischen Auslegung kann der FB in Algorithmen eingesetzt werden, die mit verschiedenen Datentypen arbeiten (z. B. Integer- und Fließkomma-Mischumgebungen).
- **Datenflusssysteme**: In rein datenflussorientierten Applikationen, bei denen keine Ereignisse benötigt werden, fügt sich der FB nahtlos ein.

## Vergleich mit ähnlichen Bausteinen
- **Klassische ADD-FBs (z. B. `ADD` aus IEC 61131-3)**: Diese besitzen meist konkrete Dateneingänge und -ausgänge sowie Ereignissteuerung. Der `AUDI_ADD_2` ersetzt dies durch eine Adapter-Schnittstelle, was eine höhere Abstraktion und Kapselung ermöglicht.
- **Generische Addierer (z. B. `GEN_ADD`)**: Solche Bausteine sind ebenfalls generisch, verwenden aber häufig direkte Datenports. Der `AUDI_ADD_2` ist speziell für adapterbasierte Schnittstellen optimiert.

## Fazit
Der **AUDI_ADD_2** ist ein spezialisierter, generischer Additions-FB für adapterbasierte 4diac-IDE-Umgebungen. Durch den Verzicht auf klassische Ports und die Nutzung des `AUDI`-Adaptertyps eignet er sich besonders für datenflussorientierte und stark modularisierte Steuerungsanwendungen. Seine generische Ausführung erhöht die Wiederverwendbarkeit über verschiedene Datentypen hinweg.