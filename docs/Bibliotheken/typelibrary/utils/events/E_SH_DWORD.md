# E_SH_DWORD

![E_SH_DWORD](https://github.com/user-attachments/assets/4a619be9-7e33-4f44-8681-9377f504e8e7)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `E_SH_DWORD` implementiert eine Sample-and-Hold-Funktionalität für DWORD-Werte. Er speichert den aktuellen Eingangswert bei einer Anforderung und gibt ihn am Ausgang aus, bis ein neuer Wert gespeichert wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Normaler Ausführungsanforderung. Löst die Speicherung des aktuellen Eingangswerts aus, wenn dieser sich vom gespeicherten Wert unterscheidet.

### **Ereignis-Ausgänge**
- `CNF`: Ausführungsbestätigung. Wird nach erfolgreicher Speicherung des Eingangswerts ausgelöst.

### **Daten-Eingänge**
- `IN` (DWORD): Der zu speichernde Eingangswert.

### **Daten-Ausgänge**
- `OUT` (DWORD): Der gespeicherte Ausgangswert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock wechselt bei einer `REQ`-Anforderung in den Zustand `HOLD`, wenn sich der Eingangswert `IN` vom aktuellen Ausgangswert `OUT` unterscheidet. Im Zustand `HOLD` wird der Algorithmus `HOLD` ausgeführt, der den Eingangswert `IN` in den Ausgang `OUT` kopiert und anschließend eine `CNF`-Bestätigung ausgibt. Danach kehrt der Funktionsblock in den Zustand `START` zurück.

## Technische Besonderheiten
- Der Funktionsblock ist ein BasicFB mit einer einfachen Zustandsmaschine (ECC).
- Die Speicherung erfolgt nur bei Änderung des Eingangswerts.

## Zustandsübersicht
- `START`: Initialzustand, wartet auf eine `REQ`-Anforderung.
- `HOLD`: Zustand, in dem der Eingangswert gespeichert und eine Bestätigung ausgegeben wird.

## Anwendungsszenarien
- Speicherung von Sensorwerten für spätere Verarbeitung.
- Vermeidung von überflüssigen Aktualisierungen bei unveränderten Werten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Speicherbausteinen bietet `E_SH_DWORD` eine bedingte Speicherung nur bei Wertänderung.
- Ähnlich zu anderen Sample-and-Hold-Bausteinen, aber spezialisiert auf DWORD-Werte.

## Fazit
Der `E_SH_DWORD`-Funktionsblock ist ein effizientes Werkzeug zur bedingten Speicherung von DWORD-Werten, das überflüssige Aktualisierungen vermeidet und damit Ressourcen schont.
