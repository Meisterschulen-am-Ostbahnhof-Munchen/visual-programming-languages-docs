# AUDI_UDINT_TO_UDI

```{index} single: AUDI_UDINT_TO_UDI
```

## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der AUDI_UDINT_TO_UDI Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines UDINT-Werts in das AUDI-Adapterformat dient.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Event zur Auslösung der Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- **OUT**: UDINT-Eingangswert, der konvertiert werden soll

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**
- **AUDI_OUT**: Plug vom Typ `AUDI`

## Funktionsweise
Der Funktionsblock empfängt einen UDINT-Wert am Daten-Eingang OUT und wandelt diesen bei Eintreffen des REQ-Ereignisses in das AUDI-Adapterformat um.