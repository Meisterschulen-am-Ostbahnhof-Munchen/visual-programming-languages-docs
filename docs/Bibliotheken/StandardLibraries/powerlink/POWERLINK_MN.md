# POWERLINK_MN

```{index} single: POWERLINK_MN
```

* * * * * * * * * *

## Einleitung
Der POWERLINK_MN Funktionsblock dient zur Konfiguration des openPOWERLINK Feldbusses. Er fungiert als Managing Node (MN) und initialisiert das Netzwerk.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierung des Dienstes. Startet den Konfigurationsprozess.

### **Ereignis-Ausgänge**
- **INITO**: Bestätigung der Initialisierung. Zeigt an, ob der Start erfolgreich war.

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für den INIT-Eingang (TRUE = Start, FALSE = Stopp).
- **CDC_CFG** (STRING): Gerätekonfiguration (Device Configuration).
- **APP_CFG** (STRING): Anwendungskonfiguration (Application Configuration).
- **DEV_NAME** (STRING): Name des Ethernet-Geräts, das für POWERLINK verwendet werden soll (z.B. "eth0").

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifizierer für den INITO-Ausgang.
- **STATUS** (STRING): Statusinformation des Dienstes.

## Funktionsweise
Der Block initialisiert den openPOWERLINK Stack auf dem angegebenen Ethernet-Interface (`DEV_NAME`). Die Konfigurationsdateien für Gerät (`CDC_CFG`) und Anwendung (`APP_CFG`) werden geladen.

## Anwendungsszenarien
- Zentrale Steuerung eines POWERLINK-Netzwerks.
- Master-Komponente in einem Echtzeit-Ethernet-System.

## Metadaten
| Attribut | Wert |
| :--- | :--- |
| Copyright | (c) 2011 AIT |
| Lizenz | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner) |
| 4diac-Paket | powerlink |