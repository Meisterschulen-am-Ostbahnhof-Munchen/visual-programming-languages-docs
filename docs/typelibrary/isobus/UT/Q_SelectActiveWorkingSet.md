# Q_SelectActiveWorkingSet

![Q_SelectActiveWorkingSet](https://user-images.githubusercontent.com/116869307/214148333-97dd868b-07dc-4e3c-9dcf-aa68d76603f2.png)

* * * * * * * * * *

## Einleitung  
Der **Q_SelectActiveWorkingSet** ist ein standardkonformer Funktionsbaustein zur Steuerung aktiver Arbeitsbereiche in Virtual Terminals, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 implementiert die ISO 11783-6 (Teil 6 - F.64) Spezifikation für VT-Systeme ab Version 6.

## Schnittstellenstruktur  

### **Ereignis-Eingänge**  
- `INIT`: Initialisierungsanforderung  
- `REQ`: Arbeitsbereichswechsel-Anforderung  

### **Ereignis-Ausgänge**  
- `INITO`: Initialisierungsbestätigung  
- `CNF`: Wechselbestätigung  

### **Daten-Eingänge**  
- `pau8Name` (USINT[8]): ISO-NAME des neuen aktiven Arbeitsbereichs  

### **Daten-Ausgänge**  
- `STATUS` (STRING): Betriebsstatusmeldung  
- `pau8OldName` (USINT[8]): ISO-NAME des vorherigen Arbeitsbereichs  
- `s16result` (INT): ISO-konformer Ergebniscode  

## Funktionsweise  

1. **Initialisierung**:  
   - `INIT` ohne Parameter  
   - `INITO` bestätigt Betriebsbereitschaft  

2. **Arbeitsbereichswechsel**:  
   - `REQ` mit 8-Byte ISO-NAME des Zielarbeitsbereichs  
   - Führt Kontextwechsel durch  
   - `CNF` liefert Betriebsstatus und vorherigen Arbeitsbereich  

3. **ISO-NAME Format**:  
   - 8-Byte Array nach ISO 11783-5 Spezifikation  

## Technische Besonderheiten  

✔ **ISO 11783-6 konform** (F.64)  
✔ **Exklusiv für VT Version 6+**  
✔ **Vollständiger Kontextwechsel** (Alle zugehörigen Ressourcen)  
✔ **Rückverfolgbarkeit** (Vorheriger Arbeitsbereich)  

## ISO-NAME Struktur  

| Byte | Inhalt                  |  
|------|-------------------------|  
| 0-1  | Herstellerkennung       |  
| 2-3  | Gerätekennung           |  
| 4-5  | Geräteinstanz           |  
| 6-7  | Arbeitsbereichskennung  |  

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

- **Multi-Client-Systeme**: Gerätewechsel  
- **Benutzerprofile**: Individuelle Arbeitsumgebungen  
- **Prozessphasen**: Betriebsmodus-Wechsel  
- **Diagnosemanagement**: Service-/Normalmodus  

## Vergleich mit ähnlichen Bausteinen  

| Feature        | Q_SelectActiveWorkingSet | VtContextSwitch | VtWorkspaceManager |  
|---------------|--------------------------|-----------------|--------------------|  
| ISO-Standard  | ✔                        | ✖               | ✖                  |  
| VT-Version    | 6+                       | Alle            | Alle               |  
| ISO-NAME      | ✔                        | ✖               | ✖                  |  
| Rückmeldung   | ✔                        | ✖               | ✔                  |  

## Fazit  

Der Q_SelectActiveWorkingSet-Baustein bietet zentrale Arbeitsbereichssteuerung:  

- **Sicher**: ISO-konforme Identifikation  
- **Effizient**: Kompletter Kontextwechsel  
- **Transparent**: Vorheriger Zustand rückverfolgbar  

Unverzichtbar für:  
- Komplexe Multi-Client-Systeme  
- Flexible Benutzerumgebungen  
- Prozessorientierte VT-Anwendungen
