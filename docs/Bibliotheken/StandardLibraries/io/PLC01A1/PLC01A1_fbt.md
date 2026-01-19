# PLC01A1

```{index} single: PLC01A1
```

<img width="1073" height="540" alt="image" src="https://github.com/user-attachments/assets/5a5bf23e-8741-4ccf-8f3d-aac2afba49b1" />

* * * * * * * * * *

## Einleitung

Der PLC01A1 Funktionsblock dient als Schnittstelle für den Zugriff auf die Ein- und Ausgänge des PLC01A1-Moduls. Dieser Baustein ermöglicht die Ansteuerung von 8 digitalen Ausgängen und das Auslesen von 8 digitalen Eingängen über eine standardisierte 4diac-Schnittstelle.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Service-Initialisierungsereignis
  - Verknüpft mit: QI, UpdateInterval, IN1-IN8, OUT1-OUT8

### **Ereignis-Ausgänge**

- **INITO**: Initialisierungsbestätigung
  - Verknüpft mit: QO, STATUS
- **IND**: Indikation vom Ressource
  - Verknüpft mit: QO, STATUS

### **Daten-Eingänge**

- **QI** (BOOL): Ereignis-Eingangsqualifizierer
- **IN1-IN8** (WSTRING): 8 digitale Eingänge
- **OUT1-OUT8** (WSTRING): 8 digitale Ausgänge
- **UpdateInterval** (UINT): Aktualisierungsintervall in Hz (Initialwert: 25)

### **Daten-Ausgänge**

- **QO** (BOOL): Ereignis-Ausgangsqualifizierer
- **STATUS** (WSTRING): Service-Statusinformation

### **Adapter**

Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise

Der PLC01A1 Funktionsblock initialisiert die Hardware-Schnittstelle beim Empfang des INIT-Ereignisses. Nach erfolgreicher Initialisierung wird das INITO-Ereignis ausgegeben. Der Baustein überwacht kontinuierlich die Eingänge IN1-IN8 und aktualisiert die Ausgänge OUT1-OUT8 entsprechend der Konfiguration. Das Aktualisierungsintervall kann über den UpdateInterval-Parameter angepasst werden.

## Technische Besonderheiten

- Verwendet WSTRING-Datentyp für alle Ein-/Ausgänge
- Konfigurierbares Aktualisierungsintervall (Standard: 25 Hz)
- Separate Initialisierungs- und Betriebszustände
- Statusrückmeldung über STATUS-Ausgang

## Zustandsübersicht

1. **Nicht initialisiert**: Wartet auf INIT-Ereignis
2. **Initialisierung**: Verarbeitet INIT mit Konfigurationsdaten
3. **Betrieb**: Überwacht Eingänge und steuert Ausgänge
4. **Fehler**: Gibt Fehlerstatus über STATUS aus

## Anwendungsszenarien

- Anbindung von PLC01A1-Hardware an 4diac-Steuerungen
- Digitale Signalverarbeitung in Automatisierungssystemen
- IO-Management in verteilten Steuerungssystemen
- Prototypenentwicklung mit PLC01A1-Modulen

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu generischen IO-Bausteinen bietet PLC01A1 eine spezifische Anpassung für das PLC01A1-Modul mit vordefinierten 8 Ein- und 8 Ausgängen. Die Verwendung von WSTRING ermöglicht eine flexible Datenrepräsentation, unterscheidet sich jedoch von typischen BOOL-basierten IO-Bausteinen.

## Fazit

Der PLC01A1 Funktionsblock stellt eine zuverlässige und konfigurierbare Schnittstelle für die PLC01A1-Hardware in 4diac-basierten Steuerungssystemen dar. Durch die klare Trennung von Initialisierungs- und Betriebsphase sowie die konfigurierbare Aktualisierungsrate eignet sich der Baustein sowohl für Echtzeit-Anwendungen als auch für allgemeine Automatisierungsaufgaben.