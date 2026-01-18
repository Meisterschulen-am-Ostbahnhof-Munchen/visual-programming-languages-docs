# AUDI_UDI_TO_UDINT

```{index} single: AUDI_UDI_TO_UDINT
```

## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der AUDI_UDI_TO_UDINT Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung des AUDI-Adapterformats in einen UDINT-Wert dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- **CNF**: Bestätigungs-Event nach erfolgter Konvertierung

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- **IN**: UDINT-Ausgangswert der konvertierten Daten

### **Adapter**
- **AUDI_IN**: Socket vom Typ `AUDI`

## Funktionsweise
Der Funktionsblock empfängt Daten über den AUDI-Adapter-Socket und stellt den enthaltenen UDINT-Wert am Ausgang IN zur Verfügung, sobald ein Ereignis über den Adapter eintrifft (CNF).