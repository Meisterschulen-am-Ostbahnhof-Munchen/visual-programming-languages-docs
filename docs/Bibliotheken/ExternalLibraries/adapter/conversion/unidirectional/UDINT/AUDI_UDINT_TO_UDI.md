# AUDI_UDINT_TO_UDI

```{index} single: AUDI_UDINT_TO_UDI
```

## Einleitung
Der AUDI_UDINT_TO_UDI Funktionsblock ist ein Composite-Funktionsblock, der zur Konvertierung eines UDINT-Werts in das AUDI-Adapterformat dient.

![AUDI_UDINT_TO_UDI](AUDI_UDINT_TO_UDI.svg)

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



## 🛠️ Zugehörige Übungen

* [Uebung_083_AX](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_083_AX.md)

