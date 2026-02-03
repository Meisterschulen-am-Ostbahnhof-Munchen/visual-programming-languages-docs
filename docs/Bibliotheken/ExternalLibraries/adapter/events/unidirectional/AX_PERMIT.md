# AX_PERMIT (Unidirectional Adapter Permit)

```{index} single: AX_PERMIT (Unidirectional Adapter Permit)
```

## Einleitung
Der `AX_PERMIT` Funktionsblock ist eine adapterbasierte Variante des `E_PERMIT` Bausteins, implementiert als **Basic Function Block**. Er ermöglicht die bedingte Weitergabe eines Ereignisses, basierend auf dem booleschen Datenwert eines eingehenden `AX`-Adapters.

Der Baustein empfängt ein kombiniertes Ereignis- und Bool-Signal über einen `AX`-Adapter (genannt `PERMIT`). Das eingehende Ereignis wird nur dann an den Ausgang (`EO`) weitergeleitet, wenn der boolesche Datenwert des `PERMIT`-Adapters (`PERMIT.D1`) `TRUE` ist. Der Datenwert `PERMIT.D1` wird dabei **nicht** am Ausgang (`EO`) weitergereicht, sondern nur als Bedingung genutzt.

![AX_PERMIT](AX_PERMIT.svg)

## Schnittstellenstruktur

### **Adapter (Socket)**
- **PERMIT**: Eingangsadapter vom Typ `AX` (Ereignis `E1` + Daten `D1`). Dieser Adapter steuert den Baustein.

### **Ereignis-Ausgänge**
- **EO**: Reiner Ereignis-Ausgang (Typ `Event`). Dieser Event wird ausgelöst, wenn die Bedingung erfüllt ist.

## Funktionsweise
1.  **Ereignisempfang**: Wenn am `PERMIT`-Socket ein Ereignis (`PERMIT.E1`) eintrifft, wird der zugehörige boolesche Datenwert (`PERMIT.D1`) als Bedingung geprüft.
2.  **Bedingte Weiterleitung**: Nur wenn `PERMIT.D1 = TRUE` ist, wird der Ereignis-Ausgang `EO` ausgelöst. Andernfalls wird das Ereignis blockiert.
3.  **Datendurchleitung**: Der boolesche Datenwert (`PERMIT.D1`) wird vom Baustein verwendet, aber **nicht** über den Ereignis-Ausgang `EO` weitergereicht.

## Technische Besonderheiten
✔ **Basic Function Block**: Direkte Implementierung der Logik.
✔ **Adapter-basiert**: Nutzt `AX`-Adapter als Eingang.
✔ **Permissive Logik**: Leitet Ereignisse bedingt weiter.
✔ **Keine Datenweitergabe am Ausgang**: Der Ausgang `EO` ist ein reiner Ereignis-Ausgang und enthält keine Daten (`With Var` ist nicht definiert).

## Anwendungsszenarien
- **Freigabeschaltung**: Ein nachfolgender Baustein soll nur dann getriggert werden, wenn eine Freigabe (`PERMIT.D1 = TRUE`) aktiv ist.
- **Konditionale Ereignissteuerung**: Steuerung des Ereignisflusses basierend auf einem externen booleschen Status, der über einen AX-Adapter kommt.



## 🛠️ Zugehörige Übungen

* [Uebung_009_AX](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_009_AX.md)

