# Q_SelectColourMap

![Q_SelectColourMap](https://user-images.githubusercontent.com/116869307/214152861-d7ab7c89-b643-4672-9689-addd4eddc23a.png)

* * * * * * * * * *

## Einleitung  
Der **Q_SelectColourMap** ist ein standardkonformer Funktionsbaustein zur Verwaltung von Farbpaletten in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.60) Spezifikation für VT-Systeme ab Version 4.

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  
- `INIT`: Initialisierungsanforderung  
- `REQ`: Farbpaletten-Wechselanforderung  

### **Ereignis-Ausgänge**  
- `INITO`: Initialisierungsbestätigung  
- `CNF`: Wechselbestätigung  

### **Daten-Eingänge**  
- `u16ObjIdColourMap` (UINT): Farbpaletten-Objekt-ID oder 0xFFFF für Standardpalette  

### **Daten-Ausgänge**  
- `STATUS` (STRING): Betriebsstatusmeldung  
- `u16OldObjIdColourMap` (UINT): Vorherige Farbpaletten-ID  
- `s16result` (INT): ISO-konformer Ergebniscode  

## Funktionsweise  

1. **Initialisierung**:  
   - `INIT` ohne Parameter  
   - `INITO` bestätigt Betriebsbereitschaft  

2. **Palettenwechsel**:  
   - `REQ` mit Ziel-Farbpaletten-ID  
   - Globaler Farbmanagement-Wechsel  
   - `CNF` liefert Betriebsstatus und vorherige Palette  

3. **Spezialwerte**:  
   - `0xFFFF`: Setzt Standard-ISO-Farbtabelle  

## Technische Besonderheiten  

✔ **ISO 11783-6 konform** (F.60)  
✔ **Globale Wirkung**: Beeinflusst alle Arbeitsbereiche  
✔ **Lange Ausführungszeit**: Bei komplexen Paletten  
✔ **Rückverfolgbarkeit**: Vorherige Palette speicherbar  

## Farbpaletten-Referenz  

| Wert       | Bedeutung                     |  
|------------|-------------------------------|  
| 0x0001-FFFE| Benutzerdefinierte Paletten   |  
| 0xFFFF     | ISO-Standardpalette (A.3)     |  

## Rückgabecodes (s16result)  

| Code | Konstante               | Bedeutung                          |  
|------|-------------------------|------------------------------------|  
| 0    | VT_E_NO_ERR             | Erfolgreicher Wechsel             |  
| -6   | VT_E_OVERFLOW           | Pufferüberlauf                   |  
| -8   | VT_E_NOACT              | VT nicht bereit                   |  
| -21  | VT_E_NO_INSTANCE        | Kein VT-Client verfügbar          |  
| -129 | VT_E_ISO_INSTANCE_INVALID | Ungültige VT-Instanz             |  
| -130 | VT_E_NOT_ALIVE          | VT nicht aktiv                    |  

## Anwendungsszenarien  

- **Designwechsel**: Dynamische Farbschemata  
- **Nachtmodus**: Augenschonende Paletten  
- **Markenspezifika**: Corporate Design  
- **Barrierefreiheit**: Hochkontrast-Modi  

## Vergleich mit ähnlichen Bausteinen  

| Feature        | Q_SelectColourMap | VtColorManager | VtPaletteControl |  
|---------------|-------------------|----------------|------------------|  
| ISO-Standard  | ✔                 | ✖              | ✖                |  
| Globalwirkung | ✔                 | ✖              | ✔                |  
| Standardpalette| ✔                | ✖              | ✖                |  
| Rückmeldung   | ✔                 | ✖              | ✔                |  

## Fazit  

Der Q_SelectColourMap-Baustein bietet professionelle Farbverwaltung:  

- **Umfassend**: Globale Farbsteuerung  
- **Flexibel**: Benutzer- und Standardpaletten  
- **Zuverlässig**: ISO-konforme Implementierung  

Unverzichtbar für:  
- Designorientierte Anwendungen  
- Adaptive Visualisierungssysteme  
- Markenspezifische Oberflächen
