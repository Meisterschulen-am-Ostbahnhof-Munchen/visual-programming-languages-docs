# E_SH_BYTE

![E_SH_BYTE](https://github.com/user-attachments/assets/7c5430de-6de9-455d-af3e-55f624b415c5)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `E_SH_BYTE` implementiert eine Sample-and-Hold-Funktionalität für den Datentyp `BYTE`. Er dient dazu, einen Eingabewert zu speichern und konstant zu halten, bis ein neuer Wert gesampelt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Auslösendes Ereignis für die normale Ausführung. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigungsereignis nach der Ausführung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (BYTE): Eingangswert, der gesampelt werden soll.

### **Daten-Ausgänge**
- `OUT` (BYTE): Ausgangswert, der den gehaltenen Wert repräsentiert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Bei Eintreffen des `REQ`-Ereignisses wird geprüft, ob sich der Eingabewert `IN` vom aktuellen Ausgabewert `OUT` unterscheidet.
2. Falls eine Änderung vorliegt, wird der Algorithmus `HOLD` ausgeführt, der den Wert von `IN` nach `OUT` kopiert.
3. Das `CNF`-Ereignis wird ausgelöst, um die erfolgreiche Ausführung zu bestätigen.
4. Der FB kehrt in den Ausgangszustand zurück.

## Technische Besonderheiten
- Der FB nutzt eine einfache Zustandsmaschine mit zwei Zuständen (`START` und `HOLD`).
- Die Übergangsbedingung `REQ[IN <> OUT]` stellt sicher, dass nur bei Änderungen des Eingabewerts eine Aktion erfolgt.

## Zustandsübersicht
1. **START**: Initialzustand, wartet auf eine Änderung des Eingabewerts.
2. **HOLD**: Aktiver Zustand, in dem der Wert gehalten und das Bestätigungsereignis ausgelöst wird.

## Anwendungsszenarien
- Signalverarbeitung, bei Werte zwischengespeichert werden müssen.
- Steuerungssysteme, die konstante Ausgabewerte benötigen, bis neue Daten verfügbar sind.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu einfachen Speicherbausteinen bietet `E_SH_BYTE` eine ereignisgesteuerte Abfrage des Eingabewerts.
- Andere Sample-and-Hold-Blöcke können für unterschiedliche Datentypen implementiert sein.

## Fazit
Der `E_SH_BYTE`-Funktionsblock ist ein effizientes Werkzeug für die Zwischenspeicherung von Byte-Werten in ereignisgesteuerten Systemen. Seine einfache und klare Struktur macht ihn besonders geeignet für grundlegende Steuerungsaufgaben.
