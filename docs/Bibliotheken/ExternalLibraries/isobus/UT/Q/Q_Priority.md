# Q_Priority

![Q_Priority](https://user-images.githubusercontent.com/116869307/214148302-f10f051a-fad7-42af-a3e0-9f5e0eedbaf3.png)

* * * * * * * * * *  

## Einleitung  
Der **Q_Priority** ist ein standardkonformer Funktionsbaustein zur Prioritätssteuerung von Alarmmasken in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.40) Spezifikation für VT-Alarmmanagement.  

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  
- `INIT`: Initialisierungsanforderung (mit Alarmmasken-ID)  
- `REQ`: Prioritätsänderungs-Anforderung  

### **Ereignis-Ausgänge**  
- `INITO`: Initialisierungsbestätigung  
- `CNF`: Änderungsbestätigung  

### **Daten-Eingänge**  
- `u16ObjId` (UINT): Alarmmasken-Objekt-ID (16-bit)  
- `u8Priority` (USINT): Neue Priorität (0-255)  

### **Daten-Ausgänge**  
- `STATUS` (STRING): Betriebsstatusmeldung  
- `u8OldPriority` (USINT): Vorherige Priorität  
- `s16result` (INT): ISO-konformer Ergebniscode  

## Funktionsweise  

1. **Initialisierung**:  
   - `INIT` mit Alarmmasken-ID  
   - `INITO` bestätigt Betriebsbereitschaft  

2. **Prioritätsänderung**:  
   - `REQ` mit neuem Prioritätswert  
   - Aktualisiert die Alarmdarstellungsreihenfolge  
   - `CNF` liefert Ergebnisstatus und vorherigen Wert  

3. **Prioritätslogik**:  
   - Niedrigere Zahlen = Höhere Priorität  
   - Beeinflusst Alarm-Anzeigereihenfolge  

## Technische Besonderheiten  

✔ **ISO 11783-6 konform** (F.40)  
✔ **Echtzeit-Priorisierung** (Sofortige Wirkung)  
✔ **Rückverfolgbarkeit** (Vorherige Priorität)  
✔ **Breiter Wertebereich** (0-255)  

## Prioritätsreferenz  

| Priorität | Typische Verwendung         |  
|-----------|-----------------------------|  
| 0-31      | Kritische Systemalarme      |  
| 32-63     | Wichtige Prozessalarme      |  
| 64-127    | Standardwarnungen           |  
| 128-255   | Informationsmeldungen       |  

## Rückgabecodes (s16result)  

| Code | Konstante               | Bedeutung                          |  
|------|-------------------------|------------------------------------|  
| 0    | VT_E_NO_ERR             | Erfolgreiche Änderung             |  
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |  
| -8   | VT_E_NOACT              | VT nicht bereit                   |  
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |  
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |  
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |  

## Anwendungsszenarien  

- **Alarmmanagement**: Dynamische Prioritätsanpassung  
- **Prozesssteuerung**: Wichtigkeitseinstufung  
- **Diagnosesysteme**: Eskalationsmanagement  
- **Wartungsmodi**: Temporäre Prioritätsänderungen  

## Vergleich mit ähnlichen Bausteinen  

| Feature        | Q_Priority | VtAlarmPriority | VtEventManager |  
|---------------|------------|-----------------|----------------|  
| ISO-Standard  | ✔          | ✖               | ✖              |  
| Echtzeitwirkung | ✔      | ✔               | ✖              |  
| Wertebereich  | 0-255      | 0-127           | 0-31           |  
| Rückmeldung   | ✔          | ✖               | ✔              |  

## Fazit  

Der Q_Priority-Baustein bietet essentielle Alarmsteuerung:  

- **Dynamisch**: Sofortige Prioritätsanpassung  
- **Transparent**: Rückmeldung des vorherigen Zustands  
- **Robust**: Volle ISO-Konformität  

Unverzichtbar für:  
- Professionelle Alarmmanagementsysteme  
- Prozesskritische Anwendungen  
- Flexible Diagnoselösungen
