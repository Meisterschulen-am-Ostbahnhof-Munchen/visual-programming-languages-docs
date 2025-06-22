# ARRAY2VALUES_2_LREAL

![ARRAY2VALUES_2_LREAL](https://github.com/user-attachments/assets/e5c38d35-4f15-452d-90d0-e75074d238fe)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ARRAY2VALUES_2_LREAL` dient zur Umwandlung eines LREAL-Arrays mit zwei Elementen in zwei separate LREAL-Ausgabewerte. Dieser Baustein ist besonders nützlich, wenn Array-Daten in einzelne Variablen für die weitere Verarbeitung aufgeteilt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Dienst-Anforderung. Löst die Verarbeitung des Eingabe-Arrays aus.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung der angeforderten Dienstleistung. Wird nach erfolgreicher Verarbeitung ausgelöst.

### **Daten-Eingänge**
- `IN`: LREAL-Array mit genau zwei Elementen. Dies ist der Eingabewert, der in zwei separate Werte aufgeteilt wird.

### **Daten-Ausgänge**
- `OUT_1`: Erster LREAL-Wert aus dem Eingabe-Array.
- `OUT_2`: Zweiter LREAL-Wert aus dem Eingabe-Array.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird das Eingabe-Array `IN` verarbeitet. Die beiden Elemente des Arrays werden auf die Ausgänge `OUT_1` und `OUT_2` verteilt. Nach erfolgreicher Verarbeitung wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock erwartet zwingend ein Array mit genau zwei Elementen. Andere Array-Größen führen zu Fehlern.
- Die Datentypen sind auf LREAL (64-Bit Gleitkommazahl) festgelegt, was eine hohe Genauigkeit gewährleistet.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Verarbeitet das Eingabe-Array und verteilt die Werte auf die Ausgänge.
3. **Confirmation**: Sendet das `CNF`-Ereignis und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Aufteilung von Sensor-Daten, die als Array übertragen werden, in einzelne Messwerte.
- Verarbeitung von Koordinatenpaaren (z.B. X/Y-Werte) in separate Variablen.
- Allgemeine Datenumwandlung in Systemen, die mit Arrays arbeiten müssen, aber einzelne Werte benötigen.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu generischen Array-Verarbeitungsblöcken ist dieser Baustein spezialisiert auf:
- Fest vorgegebene Array-Größe (2 Elemente)
- Spezifischer Datentyp (LREAL)
- Direkte Zuweisung ohne zusätzliche Konfiguration

## Fazit
Der `ARRAY2VALUES_2_LREAL` Funktionsblock bietet eine einfache und effiziente Lösung für die Aufteilung von 2-elementigen LREAL-Arrays in einzelne Werte. Seine spezialisierte Natur macht ihn besonders performant für den vorgesehenen Einsatzzweck, während die feste Array-Größe die Fehlersicherheit erhöht.
