# ARRAY2ARRAY_2_LREAL

![ARRAY2ARRAY_2_LREAL](https://github.com/user-attachments/assets/4be383a3-0590-4e45-84a1-177a1bc5393b)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ARRAY2ARRAY_2_LREAL` dient zur Übertragung von Daten zwischen zwei Arrays des Typs `LREAL` mit jeweils zwei Elementen. Es handelt sich um einen Service Interface Function Block, der eine einfache Schnittstelle für die Datenübertragung bereitstellt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service Request. Wird verwendet, um die Übertragung der Daten zu initiieren. Verknüpft mit dem Daten-Eingang `IN`.

### **Ereignis-Ausgänge**
- **CNF**: Confirmation of Requested Service. Bestätigt die erfolgreiche Übertragung der Daten. Verknüpft mit dem Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- **IN**: Array-Eingang vom Typ `LREAL` mit zwei Elementen. Enthält die zu übertragenden Daten.

### **Daten-Ausgänge**
- **OUT**: Array-Ausgang vom Typ `LREAL` mit zwei Elementen. Enthält die übertragenen Daten.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock überträgt die Daten vom Eingangsarray `IN` zum Ausgangsarray `OUT`, wenn das Ereignis `REQ` ausgelöst wird. Nach erfolgreicher Übertragung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist als Service Interface Function Block implementiert und kann sowohl in der Anwendung als auch in der Ressourcenebene verwendet werden.
- Die Arrays sind auf zwei Elemente beschränkt (`ArraySize="2"`).

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Überträgt Daten von `IN` nach `OUT`.
3. **Confirmation**: Löst das `CNF`-Ereignis aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Übertragung von Messwerten zwischen verschiedenen Systemkomponenten.
- Datenweiterleitung in Steuerungssystemen, wo Arrays mit zwei `LREAL`-Werten verarbeitet werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Array-Übertragungsblöcken ist dieser Funktionsblock spezialisiert auf Arrays mit genau zwei `LREAL`-Elementen.
- Einfacher und spezifischer als allgemeine Array-Manipulationsblöcke.

## Fazit
Der `ARRAY2ARRAY_2_LREAL`-Funktionsblock bietet eine einfache und effiziente Lösung für die Übertragung von Daten zwischen zwei `LREAL`-Arrays fester Größe. Seine spezifische Auslegung macht ihn ideal für Anwendungen, die genau diese Funktionalität benötigen.
