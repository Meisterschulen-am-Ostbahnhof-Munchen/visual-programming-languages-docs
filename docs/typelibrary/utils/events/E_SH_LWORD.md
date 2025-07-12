# E_SH_LWORD

![E_SH_LWORD](https://github.com/user-attachments/assets/a362d0c5-2a5f-46e5-91fc-9223343701bd)

* * * * * * * * * *
## Einleitung
Der Funktionsblock E_SH_LWORD implementiert eine Sample-and-Hold-Funktionalität für den Datentyp LWORD (64-Bit unsigned integer). Er speichert den aktuellen Eingangswert bei Anforderung und gibt diesen bis zur nächsten Änderung am Ausgang aus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung (triggert die Übernahme des Eingangswerts)

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung (wird nach erfolgreicher Wertübernahme ausgegeben)

### **Daten-Eingänge**
- **IN** (LWORD): Eingangswert der übernommen werden soll

### **Daten-Ausgänge**
- **OUT** (LWORD): Gespeicherter Ausgangswert

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Bei Empfang eines REQ-Ereignisses wird geprüft, ob sich der Eingangswert (IN) vom aktuellen Ausgangswert (OUT) unterscheidet
2. Bei Änderung wird der Algorithmus HOLD ausgeführt, der den neuen Wert übernimmt
3. Nach erfolgreicher Übernahme wird das CNF-Ereignis ausgelöst
4. Der Block kehrt in den Startzustand zurück

## Technische Besonderheiten
- Verarbeitet 64-Bit unsigned integer Werte (LWORD)
- Implementiert als Basic Function Block mit zwei Zuständen (START und HOLD)
- Wertübernahme nur bei tatsächlicher Änderung des Eingangswerts

## Zustandsübersicht
1. **START**: Initialzustand, wartet auf Anforderung
2. **HOLD**: Aktiver Zustand während der Wertübernahme

## Anwendungsszenarien
- Signalverarbeitung bei langsamen Änderungsraten
- Pufferung von Sensorwerten
- Vermeidung von häufigen Aktualisierungen bei konstanten Werten

## Vergleich mit ähnlichen Bausteinen
- Spezialisiert auf LWORD-Datentyp (64-Bit)
- Einfacher als allgemeine Sample-and-Hold Blöcke mit mehr Parametern
- Keine zusätzlichen Features wie Zeitverzögerungen oder Filter

## Fazit
Der E_SH_LWORD bietet eine einfache und effiziente Lösung für die Sample-and-Hold-Funktionalität bei 64-Bit Werten. Seine schlanke Implementierung macht ihn besonders geeignet für ressourcenbeschränkte Systeme, wo grundlegende Haltefunktionalität benötigt wird.
