# AUDI_ADD_3


![AUDI_ADD_3](./AUDI_ADD_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `AUDI_ADD_3` führt eine arithmetische Addition von drei Eingangswerten durch. Es handelt sich um einen generischen Baustein, der über Adapter-Schnittstellen die Werte aufnimmt und das Ergebnis über einen weiteren Adapter ausgibt. Der FB ist als Teil der 4diac-IDE für IEC 61499-2 konzipiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden. Die Eingangswerte werden über die Adapter-Schnittstellen bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge vorhanden. Das Ergebnis wird über den Adapter-Ausgang bereitgestellt.

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| IN1 | `adapter::types::unidirectional::AUDI` | Socket (Eingang) | ADD input 1 |
| IN2 | `adapter::types::unidirectional::AUDI` | Socket (Eingang) | ADD input 2 |
| IN3 | `adapter::types::unidirectional::AUDI` | Socket (Eingang) | ADD input 3 |
| OUT | `adapter::types::unidirectional::AUDI` | Plug (Ausgang) | ADD result |

## Funktionsweise
Der FB addiert die drei Werte, die über die Adapter `IN1`, `IN2` und `IN3` anliegen. Das Ergebnis wird kontinuierlich über den Adapter `OUT` ausgegeben. Da es sich um einen generischen Baustein handelt, wird der konkrete Datentyp der Addition durch die Attribute `eclipse4diac::core::GenericClassName` und `eclipse4diac::core::TypeHash` zur Laufzeit festgelegt.

## Technische Besonderheiten
- Der FB ist zustandslos (rein kombinatorisch) – kein ECC erforderlich.
- Er nutzt das Eclipse 4diac Generic-Type-System, um eine flexible Wiederverwendbarkeit für verschiedene arithmetische Datentypen (z. B. INT, REAL, LREAL) zu ermöglichen.
- Die Verbindung erfolgt ausschließlich über Adapter des Typs `adapter::types::unidirectional::AUDI`, die eine standardisierte unidirektionale Schnittstelle für arithmetische Operationen bereitstellen.

## Zustandsübersicht
Der FB besitzt keine Zustandsmaschine (keine ECC-Elemente in der XML). Das Verhalten ist rein datengetrieben: Bei jeder Änderung eines Eingangswerts wird das Ausgangsergebnis neu berechnet.

## Anwendungsszenarien
- **Summierung von Messwerten:** Drei analoge Sensorwerte (z. B. Temperaturen) aufsummieren.
- **Mischungsberechnung:** Addieren von drei Mengen oder Volumenströmen in der Verfahrenstechnik.
- **Generische Addition:** Verwendung in Bibliotheken, bei denen der Datentyp erst zur Projektierungszeit festgelegt wird.

## Vergleich mit ähnlichen Bausteinen
- **ADD_2:** Führt eine Addition von zwei Werten durch – `AUDI_ADD_3` erweitert dies auf drei Eingänge.
- **ADD_4:** Addiert vier Werte – `AUDI_ADD_3` spezifiziert drei Eingänge.
- **MUL_3:** Multipliziert drei Werte – im Gegensatz zur Addition.
Alle genannten Bausteine verwenden das gleiche Adapter-Konzept und sind generisch.

## Fazit
Der `AUDI_ADD_3` ist ein flexibler, generischer Funktionsblock für die Addition von drei Werten. Seine reine Adapter-Schnittstelle und die Zustandslosigkeit machen ihn einfach in der Handhabung und ideal für modulare Automatisierungslösungen auf Basis von IEC 61499.